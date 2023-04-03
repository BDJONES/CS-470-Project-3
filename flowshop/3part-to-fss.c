#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    FILE* file = fopen(argv[1], "r");

    int n, limit;
    fscanf(file, "%d %d\n", &n, &limit);

    int a[3 * n];
    for (int i = 0; i < 3 *n; ++i) {
        fscanf(file, "%d\n", a + i);
        a[i] += limit;
    }
    limit *= 4;

    printf("%d\n", 4 * n + 1);
    printf("0 %d %d\n", limit, limit * 2);
    for (int i = 1; i < n; ++i) {
        printf("%d %d %d\n", limit * 2, limit, limit * 2);
    }
    printf("%d %d 0\n", limit * 2, limit);

    for (int i = 0; i < 3 * n; ++i) {
        printf("0 %d 0\n", a[i]);
    }
}