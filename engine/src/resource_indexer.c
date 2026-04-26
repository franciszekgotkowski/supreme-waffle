#include <common/errors.h>
#include <engine/memory_arena.h>
#include <assert.h>
#include <common/typedefs.h>
#include <engine/resource_indexers.h>
#include <strings.h>

void InitializeResourceIndexer(
	void* ptr,
	u32 maxAmountOfResources,
	MemoryArena* arena
) {
	assert(ptr);
	assert(maxAmountOfResources < MAX_AMOUNT_OF_RESOURCES_IN_INDEXER);
	assert(arena);

	ResourceIndexer* riPtr = ptr;
	*riPtr = (ResourceIndexer){
		.maxAmountOfResources = maxAmountOfResources,
		.currentAmountOfResources = 0,
		.indexes = ptr + sizeof(ResourceIndexer),
		.arena = arena
	};
}

ResourceID RegisterNewResource_ResourceIndexer(
	ResourceIndexer* indexer,
	u64 size,
	Error* err
) {
	assert(indexer);
	assert(err);

	if (indexer->arena->locked) {
		*err = LOCKED;
		return 0;
	}

	if (indexer->currentAmountOfResources >= indexer->maxAmountOfResources) {
		*err = OUT_OF_INDEXES;
		return 0;
	}

	Error error;
	void* ptr = registerMemory_MemoryArena(
		indexer->arena,
		size,
		&error
	);

	if (error != OK) {
		assert(error == OUT_OF_MEMORY || error == LOCKED);
		*err = error;
		return 0;
	}

	indexer->indexes[indexer->currentAmountOfResources] = ptr;
	indexer->currentAmountOfResources++;

	return OK;
}

void* GetResource_ResourceIndexer(
	ResourceIndexer* indexer,
	ResourceID id
) {
	assert(indexer);
	assert(id < indexer->currentAmountOfResources);

	return indexer->indexes[id];
}