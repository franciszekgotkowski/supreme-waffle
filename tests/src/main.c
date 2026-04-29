#include <common/typedefs.h>
#include <stdio.h>

#include <tests/memory_arena_tests.h>

int main(void) {
	i32 success = 0;

    success += run_memory_arena_test();

  		printf("\n0================================0\n");
    if (success == 0) {
    	printf("All tests passed!");
    } else {
   		printf("%d test groups did not pass!");
    }
   	printf("\n0================================0\n");

    return success;
}