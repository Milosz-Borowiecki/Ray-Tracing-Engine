#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"
#include "pixel.h"

#include <iostream>

static color prepare_vector_to_write(const color& pixel_color,const float& scale){

    glm::vec3 final_color = glm::clamp(
        glm::vec3(sqrt(scale * pixel_color.x),sqrt(scale * pixel_color.y),sqrt(scale * pixel_color.z)),
        glm::vec3(0.0f),
        glm::vec3(0.999f)
        );

    final_color = final_color * 256.0f;

    return final_color;
}

inline pixel_data prepare_pixel_to_write(const pixel_data& data,const float& scale){

    glm::vec3 color = prepare_vector_to_write(data.color,scale);
    glm::vec3 albedo = prepare_vector_to_write(data.albedo,scale);
    glm::vec3 normal = prepare_vector_to_write(data.normal,scale);

    return pixel_data(color,albedo,normal);
}

#endif