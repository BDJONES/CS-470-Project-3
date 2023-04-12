#pragma once

#include <vector>

typedef struct Triple {
    int x;
    int y;
    int z;
    int score;
} Triple;

std::vector<Triple> bruteforce_3dm(std::vector<Triple>& T);
std::vector<Triple> heuristic_3dm(std::vector<Triple>& T);