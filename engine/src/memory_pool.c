#include <assert.h>
#include <stdio.h>

#include <platform/memory_allocations.h>
#include <../headers/engine/handle_input.h>
#include <platform/window.h>

#include <engine/memory_pool.h>
#include <engine/scene.h>

#include <common/errors.h>
#include <common/range.h>
#include <common/typedefs.h>

extern PointerTable* GameMemory;

static inline u64 totalMemoryFootprint() {
	u64 sum = 0;
	for range(i, AMOUNT_OF_ENGINE_MEMORY_REGIONS) {
		sum += RegionCapacity[i];
	}
	return sum;
};

PointerTable* InitializePool() {

	u64 poolSize = totalMemoryFootprint();
	printf("Total pool size: %lluMB %lluKB (%llu)\n", (llu)(poolSize/MB), (llu)((poolSize%MB)/KB), (llu)(poolSize));

	void* pool = mem_alloc(poolSize);

	assert(pool);

	void* stackTop = pool;

	PointerTable* table = (PointerTable*)pool;
	table->capacity = poolSize;
	table->amountOfRegions = 0;

	for range(i, AMOUNT_OF_ENGINE_MEMORY_REGIONS) {
		InitializeRegion(table, stackTop, i, RegionCapacity[i]);
		stackTop += RegionCapacity[i];
	}
	assert((u64)stackTop - (u64)pool == (u64)poolSize);

	table->poolTop = stackTop;

	return pool;
}

void InitializeRegion(
	PointerTable* table,
	void* ptr,
	u64 regionIndex,
	u64 size
) {
	assert(table);
	assert(ptr);
	assert(regionIndex < AMOUNT_OF_ENGINE_MEMORY_REGIONS);

	table->amountOfRegions += 1;
	table->regions[regionIndex] = (Region){
		.ptr = ptr,
		.capacity = size
	};

}

inline void* getRegion(
	Regions region
) {
	PointerTable* table = GameMemory;
	assert(table);
	assert(region >= 0 && region < AMOUNT_OF_ENGINE_MEMORY_REGIONS);
	void* ptr = table->regions[region].ptr;
	assert(ptr);
	return ptr;
}

inline u64 getRegionCapacity(
	PointerTable* table,
	Regions region
) {
	assert(table);
	assert(region >= 0 && region < AMOUNT_OF_ENGINE_MEMORY_REGIONS);
	u64 capacity = table->regions[region].capacity;
	return capacity;
}