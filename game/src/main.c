#include <engine/print.h>
#include <engine/range.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    print(69);

    for range(i, argc){
        printf("%s\n", argv[i]);
    }

    loop();
}
