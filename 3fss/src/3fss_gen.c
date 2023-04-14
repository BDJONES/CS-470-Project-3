#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char** argv) {
    if (argc != 4) {
        printf("Usage: %s [n] [limit] [file]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int n = atoi(argv[1]);
    int limit = atoi(argv[2]);

    FILE* file = fopen(argv[3], "w");

    srand(time(NULL));
    for (int i = 0; i < n; ++i) {
        fprintf(file, "%d %d %d\n", rand() % limit + 1, rand() % limit + 1, rand() % limit + 1);
    }

    fprintf(file, "$\n");
}