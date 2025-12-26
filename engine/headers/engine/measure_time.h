#pragma once

#include <engine/typedefs.h>

typedef struct {
    u8 arr[32];
} timestamp;

timestamp make_stamp();
f64 time_elapsed(timestamp* ptr);


