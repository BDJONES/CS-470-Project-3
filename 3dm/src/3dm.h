#pragma once

#include <vector>

typedef struct Triple {
    int x;
    int y;
    int z;
    int score;
} Triple;

std::vector<Triple> bruteforce_3dm(int set_size, std::vector<Triple>& T);
std::vector<Triple> heuristic_3dm(int set_size, std::vector<Triple>& T);