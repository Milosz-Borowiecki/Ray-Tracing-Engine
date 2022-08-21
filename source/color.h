#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"

#include <iostream>

void write_color(std::ostream &out,const color& pixel_color, int samples_per_pixel) {

    // Divide the color by the number of samples and gamma-correct for gamma=2.0.
    auto scale = 1.0f / samples_per_pixel;
    glm::vec3 color = glm::clamp(
        glm::vec3(sqrt(scale * pixel_color.x),sqrt(scale * pixel_color.y),sqrt(scale * pixel_color.z)),
        glm::vec3(0.0f),
        glm::vec3(0.999f)
        );

    // Write the translated [0,255] value of each color component.
    out << static_cast<int>(256 * color.x) << ' '
        << static_cast<int>(256 * color.y) << ' '
        << static_cast<int>(256 * color.z) << '\n';
}

#endif