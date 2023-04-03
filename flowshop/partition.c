#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int partition_integer(int n, int k, int a, int b, int *result) {
    if (k * a > n || k * b < n) {
        return -1; // Not possible to partition n into k numbers between a and b.
    }

    int remaining = n;
    for (int i = 0; i < k - 1; i++) {
        int min_val = a;
        int max_val = remaining - (k - i - 1) * a;

        if (max_val > b) {
            max_val = b;
        }

        result[i] = min_val + rand() % (max_val - min_val + 1);
        remaining -= result[i];
    }

    result[k - 1] = remaining;

    return 0;
}

int main() {
    int n, k, a, b;
    printf("Enter n, k, a, b: ");
    scanf("%d%d%d%d", &n, &k, &a, &b);

    int *result = (int *)malloc(k * sizeof(int));
    srand(time(NULL));

    if (partition_integer(n, k, a, b, result) == -1) {
        printf("It's not possible to partition %d into %d numbers between %d and %d.\n", n, k, a, b);
    } else {
        printf("Partitioned integers: ");
        for (int i = 0; i < k; i++) {
            printf("%d ", result[i]);
        }
        printf("\n");
    }

    free(result);
    return 0;
}
