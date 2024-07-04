#ifndef PIXEL_H
#define PIXEL_H

#include <glm/geometric.hpp>
#include "rtweekend.h"


struct pixelData {
    glm::vec3 color{};
    glm::vec3 albedo{};
    glm::vec3 normal{};

    pixelData(glm::vec3 all) : color(all), albedo(all), normal(all){}

    pixelData(glm::vec3 col,glm::vec3 alb,glm::vec3 norm,float dep) : color(col), albedo(alb), normal(norm), depth(dep){}

    pixelData() = default;

    pixelData& operator+=(const pixelData &v) {
        color += v.color;
        albedo += v.albedo;
        normal += v.normal;

        return *this;
    }
};
#endif