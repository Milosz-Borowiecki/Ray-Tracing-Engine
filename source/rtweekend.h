#ifndef RTWEEKEND_H
#define RTWEEKEND_H

#include <cmath>
#include <limits>
#include <memory>
#include <random>
#include <cstdlib>

using std::shared_ptr;
using std::make_shared;
using std::sqrt;


const float infinity = std::numeric_limits<float>::infinity();
const float pi = 3.1415926535897932385f;


inline float degrees_to_radians(float degrees) {
    return degrees * pi / 180.0f;
}

inline float random_float() {
    static std::uniform_real_distribution<float> distribution(0.0f, 1.0f);
    static std::mt19937 generator;
    return distribution(generator);
}

inline float random_float_classic() {
    return rand() / (RAND_MAX + 1.0f);
}

inline float random_float(float min, float max) {
    return min + (max - min) * random_float_classic();
}

inline float clamp(float x, float min, float max) {
    if (x < min) return min;
    if (x > max) return max;
    return x;
}

#include "ray.h"
#include "vec3.h"

#endif