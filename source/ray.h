#ifndef RAY_H
#define RAY_H

#include "vec3.h"

class ray {
    public:

        ray() {};
        ray(const point3& p_origin, const point3& p_direction) : orig(p_origin), dir(p_direction){};

        point3 origin() const;
        point3 direction() const;

        point3 at(float t) const;

        point3 orig{};
        point3 dir{};
};

#endif