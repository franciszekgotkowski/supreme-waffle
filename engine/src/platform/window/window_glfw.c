
// DEPRECATED
// PLEASE DONT USE IT
// FILE IS SAVED FOR THE SAKE OF PRESERVATION

#include <assert.h>
#include <stdio.h>

#include <engine/platform/input_data.h>
#include <engine/memory_pool.h>
#include <engine/platform/window_data.h>
#include <engine/errors.h>

#include <external/glad/glad.h>
#include <external/glfw3.h>

extern PointerTable* GameMemory;

void inputCallback(
	GLFWwindow* window,
	i32 key,
	i32 scancode,
	i32 action,
	i32 mods
);

static void framebuffer_size_callback(
	GLFWwindow *window,
	i32 width,
	i32 height
) {
	assert(window);
	assert(GameMemory);

	WindowData* windowData = GameMemory->regions[WINDOW_DATA].ptr;

	printf("window is resized from %dx%d to %dx%d\n", windowData->height, windowData->width, height, width);

    windowData->width = width;
    windowData->height = height;

    glViewport(0, 0, windowData->width, windowData->height);
}

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
) {
    assert(windowData);
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



    (*windowData) = (WindowData){
        .window = NULL,
        .height = height,
        .width = width,
        .fps = fps,
        .frametime = 1000.0f*1/fps,
        .cursorMode = cursorModeGlfw,
        .vsync = vsync,
        .resizable = resizable,
        .windowShouldClose = false,
        .clearColor = clearColor,
    };

    // if (!glfwInit()) {return LIBRARY_FAIL;}
    assert(glfwInit());

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, resizable ? GLFW_TRUE : GLFW_FALSE);

    windowData->window = glfwCreateWindow(width, height, title, NULL, NULL);
    assert(windowData->window);
    // if (!windowData->window) {
    //     glfwTerminate();
    //     return LIBRARY_FAIL;
    // }

    glfwMakeContextCurrent(windowData->window);
    glfwSetInputMode(windowData->window, GLFW_CURSOR, cursorModeGlfw);
    glfwSwapInterval(vsync);

    assert(gladLoadGLLoader((GLADloadproc) glfwGetProcAddress));
    // if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
    //     printf("Failed to initialize GLAD\n");
    //     return LIBRARY_FAIL;
    // }

    glfwGetFramebufferSize(windowData->window, &(windowData->width), &(windowData->height));
    glViewport(0, 0, windowData->width, windowData->height);
    glClearColor(windowData->clearColor.arr[0],windowData->clearColor.arr[1], windowData->clearColor.arr[2], windowData->clearColor.arr[3]);

    glfwSetFramebufferSizeCallback(windowData->window, framebuffer_size_callback);
}

void WindowShouldClose(
	WindowData* window
) {
	assert(window);
	window->windowShouldClose = true;
}

void CloseWindow() {
    glfwTerminate();
}

