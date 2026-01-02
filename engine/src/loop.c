#include <external/glad/glad.h>
#include <external/glfw3.h>

#include <engine/typedefs.h>
#include <engine/measure_time.h>

#include <stdio.h>
#include <stdbool.h>
#include <time.h>

i32 windowWidth = 800;
i32 windowHeight = 600;

extern

void checkExit(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

int loop() {
    if (!glfwInit()) {
        printf("Failed to initialize flgw!\n");
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window) {
        printf("Failed to initialize window!\n");
        glfwTerminate();
        return -1;
    }

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        printf("Failed to initialize GLAD\n");
        return -1;
    }

    glfwGetFramebufferSize(window, &windowWidth, &windowHeight);
    glViewport(0, 0, windowWidth, windowHeight);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    timestamp stamp = make_stamp();
    u32 frame = 0;
    while (!glfwWindowShouldClose(window)) {
        checkExit(window);

        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
        glfwPollEvents();
        printf("frame: %d\t timediff: %fms\n", ++frame, elapsed_time(&stamp));
    }

    glfwTerminate();
    return 0;
}
