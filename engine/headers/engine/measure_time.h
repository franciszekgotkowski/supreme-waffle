#pragma once

#include <engine/typedefs.h>

typedef struct {
    u8 arr[32];
} timestamp;

timestamp make_stamp();
f64 elapsed_time(timestamp* ptr);
f64 read_elapsed_time(timestamp* ptr);
void wait_for_frame(timestamp* ptr, f64 fps);

