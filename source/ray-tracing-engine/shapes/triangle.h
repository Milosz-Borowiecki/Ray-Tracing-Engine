#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "hittable.h"
#include "../vec3.h"
#include "array"

class Triangle : public Hittable {
    public:
        Triangle(std::array<point3,3> p_vertices,uint32_t material_index);

        bool hit(const Ray& r,const float& t_min_s,const float& t_max_s, HitRecord& rec) const override;

    public:
        std::array<point3,3> vertices;
        point3 normal{};
        uint32_t mat_idx{};
};

#endif