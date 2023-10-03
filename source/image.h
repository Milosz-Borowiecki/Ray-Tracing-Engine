#ifndef IMAGE_H
#define IMAGE_H

#include "pixel.h"

template <size_t array_size>
class image {
    public:
        std::unique_ptr<std::array<uint8_t, array_size>> color_image = std::make_unique<std::array<uint8_t, array_size>>();
        std::unique_ptr<std::array<uint8_t, array_size>> albedo_image = std::make_unique<std::array<uint8_t, array_size>>();
        std::unique_ptr<std::array<uint8_t, array_size>> normal_image = std::make_unique<std::array<uint8_t, array_size>>();
        
        void save_pixel_data(const pixel_data& data,uint32_t index){
            color_image->data()[index] = static_cast<uint8_t>(data.color.x);
            albedo_image->data()[index] = static_cast<uint8_t>(data.albedo.x);
            normal_image->data()[index] = static_cast<uint8_t>(data.normal.x);
            index += 1;
            color_image->data()[index] = static_cast<uint8_t>(data.color.y);
            albedo_image->data()[index] = static_cast<uint8_t>(data.albedo.y);
            normal_image->data()[index] = static_cast<uint8_t>(data.normal.y);
            index += 1;
            color_image->data()[index] = static_cast<uint8_t>(data.color.z);
            albedo_image->data()[index] = static_cast<uint8_t>(data.albedo.z);
            normal_image->data()[index] = static_cast<uint8_t>(data.normal.z);
        }
};
#endif