#include <engine/font.h>
#include "engine/memory_arena.h"
#include "engine/platform/file_io.h"
#include <engine/platform/memory_allocations.h>
#include <engine/memory_pool.h>
#include <engine/platform/window_data.h>
#include <engine/platform/input_data.h>

#include <engine/string_utils.h>

#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

PointerTable* GameMemory = NULL;

int main(int argc, char *argv[]) {

	GameMemory = InitializePool(10000);

    InitializeWindow(GameMemory, 800, 600, 144, true, true, (v4){.arr = {0.18f, 0.20f, 0.25f, 1.0f}}, "Der Spiel!", CURSOR_NORMAL);
    InitializeInput(GameMemory);
    InitializeMemoryArena(GameMemory->regions[MEMORY_ARENA].ptr, GameMemory->regions[MEMORY_ARENA].len);
    // InitializeCanvas();

    FileData file;
    readEntireFile("../../assets/fonts/bdf/cherry-11-r.bdf", &file);
    u64 space = SpaceNeededForFont(file);
    printf("space needed for cherry-11-r.bdf = %llu\n", (llu)space);

    GameLoop(GameMemory);

	printf("amount of memory regions in enum %d\n", AMOUNT_OF_ENGINE_MEMORY_REGIONS);
	// InitializeGameState()
	// LoadSceneFromDisk();
}
