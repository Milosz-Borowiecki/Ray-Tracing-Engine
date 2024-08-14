#ifndef RENDERER_H
#define RENDERER_H

#include <iostream>
#include <glm/geometric.hpp>
#include <glm/vec4.hpp>
#include "camera.h"
#include "renderLayer.h"
#include "hittable.h"
#include "color.h"
#include "Materials/material.h"
#include "Materials/materials.h"
#include "rtweekend.h"

struct RenderOptions {
    int image_width;
    int image_height;
    int samples_per_pixel;
    int max_bounces;
    bool transparent;
    float scale;
};

class Renderer {
    public:
        Renderer(const RenderOptions& options);

        void render(const Camera& cam,const Hittable& world);

        RenderLayer getRenderLayer();
    private:

        pixel castRay(const Ray& r,const int& depth);

        color reflectRay(const Ray& r,const int& depth);

    private:
        const Camera* m_camera = nullptr;
        const Hittable* m_scene = nullptr;
        RenderOptions m_options;
        RenderLayer m_renderLayer;
};

#endif