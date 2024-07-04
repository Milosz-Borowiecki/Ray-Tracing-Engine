#ifndef IMAGE_H
#define IMAGE_H

#include "pixel.h"

struct renderLayerSettings  {
    int width;
    int height;
};

class renderLayer {

    public:
        renderLayer(int p_width,int p_height): width(p_width), height(p_height){
            int size = width * height * 4;
            color_layer.reserve(size);
            albedo_layer.reserve(size);
            normal_layer.reserve(size);
        }

        void resize(int p_width,int p_height,int p_channels){
            color_layer.clear();
            color_layer.shrink_to_fit();
            albedo_layer.clear();
            albedo_layer.shrink_to_fit();
            normal_layer.clear();
            normal_layer.shrink_to_fit();
            depth_layer.clear();
            depth_layer.shrink_to_fit();
        }
        
        void save_pixel_data(const pixelData& data,uint32_t index){
            color_layer.at(index) = static_cast<uint8_t>(data.color.x);
            albedo_layer.at(index) = static_cast<uint8_t>(data.albedo.x);
            normal_layer.at(index) = static_cast<uint8_t>(data.normal.x);
            index += 1;
            color_layer.at(index) = static_cast<uint8_t>(data.color.y);
            albedo_layer.at(index) = static_cast<uint8_t>(data.albedo.y);
            normal_layer.at(index) = static_cast<uint8_t>(data.normal.y);
            index += 1;
            color_layer.at(index) = static_cast<uint8_t>(data.color.z);
            albedo_layer.at(index) = static_cast<uint8_t>(data.albedo.z);
            normal_layer.at(index) = static_cast<uint8_t>(data.normal.z);
        }
    private:
        int width;
        int height;
        float max_depth, min_depth;
        std::vector<uint8_t> color_layer;
        std::vector<uint8_t> albedo_layer;
        std::vector<uint8_t> normal_layer;
        std::vector<uint8_t> depth_layer;
};
#endif