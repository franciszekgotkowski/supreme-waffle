#include <assert.h>
#include <stdio.h>

#include <engine/window_data.h>
#include <engine/errors.h>

Error InitializeWindow(PointerTable* table, i32 width, i32 height, i32 fps, bool vsync, v4 clearColor, str title, i32 cursorMode) {
    assert(table);
    assert(title);
    assert(width > 0 && height > 0 && fps > 0);

    WindowData* windowData = table->regions[WINDOW_DATA].ptr;
    assert(windowData);


    (*windowData) = (WindowData){
        .window = NULL,
        .height = height,
        .width = width,
        .fps = fps,
        .cursorMode = cursorMode,
        .vsync = vsync,
        .clearColor = clearColor,
    };

    if (!glfwInit()) {return LIBRARY_FAIL;}
    assert(glfwInit());

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    windowData->window = glfwCreateWindow(width, height, title, NULL, NULL);
    assert(windowData->window);
    if (!windowData->window) {
        glfwTerminate();
        return LIBRARY_FAIL;
    }

    glfwMakeContextCurrent(windowData->window);
    glfwSetInputMode(windowData->window, GLFW_CURSOR, cursorMode);
    glfwSwapInterval(vsync);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        printf("Failed to initialize GLAD\n");
        return LIBRARY_FAIL;
    }

    glfwGetFramebufferSize(windowData->window, &(windowData->width), &(windowData->height));
    glViewport(0, 0, windowData->width, windowData->height);
    glClearColor(windowData->clearColor.arr[0],windowData->clearColor.arr[1], windowData->clearColor.arr[2], windowData->clearColor.arr[3]);

    return OK;
}

Error CloseWindow(PointerTable* table) {
    assert(table);
    if (!table) {
        return NULL_POINTER;
    }

    glfwTerminate();
    return OK;
}

void GameLoop(PointerTable* table) {
    WindowData* windowData = table->regions[WINDOW_DATA].ptr;

    while (!glfwWindowShouldClose(windowData->window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(windowData->window);
        glfwPollEvents();
    }
}
