#include <engine/measure_time.h>
#include <engine/typedefs.h>

#include <string.h>
#include <time.h>
#include <stdbool.h>

typedef struct timespec timespec;

typedef struct timestamp_linux {
    timespec start;
    timespec stop;
}timestamp_linux;

_Static_assert(sizeof(timestamp_linux) == sizeof(timestamp), "timestamp storage too small");

inline timestamp make_stamp(bool initialization){
    timestamp_linux stamp = {};
    timestamp t = {};
    clock_gettime(CLOCK_MONOTONIC, &(stamp.start));
    memcpy(&t, &stamp, sizeof(stamp));
    return  t;
}

inline f64 elapsed_time(timestamp* ptr) {
    timestamp_linux* stamp_ptr = (timestamp_linux*)ptr;
    clock_gettime(CLOCK_MONOTONIC, &(stamp_ptr->stop));
    timespec diffspec = {
        .tv_sec = stamp_ptr->stop.tv_sec - stamp_ptr->start.tv_sec,
        .tv_nsec = stamp_ptr->stop.tv_nsec - stamp_ptr->start.tv_nsec
    };

    f64 diff = diffspec.tv_sec + (f64)(diffspec.tv_nsec/1000000000.0);

    return diff;
}


