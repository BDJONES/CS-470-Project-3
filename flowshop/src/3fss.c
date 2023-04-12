#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "3fss.h"

typedef enum {
    HEURISTIC,
    BRUTEFORCE
} Mode;

int main (int argc, char** argv) {
    Mode mode;
    FILE* file = NULL;

    if (argc < 2 || argc > 3) {
        printf("Usage: %s [option] file\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if (argc == 2) {
        mode = HEURISTIC;
        (file = fopen(argv[1], "r")) || fprintf(stderr, "Could not open file '%s'\n", argv[1]);
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
        (file = fopen(argv[2], "r")) || fprintf(stderr, "Could not open file '%s'\n", argv[2]);
    }

    if (!file) exit(EXIT_FAILURE);

    int n;
    fscanf(file, "%d\n", &n);
    if (n <= 0) {
        fprintf(stderr, "Must provide number of jobs\n");
        exit(EXIT_FAILURE);
    }

    job jobs[n];
    for (int i = 0; i < n; ++i) {
        if (feof(file)) {
            fprintf(stderr, "Expected %d jobs but got %d\n", n, i);
            exit(EXIT_FAILURE);
        }

        jobs[i].id = i + 1;
        int count = fscanf(file, "%d %d %d\n", 
            jobs[i].d, jobs[i].d + 1, jobs[i].d + 2);

        if (count != 3) {
            fprintf(stderr, "Expected 3 operations but got %d\n", count);
            exit(EXIT_FAILURE);
        }
    }

    clock_t time = clock();

    int sequence[n];
    int makespan;

    if (mode == HEURISTIC) {
        makespan = heuristic_3fss(jobs, n, sequence);
    } else if (mode == BRUTEFORCE) {
        makespan = bruteforce_3fss(jobs, n, sequence);
    }

    time = clock() - time;

    printf("makespan: %d\n", makespan);
    printf("sequence:");
    for (int i = 0; i < n; ++i) {
        printf(" %d", sequence[i]);
    }
    printf("\nruntime: %fs\n", ((float)time)/CLOCKS_PER_SEC);

    fclose(file);
}