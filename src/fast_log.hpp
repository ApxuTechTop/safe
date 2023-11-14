#pragma once
#include <fast_power.hpp>
#include <vector>
#include <utility>
#include <cmath>

std::vector<long long> fast_log(long long a, long long p, long long b)
{
    long long m = std::ceil(std::pow(p, 0.5));
    long long k = std::ceil(std::pow(p, 0.5));
    std::vector<long long> X;
    std::vector<std::pair<long long, long long>> A;
    std::vector<std::pair<long long, long long>> B;
    A.reserve(k + 1);
    for (long long i = 1; i <= k; ++i)
    {
        A.emplace_back(pow_mod(a, i * m, p), i);
    }
    B.reserve(m + 1);
    for (long long j = 0; j < m; ++j)
    {
        B.emplace_back((b * pow_mod(a, j, p)) % p, j);
    }
    for (auto [a, i] : A)
    {
        for (auto [b, j] : B)
        {
            if (a == b)
            {
                X.push_back(i * m - j);
            }
        }
    }
    return X;
}