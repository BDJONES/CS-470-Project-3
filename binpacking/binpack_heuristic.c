#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Compare function from includehelp
int compare(const void* numA, const void* numB)
{
    const int* num1 = (const int*)numA;
    const int* num2 = (const int*)numB;

    if (*num1 > *num2) {
        return 1;
    }
    else {
        if (*num1 == *num2)
            return 0;
        else
            return -1;
    }
}

void printBins(int *bins, int num_bins){
    int i;
    for (i = 0; i < num_bins; i++){
        printf("%d", bins[i]);
        if(i != num_bins - 1){
            printf(" | ");
        }
    }
    printf("\n");
}

int checkOccupied(int *bins, int num_bins){
    int occupied = 0;
    int i = 0;
    for(i = 0; i < num_bins; i++){
        if (bins[i] > 0){
            occupied++;
        }
    }
    return occupied;
}

int main(int argc, char **argv){
    if (argc != 2) {
        printf("Usage: ./binpack_brute {filename}\n");
        exit(EXIT_FAILURE);
    }

    FILE* file = fopen(argv[1], "r");
    char *line[128];
    fgets(line, 128, file);
    int bin_cap = atoi(line);
    printf("Bin Capacity: %d\n", bin_cap);
    fgets(line, INT8_MAX, file);
    int num_weights = atoi(line);
    printf("# Weights: %d\n", num_weights);

    int weights[num_weights];

    int i = 0;
    while(fgets(line, INT8_MAX, file) != NULL){
        if (i >= num_weights){
            printf("Expected %d weights, file contains at least %d.\n", num_weights, i + 1);
            exit(EXIT_FAILURE);
        }
        weights[i] = atoi(line);
        i++;
    }

    int sum = 0;
    for (i = 0; i < num_weights; i++){
        printf("%d\n", weights[i]);
        sum += weights[i];
    }
    if (sum <= bin_cap){
        printf("Optimal Solution: 1");
        return 1;
    }

    // First Fit
    int max_bins = num_weights;
    int bins[max_bins];
    for (i = 0; i < max_bins; i++){
        bins[i] = 0;
    }
    // printBins(bins, max_bins);
    int optimal = max_bins + 1;

    clock_t t;
    t = clock();
    int j;
    
    for(i = 0; i < num_weights; i++){
        for(j = 0; j < num_weights; j++){
            if(bins[j] + weights[i] < bin_cap){
                bins[j] += weights[i];
                break;
            }
            if(j == num_weights - 1){
                optimal = -1;
            }
        }
    }
    if(optimal == -1){
        printf("No Solution.\n");
        return -1;
    }
    optimal = checkOccupied(bins, num_weights);
    printf("Optimal Solution: %d\n", optimal);
    return optimal;
}