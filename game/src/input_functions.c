#include <engine/memory_pool.h>
#include <engine/platform/window_data.h>
#include <game/input_functions.h>
#include <engine/platform/input.h>

#include <assert.h>
#include <stdio.h>

void CheckForExit(
	PointerTable* table
) {
	assert(table);

	if (KeyJustReleased(K_ESC)) {
		WindowShouldClose(getRegion(WINDOW_DATA));
	}
}

void MouseMoved(
	PointerTable* table
) {
	mouseState* mouse = &(((InputData*)getRegion(INPUT_DATA))->mouse);
	assert(table);


	if(
		mouse->dx != 0.0 ||
		mouse->dy != 0.0
	) {
		printf("mouse moved from (%f, %f) to (%f, %f)", mouse->x, mouse->y, mouse->x - mouse->dx, mouse->y - mouse->dy);
		printf("\t moved by (%f, %f)\n", mouse->dx, mouse->dy);
	}

	// this has to run on the end
	mouse->dx = 0.0;
	mouse->dy = 0.0;
}




void InsertInputFunctions() {
	PushInputFunction(getRegion(INPUT_FUNCTIONS), CheckForExit);
	PushInputFunction(getRegion(INPUT_FUNCTIONS), MouseMoved);
}

void handleInput(
	PointerTable* table
) {
	assert(table);
	RunAllInputFunctions(getRegion(INPUT_FUNCTIONS));
}