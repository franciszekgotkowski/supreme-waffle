#include <string.h>
#include <engine/measure_time.h>
#include <engine/typedefs.h>

#include <time.h>

typedef struct timespec timespec;

typedef struct {
    timespec then;
    timespec now;
}lin_stamp;

_Static_assert(sizeof(lin_stamp) == sizeof(timestamp), "lin_stamp has different size from timestamp");

timestamp make_stamp() {
    lin_stamp stamp = {};

    clock_gettime(CLOCK_MONOTONIC, &stamp.now);
    timestamp t;
    memcpy(&t, &stamp, sizeof(t));
    return t;
}

static inline f64 time_diff(timespec then, timespec now) {
    f64 timeThen = then.tv_sec*1000.0 + then.tv_nsec/1000000.0;
    f64 timeNow = now.tv_sec*1000.0 + now.tv_nsec/1000000.0;
    return timeNow - timeThen;
}

f64 elapsed_time(timestamp* ptr) {
    lin_stamp* stamp = (lin_stamp*)ptr;

    stamp->then = stamp->now;
    clock_gettime(CLOCK_MONOTONIC, &stamp->now);

    return time_diff(stamp->then, stamp->now);
}

f64 read_elapsed_time(timestamp* ptr) {
    lin_stamp* stamp = (lin_stamp*)ptr;
    return time_diff(stamp->then, stamp->now);
}

void wait_for_frame(timestamp* ptr, f64 fps) {
    lin_stamp* stamp = (lin_stamp*)ptr;

    u64 timePerFrame = 1000000000/fps;

    timespec target = {
        .tv_sec = (timePerFrame/1000000000),
        .tv_nsec = (timePerFrame%1000000000)
    };

    timespec timediff = {
        .tv_sec = stamp->now.tv_sec - stamp->then.tv_sec,
        .tv_nsec = stamp->now.tv_nsec - stamp->then.tv_nsec,
    };

    timespec timeToWait = {
        .tv_sec = target.tv_sec - timediff.tv_sec,
        .tv_nsec = target.tv_nsec - timediff.tv_nsec
    };

    nanosleep(&timeToWait, NULL);
}
