#include <assert.h>
#include <engine/print.h>
#include <engine/range.h>
#include <engine/memory.h>
#include <stdio.h>

int main(int argc, char *argv[]) {

    u64 alloc_size = 500*MB;

    i32* mem = mem_alloc(alloc_size);
    assert(mem);

    for range(i, alloc_size/4) {
        mem[i] = i;
    }

    for range(i, argc){
        printf("%s\n", argv[i]);
    }

    loop();

    mem_dealloc(mem, alloc_size);
}
