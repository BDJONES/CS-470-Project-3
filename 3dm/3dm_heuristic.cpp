#include <stdlib.h>
#include <vector>
#include <memory.h>
#include <algorithm>

#include "3dm.h"

std::vector<Triple> heuristic_3dm(std::vector<Triple>& T) {
    int M = 0;
    for (Triple t : T) {
        M = std::max(M, std::max(t.x, std::max(t.y, t.z)));
    }

    int X[M + 1], Y[M + 1], Z[M + 1];
    memset(X, 0, sizeof(int) * (M + 1));
    memset(Y, 0, sizeof(int) * (M + 1));
    memset(Z, 0, sizeof(int) * (M + 1));

    for (Triple t : T) {
        ++X[t.x];
        ++Y[t.y];
        ++Z[t.z];
    }

    for (Triple& t : T) {
        t.score = X[t.x] + Y[t.y] + Z[t.z];
    }

    std::sort(T.begin(), T.end(), [](Triple a, Triple b) -> bool {
        return a.score < b.score;
    });

    memset(X, 0, sizeof(int) * (M + 1));
    memset(Y, 0, sizeof(int) * (M + 1));
    memset(Z, 0, sizeof(int) * (M + 1));

    std::vector<Triple> set;

    for (Triple t : T) {
        if (X[t.x] == 0 && Y[t.y] == 0 && Z[t.z] == 0) {
            set.push_back(t);
            ++X[t.x];
            ++Y[t.y];
            ++Z[t.z];
        }
    }

    return set;
}