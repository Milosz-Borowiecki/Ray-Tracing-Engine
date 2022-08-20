#ifndef MATERIAL_DIELECTRIC
#define MATERIAL_DIELECTRIC

#include "material.h"

class dielectric : public material {
    public:
        dielectric(float index_of_refraction) : ir(index_of_refraction) {}

        virtual bool scatter(
            const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered
        ) const override;

    public:
        float ir;

    private:
        static float reflectance(float cosine, float ref_idx);
};

#endif