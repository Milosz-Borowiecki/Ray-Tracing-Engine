#ifndef MATERIAL_METAL
#define MATERIAL_METAL

#include "material.h"

class Metal : public Material {
    public:
        Metal(const color& a, float f);

        virtual bool scatter(
            const Ray& r_in, const HitRecord& rec, color& attenuation, Ray& scattered
        ) const override;

    public:
        color albedo;
        float fuzz;
};

#endif