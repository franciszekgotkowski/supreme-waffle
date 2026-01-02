#pragma once

#include <engine/typedefs.h>

typedef struct {
	u64 len;
	void* ptr;
} Region;

#define MAXIMUM_AMOUNT_OF_REGIONS 20
typedef struct {
	u64 emountOfRegions;
	Region regions[MAXIMUM_AMOUNT_OF_REGIONS];
} PointerTable ;

typedef enum {
	POINTER_TABLE,
	WINDOW_DATA,
	INPUT_DATA,

	ENUM_COUNT
} Regions ;

PointerTable* InitializePool();
