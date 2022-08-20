#ifndef MATERIAL_LAMBERTIAN
#define MATERIAL_LAMBERTIAN

#include "material.h"

class lambertian : public material {
    public:
        lambertian(const color& a);

        virtual bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const override;

    public:
        color albedo;
};

#endif