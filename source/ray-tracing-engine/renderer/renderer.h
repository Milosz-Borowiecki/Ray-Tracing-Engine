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
#include "../scene.h"

class Renderer {
    public:
        struct RenderSettings {
            uint32_t samples_per_pixel = 10;
            uint32_t max_bounces = 8;
            bool transparent = false;
        };      

        Renderer() = default;

        void render(const Camera& cam,const Scene& world);

        void resizeRenderLayer(const uint32_t& width,const uint32_t& height);

        RenderLayer getRenderLayer();
    private:
        pixel castRay(const Ray& r,const int& depth);

        color reflectRay(const Ray& r,const int& depth);

    private:
        const Camera* m_camera = nullptr;
        const Scene* m_scene = nullptr;
        RenderSettings m_renderSettings;
        RenderLayer m_renderLayer;
};

#endif