#include <stdlib.h>
#include <vector>
#include <memory.h>
#include <algorithm>

#include "3dm.h"

std::vector<Triple> heuristic_3dm(int set_size, std::vector<Triple>& T) {
    int X[set_size + 1], Y[set_size + 1], Z[set_size + 1];
    memset(X, 0, sizeof(int) * (set_size + 1));
    memset(Y, 0, sizeof(int) * (set_size + 1));
    memset(Z, 0, sizeof(int) * (set_size + 1));

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

    memset(X, 0, sizeof(int) * (set_size + 1));
    memset(Y, 0, sizeof(int) * (set_size + 1));
    memset(Z, 0, sizeof(int) * (set_size + 1));

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