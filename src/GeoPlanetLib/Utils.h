#pragma once

#include <cmath>

/**
 * Generates random float value from 0.0 to 1.0
 */
float rand_f()
{
    return static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
}

/**
 * Generates random float value from 0.0 to range
 */
float rand_f(float range)
{
    return static_cast<float>(rand()) / static_cast<float>(RAND_MAX / range);
}

float rand_f(float from, float to)
{
    if (from > to) {
        return NAN;
    }
    auto res = rand_f(to - from);
    return res + from;
}
