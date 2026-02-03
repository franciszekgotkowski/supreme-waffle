#include <engine/typedefs.h>

#include <engine/typedefs.h>
#include <engine/errors.h>
#include <engine/platform/window_data.h>
#include <engine/platform/input_data.h>
#include <engine/memory_pool.h>
#include <engine/scene.h>
#include <engine/platform/memory_allocations.h>

u64 RegionCapacity[AMOUNT_OF_ENGINE_MEMORY_REGIONS] = {
	[POINTER_TABLE] = sizeof(PointerTable),
	[WINDOW_DATA] = sizeof(WindowData),
	[INPUT_DATA] = sizeof(InputData),
	[GAME_SCENE] = SIZEOF_LARGEST_SCENE,
	[LOADING_SCREEN_SCENE] = SIZEOF_LOADING_SCREEN_SCENE,
};