#include <assert.h>
#include <stdbool.h>

#include <common/errors.h>
#include <common/range.h>

#include <engine/memory_pool.h>

#include <../headers/engine/handle_input.h>
#include <platform/window.h>

extern PointerTable* GameMemory;
InputData* inputData = NULL;

void InitializeInputFunctions() {
	InputFunctions* const input = getRegion(INPUT_FUNCTIONS);
	assert(input);

	*input = (InputFunctions){
		.amountOfFunctions = 0,
		.function = {},
	};
}

void PushInputFunction(
	InputFunction func
) {
	InputFunctions* const input = getRegion(INPUT_FUNCTIONS);
	assert(input);
	assert(func);
	assert(input->amountOfFunctions >= 0);
	assert(input->amountOfFunctions < MAXIMUM_INPUT_FUNCTIONS_AMOUNT);

	input->function[input->amountOfFunctions] = func;
	input->amountOfFunctions++;
}

void PopInputFunction() {
	InputFunctions* const input = getRegion(INPUT_FUNCTIONS);
	assert(input);
	assert(input->amountOfFunctions > 0);
	assert(input->amountOfFunctions < MAXIMUM_INPUT_FUNCTIONS_AMOUNT);

	input->amountOfFunctions--;
}

void ClearInputFunction() {
	InputFunctions* const input = getRegion(INPUT_FUNCTIONS);
	assert(input);
	assert(input->amountOfFunctions > 0);
	assert(input->amountOfFunctions < MAXIMUM_INPUT_FUNCTIONS_AMOUNT);

	input->amountOfFunctions = 0;
}

inline void RunAllInputFunctions() {
	InputFunctions* const inputFunctions = getRegion(INPUT_FUNCTIONS);
	assert(inputFunctions);
	assert(inputFunctions->amountOfFunctions >= 0);
	assert(inputFunctions->amountOfFunctions < MAXIMUM_INPUT_FUNCTIONS_AMOUNT);

	for range(i, inputFunctions->amountOfFunctions) {
		inputFunctions->function[i]();
	}
}

inline bool KeyJustPressed(
	KeyboardKeys key
) {
	assert(inputData);

	if (
		inputData->keyboard.pressedNow[key] &&
		!inputData->keyboard.pressedPreviously[key]
	) {
		return true;
	} else {
		return false;
	}
}

inline bool KeyLongPressed(
	KeyboardKeys key
) {
	assert(inputData);

	if (
		inputData->keyboard.pressedNow[key] &&
		inputData->keyboard.pressedPreviously[key]
	) {
		return true;
	} else {
		return false;
	}
}

bool KeyIsPressed(
	KeyboardKeys key
) {
	assert(inputData);

	if (
		inputData->keyboard.pressedNow[key]
	) {
		return true;
	} else {
		return false;
	}
}

inline bool KeyJustReleased(
	KeyboardKeys key
) {
	assert(inputData);

	if (
		!inputData->keyboard.pressedNow[key] &&
		inputData->keyboard.pressedPreviously[key]
	) {
		return true;
	} else {
		return false;
	}
}
void InitializeInputData() {

	assert(inputData == NULL);
	inputData = (InputData*)getRegion(INPUT_DATA);
	assert(inputData);

	InitializeInputCallbacks();
}
