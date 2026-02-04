#include "engine/memory_pool.h"
#include "engine/platform/window_data.h"
#include <assert.h>
#include <game/input_functions.h>
#include <engine/platform/input.h>

void CheckForExit(
	PointerTable* table
) {
	assert(table);

	if (KeyJustReleased(K_ESC)) {
		WindowShouldClose(getRegion(WINDOW_DATA));
	}
}

void InsertInputFunctions() {
	PushInputFunction(getRegion(INPUT_FUNCTIONS), CheckForExit);
}

void handleInput(
	PointerTable* table
) {
	assert(table);
	RunAllInputFunctions(getRegion(INPUT_FUNCTIONS));
}