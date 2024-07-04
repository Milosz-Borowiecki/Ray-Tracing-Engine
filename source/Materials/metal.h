#ifndef MATERIAL_METAL
#define MATERIAL_METAL

#include "material.h"

class metal : public material {
    public:
        metal(const color& a, float f);

        virtual bool scatter(
            const ray& r_in, const hitRecord& rec, color& attenuation, ray& scattered
        ) const override;

    public:
        color albedo;
        float fuzz;
};

#endif