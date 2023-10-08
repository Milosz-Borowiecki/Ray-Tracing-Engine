#ifndef MATERIAL_DIELECTRIC
#define MATERIAL_DIELECTRIC

#include "material.h"

class dielectric : public material {
    public:
        dielectric(const color& a,float index_of_refraction) : albedo(a) ,ir(index_of_refraction) {}

        virtual bool scatter(
            const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered
        ) const override;

    public:
        float ir;
        color albedo;
    private:
        static float reflectance(float cosine, float ref_idx);
};

#endif