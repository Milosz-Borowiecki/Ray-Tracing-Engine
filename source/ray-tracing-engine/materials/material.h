#ifndef MATERIAL_H
#define MATERIAL_H

#include "../rtweekend.h"
#include "../shapes/hittable.h"

class Material {
    public:
        virtual bool scatter(const Ray& r_in, const HitRecord& rec, color& attenuation, Ray& scattered) const = 0;
};

#endif