#pragma once

typedef struct job {
    int id;
    int d[3];   // duration of each operation
    int start[3];
} job;

int heuristic_3fss(job jobs[], int n, int sequence[]);
int bruteforce_3fss(job jobs[], int n, int sequence[]);