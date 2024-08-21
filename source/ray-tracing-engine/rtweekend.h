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


constexpr float infinity = std::numeric_limits<float>::infinity();
constexpr float pi = 3.1415926535897932385f;


inline float degreesToRadians(float degrees) {
    return degrees * pi / 180.0f;
}

inline float randomFloat() {
    static std::uniform_real_distribution<float> distribution(0.0f, 1.0f);
    static std::mt19937 generator;
    return distribution(generator);
}

inline float randomFloatClassic() {
    return rand() / (RAND_MAX + 1.0f);
}

inline float randomFloat(float min, float max) {
    return min + (max - min) * randomFloatClassic();
}

#include "ray.h"
#include "vec3.h"

#endif