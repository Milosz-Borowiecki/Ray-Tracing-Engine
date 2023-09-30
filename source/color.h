#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"

#include <iostream>

void write_color(const color& pixel_color) {
    std::cout << pixel_color.x << ' '
        << pixel_color.y << ' '
        << pixel_color.z << '\n';
}

color prepare_color_to_write(const color& pixel_color,const float& scale){

    glm::vec3 final_color = glm::clamp(
        glm::vec3(sqrt(scale * pixel_color.x),sqrt(scale * pixel_color.y),sqrt(scale * pixel_color.z)),
        glm::vec3(0.0f),
        glm::vec3(0.999f)
        );

    final_color.x = 256 * final_color.x;
    final_color.y = 256 * final_color.y;
    final_color.z = 256 * final_color.z;

    return final_color;
}

#endif