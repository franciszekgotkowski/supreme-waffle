#include <engine/memory_arena.h>
#include <../headers/engine/handle_input.h>
#include <common/errors.h>
#include <assert.h>
#include <engine/memory_pool.h>
#include <engine/scene.h>
#include <string.h>
#include <common/range.h>
#include <engine/static_resources.h>
#include <engine/resource_indexers.h>

extern PointerTable* GameMemory;

extern const u32 SizesForEachStaticResource[AMOUNT_OF_STATIC_RESOURCES];
extern const u32 DefaultAmountsOfIndexes[AMOUNT_OF_STATIC_RESOURCES];

static void InitializeStaticResourceIndexer(
	SceneData* sceneData,
	bool exist[AMOUNT_OF_STATIC_RESOURCES]
) {
	assert(sceneData);
	assert(exist);

	memcpy(
		&(sceneData->staticResourcesIndexer.exist),
		exist,
		(AMOUNT_OF_STATIC_RESOURCES * sizeof(bool))
	);

	Error err;
	MemoryArena* arenaPtr = &sceneData->arena;

	for range(i, AMOUNT_OF_STATIC_RESOURCES) {
		if (sceneData->staticResourcesIndexer.exist[i]) {
			assert(SizesForEachStaticResource[i] != 0);
			void* t = registerMemory_MemoryArena(
				arenaPtr,
				SizesForEachStaticResource[i],
				&err
			);
			assert(err == OK);
			assert(t);
			InitializeResourceIndexer(
				t,
				i
			);
			sceneData->staticResourcesIndexer.ptr[i] = t;
		}
	}
}

void InitializeScene(
	void* sceneData,
	u64 size,
	str uiPath,
	str areaPath,
	bool StaticResourcesExist[AMOUNT_OF_STATIC_RESOURCES]
) {
	assert(sceneData);
	assert(uiPath);
	assert(areaPath);
	assert(sizeof(SceneData) <= size);

	SceneData* const scenePtr = sceneData;

	*scenePtr = (SceneData){
		.staticResourcesIndexer = {},
		.arena = InitializeMemoryArena(
			sceneData + sizeof(SceneData),
			size - sizeof(SceneData)
		)
	};

	InitializeStaticResourceIndexer(
		scenePtr,
		StaticResourcesExist
	);

	// TODO
	// loadUi()
	// loadArea()

}

// Last parameter is temporary!!!
// It will be autodetermined by the scene fiele when the time is right
Error LoadGameScene(
	str uiPath,
	str areaPath
) {
	assert(uiPath);
	assert(areaPath);

	InitializeScene(
		getRegion(GAME_SCENE),
		getRegionCapacity(GameMemory, GAME_SCENE),
		uiPath,
		areaPath,
		(bool[]){
			true,
			true,
			true
		}
	);

	return OK;
}

// Last parameter is temporary!!!
// It will be autodetermined by the scene fiele when the time is right
Error LoadLoadingScreenScene(
	str uiPath,
	str areaPath
) {
	assert(uiPath);
	assert(areaPath);

	InitializeScene(
		getRegion(LOADING_SCREEN_SCENE),
		getRegionCapacity(GameMemory, LOADING_SCREEN_SCENE),
		uiPath,
		areaPath,
		(bool[]){
			true,
			true,
			true
		}
	);

	return OK;
}

void* GetStaticResource_SceneData(
	SceneData* sceneData,
	StaticResources staticResource
) {
	assert(sceneData);
	assert(staticResource < AMOUNT_OF_STATIC_RESOURCES);

	if (!sceneData->staticResourcesIndexer.exist[staticResource]) {
		return NULL;
	}
	return sceneData->staticResourcesIndexer.ptr[staticResource];
}