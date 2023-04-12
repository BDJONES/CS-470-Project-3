#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char** argv) {
    if (argc != 3) {
        printf("Usage: %s {n} {limit}", argv[0]);
    }

    int n = atoi(argv[1]);
    int limit = atoi(argv[2]);

    printf("%d\n", n);

    srand(time(NULL));
    for (int i = 0; i < n; ++i) {
        printf("%d %d %d\n", rand() % (limit+1), rand() % (limit+1), rand() % (limit+1));
    }
}