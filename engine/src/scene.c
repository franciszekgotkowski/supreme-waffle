#include <assert.h>
#include <engine/memory_pool.h>
#include <engine/scene.h>

// TODO: Write file parser for .ui files
static u64 evalueateUiSizeInBytes(str path) {
	assert(path);
}

static u64 evalueateAreaSizeInBytes(str path) {
	assert(path);
}

Error InitializeScene(SceneData* sceneData, u64 capacity, str uiPath, str areaPath) {
	assert(sceneData);

	u64 uiSizeInBytes = evalueateUiSizeInBytes(uiPath);
	assert(uiSizeInBytes + evalueateAreaSizeInBytes(areaPath) <= capacity);
	if ()

	*sceneData = (SceneData){
		.sceneCapacity = capacity,
		.uiData = (void*)sceneData + sizeof(SceneData),
		.areaData = (void*)sceneData + sizeof(SceneData) + uiSizeInBytes
	};

}

Error InitializeGameScene(PointerTable* table, str path) {
	assert(table);
	return InitializeScene(
		table->regions[GAME_SCENE].ptr,
		table->regions[GAME_SCENE].capacity,
		path
	);
}

Error InitializeLoadingScreenScene(PointerTable* table, str path) {
	assert(table);
	return InitializeScene(
		table->regions[LOADING_SCREEN_SCENE].ptr,
		table->regions[LOADING_SCREEN_SCENE].capacity,
		path
	);
}