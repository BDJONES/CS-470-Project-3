#include <stdlib.h>
#include <memory.h>

#include "3fss.h"

// source: https://www.quickperm.org/
static int quickperm(int a[], int p[], int i, int n) {
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

static int max(int a, int b) {
    return a > b ? a : b;
}

int bruteforce_3fss(job jobs[], int n, int sequence[]) {
    int p[n + 1], o[n];

    for (int i = 0; i < n; ++i) {
        p[i] = o[i] = i;
    }
    p[n] = n;

    int min_length = __INT_MAX__;

    for (int j = 1; j < n;) {
        jobs[o[0]].start[0] = 0;
        jobs[o[0]].start[1] = jobs[o[0]].d[0];
        jobs[o[0]].start[2] = jobs[o[0]].start[1] + jobs[o[0]].d[1];
        for (int i = 1; i < n; ++i) {
            jobs[o[i]].start[0] = jobs[o[i-1]].start[0] + jobs[o[i-1]].d[0];
            jobs[o[i]].start[1] = max(jobs[o[i]].start[0] + jobs[o[i]].d[0], jobs[o[i-1]].start[1] + jobs[o[i-1]].d[1]);
            jobs[o[i]].start[2] = max(jobs[o[i]].start[1] + jobs[o[i]].d[1], jobs[o[i-1]].start[2] + jobs[o[i-1]].d[2]);
        }
        int length1 = jobs[o[n-1]].start[0] + jobs[o[n-1]].d[0];
        int length2 = jobs[o[n-1]].start[1] + jobs[o[n-1]].d[2];
        int length3 = jobs[o[n-1]].start[2] + jobs[o[n-1]].d[2];

        int length = max(length1, max(length2, length3));
        if (length < min_length) {
            min_length = length;
            memcpy(sequence, o, n * sizeof(int));
        }

        j = quickperm(o, p, j, n);
    }

    for (int i = 0; i < n; ++i) ++sequence[i];

    return min_length;
}