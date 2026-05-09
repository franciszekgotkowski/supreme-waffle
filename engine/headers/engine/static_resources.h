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

	DATA_BUFFER_INDEXER,			// general purpose container for vertex data, textures, data for game logic etc.
	RENDER_PROGRAM_INDEXER,			// stores render program data. Render program might be a glsl shader or something else - it might be as well a software rendering function. When program uses opengl RENDER_PROGRAM would be just id to opengl shader program
	// GAME_OBJECT_INDEXER,
	// RENDER_OBJECT_INDEXER,

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