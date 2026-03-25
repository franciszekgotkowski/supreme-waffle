#include <primitives/typedefs.h>

#include <primitives/typedefs.h>
#include <primitives/errors.h>
#include <platform/window_data.h>
#include <platform/input.h>
#include <engine/memory_pool.h>
#include <engine/scene.h>
#include <platform/memory_allocations.h>

// It has to have values for all regions from Regions enum. otherwise weird things may happen
u64 RegionCapacity[AMOUNT_OF_ENGINE_MEMORY_REGIONS] = {
	[POINTER_TABLE] = sizeof(PointerTable),
	[WINDOW_DATA] = sizeof(WindowData),
	[INPUT_DATA] = sizeof(InputData),
	[INPUT_FUNCTIONS] = sizeof(InputFunctions),
	[GAME_SCENE] = SIZEOF_LARGEST_SCENE,
	[LOADING_SCREEN_SCENE] = SIZEOF_LOADING_SCREEN_SCENE,
};