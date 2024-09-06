#include "color.h"

void preparePixelToWrite(const pixel& data){

    pixel this_data = data;

    this_data = glm::sqrt(this_data);
    this_data = glm::clamp(this_data,glm::vec4(0.0f),glm::vec4(1.0f));

    this_data = this_data * 255.0f;

    int rbyte = static_cast<int>(this_data.r);
    int gbyte = static_cast<int>(this_data.g);
    int bbyte = static_cast<int>(this_data.b);

    // Write out the pixel color components.
    std::cout << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}