#pragma once

#include <engine/memory_pool.h>
#include <engine/typedefs.h>
#include <engine/errors.h>

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
    i32 cursorMode;
    bool vsync;
    bool resizable;
    v4 clearColor;
} WindowData ;

Error InitializeWindow(PointerTable* table, i32 width, i32 height, i32 fps, bool vsync, bool resizable, v4 clearColor, str title, CursorMode cursorMode);

Error CloseWindow(PointerTable* table);

void GameLoop(PointerTable* table);
