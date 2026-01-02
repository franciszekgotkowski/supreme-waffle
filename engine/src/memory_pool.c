#include <assert.h>

#include <engine/memory_allocations.h>

#include <engine/memory_pool.h>
#include <../headers/engine/input_data.h>
#include <engine/window_data.h>
#include <stdio.h>

PointerTable* InitializePool() {

	u64 poolSize = sizeof(PointerTable) + sizeof(WindowData) + sizeof(InputData);
	printf("PointerTable size: %lu\nWindowData size: %lu\nInputData size: %lu\ntotal size: %lu\n\n",sizeof(PointerTable), sizeof(WindowData), sizeof(InputData), poolSize);

	void* pool = mem_alloc(poolSize);
	assert(pool);

	void* temp = pool;

	PointerTable* table = (PointerTable*)temp;
	table->emountOfRegions = ENUM_COUNT;
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

	return pool;
}
