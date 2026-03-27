#include <engine/window.h>
#include <engine/memory_pool.h>
#include <platform/window.h>

#include <assert.h>
#include <stddef.h>
#include <wchar.h>

extern PointerTable* GameMemory;
WindowData* windowData = NULL;

void InitializeEngineWindow(
    i32 windowWidth,
    i32 windowHeight,
    i32 fps,
    bool vsync,
    bool resizable,
    v4 clearColor,
    str title,
    CursorMode cursorMode
) {
    // WindowData* const windowData = getRegion(WINDOW_DATA);
    assert(GameMemory);
    assert(title);
    assert(windowWidth > 0 && windowHeight > 0 && fps > 0);
    assert(windowData == NULL);

    windowData = (WindowData*)getRegion(WINDOW_DATA);
    assert(windowData);

    TimeStamp t = InitializeTimeStamp();

    (*windowData) = (WindowData){
        .window = NULL,
        .windowHeight = windowHeight,
        .windowWidth = windowWidth,
        .fps = fps,
        .frametime = CalculateFrametime(fps),
        .cursorMode = cursorMode,
        .vsync = vsync,
        .resizable = resizable,
        .windowShouldClose = false,
        .clearColor = clearColor,
        .framesElapsed = 0,
        .bootTimeStamp = t,
        .frametimeEveningTimeStamp = t,
    };

    InitializeWindow(
        windowWidth,
        windowHeight,
        vsync,
        resizable,
        clearColor,
        title,
        cursorMode
    );
}


void SetWindowToClose() {
    assert(windowData);
    windowData->windowShouldClose = true;
}
