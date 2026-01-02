#include <engine/memory_allocations.h>
#include <engine/memory_pool.h>
#include <engine/window_data.h>

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

bool WindowShouldClose = false;
PointerTable* GameMemory = NULL;

int main(int argc, char *argv[]) {

	GameMemory = InitializePool();

    InitializeWindow(GameMemory, 800, 600, 144, true, (v4){.arr = {0.18f, 0.20f, 0.25f, 1.0f}}, "Der Spiel!", GLFW_CURSOR_NORMAL);

    GameLoop(GameMemory);

	printf("amount of region elements in enum %d\n", ENUM_COUNT);
	// InitializeWindow();
	// InitializeGameState()
	// LoadSceneFromDisk();

	// while (!WindowShouldClose) {
	// 	GetInput();

	// 	UpdateLogic();

	// 	Render();
	// }

}
