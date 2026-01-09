#include "engine/measure_time.h"
#include <assert.h>
#include <stdio.h>

#include <engine/input_data.h>
#include <engine/memory_pool.h>
#include <engine/window_data.h>
#include <engine/errors.h>

#include <external/glad/glad.h>
#include <external/glfw3.h>

extern PointerTable* GameMemory;

void inputCallback(GLFWwindow* window, i32 key, i32 scancode, i32 action, i32 mods);

static void framebuffer_size_callback(GLFWwindow *window, i32 width, i32 height) {
	assert(window);
	assert(GameMemory);

	WindowData* windowData = GameMemory->regions[WINDOW_DATA].ptr;

	printf("window is resized from %dx%d to %dx%d\n", windowData->height, windowData->width, height, width);

    windowData->width = width;
    windowData->height = height;

    glViewport(0, 0, windowData->width, windowData->height);
}

Error InitializeWindow(PointerTable* table, i32 width, i32 height, i32 fps, bool vsync, bool resizable, v4 clearColor, str title, CursorMode cursorMode) {
    assert(table);
    assert(title);
    assert(width > 0 && height > 0 && fps > 0);

    i32 cursorModeGlfw;
    switch (cursorMode) {
   		case CURSOR_NORMAL:
    		cursorModeGlfw = GLFW_CURSOR_NORMAL;
     		break;
       	case CURSOR_HIDDEN:
       		cursorModeGlfw = GLFW_CURSOR_HIDDEN;
        	break;
        case CURSOR_DISABLED:
       		cursorModeGlfw = GLFW_CURSOR_DISABLED;
        	break;
        default:
       		cursorModeGlfw = GLFW_CURSOR_NORMAL;
         	break;
    }

    WindowData* windowData = table->regions[WINDOW_DATA].ptr;
    assert(windowData);


    (*windowData) = (WindowData){
        .window = NULL,
        .height = height,
        .width = width,
        .fps = fps,
        .frametime = 1000.0f*1/fps,
        .cursorMode = cursorModeGlfw,
        .vsync = vsync,
        .resizable = resizable,
        .clearColor = clearColor,
    };

    if (!glfwInit()) {return LIBRARY_FAIL;}
    assert(glfwInit());

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, resizable ? GLFW_TRUE : GLFW_FALSE);

    windowData->window = glfwCreateWindow(width, height, title, NULL, NULL);
    assert(windowData->window);
    if (!windowData->window) {
        glfwTerminate();
        return LIBRARY_FAIL;
    }

    glfwMakeContextCurrent(windowData->window);
    glfwSetInputMode(windowData->window, GLFW_CURSOR, cursorModeGlfw);
    glfwSwapInterval(vsync);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        printf("Failed to initialize GLAD\n");
        return LIBRARY_FAIL;
    }

    glfwGetFramebufferSize(windowData->window, &(windowData->width), &(windowData->height));
    glViewport(0, 0, windowData->width, windowData->height);
    glClearColor(windowData->clearColor.arr[0],windowData->clearColor.arr[1], windowData->clearColor.arr[2], windowData->clearColor.arr[3]);

    glfwSetFramebufferSizeCallback(windowData->window, framebuffer_size_callback);

    return OK;
}

void GameLoop(PointerTable* table) {
    WindowData* windowData = table->regions[WINDOW_DATA].ptr;
    InputData* inputData = table->regions[INPUT_DATA].ptr;

    timestamp stamp = make_stamp();
    while (!glfwWindowShouldClose(windowData->window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        if (inputData->keyboard.pressedPreviously[K_ESC] && !inputData->keyboard.pressedNow[K_ESC]) {
       		printf("Odciśnięto Escape!\n");
      		glfwSetWindowShouldClose(windowData->window, true);
        }

        glfwSwapBuffers(windowData->window);
        glfwPollEvents();
        printf("frame rendered in %fms\n", elapsed_time(&stamp));
    }
}

Error CloseWindow(PointerTable* table) {
    assert(table);
    if (!table) {
        return NULL_POINTER;
    }

    glfwTerminate();
    return OK;
}

