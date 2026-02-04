#include "engine/platform/graphics.h"
#include "game/input_functions.h"
#include <engine/memory_pool.h>
#include <engine/platform/window_data.h>
#include <engine/platform/input.h>
#include <assert.h>
#include <game/game_loop.h>
#include <engine/platform/game_loop.h>

#include <stdbool.h>

void GameLoop(
	PointerTable* table
) {
	assert(table);
	while (!((WindowData*)getRegion(WINDOW_DATA))->windowShouldClose) {
		clearScreen(table);

		handleInput(table);
		// handleEditor();
		// handleGameEvents(table);
		// renderScene(table);

		updateBuffer(table);
		handleEngineEvents(table);
	}
	CloseWindow();
}