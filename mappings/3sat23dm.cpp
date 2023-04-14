#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <vector>
#include <algorithm>

struct Triple {
    int x;
    int y;
    int z;

    int& operator[](int i) {
        switch (i) {
            case 0: return x;
            case 1: return y;
            case 2: return z;
            default: return x;
        }
    }
};

int X_n = 0;
int Y_n = 0;
int Z_n = 0;

int extendWheel(bool sign, std::vector<Triple>& wheel) {
    if (wheel.empty()) {
        Triple t = {++X_n, ++Y_n, ++Z_n};
        Triple f = {X_n, ++Y_n, Z_n};
        wheel.push_back(t);
        wheel.push_back(f);
        return sign ? t[1] : f[1];
    }

    wheel.back()[0] = ++X_n;

    Triple t = {X_n, ++Y_n, ++Z_n};
    Triple f = {wheel.front()[0], ++Y_n, Z_n};

    wheel.push_back(t);
    wheel.push_back(f);

    return sign ? t[1] : f[1];
}

int main(int argc, char** argv) {
    if (argc != 3) {
        printf("Usage: %s file_3sat file_3dm\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    FILE* from = fopen(argv[1], "r");
    FILE* to = fopen(argv[2], "w");

    if (from == NULL) {
        fprintf(stderr, "Failed to open file '%s'\n", argv[1]);
        exit(EXIT_FAILURE);
    }
    if (to == NULL) {
        fprintf(stderr, "Failed to open file '%s'\n", argv[2]);
        exit(EXIT_FAILURE);
    }

    int max_var = 0;
    std::vector<Triple> clauses;
    while (!feof(from)) {
        char c = fgetc(from);
        if (c == '$') break;
        ungetc(c, from);

        Triple clause;
        int count = fscanf(from, "%d %d %d\n", &clause[0], &clause[1], &clause[2]);
        if (count != 3) {
            fprintf(stderr, "Expect 3 terms per line\n");
            exit(EXIT_FAILURE);
        }
        clauses.push_back(clause);

        max_var = std::max(max_var, std::max(std::max(abs(clause[0]), abs(clause[1])), abs(clause[2])));
    }

    std::vector<std::vector<Triple>> wheels(max_var);
    std::vector<Triple> triples;

    for (Triple c : clauses) {
        int x = ++X_n;
        int z = ++Z_n;
        for (int i = 0; i < 3; ++i) {
            triples.push_back({
                x,
                extendWheel(c[i] > 0, wheels[ abs(c[i]) - 1 ]),
                z
            });
        }
    }

    for (int i = 0; i < clauses.size() * 2; ++i) {
        ++X_n;
        ++Z_n;
        for (std::vector<Triple> w : wheels) {
            for (Triple t : w) {
                triples.push_back({X_n, t[1], Z_n});
            }
        }
    }

    fprintf(to, "%d\n", std::max(X_n, std::max(Y_n, Z_n)));

    for (Triple t : triples) {
        fprintf(to, "%d %d %d\n", t[0], t[1], t[2]);
    }

    for (std::vector<Triple>& w : wheels) {
        for (Triple t : w) {
            fprintf(to, "%d %d %d\n", t[0], t[1], t[2]);
        }
    }
}