#ifndef IMAGE_H
#define IMAGE_H

#include "pixelsOfLayers.h"

class RenderLayer {

    public:
        RenderLayer(const uint32_t& width,const uint32_t& height): m_width(width), m_height(height){
            pixels.reserve(m_width * height);
        }

        RenderLayer() = default;

        void resize(const uint32_t& width,const uint32_t& height){
            pixels.clear();
            pixels.shrink_to_fit();
            pixels.reserve(width * height);
            m_width = width;
            m_height = height;
        }

        size_t getWidth(){
            return m_width;
        }

        size_t getHeight(){
            return m_height;
        }
        
        void savePixelData(const pixel& data,const size_t& index){
            pixels.assign(index,data);
        }
    private:
        uint32_t m_width;
        uint32_t m_height;
        std::vector<pixel> pixels;
};
#endif