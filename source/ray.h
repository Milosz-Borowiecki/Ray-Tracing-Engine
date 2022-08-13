#ifndef RAY_H
#define RAY_H

#include "vec3.h"

class ray {
    public:
        ray() {}
        ray(const point3& origin, const glm::vec3& direction)
            : orig(origin), dir(direction)
        {}

        point3 origin() const  { return orig; }
        glm::vec3 direction() const { return dir; }

        point3 at(float t) const {
            return orig + t*dir;
        }

    public:
        point3 orig;
        glm::vec3 dir;
};

#endif