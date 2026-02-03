#include <engine/errors.h>
#include <assert.h>
#include <engine/memory_pool.h>
#include <engine/scene.h>

extern PointerTable* GameMemory;

// TODO: Write file parser for .ui files
static u64 evalueateUiSizeInBytes(
	str path
) {
	assert(path);
	return 0;
}

static u64 evalueateAreaSizeInBytes(
	str path
) {
	assert(path);
	return 0;
}

Error InitializeScene(
	SceneData* sceneData,
	u64 capacity,
	str uiPath,
	str areaPath
) {
	assert(sceneData);
	assert(uiPath);
	assert(areaPath);

	u64 uiSizeInBytes = evalueateUiSizeInBytes(uiPath);
	assert(uiSizeInBytes + evalueateAreaSizeInBytes(areaPath) <= capacity);
	if (uiSizeInBytes + evalueateAreaSizeInBytes(areaPath) > capacity) {
		return OUT_OF_MEMORY;
	}

	*sceneData = (SceneData){
		.sceneCapacity = capacity,
		.uiData = (void*)sceneData + sizeof(SceneData),
		.areaData = (void*)sceneData + sizeof(SceneData) + uiSizeInBytes
	};

	return OK;
}

Error InitializeGameScene(
	str uiPath,
	str areaPath
) {
	assert(uiPath);
	assert(areaPath);

	return InitializeScene(
		getRegion(GameMemory, GAME_SCENE),
		getRegionCapacity(GameMemory, GAME_SCENE),
		uiPath,
		areaPath
	);

	return OK;
}

Error InitializeLoadingScreenScene(
	str uiPath,
	str areaPath
) {
	assert(uiPath);
	assert(areaPath);

	return InitializeScene(
		getRegion(GameMemory, LOADING_SCREEN_SCENE),
		getRegionCapacity(GameMemory, LOADING_SCREEN_SCENE),
		uiPath,
		areaPath
	);

	return OK;
}