#ifndef PIXEL_H
#define PIXEL_H

#include <glm/geometric.hpp>
#include "rtweekend.h"

struct pixel_data {
    glm::vec3 color{};
    glm::vec3 albedo{};
    glm::vec3 normal{};

    pixel_data(glm::vec3 all) : color(all), albedo(all), normal(all){}

    pixel_data(glm::vec3 col,glm::vec3 alb,glm::vec3 norm) : color(col), albedo(alb), normal(norm){}

    pixel_data(){}

    pixel_data& operator+=(const pixel_data &v) {
        color += v.color;
        albedo += v.albedo;
        normal += v.normal;

        return *this;
    }
};
#endif