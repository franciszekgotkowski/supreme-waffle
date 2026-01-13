#include <engine/platform/memory_allocations.h>
#include <engine/memory_pool.h>
#include <engine/platform/window_data.h>
#include <engine/platform/input_data.h>

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

PointerTable* GameMemory = NULL;

int main(int argc, char *argv[]) {

	GameMemory = InitializePool(0);

    InitializeWindow(GameMemory, 800, 600, 144, true, true, (v4){.arr = {0.18f, 0.20f, 0.25f, 1.0f}}, "Der Spiel!", CURSOR_NORMAL);
    InitializeInput(GameMemory);

    GameLoop(GameMemory);

	printf("amount of memory regions in enum %d\n", AMOUNT_OF_ENGINE_MEMORY_REGIONS);
	// InitializeGameState()
	// LoadSceneFromDisk();
}
