#ifndef RENDERER_H
#define RENDERER_H

#include <iostream>
#include <glm/geometric.hpp>
#include "camera.h"
#include "image.h"
#include "hittable.h"
#include "color.h"
#include "Materials/material.h"
#include "Materials/materials.h"
#include "rtweekend.h"

struct render_options {
    float aspect_ratio;
    int image_width;
    int image_height;
    int samples_per_pixel;
    int max_depth;
    int channels;
    float scale;
};

class renderer {
    public:
        renderer(const render_options& options) : m_options(options){}

        image render(const camera& cam,const hittable& world);

        pixel_data super_ray(const ray& r,const int& depth);

        color ray_color(const ray& r,const int& depth);

    private:
        const camera* m_camera = nullptr;
        const hittable* m_scene = nullptr;
        const render_options m_options;
};

#endif