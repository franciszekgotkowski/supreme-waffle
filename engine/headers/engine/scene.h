#pragma once

#include <engine/memory_pool.h>

#include <engine/ui.h>
#include <engine/area.h>
#include <engine/typedefs.h>

#define SCENE_FILES_LOCATION "../../assets/scene/"
#define SIZEOF_XS_SCENE (5*MB)
#define SIZEOF_S_SCENE (25*MB)
#define SIZEOF_M_SCENE (75*MB)
#define SIZEOF_L_SCENE (150*MB)
#define SIZEOF_XL_SCENE (300*MB)

#define SIZEOF_LARGEST_SCENE SIZEOF_XL_SCENE
#define SIZEOF_LOADING_SCREEN_SCENE SIZEOF_S_SCENE

typedef struct {
	u64 sceneCapacity;
	UiData* uiData;
	AreaData* areaData;
} SceneData ;

Error InitializeScene(
	SceneData* sceneData,
	u64 cap,
	str uiPath,
	str areaPath
);

Error LoadGameScene(
	str uiPath,
	str areaPath
);

Error LoadLoadingScreenScene(
	str uiPath,
	str areaPath
);