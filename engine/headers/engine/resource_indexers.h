#pragma once

#include <engine/memory_arena.h>
#include <common/typedefs.h>
#include <common/errors.h>
#define MAX_AMOUNT_OF_RESOURCES_IN_INDEXER 100000

typedef u32 ResourceID;

// ResourceIndexer is meant to be used strictly in combination with memory arena allocator inside sceneData
// maxAmountOfResources is amount of indexes that this indexer can manage. It has to be lower than MAX_AMOUNT_OF_RESOURCES_IN_INDEXER
// Variabel 'indexes' points to memory address after corresponding ResourceIndexer struct - it is basically pointer to make size of array not hard coded
typedef struct {
	u32 maxAmountOfResources;
	u32 currentAmountOfResources;
	void** indexes;
	MemoryArena* arena;
} ResourceIndexer;

#define GetWholeIndexerSize(AmountOfIndexes) \
	(sizeof(ResourceIndexer) + AmountOfIndexes*sizeof(void*))

// Intializes ResourceIndexer on prt address
void InitializeResourceIndexer(
	void* ptr,
	u32 maxAmountOfResources,
	MemoryArena* arena
);

// Will register a new resource if it has capacity and return its ID
// Can return in error:
//	- OK
//	- OUT_OF_RANGE			if there is no more indexes to fill in
//	- OUT_OF_INDEXES			if there is no more memory to accomodate new resource
//	- LOCKED				if memory arena is locked
ResourceID RegisterNewResource_ResourceIndexer(
	ResourceIndexer* indexer,
	u64 size,
	Error* err
);

// Gets resource under ID
void* GetResource_ResourceIndexer(
	ResourceIndexer* indexer,
	ResourceID id
);