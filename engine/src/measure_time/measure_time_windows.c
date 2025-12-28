#include <engine/measure_time.h>
#include <engine/typedefs.h>
#include <time.h>
#include <windows.h>
#include <assert.h>
#include <stdio.h>

timestamp make_stamp(timestamp* ptr) {
    /*
    timestamp:
    [8bit] - frequency
    [8bit] - start
    [8bit] - stop
    [8bit] - filler
    */

    timestamp t = {0};

    LARGE_INTEGER* freq = (LARGE_INTEGER*)&t;
    LARGE_INTEGER* laststamp = freq+1;

    if (ptr == NULL) {
        QueryPerformanceFrequency(freq);
    } else {
        LARGE_INTEGER* tfreq = (LARGE_INTEGER*)&ptr;
        *freq = *tfreq;
    }

    QueryPerformanceCounter(laststamp);
    return t;
}

f64 time_elapsed(timestamp *ptr) {
    assert(ptr);

    LARGE_INTEGER* freq = (LARGE_INTEGER*)&ptr;
    LARGE_INTEGER* laststamp = freq+1;

    LARGE_INTEGER now;
    QueryPerformanceCounter(&now);

    f64 tickDiff = (f64)(laststamp->QuadPart - now.QuadPart);
    f64 frequency = (f64)(freq->QuadPart);

    f64 timeDiff = tickDiff / frequency;
    laststamp->QuadPart = now.QuadPart;
    printf("time elapsed: %fms\n", timeDiff*1000.0);
    return timeDiff;
}

void wait_for_frame(timestamp* ptr, f64 fps) {
    f64 frametime = 1000.0 / fps; // ms
    f64 elapsed = 1000.0 * time_elapsed(ptr);

    f64 timeToWait = frametime - elapsed;
    if (timeToWait < 0) { timeToWait = 0.0; }
    Sleep((u64)timeToWait);
}