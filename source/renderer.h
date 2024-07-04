#ifndef RENDERER_H
#define RENDERER_H

#include <iostream>
#include <glm/geometric.hpp>
#include <glm/vec4.hpp>
#include "camera.h"
#include "renderLayers.h"
#include "hittable.h"
#include "color.h"
#include "Materials/material.h"
#include "Materials/materials.h"
#include "rtweekend.h"

struct renderOptions {
    int image_width;
    int image_height;
    int samples_per_pixel;
    int max_bounces;
    bool transparent;
    float scale;
};

class renderer {
    public:
        renderer(const renderOptions& options) : m_options(options){}

        void render(const camera& cam,const hittable& world);

        pixelData castRay(const ray& r,const int& depth);

        color reflectRay(const ray& r,const int& depth);

    private:
        const camera* m_camera = nullptr;
        const hittable* m_scene = nullptr;
        renderOptions m_options;
};

#endif