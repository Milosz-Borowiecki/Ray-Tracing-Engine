#include "ray.h"

point3 ray::origin() const{
     return orig;
}

point3 ray::direction() const {
     return dir;
}

point3 ray::at(float t) const {
    return orig + t*dir;
}