#pragma once

#include <engine/typedefs.h>
#include <engine/errors.h>
#include <stdbool.h>

#define MAX_AMOUNT_OF_ARENA_CHECKPOINTS 100
typedef struct {
	void* checkpoints[MAX_AMOUNT_OF_ARENA_CHECKPOINTS];
	u64 amountOfCheckpoints;
	void* base; // base pointer to arena
	void* top; // current top of allocated memory
	u64 capacity; // maximum capacity of an arena including this struct
	bool locked; // if memory arena is locked, pushing or reseting memory is illegal and functions should return an error
} MemoryArena ;

Error InitializeMemoryArena(void* base, u64 cap);

Error push_MemoryArena(MemoryArena* arena, u64 size);

Error reset_MemoryArena(MemoryArena* arena);

Error addCheckpoint_MemoryArena(MemoryArena* arena, void* ptr);

Error returnToCheckpoint_MemoryArena(MemoryArena* arena, u64 idx);