#include <assert.h>
#include <bemapiset.h>
#include <external/glad/glad.h>
#include <external/glfw3.h>

#include <engine/typedefs.h>
#include <engine/measure_time.h>

#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <windows.h>

#include <winnt.h>

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
    glfwSwapInterval(0);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        printf("Failed to initialize GLAD\n");
        return -1;
    }

    glfwGetFramebufferSize(window, &windowWidth, &windowHeight);
    glViewport(0, 0, windowWidth, windowHeight);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    // printf("sizeof LARGE_INTEGER = %llu\n", sizeof(LARGE_INTEGER));
    // timestamp t = make_stamp(NULL);
    LARGE_INTEGER lastTime, nowTime, freq;
    QueryPerformanceCounter(&lastTime);
    QueryPerformanceFrequency(&freq);
    f64 fulltime = 0.0;
    i32 frameNum = 0;
    while (!glfwWindowShouldClose(window)) {
        checkExit(window);

        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);

        glfwPollEvents();
        // printf("time elapsed: %fms\n", 1000 * time_elapsed(&t));
        // wait_for_frame(&t, 60.0);
        // t = make_stamp(&t);
        QueryPerformanceCounter(&nowTime);
        f64 tickDiff = (f64)(nowTime.QuadPart - lastTime.QuadPart);
        f64 timeDiff = (f64)(tickDiff/(f64)freq.QuadPart);
        fulltime += timeDiff;
        frameNum += 1;
        printf("frame: %d\ttime elapsed %f\tfulltime: %f\n", frameNum, timeDiff*1000.0, fulltime);
        lastTime = nowTime;
        assert(fulltime < 5.0);
        f64 sleepMs = 1000.0/60.0;
        sleepMs -= timeDiff*1000.0;
        if (sleepMs < 0) { sleepMs = 0.0; }
        Sleep(sleepMs);

    }

    glfwTerminate();
    return 0;
}
