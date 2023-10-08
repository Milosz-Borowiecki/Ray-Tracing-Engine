#ifndef IMAGE_H
#define IMAGE_H

#include "pixel.h"

class image {

    public:
        image(int p_width,int p_height,int p_channels): width(p_width), height(p_height), channels(p_channels){
            int size = channels * width * height;
            color_image.resize(size);
            albedo_image.resize(size);
            normal_image.resize(size);
        }
        
        void save_pixel_data(const pixel_data& data,uint32_t index){
            color_image.at(index) = static_cast<uint8_t>(data.color.x);
            albedo_image.at(index) = static_cast<uint8_t>(data.albedo.x);
            normal_image.at(index) = static_cast<uint8_t>(data.normal.x);
            index += 1;
            color_image.at(index) = static_cast<uint8_t>(data.color.y);
            albedo_image.at(index) = static_cast<uint8_t>(data.albedo.y);
            normal_image.at(index) = static_cast<uint8_t>(data.normal.y);
            index += 1;
            color_image.at(index) = static_cast<uint8_t>(data.color.z);
            albedo_image.at(index) = static_cast<uint8_t>(data.albedo.z);
            normal_image.at(index) = static_cast<uint8_t>(data.normal.z);
        }
        
        int channels;
        int width;
        int height;
        std::vector<uint8_t> color_image;
        std::vector<uint8_t> albedo_image;
        std::vector<uint8_t> normal_image;
};
#endif