#ifndef IMAGE_H
#define IMAGE_H

#include "rtweekend.h"

class RenderLayer {
    public:
        RenderLayer() = default;

        void resize(const uint32_t& width,const uint32_t& height){
            pixels.clear();
            pixels.shrink_to_fit();
            pixels.reserve(width * height);
            m_width = width;
            m_height = height;
        }

        uint32_t getWidth() const {
            return m_width;
        }

        uint32_t getHeight() const {
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