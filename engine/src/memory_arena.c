#include <engine/memory_pool.h>
#include <engine/errors.h>
#include <assert.h>
#include <engine/memory_arena.h>

Error InitializeMemoryArena(void* base, u64 cap) {
	assert(base);

	assert(!(cap < sizeof(MemoryArena)));
	if (cap < sizeof(MemoryArena)) {
		return OUT_OF_MEMORY;
	}

	MemoryArena* arena = base;

	*arena = (MemoryArena) {
		.amountOfCheckpoints = 0,
		.base = base,
		.top = base,
		.capacity = cap,
		.locked = false
	};

	return OK;
}

Error push_MemoryArena(MemoryArena* arena, u64 size) {
	assert(arena);

	assert(!arena->locked);
	if (arena->locked) {
		return LOCKED;
	}

	assert(size + arena->top <= arena->base);
	if (size + arena->top > arena->base) {
		return OUT_OF_MEMORY;
	}

	arena->top += size;
	return OK;
}

Error reset_MemoryArena(MemoryArena* arena) {
	assert(arena);

	assert(!arena->locked);
	if (arena->locked) {
		return LOCKED;
	}

	arena->top = arena->base;

	return OK;
}

Error addCheckpoint_MemoryArena(MemoryArena* arena, void* ptr) {
	assert(arena);
	assert(ptr);

	assert(!arena->locked);
	if (arena->locked) {
		return LOCKED;
	}

	assert(!(arena->amountOfCheckpoints >= MAX_AMOUNT_OF_ARENA_CHECKPOINTS));
	if (arena->amountOfCheckpoints >= MAX_AMOUNT_OF_ARENA_CHECKPOINTS) {
		return OUT_OF_MEMORY;
	}

	assert(!(ptr > arena->base || ptr <= arena->base+arena->capacity));
	if (ptr > arena->base || ptr <= arena->base+arena->capacity) {
		return OUT_OF_RANGE;
	}

	arena->checkpoints[arena->amountOfCheckpoints] = ptr;
	arena->amountOfCheckpoints += 1;
	return OK;
}

Error returnToCheckpoint_MemoryArena(MemoryArena* arena, u64 idx) {
	assert(arena);

	assert(!arena->locked);
	if (arena->locked) {
		return LOCKED;
	}

	assert(!(idx > arena->amountOfCheckpoints));
	if (idx > arena->amountOfCheckpoints) {
		return OUT_OF_RANGE;
	}

	arena->amountOfCheckpoints = idx+1;
	arena->top = arena->checkpoints[idx];

	return OK;
}