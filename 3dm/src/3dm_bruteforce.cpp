#include <algorithm>
#include <memory.h>
#include <queue>
#include <stdio.h>

#include "3dm.h"

typedef struct Node {
    std::vector<Triple> set;
    std::vector<Triple> remaining;
} Node;

static int upperBound(int set_size, std::vector<Triple>& set, std::vector<Triple>& remaining) {
    bool X[set_size + 1], Y[set_size + 1], Z[set_size + 1];
    memset(X, false, sizeof(bool) * (set_size + 1));
    memset(Y, false, sizeof(bool) * (set_size + 1));
    memset(Z, false, sizeof(bool) * (set_size + 1));

    int count = set.size();

    for (Triple& t : set) {
        X[t.x] = Y[t.y] = Z[t.z] = true;
    }

    for (Triple& t : remaining) {
        if (X[t.x] || Y[t.y] || Z[t.z]) continue;
        ++count;
    }

    return std::min(count, set_size);
}

std::vector<Triple> bruteforce_3dm(int set_size, std::vector<Triple>& T) {
    std::queue<Node> candidates;
    candidates.push({{}, T});

    Node best = {heuristic_3dm(set_size, T), {}};
    int lowerBound = best.set.size();

    while (!candidates.empty()) {
        Node candidate = candidates.front();
        candidates.pop();

        if (candidate.set.size() > lowerBound) {
            lowerBound = candidate.set.size();
            best = candidate;
        }

        if (!candidate.remaining.empty()) {
            Triple t = candidate.remaining.back();
            candidate.remaining.pop_back();

            bool valid = true;
            for (Triple& s : candidate.set) {
                if (t.x == s.x || t.y == s.y || t.z == s.z) {
                    valid = false;
                    break;
                }
            }

            if (valid) {
                Node child = candidate;
                child.set.push_back(t);

                if (child.set.size() > lowerBound) {
                    lowerBound = child.set.size();
                    best = child;
                }

                if (upperBound(set_size, child.set, child.remaining) > lowerBound) {
                    candidates.push(child);
                }
            }

            if (upperBound(set_size, candidate.set, candidate.remaining) > lowerBound) {
                candidates.push(candidate);
            }
        }
    }

    return best.set;
}