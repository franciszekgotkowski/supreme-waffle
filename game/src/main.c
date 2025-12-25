#include <engine/print.h>
#include <engine/range.h>
#include <engine/memory.h>
#include <stdio.h>

int main(int argc, char *argv[]) {

    u64 alloc_size = 5*GB;

    i32* mem = mem_alloc(alloc_size);

    for range(i, alloc_size/4) {
        mem[i] = i;
    }

    for range(i, argc){
        printf("%s\n", argv[i]);
    }

    loop();

    mem_dealloc(mem, alloc_size);
}
