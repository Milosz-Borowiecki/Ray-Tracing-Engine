#include "imageConvert.h"

std::vector<uint8_t> convertToBW(const RenderLayer& render_lay) {
    std::vector<uint8_t> image;
    image.reserve(render_lay.getWidth() * render_lay.getHeight());
    for(auto pixel_obj : render_lay.getPixels()){
        float value = (0.299f * pixel_obj.r + 0.587f * pixel_obj.g + 0.114f * pixel_obj.b);
        value = std::clamp(value,0.0f,1.0f);
        value *= 255.0f;
    
        image.push_back(static_cast<uint8_t>(value));
    }

    return image;
}

std::vector<uint8_t> convertToRGB(const RenderLayer& render_lay) {
    std::vector<uint8_t> image;
    image.reserve(render_lay.getWidth() * render_lay.getHeight() * 3);
    for(auto pixel_obj : render_lay.getPixels()){
        pixel_obj = glm::clamp(pixel_obj,glm::vec4(0.0f),glm::vec4(1.0f));
        pixel_obj *= 255.0f;

        auto pixel_24_bit = {
            static_cast<uint8_t>(pixel_obj.r),
            static_cast<uint8_t>(pixel_obj.g),
            static_cast<uint8_t>(pixel_obj.b)
        };
    
        image.insert(image.end(),pixel_24_bit);
    }
    return image;
}

std::vector<uint8_t> convertToRGBA(const RenderLayer& render_lay) {
    std::vector<uint8_t> image;
    image.reserve(render_lay.getWidth() * render_lay.getHeight() * 4);
    for(auto pixel_obj : render_lay.getPixels()){
        pixel_obj = glm::clamp(pixel_obj,glm::vec4(0.0f),glm::vec4(1.0f));
        pixel_obj *= 255.0f;

        auto pixel_32_bit = {
            static_cast<uint8_t>(pixel_obj.r),
            static_cast<uint8_t>(pixel_obj.g),
            static_cast<uint8_t>(pixel_obj.b),
            static_cast<uint8_t>(pixel_obj.a)
        };
    
        image.insert(image.end(),pixel_32_bit);
    }
    return image;
}