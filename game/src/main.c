#include <engine/memory_allocations.h>
#include <engine/memory_pool.h>
#include <engine/window_data.h>
#include <engine/input_data.h>

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

PointerTable* GameMemory = NULL;

int main(int argc, char *argv[]) {

	GameMemory = InitializePool();
	printf("base of memory pool %llu\n", (long long unsigned int)GameMemory);

    InitializeWindow(GameMemory, 800, 600, 144, false, (v4){.arr = {0.18f, 0.20f, 0.25f, 1.0f}}, "Der Spiel!", CURSOR_NORMAL);
    InitializeInput(GameMemory);

    GameLoop(GameMemory);

	printf("amount of memory regions in enum %d\n", ENUM_COUNT);
	// InitializeGameState()
	// LoadSceneFromDisk();
}
