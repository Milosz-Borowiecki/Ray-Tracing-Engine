#ifndef HITTABLE_H
#define HITTABLE_H

#include <glm/geometric.hpp>
#include "ray.h"
#include "rtweekend.h"

class Material;

struct HitRecord {
    point3 p{};
    glm::vec3 normal{};
    shared_ptr<Material> mat_ptr;
    float t{};
    bool front_face{};

    inline void setFaceNormal(const Ray& r, glm::vec3& outward_normal) {
        front_face = glm::dot(r.direction(), outward_normal) < 0.0f;
        if (front_face) {
            normal = outward_normal;
        } else {
            normal = -outward_normal;
        }
    }
};

class Hittable {
    public:
        virtual ~Hittable() = default;
        virtual bool hit(const Ray& r,const float& t_min,const float& t_max, HitRecord& rec) const = 0;
};

#endif