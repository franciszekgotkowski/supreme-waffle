#include "internal/window_data.h"
#include <engine/print.h>
#include <engine/range.h>
#include <engine/memory.h>

#include <internal/memory_pool.h>

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

bool WindowShouldClose = false;
PointerTable* GameMemory = NULL;

int main(int argc, char *argv[]) {

	GameMemory = InitializePool();

	*((WindowData*)GameMemory->regions[WINDOW_DATA].ptr) = (WindowData){0};
	*((WindowData*)GameMemory->regions[WINDOW_DATA].ptr) = (WindowData){0};

	printf("amount of element in enum %d\n", ENUM_COUNT);
	// InitializeWindow();
	// InitializeGameState();
	// LoadSceneFromDisk();

	// while (!WindowShouldClose) {
	// 	GetInput();

	// 	UpdateLogic();

	// 	Render();
	// }

}
