#include <stdbool.h>
#include <stddef.h>
#include <ctype.h>
#include <stdio.h>

// TODO: Include more header files (read the manpages to find out more!)

int main(int argc, const char* argv[]) {
    if (argc < 2) {
        printf("ERROR: No arguments\n");
        return 1;
    }

    for (int i =1; i < argc; i++) {
        for (int j = 0; argv[i][j] != '\0'; j++){
            putchar(toupper(argv[i][j]));
        }
        if ( i < argc - 1) {
            putchar(',');
        }
    }
    putchar('\n');
    return 0;
}
