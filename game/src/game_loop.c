#include <engine/memory_pool.h>
#include <engine/platform/window_data.h>
#include <assert.h>
#include <game/game_loop.h>
#include <engine/platform/game_loop.h>

#include <stdbool.h>

void GameLoop(
	PointerTable* table
) {
	assert(table);
	while (!((WindowData*)getRegion(table, WINDOW_DATA))->windowShouldClose) {
		clearScreen(table);

		// if (((InputData*)getRegion(table, INPUT_DATA))->keyboard.pressedNow[K_ESC]) {
		// 	WindowShouldClose(getRegion(table, WINDOW_DATA));
		// }

		// handleInput(table);
		// handleEditor();
		// handleGameEvents(table);
		// renderScene(table);

		updateBuffer(table);
		handleEngineEvents(table);
	}
	CloseWindow();
}