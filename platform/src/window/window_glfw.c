#include <assert.h>
#include <stdio.h>

#include <export/platform/window.h>

#include <common/typedefs.h>

#include <external/glad/glad.h>
#include <external/glfw3.h>


extern WindowData* windowData;

static void framebuffer_size_callback(
	GLFWwindow *window,
	i32 width,
	i32 height
) {
	assert(window);
	assert(windowData);

	printf("window is resized from %dx%d to %dx%d\n", windowData->windowHeight, windowData->windowWidth, height, width);

    windowData->windowWidth = width;
    windowData->windowHeight = height;

    glViewport(0, 0, windowData->windowWidth, windowData->windowHeight);
}

static inline void window_should_close_callback(
	GLFWwindow* window
) {
	assert(window);
	assert(windowData);
	windowData->windowShouldClose = true;
}

void InitializeWindow(
	i32 windowWidth,
	i32 windowHeight,
	bool vsync,
	bool resizable,
	v4 clearColor,
	str title,
	CursorMode cursorMode
) {
	// assert(windowData == NULL);
	// WindowData* const windowData = getRegion(WINDOW_DATA);
	assert(windowData);
    assert(title);
    assert(windowWidth > 0 && windowHeight > 0);

	// GLFWwindow* windowPtr = windowData->window;

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

    assert(glfwInit());

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, resizable ? GLFW_TRUE : GLFW_FALSE);

    windowData->window = glfwCreateWindow(windowWidth, windowHeight, title, NULL, NULL);

    glfwMakeContextCurrent(windowData->window);
    glfwSetInputMode(windowData->window, GLFW_CURSOR, cursorModeGlfw);

    glfwSwapInterval(vsync);

    assert(gladLoadGLLoader((GLADloadproc) glfwGetProcAddress));

    glfwGetFramebufferSize(windowData->window, &windowWidth, &windowHeight);
    glViewport(0, 0, windowWidth, windowHeight);
    glClearColor(clearColor.arr[0],clearColor.arr[1], clearColor.arr[2], clearColor.arr[3]);

    glfwSetFramebufferSizeCallback(windowData->window, framebuffer_size_callback);
    glfwSetWindowCloseCallback(windowData->window, window_should_close_callback);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glfwPollEvents();
}

void CloseWindow() {
    glfwTerminate();
}

