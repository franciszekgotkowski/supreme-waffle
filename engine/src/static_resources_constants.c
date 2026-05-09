#include <engine/resource_indexers.h>
#include <engine/static_resources.h>
#include <common/typedefs.h>
#include <stdbool.h>

#include <assert.h>

const u32 DEFAULT_AMOUNT_OF_BUFFER_INDEXES = 1000;

// Default amounts of elements each indexer can handle.
// Unfortunately i can set values for all static resources.
// This may seem as a problem but really is not for 2 reasons:
// 		- default value is 0 and i can assert for that and know if an index is wrong
//		- it is only for InitializeStaticResourceIndexer function
const u32 DefaultAmountsOfIndexes[] = {
	[FONT_INDEXER] = 100,
	[RENDER_PROGRAM_INDEXER] = 1000,
	[DATA_BUFFER_INDEXER] = DEFAULT_AMOUNT_OF_BUFFER_INDEXES,
};
_Static_assert(
	sizeof(DefaultAmountsOfIndexes)/sizeof(u32) == AMOUNT_OF_STATIC_RESOURCES,
	""
);

const bool IsStaticResourceAnIndexer[] = {
	[TEXT_RENDERING_OBJECT] = false,
	[FONT_INDEXER] = true,
	[DATA_BUFFER_INDEXER] = true,
	[RENDER_PROGRAM_INDEXER] = true,
};
_Static_assert(
	sizeof(IsStaticResourceAnIndexer)/sizeof(bool) == AMOUNT_OF_STATIC_RESOURCES,
	""
);

const u32 SizesForEachStaticResource[] = {
	[TEXT_RENDERING_OBJECT] = TOTAL_SIZE_FOR_TEXT_RENDERING,
	[FONT_INDEXER] = GetWholeIndexerSize(DefaultAmountsOfIndexes[FONT_INDEXER]),
	[DATA_BUFFER_INDEXER] = GetWholeIndexerSize(DefaultAmountsOfIndexes[DATA_BUFFER_INDEXER]),
	[RENDER_PROGRAM_INDEXER] = GetWholeIndexerSize(DefaultAmountsOfIndexes[RENDER_PROGRAM_INDEXER]),
};
_Static_assert(
	sizeof(SizesForEachStaticResource)/sizeof(u32) == AMOUNT_OF_STATIC_RESOURCES,
	""
);
