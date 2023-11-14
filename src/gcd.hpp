#pragma once

#include <array>

std::array<long, 3> gcd(long a, long b) {
    std::array<long, 3> U = {a, 1, 0};
    std::array<long, 3> V = {b, 0, 1};
    std::array<long, 3> T;
    while (V[0] != 0) {
        long q = U[0] / V[0];
        T = {U[0] % V[0], U[1] - q * V[1], U[2] - q * V[2]};
        U = V;
        V = T;
    }
    return U;
}