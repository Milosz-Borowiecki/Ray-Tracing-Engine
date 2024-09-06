#include "ray.h"

point3 Ray::origin() const{
     return orig;
}

point3 Ray::direction() const {
     return dir;
}

point3 Ray::at(float t) const {
    return orig + t*dir;
}