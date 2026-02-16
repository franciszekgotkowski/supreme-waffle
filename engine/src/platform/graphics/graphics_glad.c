#include <engine/platform/graphics.h>
#include <engine/memory_pool.h>
#include <engine/platform/window_data.h>

#include <external/glad/glad.h>

#include <assert.h>

extern PointerTable* GameMemory;

void clearScreen() {
	glClear(GL_COLOR_BUFFER_BIT);
}

// function that gets v2u32 with pixel offsets and transforms them into screenspace v2 that starts at (0, 0)
inline v2 PixelsToScreenspace(v2u32 px) {
	WindowData* windowData = (WindowData*)getRegion(WINDOW_DATA);
	assert(px.x < windowData->width);
	assert(px.y < windowData->height);
	v2 ret = {
		.x = (f32)( (i32)px.x - windowData->width/2 ) / (f32)(windowData->width/2),
		.y = (f32)( (i32)px.y - windowData->height/2 ) / (f32)(-windowData->height/2),
	};

	return ret;
}

