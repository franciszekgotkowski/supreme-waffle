#pragma once

#include <common/keycodes.h>
#include <platform/collect_input.h>

#include <stdbool.h>
#include <stddef.h>

// checks if key have just been pressed
bool KeyJustPressed(
	KeyboardKeys key
);

// ckecks if key is pressed now and was in previous frame
bool KeyLongPressed(
	KeyboardKeys key
);

// checks if key is pressed (does not consider previous frame)
bool KeyIsPressed(
	KeyboardKeys key
);

// checks if key has just been released
bool KeyJustReleased(
	KeyboardKeys key
);

void InitializeInputData();

// This function sets input function callbacks for game to run every frame.
// Functions will look at input and then do something
void InitializeInputFunctions();

void PushInputFunction(
	InputFunction func
);

void PopInputFunction();

void ClearInputFunction();

void RunAllInputFunctions();