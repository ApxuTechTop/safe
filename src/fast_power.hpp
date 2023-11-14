#pragma once

#include <iostream>

long get_digit(long number, long n)
{
    return (number >> n) & 1;
}

long pow_mod(long a, long x, long p)
{
    long max_pow = 0;
    while ((1l << ++max_pow) < x) {
    }
    long next_a = 1;
    for (long i = max_pow-1; i >= 0; --i)
    {
        next_a = (next_a * next_a) % p;
        long digit = get_digit(x, i);
        if (digit == 1)
        {
            next_a = (next_a * a) % p;
        }
    }
    return next_a;
}

