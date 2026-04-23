#pragma once

#include <engine/memory_pool.h>
#include <engine/resource_indexers.h>
#include <engine/text_rendering.h>
#include <stdbool.h>

typedef enum {
	TEXT_RENDERING_OBJECT,
	FONT_INDEXER,
	OBJECT_3D_INDEXER,

	AMOUNT_OF_STATIC_SCENE_RESOURCES
} StaticResources;

// Indexer made specifically to contain Indexers that will be dynamically allocated on the scene stack if needed. It lives in SceneData struct
typedef struct {
	bool exist[AMOUNT_OF_STATIC_SCENE_RESOURCES];
	void* ptr[AMOUNT_OF_STATIC_SCENE_RESOURCES];
} StaticResourcesIndexer;

// Initializes the static resource onto
Error InitializeStaticResource(
	StaticResourcesIndexer* staticSceneResources,
	StaticResources resource
);

void* GetStaticResource(
	StaticResourcesIndexer* staticSceneResources,
	StaticResources resource
);