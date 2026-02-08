#include "engine/platform/graphics.h"
#include "game/input_functions.h"
#include <engine/memory_pool.h>
#include <engine/platform/window_data.h>
#include <engine/platform/input.h>
#include <assert.h>
#include <game/game_loop.h>
#include <engine/platform/game_loop.h>

#include <stdbool.h>

extern PointerTable* GameMemory;

void GameLoop() {
	const PointerTable* table = GameMemory;
	assert(table);
	while (!((WindowData*)getRegion(WINDOW_DATA))->windowShouldClose) {
		clearScreen();

		handleInput();
		// handleEditor();
		// handleGameEvents(table);
		// renderScene(table);

		updateBuffer();
		handleEngineEvents();
	}
	CloseWindow();
}