#ifndef VEC3_H
#define VEC3_H

#include <glm/vec3.hpp>
#include <glm/geometric.hpp>
#include "rtweekend.h"

using point3 = glm::vec3;   // 3D point
using color = glm::vec3;    // RGB color

inline glm::vec3 random() {
    return glm::vec3(random_float(), random_float(), random_float());
}

inline glm::vec3 random(float min, float max) {
    return glm::vec3(random_float(min, max), random_float(min, max), random_float(min, max));
}

static glm::vec3 random_in_unit_sphere() {
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

static glm::vec3 random_unit_vector() {
    return glm::normalize(random_in_unit_sphere());
}

static bool near_zero(glm::vec3 e) {
    const auto s = 1e-8;
    return (fabs(e.x) < s) && (fabs(e.y) < s) && (fabs(e.z) < s);
}

static glm::vec3 reflect(const glm::vec3& v, const glm::vec3& n) {
    return v - 2 * glm::dot(v, n) * n;
}

static glm::vec3 refract(const glm::vec3& uv, const glm::vec3& n, float etai_over_etat) {
    const float cos_theta = fmin(glm::dot(-uv, n), 1.0f);
    const glm::vec3 r_out_perp = etai_over_etat * (uv + cos_theta * n);
    const glm::vec3 r_out_parallel = -sqrt(fabs(1.0f - glm::dot(r_out_perp, r_out_perp))) * n;
    return r_out_perp + r_out_parallel;
}

static glm::vec3 random_in_unit_disk() {
    while (true) {
        const auto p = glm::vec3(random_float(-1, 1), random_float(-1, 1), 0);
        if (glm::dot(p, p) >= 1) {
            continue;
        }
        else {
            return p;
        }
    }
}

#endif