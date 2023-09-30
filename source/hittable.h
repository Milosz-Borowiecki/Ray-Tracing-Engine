#ifndef HITTABLE_H
#define HITTABLE_H

#include <glm/geometric.hpp>
#include "ray.h"
#include "rtweekend.h"

class material;

struct hit_record {
    point3 p{};
    glm::vec3 normal{};
    shared_ptr<material> mat_ptr;
    float t{};
    bool front_face{};

    inline void set_face_normal(const ray& r, glm::vec3& outward_normal) {
        front_face = glm::dot(r.direction(), outward_normal) < 0.0f;
        if (front_face) {
            normal = outward_normal;
        } else {
            normal = -outward_normal;
        }
    }
};

class hittable {
    public:
        virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const = 0;
};

#endif