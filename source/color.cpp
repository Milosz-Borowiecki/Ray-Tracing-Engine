#include "color.h"

color prepareVectorToWrite(const color& pixel_color,const float& scale){

    glm::vec3 final_color = glm::clamp(
        glm::vec3(sqrt(scale * pixel_color.x),sqrt(scale * pixel_color.y),sqrt(scale * pixel_color.z)),
        glm::vec3(0.0f),
        glm::vec3(1.0f)
        );

    final_color = final_color * 256.0f;

    return final_color;
}

pixelData preparePixelToWrite(const pixelData& data,const float& scale){

    glm::vec3 color = prepareVectorToWrite(data.color,scale);
    glm::vec3 albedo = prepareVectorToWrite(data.albedo,scale);
    glm::vec3 normal = prepareVectorToWrite(data.normal,scale);

    return pixelData(color,albedo,normal);
}