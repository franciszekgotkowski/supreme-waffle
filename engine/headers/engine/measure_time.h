#pragma once

#include <engine/typedefs.h>

typedef struct {
    u64 arr[4];
} timestamp;

timestamp make_stamp(timestamp* ptr);
f64 time_elapsed(timestamp* ptr);
void wait_for_frame(timestamp* ptr, f64 fps);

