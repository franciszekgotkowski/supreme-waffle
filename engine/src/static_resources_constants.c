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
	[SHADER_PROGRAM_INDEXER] = 1000,
	[TEXTURE_ID_INDEXER] = 200,
	[BUFFER_DATA_INDEXER] = DEFAULT_AMOUNT_OF_BUFFER_INDEXES,
	[BUFFER_SHADER_BINDING_INDEXER] = DEFAULT_AMOUNT_OF_BUFFER_INDEXES,
	[TEXTURE_BITMAP_INDEXER] = 300,
};
_Static_assert(
	sizeof(DefaultAmountsOfIndexes)/sizeof(u32) == AMOUNT_OF_STATIC_RESOURCES
);

const bool IsStaticResourceAnIndexer[] = {
	[TEXT_RENDERING_OBJECT] = false,
	[FONT_INDEXER] = true,
	[BUFFER_DATA_INDEXER] = true,
	[SHADER_PROGRAM_INDEXER] = true,
	[TEXTURE_ID_INDEXER] = true,
	[BUFFER_SHADER_BINDING_INDEXER] = true,
	[TEXTURE_BITMAP_INDEXER] = true,
};
_Static_assert(
	sizeof(IsStaticResourceAnIndexer)/sizeof(bool) == AMOUNT_OF_STATIC_RESOURCES
);

const u32 SizesForEachStaticResource[] = {
	[TEXT_RENDERING_OBJECT] = TOTAL_SIZE_FOR_TEXT_RENDERING,
	[FONT_INDEXER] = GetWholeIndexerSize(DefaultAmountsOfIndexes[FONT_INDEXER]),
	[BUFFER_DATA_INDEXER] = GetWholeIndexerSize(DefaultAmountsOfIndexes[BUFFER_DATA_INDEXER]),
	[SHADER_PROGRAM_INDEXER] = GetWholeIndexerSize(DefaultAmountsOfIndexes[SHADER_PROGRAM_INDEXER]),
	[TEXTURE_ID_INDEXER] = GetWholeIndexerSize(DefaultAmountsOfIndexes[TEXTURE_ID_INDEXER]),
	[BUFFER_SHADER_BINDING_INDEXER] = GetWholeIndexerSize(DefaultAmountsOfIndexes[BUFFER_SHADER_BINDING_INDEXER]),
	[TEXTURE_BITMAP_INDEXER] = GetWholeIndexerSize(DefaultAmountsOfIndexes[TEXTURE_BITMAP_INDEXER]),
};
_Static_assert(
	sizeof(SizesForEachStaticResource)/sizeof(u32) == AMOUNT_OF_STATIC_RESOURCES
);
