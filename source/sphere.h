#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "vec3.h"

#include <glm/geometric.hpp>

class sphere : public hittable {
    public:
        sphere() {}
        sphere(point3 cen, float r, shared_ptr<material> m)
            : center(cen), radius(r), mat_ptr(m) {};

        virtual bool hit(const ray& r, float t_min_s, float t_max_s, hit_record& rec) const override;

    public:
        point3 center{};
        float radius{};
        shared_ptr<material> mat_ptr;
};

bool sphere::hit(const ray& r, float t_min_s, float t_max_s, hit_record& rec) const {
    const glm::vec3 oc = r.origin() - center;
    const glm::vec3 pre_a = r.direction();
    const auto a = glm::dot(pre_a,pre_a);
    const auto half_b = glm::dot(oc, pre_a);
    const auto c = glm::dot(oc,oc) - radius*radius;

    const auto discriminant = half_b*half_b - a*c;
    if (discriminant < 0) {
        return false;
    }
    const auto sqrtd = sqrt(discriminant);

    auto root = (-half_b - sqrtd) / a;
    if (root < t_min_s || t_max_s < root) {
        root = (-half_b + sqrtd) / a;
        if (root < t_min_s || t_max_s < root){
            return false;
        }
    }

    rec.t = root;
    rec.p = r.at(rec.t);
    glm::vec3 outward_normal = (rec.p - center) / radius;
    rec.set_face_normal(r, outward_normal);
    rec.mat_ptr = mat_ptr;

    return true;
}

#endif