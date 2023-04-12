#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    if (argc != 3) {
        printf("Usage: %s file_3part file_3fss\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    FILE* from = fopen(argv[1], "r");
    FILE* to = fopen(argv[2], "w");

    if (from == NULL) {
        fprintf(stderr, "Failed to open file '%s'\n", argv[1]);
        exit(EXIT_FAILURE);
    }
    if (to == NULL) {
        fprintf(stderr, "Failed to open file '%s'\n", argv[2]);
        exit(EXIT_FAILURE);
    }

    int n, limit;
    fscanf(from, "%d %d\n", &n, &limit);

    int a[3 * n];
    for (int i = 0; i < 3 *n; ++i) {
        fscanf(from, "%d\n", a + i);
        a[i] += limit;
    }
    limit *= 4;

    fprintf(to, "%d\n", 4 * n + 1);
    fprintf(to, "0 %d %d\n", limit, limit * 2);
    for (int i = 1; i < n; ++i) {
        fprintf("%d %d %d\n", limit * 2, limit, limit * 2);
    }
    fprintf(to, "%d %d 0\n", limit * 2, limit);

    for (int i = 0; i < 3 * n; ++i) {
        fprintf(to, "0 %d 0\n", a[i]);
    }
}