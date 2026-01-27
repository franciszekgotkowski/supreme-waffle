#include <assert.h>

#include <engine/platform/memory_allocations.h>

#include <engine/memory_pool.h>
#include <engine/scene.h>
#include <engine/errors.h>
#include <engine/platform/input_data.h>
#include <engine/platform/window_data.h>
#include <engine/typedefs.h>

PointerTable* InitializePool() {

	u64 poolSize = (
		sizeof(PointerTable) +
		sizeof(WindowData) +
		sizeof(InputData) +
		SIZEOF_LARGEST_SCENE +
		SIZEOF_LOADING_SCREEN_SCENE
	);

	void* pool = mem_alloc(poolSize);

	assert(pool);

	void* stackTop = pool;
	Error err;

	PointerTable* table = (PointerTable*)pool;
	table->capacity = poolSize;
	table->emountOfRegions = 0;

	err = InitializeRegion(table, stackTop, POINTER_TABLE, sizeof(PointerTable));
	assert(err == OK);
	stackTop += sizeof(PointerTable);

	err = InitializeRegion(table, stackTop, WINDOW_DATA, sizeof(WindowData));
	assert(err == OK);
	stackTop += sizeof(WindowData);

	err = InitializeRegion(table, stackTop, INPUT_DATA, sizeof(InputData));
	assert(err == OK);
	stackTop += sizeof(InputData);

	err = InitializeRegion(table, stackTop, GAME_SCENE, SIZEOF_LARGEST_SCENE);
	assert(err == OK);
	stackTop += SIZEOF_LARGEST_SCENE;

	err = InitializeRegion(table, stackTop, LOADING_SCREEN_SCENE, SIZEOF_LOADING_SCREEN_SCENE);
	assert(err == OK);
	stackTop += SIZEOF_LOADING_SCREEN_SCENE;

	assert((u64)stackTop - (u64)pool == (u64)poolSize);

	table->poolTop = stackTop;

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
		.capacity = size
	};

	return OK;
}