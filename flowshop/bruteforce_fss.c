#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// source: https://www.quickperm.org/
int quickperm(int* a, int* p, int i, int n) {
    if (i >= n) i = 1;  // loop back to the first permutation

    --p[i];
    int j = i % 2 == 1 ? p[i] : 0;
    
    // swap a[j], a[i]
    int temp = a[j];
    a[j] = a[i];
    a[i] = temp;
    
    i = 1;
    while (p[i] == 0) {
        p[i] = i;
        ++i;
    }

    return i;
}

int max(int a, int b) {
    return a > b ? a : b;
}

int main (int argc, char** argv) {
    if (argc != 2) {
        printf("Usage: ./bruteforce {filename}\n");
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

    int T[n][3];
    for (int i = 0; i < n; ++i) {
        if (feof(file)) {
            printf("Expected %d jobs but got %d\n", n, i);
            exit(EXIT_FAILURE);
        }

        int count = fscanf(file, "%d %d %d\n", T[i], T[i] + 1, T[i] + 2);

        if (count != 3) {
            printf("Expected 3 operations but got %d\n", count);
            exit(EXIT_FAILURE);
        }
    }

    int p[n + 1], o[n], o_min[n];


    for (int i = 0; i < n; ++i) {
        p[i] = o[i] = o_min[i] = i;
    }
    p[n] = n;

    int S[n][3];
    int S_min[n][3];

    int min_length = __INT_MAX__;

    clock_t time = clock();

    for (int j = 1; j < n;) {
        S[o[0]][0] = 0;
        S[o[0]][1] = T[o[0]][0];
        S[o[0]][2] = S[o[0]][1] + T[o[0]][1];
        for (int i = 1; i < n; ++i) {
            S[o[i]][0] = S[o[i-1]][0] + T[o[i-1]][0];
            S[o[i]][1] = max(S[o[i]][0] + T[o[i]][0], S[o[i-1]][1] + T[o[i-1]][1]);
            S[o[i]][2] = max(S[o[i]][1] + T[o[i]][1], S[o[i-1]][2] + T[o[i-1]][2]);
        }
        int length1 = S[o[n-1]][0] + T[o[n-1]][0];
        int length2 = S[o[n-1]][1] + T[o[n-1]][2];
        int length3 = S[o[n-1]][2] + T[o[n-1]][2];

        int length = max(length1, max(length2, length3));
        if (length < min_length) {
            min_length = length;
            memcpy(o_min, o, n * sizeof(int));
            memcpy(S_min, S, n * 3 * sizeof(int));
        }

        j = quickperm(o, p, j, n);
    }

    time = clock() - time;
    
    char m[3][min_length];
    for (int i = 0; i < min_length; ++i) {
        m[0][i] = m[1][i] = m[2][i] = -1;
    }
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int k = S_min[j][i]; k < S_min[j][i] + T[j][i]; ++k) {
                m[i][k] = j;
            }
        }
    }

    int numDigits = floor(log10(abs(n - 1))) + 1;
    for (int j = 0; j < min_length; ++j) {
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

    printf("\nlength: %d\n", min_length);
    printf("sequence:");
    for (int i = 0; i < n; ++i) {
        printf(" %d", o_min[i] + 1);
    }
    printf("\nruntime: %fs\n", ((float)time)/CLOCKS_PER_SEC);

    fclose(file);
}