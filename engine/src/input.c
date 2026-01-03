#include <external/glfw3.h>
#include <assert.h>

#include <engine/memory_pool.h>
#include <engine/input_data.h>

void inputCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

Error InitializeInput(PointerTable *table) {
	assert(table);

	InputData* input = table->regions[INPUT_DATA].ptr;
	assert(input);

	*input = (InputData){};
	glfwSetKeyCallback(table->regions[WINDOW_DATA].ptr, inputCallback);

	return OK;
}