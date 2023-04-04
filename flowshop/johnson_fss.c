#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct job {
    int id;
    int d[3];   // duration of each operation
    int start[3];
} job;

int min(int a, int b) {
    return a < b ? a : b;
}

int max(int a, int b) {
    return a > b ? a : b;
}

int compare(const void* i, const void* j) {
    job a = *(job*)i;
    job b = *(job*)j;

    return min(a.d[0] + a.d[1], b.d[1] + b.d[2]) - 
           min(b.d[0] + b.d[1], a.d[1] + a.d[2]);
}

int main (int argc, char** argv) {
    if (argc != 2) {
        printf("Usage: ./johnson {filename}\n");
        exit(EXIT_FAILURE);
    }

    FILE* file = fopen(argv[1], "r");
    if (file == NULL) {
        printf("Could not open file '%s'\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    int n;
    fscanf(file, "%d\n", &n);
    if (n <= 0) {
        printf("Must provide number of jobs\n");
        exit(EXIT_FAILURE);
    }

    job jobs[n];
    for (int i = 0; i < n; ++i) {
        if (feof(file)) {
            printf("Expected %d jobs but got %d\n", n, i);
            exit(EXIT_FAILURE);
        }

        jobs[i].id = i + 1;
        int count = fscanf(file, "%d %d %d\n", 
            jobs[i].d, jobs[i].d + 1, jobs[i].d + 2);

        if (count != 3) {
            printf("Expected 3 operations but got %d\n", count);
            exit(EXIT_FAILURE);
        }
    }

    clock_t time = clock();

    qsort(jobs, n, sizeof(job), compare);
    jobs[0].start[0] = 0;
    jobs[0].start[1] = jobs[0].d[0];
    jobs[0].start[2] = jobs[0].start[1] + jobs[0].d[1];

    for (int i = 1; i < n; ++i) {
        jobs[i].start[0] = jobs[i - 1].start[0] + jobs[i - 1].d[0];
        jobs[i].start[1] = max(jobs[i].start[0] + jobs[i].d[0], 
                               jobs[i - 1].start[1] + jobs[i - 1].d[1]);
        jobs[i].start[2] = max(jobs[i].start[1] + jobs[i].d[1], 
                               jobs[i - 1].start[2] + jobs[i - 1].d[2]);
    }

    int length1 = jobs[n - 1].start[0] + jobs[n - 1].d[0];
    int length2 = jobs[n - 1].start[1] + jobs[n - 1].d[1];
    int length3 = jobs[n - 1].start[2] + jobs[n - 1].d[2];

    int makespan = max(length1, max(length2, length3));

    time = clock() - time;
    
    char m[3][makespan];
    for (int i = 0; i < makespan; ++i) {
        m[0][i] = m[1][i] = m[2][i] = -1;
    }
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int k = jobs[j].start[i]; k < jobs[j].start[i] + jobs[j].d[i]; ++k) {
                m[i][k] = jobs[j].id;
            }
        }
    }

    int numDigits = floor(log10(abs(n - 1))) + 1;
    for (int j = 0; j < makespan; ++j) {
        for (int i = 0; i < 3; ++i) {
            if (m[i][j] == -1) {
                for (int k = 0; k < numDigits + 2; ++k) {
                    printf("-");
                }
            } else {
                printf("[%0*d]", numDigits, m[i][j]);
            }
            printf(" ");
        }
        printf("\n");
    }

    printf("\nlength: %d\n", makespan);
    printf("sequence:");
    for (int i = 0; i < n; ++i) {
        printf(" %d", jobs[i].id);
    }
    printf("\nruntime: %fs\n", ((float)time)/CLOCKS_PER_SEC);

    fclose(file);
}