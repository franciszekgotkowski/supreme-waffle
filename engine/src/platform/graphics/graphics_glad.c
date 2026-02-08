#include <engine/platform/graphics.h>
#include <engine/memory_pool.h>

#include <external/glad/glad.h>

#include <assert.h>

extern PointerTable* GameMemory;

void clearScreen() {
	glClear(GL_COLOR_BUFFER_BIT);
}