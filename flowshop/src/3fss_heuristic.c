#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "3fss.h"

static int min(int a, int b) { return a < b ? a : b; }
static int max(int a, int b) { return a > b ? a : b; }

static int compare(const void* i, const void* j) {
    job a = *(job*)i;
    job b = *(job*)j;

    return min(a.d[0] + a.d[1], a.d[1] + a.d[2]) - min(b.d[0] + b.d[1], b.d[1] + b.d[2]);
}

int heuristic_3fss(job jobs[], int n, int sequence[]) {
    job temp[n];
    memcpy(temp, jobs, n * sizeof(job));

    qsort(temp, n, sizeof(job), compare);

    job jobs2[n];
    int l = 0;
    int r = n - 1;
    for (int i = 0; i < n; ++i) {
        int* d = jobs[i].d;
        if (d[0] + d[1] < d[1] + d[2]) {
            jobs2[l] = temp[i];
            sequence[l] = temp[i].id;
            ++l;
        } else {
            jobs2[r] = temp[i];
            sequence[r] = temp[i].id;
            --r;
        }
    }

    jobs2[0].start[0] = 0;
    jobs2[0].start[1] = jobs2[0].d[0];
    jobs2[0].start[2] = jobs2[0].start[1] + jobs2[0].d[1];

    for (int i = 1; i < n; ++i) {
        jobs2[i].start[0] = jobs2[i - 1].start[0] + jobs2[i - 1].d[0];
        jobs2[i].start[1] = max(jobs2[i].start[0] + jobs2[i].d[0], 
                               jobs2[i - 1].start[1] + jobs2[i - 1].d[1]);
        jobs2[i].start[2] = max(jobs2[i].start[1] + jobs2[i].d[1], 
                               jobs2[i - 1].start[2] + jobs2[i - 1].d[2]);
    }

    int length1 = jobs2[n - 1].start[0] + jobs2[n - 1].d[0];
    int length2 = jobs2[n - 1].start[1] + jobs2[n - 1].d[1];
    int length3 = jobs2[n - 1].start[2] + jobs2[n - 1].d[2];

    return max(length1, max(length2, length3));
}