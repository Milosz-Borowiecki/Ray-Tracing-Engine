#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "vec3.h"
#include <glm/geometric.hpp>

class sphere : public hittable {
    public:
        sphere() {}
        sphere(point3 cen, float r) : center(cen), radius(r) {};

        virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const override;

    public:
        point3 center;
        float radius;
};

bool sphere::hit(const ray& r, float t_min, float t_max, hit_record& rec) const {
    glm::vec3 oc = r.origin() - center;
    auto a = r.direction().length();
    auto half_b = glm::dot(oc, r.direction());
    auto c = oc.length() - radius*radius;

    auto discriminant = half_b*half_b - a*c;
    if (discriminant < 0) return false;
    auto sqrtd = sqrt(discriminant);

    auto root = (-half_b - sqrtd) / a;
    if (root < t_min || t_max < root) {
        root = (-half_b + sqrtd) / a;
        if (root < t_min || t_max < root)
            return false;
    }

    rec.t = root;
    rec.p = r.at(rec.t);
    rec.normal = (rec.p - center) / radius;

    return true;
}

#endif