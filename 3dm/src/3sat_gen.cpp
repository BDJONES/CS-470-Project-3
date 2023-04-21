#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int main(int argc, char** argv) {
    if (argc != 4) {
        printf("Usage: %s n limit file", argv[0]);
    }

    FILE* file = fopen(argv[3], "w");
    if (!file) {
        printf("Could not open file '%s'\n", argv[3]);
        exit(EXIT_FAILURE);
    }

    int n = atoi(argv[1]);
    int limit = atoi(argv[2]);

    srand(time(NULL));
    for (int i = 0; i < n; ++i) {
        fprintf(file, "%d %d %d\n", 
            (rand() % limit + 1) * (int)pow(-1, (rand() % 2)),
            (rand() % limit + 1) * (int)pow(-1, (rand() % 2)), 
            (rand() % limit + 1) * (int)pow(-1, (rand() % 2)));
    }
    fprintf(file, "$\n");
}