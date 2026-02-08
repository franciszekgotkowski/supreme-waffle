#include "engine/memory_pool.h"
#include <engine/errors.h>
#include <engine/platform/window_data.h>
#include <glad/glad.h>
#include <glfw3.h>
#include <assert.h>
#include <engine/platform/game_loop.h>

extern PointerTable* GameMemory;

bool doesSystemWantToCloseWindow() {
	PointerTable* const table = GameMemory;
	assert(table);
	WindowData* windowData = table->regions[WINDOW_DATA].ptr;
	return glfwWindowShouldClose(windowData->window);
}

void updateBuffer() {
	PointerTable* const table = GameMemory;
	assert(table);
	WindowData* windowData = table->regions[WINDOW_DATA].ptr;
	glfwSwapBuffers(windowData->window);
}

void handleEngineEvents() {
	PointerTable* const table = GameMemory;
	assert(table);
	glfwPollEvents();
}