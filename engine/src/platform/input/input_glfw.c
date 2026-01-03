#include <engine/memory_pool.h>
#include <assert.h>
#include <stdbool.h>

#include <engine/errors.h>
#include <engine/input_data.h>
#include <external/glfw3.h>

static Error updateKeyboard(PointerTable* table, i32 key, i32 scancode, i32 action, i32 mods) {
	assert(table);
	InputData* input = table->regions[INPUT_DATA].ptr;

	bool keyNow = false;
 	bool keyPast = false;
	if (action == GLFW_PRESS) {
		keyNow = 1;
		keyPast = 0 ;
	}
	if (action == GLFW_RELEASE) {
		keyNow = 0;
		keyPast = 1 ;
	}

	if (mods == GLFW_MOD_ALT) {
		input->keyboard.pressedPreviously[K_ALT] = input->keyboard.pressedNow[K_ALT];
		input->keyboard.pressedNow[K_ALT] = true;
	} else {
		input->keyboard.pressedPreviously[K_ALT] = input->keyboard.pressedNow[K_ALT];
		input->keyboard.pressedNow[K_ALT] = false;
	}

	if (mods == GLFW_MOD_CONTROL) {
		input->keyboard.pressedPreviously[K_CTRL] = input->keyboard.pressedNow[K_CTRL];
		input->keyboard.pressedNow[K_CTRL] = true;
	} else {
		input->keyboard.pressedPreviously[K_CTRL] = input->keyboard.pressedNow[K_CTRL];
		input->keyboard.pressedNow[K_CTRL] = false;
	}

	if (mods == GLFW_MOD_SHIFT) {
		input->keyboard.pressedPreviously[K_SHIFT] = input->keyboard.pressedNow[K_SHIFT];
		input->keyboard.pressedNow[K_SHIFT] = true;
	} else {
		input->keyboard.pressedPreviously[K_SHIFT] = input->keyboard.pressedNow[K_SHIFT];
		input->keyboard.pressedNow[K_SHIFT] = false;
	}

	if (mods == GLFW_MOD_SUPER) {
		input->keyboard.pressedPreviously[K_SUPER] = input->keyboard.pressedNow[K_SUPER];
		input->keyboard.pressedNow[K_SUPER] = true;
	} else {
		input->keyboard.pressedPreviously[K_SUPER] = input->keyboard.pressedNow[K_SUPER];
		input->keyboard.pressedNow[K_SUPER] = false;
	}

	switch (key) {
		case GLFW_KEY_ENTER:
			input->keyboard.pressedNow[K_ENTER] = keyNow;
			input->keyboard.pressedPreviously[K_ENTER] = keyPast;
			break;
		case GLFW_KEY_ESCAPE:
			input->keyboard.pressedNow[K_ESC] = keyNow;
			input->keyboard.pressedPreviously[K_ESC] = keyPast;
			break;
	}

	return OK;
}

// static Error updateMouse(PointerTable* table){
// 	return OK;
// }

// // GAMEPAD IS NOT IMPLEMENTED
// static Error updateGamepad(PointerTable* table){
// 	return OK;
// }

void inputCallback(GLFWwindow* window, i32 key, i32 scancode, i32 action, i32 mods) {
	assert(window);

	Error err = updateKeyboard(GameMemory, key, scancode, action, mods);
	assert(err == OK);

}