#ifndef RENDERER_H
#define RENDERER_H

#include <iostream>
#include <glm/geometric.hpp>
#include <glm/vec4.hpp>
#include "camera.h"
#include "../renderLayer.h"
#include "../shapes/hittable.h"
#include "../materials/materials.h"
#include "../rtweekend.h"
#include "../hittableList.h"

struct RenderOptions {
    uint32_t image_width;
    uint32_t image_height;
    int samples_per_pixel;
    int max_bounces;
    bool transparent;
    float scale;
};

class Renderer {
    public:
        Renderer(const RenderOptions& options);

        void render(const Camera& cam,const HittableList& world);

        RenderLayer getRenderLayer();
    private:

        pixel castRay(const Ray& r,const int& depth);

        color reflectRay(const Ray& r,const int& depth);

    private:
        const Camera* m_camera = nullptr;
        const HittableList* m_scene = nullptr;
        RenderOptions m_options;
        RenderLayer m_renderLayer;
};

#endif