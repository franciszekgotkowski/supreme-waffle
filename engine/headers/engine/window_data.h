#pragma once

#include <engine/memory_pool.h>
#include <engine/typedefs.h>
#include <engine/errors.h>

#include <external/glad/glad.h>
#include <external/glfw3.h>

#include <stdbool.h>

typedef struct {
    GLFWwindow* window;
    i32 width;
    i32 height;
    i32 fps;
    i32 cursorMode;
    bool vsync;
    v4 clearColor;
} WindowData ;

Error InitializeWindow(PointerTable* table, i32 width, i32 height, i32 fps, bool vsync, v4 clearColor, str title, i32 cursorMode);

Error CloseWindow(PointerTable* table);

void GameLoop(PointerTable* table);
