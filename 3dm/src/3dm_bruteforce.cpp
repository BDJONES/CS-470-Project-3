#include <algorithm>
#include <memory.h>
#include <queue>

#include "3dm.h"

typedef struct Node {
    std::vector<Triple> set;
    std::vector<Triple> remaining;
} Node;

int upperBound(int M, std::vector<Triple>& set, std::vector<Triple>& remaining) {
    bool X[M + 1], Y[M + 1], Z[M + 1];
    memset(X, false, sizeof(bool) * (M + 1));
    memset(Y, false, sizeof(bool) * (M + 1));
    memset(Z, false, sizeof(bool) * (M + 1));

    int count = set.size();

    for (Triple& t : set) {
        X[t.x] = Y[t.y] = Z[t.z] = true;
    }

    for (Triple& t : remaining) {
        if (X[t.x] || Y[t.y] || Z[t.z]) continue;
        ++count;
    }

    return count;
}

std::vector<Triple> bruteforce_3dm(std::vector<Triple>& T) {
    int M = 0;
    for (Triple t : T) {
        M = std::max(M, std::max(t.x, std::max(t.y, t.z)));
    }

    std::queue<Node> candidates;
    candidates.push({{}, T});

    Node best = {heuristic_3dm(T), {}};
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

                if (upperBound(M, child.set, child.remaining) >= lowerBound) {
                    candidates.push(child);
                }
            }

            if (upperBound(M, candidate.set, candidate.remaining) >= lowerBound) {
                candidates.push(candidate);
            }
        }
    }

    return best.set;
}