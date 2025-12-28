#include <engine/measure_time.h>
#include <engine/typedefs.h>
#include <windows.h>

timestamp make_stamp(timestamp* ptr) {
    /*
    timestamp:
    [8bit] - frequency
    [8bit] - start
    [8bit] - stop
    [8bit] - filler
    */

    timestamp t = {0};
    u64 *val = (u64 *) &t;
    if (!ptr) {
        QueryPerformanceFrequency((LARGE_INTEGER *) val);
    } else {
        t.arr[0] = ptr->arr[0];
    }
    QueryPerformanceCounter((LARGE_INTEGER *) (val + 1));
    return t;
}

f64 time_elapsed(timestamp *ptr) {
    u64 *val = (u64 *) ptr;
    QueryPerformanceCounter((LARGE_INTEGER *) (val + 2));
    LARGE_INTEGER freq, start, end;
    memcpy(&freq, (LARGE_INTEGER *) val, sizeof(LARGE_INTEGER));
    memcpy(&start, (LARGE_INTEGER *) (val + 1), sizeof(LARGE_INTEGER));
    memcpy(&end, (LARGE_INTEGER *) (val + 2), sizeof(LARGE_INTEGER));
    double elapsed =
            (double) (end.QuadPart - start.QuadPart) /
            (double) freq.QuadPart;
    return elapsed;
}

void wait_for_frame(timestamp* ptr, f64 fps) {
    f64 target = 1.0 / fps;
    double dt = time_elapsed(ptr);
    double remaining = target - dt;
    if (remaining > 0.0) {
        Sleep((DWORD)(remaining * 1000.0));
    }
}