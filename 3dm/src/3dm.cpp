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
        printf("Usage: %s [options] file\n", argv[0]);
        printf("Options:\n  -h  heuristic (default)\n  -b  brute force\n");
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

    int set_size = 0;
    fscanf(file, "%d\n", &set_size);
    if (set_size <= 0) {
        printf("Must provide size of set\n");
        exit(EXIT_FAILURE);
    }

    std::vector<Triple> T;
    int N = 0; 

    // read the file until we reach $ or EOF

    while (!feof(file)) {
        char c = fgetc(file);
        if (c == '$') {
            break;
        }
        ungetc(c, file);

        Triple t;
        int count = fscanf(file, "%d %d %d\n", &t.x, &t.y, &t.z);

        if (count != 3) {
            printf("Expected 3 numbers but got %d\n", count);
            exit(EXIT_FAILURE);
        }

        T.push_back(t);
        ++N;
    }
    fclose(file);

    clock_t time = clock();

    std::vector<Triple> set;
    if (mode == HEURISTIC) {
        set = heuristic_3dm(set_size, T);
    } else if (mode == BRUTEFORCE) {
        set = bruteforce_3dm(set_size, T);
    }
    
    for (Triple t : set) {
        printf("(%d, %d, %d)\n", t.x, t.y, t.z);
    }
    printf("\nSize: %d\n", (int)set.size());
    printf("Runtime: %f\n", (double)(clock() - time) / CLOCKS_PER_SEC);
}