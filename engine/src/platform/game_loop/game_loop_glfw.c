#include <engine/errors.h>
#include <engine/platform/window_data.h>
#include <glad/glad.h>
#include <glfw3.h>
#include <assert.h>
#include <engine/platform/game_loop.h>

bool shouldWindowClose(PointerTable* table) {
	assert(table);
	WindowData* windowData = table->regions[WINDOW_DATA].ptr;
	return glfwWindowShouldClose(windowData->window);
}

void updateBuffer(PointerTable* table) {
	assert(table);
	WindowData* windowData = table->regions[WINDOW_DATA].ptr;
	glfwSwapBuffers(windowData->window);
}

void handleEngineEvents(PointerTable* table) {
	assert(table);
	glfwPollEvents();
}