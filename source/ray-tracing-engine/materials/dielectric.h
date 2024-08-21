#ifndef MATERIAL_DIELECTRIC
#define MATERIAL_DIELECTRIC

#include "material.h"

class Dielectric : public Material {
    public:
        Dielectric(const color& a,float index_of_refraction) : albedo(a) ,ir(index_of_refraction) {}

        virtual bool scatter(
            const Ray& r_in, const HitRecord& rec, color& attenuation, Ray& scattered
        ) const override;

    public:
        float ir;
        color albedo;
    private:
        static float reflectance(float cosine, float ref_idx);
};

#endif