#pragma once

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
} ResourceIndexer;

#define GetWholeIndexerSize(AmountOfIndexes) \
	(sizeof(ResourceIndexer) + AmountOfIndexes*sizeof(void*))

// Intializes ResourceIndexer on prt address
void InitializeResourceIndexer(
	void* ptr,
	u32 maxAmountOfResources
);

// Will register a new resource if it has capacity and return its ID
// Can return in error:
//	- OK
//	- OUT_OF_RANGE
//	- OUT_OF_MEMORY
ResourceID RegisterNewResource_ResourceIndexer(
	ResourceIndexer* indexer,
	Error* err
);

// Gets resource under ID
void* GetResource_ResourceIndexer(
	ResourceIndexer* indexer,
	ResourceID id
);