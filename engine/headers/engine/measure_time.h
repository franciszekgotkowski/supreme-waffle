#pragma once

#include <engine/typedefs.h>

typedef struct {
    u8 arr[32];
} timestamp;

// creates timestamp to later reference
timestamp make_stamp();

// replaces old time and creates new timestamp to reference to. also returns time in ms that elapsed between now and last use of function
f64 elapsed_time(timestamp* ptr);

// reads time between last elapsed_time and elapsed_time before the last one (the same value as return value last elapsed_time)
f64 read_elapsed_time(timestamp* ptr);

// waits some amounts of miliseconds to fill in time to maintain the desired framerate. May be a little bit inacurate.
void wait_for_frame(timestamp* ptr, f64 fps);

