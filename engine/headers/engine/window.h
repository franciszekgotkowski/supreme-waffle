#pragma once

#include <common/typedefs.h>
#include <stdbool.h>
#include <platform/measure_time.h>

#include <common/cursor_modes.h>
void InitializeEngineWindow(
    i32 windowWidth,
    i32 windowHeight,
    i32 fps,
    bool vsync,
    bool resizable,
    v4 clearColor,
    str title,
    CursorMode cursorMode
);

// Sets windowShouldClose parameter to true
void SetWindowToClose();

void GameLoop();
