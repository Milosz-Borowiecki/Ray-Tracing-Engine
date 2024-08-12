#ifndef VEC3_H
#define VEC3_H

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/geometric.hpp>
#include "rtweekend.h"

using point3 = glm::vec3;   // 3D point
using color = glm::vec3;    // RGB color
using pixel = glm::vec4;    // Pixel

inline glm::vec3 random() {
    return glm::vec3(randomFloat(), randomFloat(), randomFloat());
}

inline glm::vec3 random(float min, float max) {
    return glm::vec3(randomFloat(min, max), randomFloat(min, max), randomFloat(min, max));
}

inline glm::vec3 randomInUnitSphere() {
    while (true) {
        const auto p = random(-1.0f, 1.0f);
        if (glm::dot(p, p) >= 1) {
            continue;
        }
        else {
            return p;
        }
    }
}

inline glm::vec3 randomUnitVector() {
    return glm::normalize(randomInUnitSphere());
}

inline bool nearZero(glm::vec3 e) {
    const auto s = 1e-8;
    return (fabs(e.x) < s) && (fabs(e.y) < s) && (fabs(e.z) < s);
}

inline glm::vec3 reflect(const glm::vec3& v, const glm::vec3& n) {
    return v - 2 * glm::dot(v, n) * n;
}

inline glm::vec3 refract(const glm::vec3& uv, const glm::vec3& n, float etai_over_etat) {
    const float cos_theta = fmin(glm::dot(-uv, n), 1.0f);
    const glm::vec3 r_out_perp = etai_over_etat * (uv + cos_theta * n);
    const glm::vec3 r_out_parallel = -sqrt(fabs(1.0f - glm::dot(r_out_perp, r_out_perp))) * n;
    return r_out_perp + r_out_parallel;
}

inline glm::vec3 randomInUnitDisk() {
    while (true) {
        const auto p = glm::vec3(randomFloat(-1, 1), randomFloat(-1, 1), 0);
        if (glm::dot(p, p) >= 1) {
            continue;
        }
        else {
            return p;
        }
    }
}

#endif