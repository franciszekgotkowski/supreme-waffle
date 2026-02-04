
#include <engine/platform/window_data.h>
#include <engine/memory_pool.h>
#include <assert.h>
#include <stdbool.h>

#include <engine/errors.h>
#include <engine/range.h>
#include <engine/platform/input.h>
#include <external/glfw3.h>

extern PointerTable* GameMemory;

void InitializeInputFunctions() {
	InputFunctions* input = getRegion(INPUT_FUNCTIONS);
	assert(input);

	*input = (InputFunctions){
		.amountOfFunctions = 0,
		.function = {},
	};
}

void PushInputFunction(
	InputFunctions* input,
	InputFunction func
) {
	assert(input);
	assert(func);
	assert(input->amountOfFunctions >= 0);
	assert(input->amountOfFunctions < MAXIMUM_INPUT_FUNCTIONS_AMOUNT);

	input->function[input->amountOfFunctions] = func;
	input->amountOfFunctions++;
}

void PopInputFunction(
	InputFunctions* input
) {
	assert(input);
	assert(input->amountOfFunctions > 0);
	assert(input->amountOfFunctions < MAXIMUM_INPUT_FUNCTIONS_AMOUNT);

	input->amountOfFunctions--;
}

void ClearInputFunction(
	InputFunctions* input
) {
	assert(input);
	assert(input->amountOfFunctions > 0);
	assert(input->amountOfFunctions < MAXIMUM_INPUT_FUNCTIONS_AMOUNT);

	input->amountOfFunctions = 0;
}

inline void RunAllInputFunctions(
	InputFunctions* input
) {
	assert(input);
	assert(input->amountOfFunctions >= 0);
	assert(input->amountOfFunctions < MAXIMUM_INPUT_FUNCTIONS_AMOUNT);

	for range(i, input->amountOfFunctions) {
		input->function[i](GameMemory);
	}
}

inline bool KeyJustPressed(
	KeyboardKeys key
) {
	InputData* inputData = getRegion(INPUT_DATA);
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
	InputData* inputData = getRegion(INPUT_DATA);
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
	InputData* inputData = getRegion(INPUT_DATA);
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
	InputData* inputData = getRegion(INPUT_DATA);
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
