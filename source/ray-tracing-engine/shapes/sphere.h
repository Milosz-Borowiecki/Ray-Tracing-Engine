#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "../vec3.h"

class Sphere : public Hittable {
    public:
        Sphere() {}
        Sphere(point3 cen, float r, uint32_t mat)
            : center(cen), radius(r), mat_idx(mat) {};

        bool hit(const Ray& r,const float& t_min_s,const float& t_max_s, HitRecord& rec) const override;

    public:
        point3 center{};
        float radius{};
        uint32_t mat_idx{};
};

#endif