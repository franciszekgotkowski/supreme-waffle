#pragma once

#include <engine/errors.h>
#include <engine/memory_pool.h>
#include <engine/typedefs.h>
// #include <external/glfw3.h>
#include <stdbool.h>

extern PointerTable* GameMemory;

typedef enum {
	K_A,	K_B,	K_C,	K_D,
	K_E,	K_F,	K_G,	K_H,
	K_I,	K_J,	K_K,	K_L,
	K_M,	K_N,	K_O,	K_P,
	K_Q,	K_R,	K_S,	K_T,
	K_U,	K_V,	K_W,	K_X,
	K_Y,	K_Z,	K_0,	K_1,
	K_2,	K_3,	K_4,	K_5,
	K_6,	K_7,	K_8,	K_9,
	K_SPACE,	K_ENTER,	K_BACKSPACE,	K_ESC,
	K_SHIFT,	K_CTRL,		K_ALT,		K_SUPER,

	KEYBOARD_KEYS_AMOUNT
} KeyboardKeys ;

typedef enum {
	M_LEFT = 0,
    M_RIGHT,
    M_MIDDLE,
    MB_4, // Often "Back"
    MB_5, // Often "Forward"
    MB_6,
    MB_7,
    MB_8,

    MOUSE_BUTTONS_AMOUNT
} MouseInput ;

#define MAX_KEYBOARD_BUTTONS_AMOUNT 1024
#define MAX_MOUSE_BUTTONS_AMOUNT 8

typedef struct {
	bool pressedNow[MAX_KEYBOARD_BUTTONS_AMOUNT];
    bool pressedPreviously[MAX_KEYBOARD_BUTTONS_AMOUNT];
} keyboardState ;

typedef struct {
	bool pressedNow[MAX_MOUSE_BUTTONS_AMOUNT];
    bool pressedPreviously[MAX_MOUSE_BUTTONS_AMOUNT];

    f64 x, y;
    f64 dx, dy;
    f64 scroll;
} mouseState ;

typedef struct {

} gamepadState ;

typedef struct {
	keyboardState keyboard;
	mouseState mouse;
	gamepadState gamepad;
} InputData ;

Error InitializeInput(PointerTable* table);

// void inputCallback(GLFWwindow* window, int key, int scancode, int action, int mods);