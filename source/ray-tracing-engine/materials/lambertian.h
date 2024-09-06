#ifndef MATERIAL_LAMBERTIAN
#define MATERIAL_LAMBERTIAN

#include "material.h"

class Lambertian : public Material {
    public:
        Lambertian(const color& a);

        virtual bool scatter(const Ray& r_in, const HitRecord& rec, color& attenuation, Ray& scattered) const override;

    public:
        color albedo;
};

#endif