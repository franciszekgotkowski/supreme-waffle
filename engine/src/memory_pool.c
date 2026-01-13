#include <assert.h>

#include <engine/platform/memory_allocations.h>

#include <engine/memory_pool.h>
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

	PointerTable* table = (PointerTable*)pool;
	table->size = poolSize;
	table->emountOfRegions = AMOUNT_OF_ENGINE_MEMORY_REGIONS;
	table->regions[POINTER_TABLE] = (Region){
		.ptr = temp,
		.len = sizeof(PointerTable),
	};
	temp += sizeof(PointerTable);

	table->regions[WINDOW_DATA] = (Region){
		.ptr = temp,
		.len = sizeof(WindowData)
	};
	temp += sizeof(WindowData);

	table->regions[INPUT_DATA] = (Region){
		.ptr = temp,
		.len = sizeof(InputData)
	};
	temp += sizeof(InputData);

	table->poolTop = temp;

	return pool;
}


