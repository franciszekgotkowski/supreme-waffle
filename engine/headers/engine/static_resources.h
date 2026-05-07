#pragma once

#include <common/memory_arena.h>
#include <engine/memory_pool.h>
#include <engine/resource_indexers.h>
#include <engine/text_rendering.h>
#include <stdbool.h>

// DefaultAmountsOfIndexes and SizesForEachStaticResource are in static_resources_constants.c file
typedef enum {
	TEXT_RENDERING_OBJECT,			// this is text rendering object, it stores text data alongside with its verticies
	FONT_INDEXER,					// font data
	SHADER_PROGRAM_INDEXER,			// stores shader id's
	BUFFER_DATA_INDEXER,			// this is buffer data for models loaded in
	BUFFER_SHADER_BINDING_INDEXER,	// each buffer is make to be displayes in
	TEXTURE_ID_INDEXER,				// stores texture id's loaded to renderer (probably opengl)
	TEXTURE_BITMAP_INDEXER,			// stores texture bitmaps

	AMOUNT_OF_STATIC_RESOURCES
} StaticResources;


// Indexer made specifically to contain Indexers that will be dynamically allocated on the scene stack if needed. It lives in SceneData struct
typedef struct {
	bool exist[AMOUNT_OF_STATIC_RESOURCES];
	void* ptr[AMOUNT_OF_STATIC_RESOURCES];
} StaticResourcesIndexer;

// Initializes static indexer
void InitializeStaticResource(
	void* ptr, //where to initialize
	StaticResources staticResources,
	MemoryArena* arena
);

// Returns pointer to requested StaticResource.
// Errors it can return:
// 	- OK
// 	- DOES_NOT_EXIST		in this case funcion will also return NULL
void* GetStaticResource_StaticResourceIndexer(
	StaticResourcesIndexer* staticSceneResources,
	StaticResources resource,
	Error* err
);