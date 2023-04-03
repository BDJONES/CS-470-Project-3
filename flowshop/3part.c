#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int main(int argc, char** argv) {
    if (argc != 3) {
        printf("Usage: ./input {n} {limit}");
    }

    int n = atoi(argv[1]);
    int limit = atoi(argv[2]);
    int m = n * 3;

    int partition[m];

    int remaining = n * limit;
    int min = 1;
    int max = limit - 1;

    if (remaining < m) {
        fprintf(stderr, "No partition possible.");
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

    printf("%d %d\n", n, limit);
    for (int i = 0; i < m; ++i) {
        printf("%d\n", partition[i]);
    }
}