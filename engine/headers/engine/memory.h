#pragma once

#include <engine/typedefs.h>

#define KB (u64)1024
#define MB (u64)KB*1024
#define GB (u64)MB*1024

#define page 64*KB

// allocates memory via mmap of the size given size size will be rounded to multiples of 4KB
void* mem_alloc(u64 size);
void mem_dealloc(void* ptr, u64 size);

