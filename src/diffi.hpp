#pragma once
#include <fast_power.hpp>
#include <cstdlib>
#include <ctime>
#include <cmath>

bool is_prime(long long number)
{
    if (number <= 1)
    {
        return false;
    }
    long long b = (long long)std::pow(number, 0.5);
    for (long long i = 2; i <= b; ++i)
    {
        if ((number % i) == 0)
        {
            return false;
        }
    }
    return true;
}

long long get_prime(long long range = 0)
{
    long long number = 0;
    if (range == 0)
    {
        do
        {
            number = std::rand();
        } while (!is_prime(number));
    }
    else
    {
        do
        {
            number = std::rand() % range;
        } while (!is_prime(number));
    }

    return number;
}

class Diffi
{
private:
    long long q;
    long long p;
    long long g;

public:
    Diffi()
    {
        do
        {
            q = get_prime();
            p = 2 * q + 1;
        } while (!is_prime(p));
        do
        {
            g = std::rand() % (p - 1);
        } while (pow_mod(g, q, p) == 1);
    }
    long long get_close_key()
    {
        return std::rand() % p;
    }
    long long get_open_key(long long X)
    {
        return pow_mod(g, X, p);
    }
    long long get_common_key(long long Y, long long X)
    {
        return pow_mod(Y, X, p);
    }
};