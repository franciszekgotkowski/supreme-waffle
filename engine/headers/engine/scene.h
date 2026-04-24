#pragma once

#include <engine/memory_arena.h>
#include <engine/static_resources.h>
#include <common/errors.h>
#include <common/typedefs.h>
#include <stdbool.h>

#include <platform/memory_allocations.h>

// MEMORY REGION DEFINES
#define SCENE_FILES_LOCATION "../../assets/scene/"
#define SIZEOF_XS_SCENE (5*MB)
#define SIZEOF_S_SCENE (25*MB)
#define SIZEOF_M_SCENE (75*MB)
#define SIZEOF_L_SCENE (150*MB)
#define SIZEOF_XL_SCENE (300*MB)

#define SIZEOF_LARGEST_SCENE SIZEOF_XL_SCENE
#define SIZEOF_LOADING_SCREEN_SCENE SIZEOF_S_SCENE

// Each scene has its own static resources.
// Static resources are basically any resources that are loaded in at scene startup.
// They are not assets for the game, they can be for example: TextRenderingObject or ResourceIndexer's
// Resource indexers are a way to manage resources. They serve a way to allocate, read/write data for resources and to modify them. For example all NPC resources could have update position function

typedef struct {
	StaticResourcesIndexer staticResourcesIndexer;
	MemoryArena* arena; // arena lives right after SceneData struct
} SceneData ;

// There are 2 types of files: .scene and .ui.
// They contain elements that will be loaded into scene
// First contents of .ui are loaded and then .scene
// There is separation to make it easy to load in the same ui into 2 scenes
Error InitializeScene(
	void* sceneData, // where function should start initializing data
	u64 size,
	str uiPath,
	str areaPath,
	bool exist[AMOUNT_OF_STATIC_RESOURCES]
);

Error LoadGameScene(
	str uiPath,
	str areaPath
);

Error LoadLoadingScreenScene(
	str uiPath,
	str areaPath
);

// Gets a pointer to static resource
// will return NULL if static resource does not exist in this scene
void* GetStaticResource_SceneData(
	SceneData* sceneData,
	StaticResources staticResource
);