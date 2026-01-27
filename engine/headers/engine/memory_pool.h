#pragma once

#include <assert.h>
#include <engine/typedefs.h>
#include <engine/errors.h>

typedef struct {
	u64 capacity;
	void* ptr;
} Region;

typedef enum {
	POINTER_TABLE,
	WINDOW_DATA,
	INPUT_DATA,
	GAME_SCENE,
	LOADING_SCREEN_SCENE,

	AMOUNT_OF_ENGINE_MEMORY_REGIONS
} Regions ;


// Intended use of pool with pointer table is to devide memory pool into chunks where each chunk will have their own metadata at the start and will manage rest of its memory. It is not intended to be used for gameplay dynamic allocations. This will be role of memory arenas
typedef struct {
	u64 emountOfRegions;
	u64 capacity;
	void* poolTop;
	Region regions[AMOUNT_OF_ENGINE_MEMORY_REGIONS];
} PointerTable ;

// Initializes pool with requested size. It will return NULL pointer if size is to small to contain memory needed by the engine
PointerTable* InitializePool();

// Initializes region. Can override existing memory region!!!
Error InitializeRegion(PointerTable* table, void* ptr, u64 regionIndex, u64 size);

// Memory layout:
// 		pointer table
//		window data
// 		input data
// 		sound???
// 		Default scene - scene in which gameplay will occur SIZEOF LARGEST AVAILABLE SCENE
// 			UI layer
// 				Assets
// 				Ui variables
// 			3d scene (area)
// 				Assets
// 				gameplay variables
// 		Loading screen scene - scene for loading
// 			UI layer
// 				Assets
// 				Ui variables