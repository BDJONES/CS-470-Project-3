#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int main(int argc, char** argv) {
    if (argc != 3) {
        printf("Usage: ./input n limit file\n");
        exit(EXIT_FAILURE);
    }

    int n = atoi(argv[1]);
    int limit = atoi(argv[2]);
    int m = n * 3;

    int partition[m];

    int remaining = n * limit;
    int min = 1;
    int max = limit - 1;

    if (remaining < m) {
        fprintf(stderr, "Failed to find partition.");
        exit(EXIT_FAILURE);
    }

    FILE* file = fopen(argv[3], "w");
    if (file == NULL) {
        fprintf(stderr, "Failed to open file '%s'\n", argv[3]);
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < m - 1; ++i) {
        if ((float)(remaining - min) / max > m - i - 1) {
            min = remaining - max * (m - i - 1);
        } else if ((float)(remaining - max) / min < m - i - 1) {
            max = remaining - min * (m - i - 1);
        }

        srand(time(NULL) + i);
        partition[i] = rand() % (max - min + 1) + min;
        remaining -= partition[i];
    }
    partition[m - 1] = remaining;

    fprintf(file, "%d %d\n", n, limit);
    for (int i = 0; i < m; ++i) {
        fprintf(file, "%d\n", partition[i]);
    }
}