#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "3dm.h"

typedef enum {
    HEURISTIC,
    BRUTEFORCE
} Mode;

int main (int argc, char** argv) {
    Mode mode;
    FILE* file;

    if (argc < 2 || argc > 3) {
        printf("Usage: %s [FLAG] FILE\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if (argc == 2) {
        mode = HEURISTIC;
        (file = fopen(argv[1], "r")) || printf("Could not open file '%s'\n", argv[1]);
    }

    if (argc == 3) {
        if (strcmp(argv[1], "-h") == 0) {
            mode = HEURISTIC;
        } else if (strcmp(argv[1], "-b") == 0) {
            mode = BRUTEFORCE;
        } else {
            printf("Invalid option '%s'\n", argv[1]);
            exit(EXIT_FAILURE);
        }
        (file = fopen(argv[2], "r")) || printf("Could not open file '%s'\n", argv[2]);
    }

    if (!file) {
        exit(EXIT_FAILURE);
    }

    int N;
    fscanf(file, "%d\n", &N);
    if (N <= 0) {
        printf("Must provide number of triples\n");
        exit(EXIT_FAILURE);
    }

    std::vector<Triple> T(N);
    int M = 0;

    for (int i = 0; i < N; ++i) {
        if (feof(file)) {
            printf("Expected %d triples but got %d\n", N, i);
            exit(EXIT_FAILURE);
        }

        int count = fscanf(file, "%d %d %d\n", &T[i].x, &T[i].y, &T[i].z);

        if (count != 3) {
            printf("Expected 3 integers but got %d\n", count);
            exit(EXIT_FAILURE);
        }

        M = std::max(M, std::max(T[i].x, std::max(T[i].y, T[i].z)));
    }
    fclose(file);

    clock_t time = clock();

    std::vector<Triple> set;
    if (mode == HEURISTIC) {
        set = heuristic_3dm(T);
    } else if (mode == BRUTEFORCE) {
        set = bruteforce_3dm(T);
    }
    
    for (Triple t : set) {
        printf("(%d, %d, %d)\n", t.x, t.y, t.z);
    }
    printf("\nSize: %d\n", (int)set.size());
    printf("Runtime: %f\n", (double)(clock() - time) / CLOCKS_PER_SEC);
}