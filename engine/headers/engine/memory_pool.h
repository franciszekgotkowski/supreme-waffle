#pragma once

#include <engine/typedefs.h>

typedef struct {
	u64 len;
	void* ptr;
} Region;

#define MAXIMUM_AMOUNT_OF_REGIONS 20
typedef struct {
	u64 emountOfRegions;
	u64 size;
	void* poolTop;
	Region regions[MAXIMUM_AMOUNT_OF_REGIONS];
} PointerTable ;

typedef enum {
	POINTER_TABLE,
	WINDOW_DATA,
	INPUT_DATA,

	AMOUNT_OF_ENGINE_MEMORY_REGIONS
} Regions ;

// Initializes pool with requested size. It will return NULL pointer if size is to small to contain memory needed by the engine. If size is 0 it will allocate memory only for the engine
PointerTable* InitializePool(u64 size);

// Memory layout:
// 		pointer table
//		window data
// 		input data
// 		sound???
// 		ui layer??
// 			fonts???
// 			ui images???
// 			ui composition???
// 		scene???
// 			ECS componenst???
// 				envirnoment componensts???
// 				interactive componensts???
// 				mobs componensts???
// 		gameplay???
// 			addition components???
//
//
//
//
// 		temp file storage???
//