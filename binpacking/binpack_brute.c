#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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

void updateBins(int *bins, int *store, int num_bins){
    int i;
    for (i = 0; i < num_bins; i++){
        store[i] = bins[i];
    }
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

int weightRecurse(int optimal, int bin_capacity, int num_weights, int *weights, int *bins, int idx){
    int i;
    int this_weight = weights[idx];
    int this_path_best = optimal; // Used in case of final recursion level
    int can_fit = 0;
    for (i = 0; i < num_weights; i++){
        // Skip bins where weight cannot fit
        if (bins[i] + this_weight > bin_capacity){
            continue;
        } else {
            can_fit++;
        }
        bins[i] += this_weight;
        // Has recursed to final weight
        if (idx == num_weights - 1){
            int occupied = checkOccupied(bins, num_weights);
            if (occupied < this_path_best){
                this_path_best = occupied;
            }
        // Check remaining weights recursively
        } else {
            int best_from_path = weightRecurse(optimal, bin_capacity, num_weights, weights, bins, idx + 1);
            if (best_from_path < optimal){
                optimal = best_from_path;
            }
        }
        bins[i] -= this_weight;
    }
    // if (can_fit == 0){
    //     return optimal;
    // }
    if (idx == num_weights - 1){
        return this_path_best;
    }
    return optimal;
}


int main(int argc, char **argv){
    if (argc != 2) {
        printf("Usage: ./binpack_brute {filename}\n");
        exit(EXIT_FAILURE);
    }

    // Reading values from file
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

    for (i = 0; i < num_weights; i++){
        printf("%d\n", weights[i]);
    }

    // Beginning of Solution - Initialize bins to 0
    int max_bins = num_weights;
    int bins[max_bins];
    for (i = 0; i < max_bins; i++){
        bins[i] = 0;
    }
    int optimal = max_bins + 1;

    clock_t t;
    t = clock();

    int best_bins[max_bins];
    int brute_optimal = weightRecurse(optimal, bin_cap, num_weights, weights, bins, 0);
    if (brute_optimal == -1 || brute_optimal > max_bins){
        printf("No solution.");
    } else {
        printf("Optimal Solution: %d\n", brute_optimal);
    }

    t = clock() - t;
    double time_taken = ((double)t)/CLOCKS_PER_SEC;
    printf("%.5f seconds", time_taken);
    return brute_optimal;
}