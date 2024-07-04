#ifndef MATERIAL_H
#define MATERIAL_H

#include "../rtweekend.h"
#include "../hittable.h"

struct hitRecord;

class material {
    public:
        virtual bool scatter(const ray& r_in, const hitRecord& rec, color& attenuation, ray& scattered) const = 0;
};

#endif