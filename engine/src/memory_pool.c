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

	assert(poolSize <= size);
	if (!(poolSize <= size)) {
		printf("To little space for game to start!\n");
		return NULL;
	}
	printf("Allocating %llu of bytes of which %llu will be free for use\n", (llu)size, (llu)(size - poolSize));
	pool = mem_alloc(size);
	assert(pool);

	void* temp = pool;
	Error err;

	PointerTable* table = (PointerTable*)pool;
	table->capacity = size;
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

	err = InitializeRegion(table, temp, MEMORY_ARENA, (table->capacity - poolSize));
	assert(err == OK);
	temp += sizeof(InputData);
	printf("table->capacity - poolSize = %llu\n", (llu)(table->capacity - poolSize));
	printf("there is %llu bytes of free space for the arena\n", (llu)table->regions[MEMORY_ARENA].len);

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