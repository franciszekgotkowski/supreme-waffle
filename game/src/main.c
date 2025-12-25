#include "../../engine/headers/internal/print.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
    print(67);

    for (int i = 0; i < argc; i++) {
        printf("%s\n", argv[i]);
    }
}
