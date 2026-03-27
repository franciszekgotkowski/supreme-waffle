#include <export/platform/collect_input.h>
#include <export/platform/window.h>
#include <assert.h>

#include <glfw3.h>

extern WindowData* windowData;
extern InputData* inputData;

bool doesSystemWantToCloseWindow() {
	assert(windowData);
	return glfwWindowShouldClose(windowData->window);
}

void updateBuffer() {
	assert(windowData);
	glfwSwapBuffers(windowData->window);
}

void handleEngineEvents() {
	glfwPollEvents();
}