#include <algorithm>
#include <memory.h>
#include <queue>
#include <stdio.h>

#include "3dm.h"

// Represents a partial solution
// set: the triples that have been added to the solution
// remaining: the triples that have not been added to the solution
typedef struct Node {
    std::vector<Triple> set;
    std::vector<Triple> remaining;
} Node;

// Calculate the maximum size of the final solution given the partial solution
static int upperBound(int set_size, std::vector<Triple>& solution, std::vector<Triple>& remaining) {
    // Partition the remaining triples by their x, y, and z components
    // specifically, calculate the number of partitions for each component

    bool X[set_size + 1], Y[set_size + 1], Z[set_size + 1];
    memset(X, false, sizeof(bool) * (set_size + 1));
    memset(Y, false, sizeof(bool) * (set_size + 1));
    memset(Z, false, sizeof(bool) * (set_size + 1));

    int x_part = 0, y_part = 0, z_part = 0;
    int count = solution.size();

    for (Triple& t : remaining) {
        if (!X[t.x]) {
            X[t.x] = true;
            x_part++;
        } if (!Y[t.y]) {
            Y[t.y] = true;
            y_part++;
        } if (!Z[t.z]) {
            Z[t.z] = true;
            z_part++;
        }
    }

    // Remove the partitions that are already covered by the solution
    for (Triple& t : solution) {
        if (X[t.x]) {
            x_part--;
        } if (Y[t.y]) {
            y_part--;
        } if (Z[t.z]) {
            z_part--;
        }
    }

    return solution.size() + std::min({x_part, y_part, z_part});
}

std::vector<Triple> bruteforce_3dm(int set_size, std::vector<Triple>& T) {
    std::queue<Node> candidates;
    candidates.push({{}, T});

    // Use the heuristic algorithm to establish a lower bound
    Node best = {heuristic_3dm(set_size, T), {}};
    int lowerBound = best.set.size();

    while (!candidates.empty() && lowerBound < set_size) {
        Node candidate = candidates.front();
        candidates.pop();

        if (candidate.set.size() > lowerBound) {
            lowerBound = candidate.set.size();
            best = candidate;
        }

        if (!candidate.remaining.empty()) {
            Triple t = candidate.remaining.back();
            candidate.remaining.pop_back();

            // Check if the triple can be added to the solution
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