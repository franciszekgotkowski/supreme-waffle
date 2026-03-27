#pragma once

#include <common/typedefs.h>
#include <common/cursor_modes.h>
#include "measure_time.h"
#include <stdbool.h>

typedef struct {
    void* window;
    i32 windowWidth;
    i32 windowHeight;
    i32 fps;
    i32 cursorMode;
    bool vsync;
    bool resizable;
    bool windowShouldClose;
    v4 clearColor;

    TimeStamp frametime;
    u64 framesElapsed;
    TimeStamp bootTimeStamp;
    TimeStamp frametimeEveningTimeStamp;
} WindowData ;


void InitializeWindow(
    i32 windowWidth,
    i32 windowHeight,
    bool vsync,
    bool resizable,
    v4 clearColor,
    str title,
    CursorMode cursorMode
);

void CloseWindow();