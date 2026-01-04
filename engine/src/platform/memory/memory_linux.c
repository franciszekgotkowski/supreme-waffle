#include <stdio.h>
#include <sys/mman.h>

#include <engine/memory_allocations.h>
#include <engine/typedefs.h>
#include <stddef.h>
#include <assert.h>

inline void* mem_alloc(u64 size) {
    if (size % 4*KB != 0 || size < 4*KB) {
        printf("extending size to fill entire page\n");
        u64 oldsize = size;
        size /= 4*KB;
        size *= 4*KB;
        size += 4*KB;
        printf("mapping %ld instead of %ld\n", size, oldsize);
    }
    void* ptr = mmap((void*)BASE_POOL_ADDRESS, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

    assert(ptr == (void*)BASE_POOL_ADDRESS);
    if (ptr != (void*)BASE_POOL_ADDRESS) {
    	return NULL;
    }

    return ptr;
}

inline void mem_dealloc(void* ptr, u64 size) {
    assert(ptr != NULL);
    munmap(ptr, size);
}

