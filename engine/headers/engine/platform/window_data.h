#pragma once

#include <engine/typedefs.h>
#include <engine/errors.h>
#include <engine/memory_pool.h>

#include <stdbool.h>

typedef enum {
	CURSOR_NORMAL,
	CURSOR_HIDDEN,
	CURSOR_DISABLED
} CursorMode;

typedef struct {
    void* window;
    i32 width;
    i32 height;
    i32 fps;
    f32 frametime;
    i32 cursorMode;
    bool vsync;
    bool resizable;
    bool windowShouldClose;
    v4 clearColor;
} WindowData ;

void InitializeWindow(
	WindowData* windowData,
	i32 width,
	i32 height,
	i32 fps,
	bool vsync,
	bool resizable,
	v4 clearColor,
	str title,
	CursorMode cursorMode
);

void WindowShouldClose(
	WindowData* window
);

void CloseWindow();

void GameLoop(
	PointerTable* table
);
