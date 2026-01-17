#include <stdio.h>

#include <bdf_converter/string_utils.h>
#include <bdf_converter/range.h>

str pathToFonts = "../../../assets/fonts/prebaked/";
str pathToWriteFiles = "../../../assets/fonts/baked/";

int main(int argc, char* argv[]) {

    printf("args: \n");
    for range(i, argc)  {
        printf("\t%s\t dlugosc: %d\n", argv[i], wordLength(argv[i]));
    }


}
