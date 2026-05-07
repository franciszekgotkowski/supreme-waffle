#include <common/typedefs.h>

#include <common/typedefs.h>
#include <common/errors.h>
#include <platform/window.h>
#include <engine/handle_input.h>
#include <engine/memory_pool.h>
#include <engine/scene.h>
#include <platform/memory_allocations.h>

// It has to have values for all regions from Regions enum. otherwise weird things may happen
u64 RegionCapacity[] = {
	[POINTER_TABLE] = sizeof(PointerTable),
	[WINDOW_DATA] = sizeof(WindowData),
	[INPUT_DATA] = sizeof(InputData),
	[INPUT_FUNCTIONS] = sizeof(InputFunctions),
	[LOADING_SCREEN_SCENE] = SIZEOF_LOADING_SCREEN_SCENE,
	[GAME_SCENE] = SIZEOF_LARGEST_SCENE,
};
_Static_assert(
	(sizeof(RegionCapacity)/sizeof(u64)) == AMOUNT_OF_ENGINE_MEMORY_REGIONS
);
