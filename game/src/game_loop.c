#include <assert.h>
#include <game/game_loop.h>
#include <engine/platform/game_loop.h>

#include <stdbool.h>

void GameLoop(PointerTable* table) {
	assert(table);
	while (!shouldWindowClose(table)) {
		clearScreen(table);

		// handleInput(table);
		// handleEditor();
		// handleGameEvents(table);
		// renderScene(table);

		updateBuffer(table);
		handleEngineEvents(table);
	}
}