#include <engine/platform/graphics.h>
#include <engine/memory_pool.h>

#include <external/glad/glad.h>

#include <assert.h>

void clearScreen(PointerTable* table) {
	assert(table);
	glClear(GL_COLOR_BUFFER_BIT);
}