#pragma once

typedef enum {
    OK,
    LOGIC_ERROR,
    OUT_OF_RANGE,
    OUT_OF_MEMORY,
    NULL_POINTER,
    SYSCALL_FAIL,
    LIBRARY_FAIL,
    LOCKED,

    AMOUNT_OF_ERRORS
} Error ;
