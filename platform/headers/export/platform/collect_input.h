#pragma once

#include <stdbool.h>
#include <common/keycodes.h>
#include <common/typedefs.h>

#define MAX_KEYBOARD_BUTTONS_AMOUNT 1024
#define MAX_MOUSE_BUTTONS_AMOUNT 8

// typedef struct {
// 	bool pressedNow[MAX_KEYBOARD_BUTTONS_AMOUNT];
//     bool pressedPreviously[MAX_KEYBOARD_BUTTONS_AMOUNT];
// } keyboardState ;
typedef struct {
    bool pressedNow[KEYBOARD_KEYS_AMOUNT];
    bool pressedPreviously[KEYBOARD_KEYS_AMOUNT];
    i32 mods;
} keyboardState ;

//     f64 x, y;
//     f64 dx, dy;
//     f64 scroll;
// } mouseState ;
typedef struct {
    bool pressedNow[MOUSE_BUTTONS_AMOUNT];
    bool pressedPreviously[MOUSE_BUTTONS_AMOUNT];

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

#define MAXIMUM_INPUT_FUNCTIONS_AMOUNT 1024
typedef void (*InputFunction)() ;
// Functions can be added to input qeue with PushInputFunction. They will be ran every frame in handleInput() function.
typedef struct {
    u64 amountOfFunctions;
    InputFunction function[MAXIMUM_INPUT_FUNCTIONS_AMOUNT];
} InputFunctions;

void InitializeInputCallbacks();
