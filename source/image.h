#ifndef IMAGE_H
#define IMAGE_H

#include <glm/geometric.hpp>
#include "ray.h"
#include "rtweekend.h"

struct pixel_data {
    glm::vec3 color{};
    glm::vec3 albedo{};
    glm::vec3 normal{};

    pixel_data(glm::vec3 all) : color(all), albedo(all), normal(all){}

    pixel_data(){}

    pixel_data& operator+=(const pixel_data &v) {
        color += v.color;
        albedo += v.albedo;
        normal += v.normal;
        return *this;
    }
};
#endif