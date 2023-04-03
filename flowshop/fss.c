#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    if (argc != 3) {
        printf("Usage: ./input {n} {limit}");
    }

    int n = atoi(argv[1]);
    int limit = atoi(argv[2]);

    printf("%d\n", n);

    for (int i = 0; i < n; ++i) {
        printf("%d %d %d\n", rand() % (limit+1), rand() % (limit+1), rand() % (limit+1));
    }
}