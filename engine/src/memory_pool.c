#include <assert.h>

#include <engine/platform/memory_allocations.h>

#include <engine/memory_pool.h>
#include <engine/errors.h>
#include <engine/platform/input_data.h>
#include <engine/platform/window_data.h>
#include <engine/typedefs.h>
#include <stdio.h>

PointerTable* InitializePool(u64 size) {

	u64 poolSize = sizeof(PointerTable) + sizeof(WindowData) + sizeof(InputData);
	void* pool = NULL;

	if (size == 0) {
		printf("PointerTable size: %llu\nWindowData size: %llu\nInputData size: %llu\ntotal size: %llu\n\n", (llu)(sizeof(PointerTable)), (llu)sizeof(WindowData), (llu)sizeof(InputData), (llu)poolSize);
		pool = mem_alloc(poolSize);
		assert(pool);
	} else {
		assert(poolSize <= size);
		if (!(poolSize <= size)) {
			printf("To little space for game to start!\n");
			return NULL;
		}

		printf("Allocating %llu of bytes of which %llu will be free for use\n", (llu)size, (llu)(size - poolSize));
		pool = mem_alloc(size);
		assert(pool);
	}


	void* temp = pool;
	Error err;

	PointerTable* table = (PointerTable*)pool;
	table->size = poolSize;
	table->emountOfRegions = 0;

	err = InitializeRegion(table, temp, POINTER_TABLE, sizeof(PointerTable));
	assert(err == OK);
	temp += sizeof(PointerTable);

	err = InitializeRegion(table, temp, WINDOW_DATA, sizeof(WindowData));
	assert(err == OK);
	temp += sizeof(WindowData);

	err = InitializeRegion(table, temp, INPUT_DATA, sizeof(InputData));
	assert(err == OK);
	temp += sizeof(InputData);

	// first i need to check how much space do i need
	err = InitializeRegion(table, temp, CANVAS, sizeof(InputData));
	assert(err == OK);
	temp += sizeof(InputData);

	table->poolTop = temp;

	return pool;
}

Error InitializeRegion(PointerTable* table, void* ptr, u64 regionIndex, u64 size) {
	assert(table);
	assert(ptr);

	assert(!(regionIndex >= AMOUNT_OF_ENGINE_MEMORY_REGIONS));
	if (regionIndex >= AMOUNT_OF_ENGINE_MEMORY_REGIONS) {
		return OUT_OF_RANGE;
	}

	table->emountOfRegions += 1;
	table->regions[regionIndex] = (Region){
		.ptr = ptr,
		.len = size
	};

	return OK;
}