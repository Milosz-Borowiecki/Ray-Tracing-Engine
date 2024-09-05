#include "renderer.h"
#include "../color.h"

void Renderer::render(const Camera& cam,const Scene& world){

    m_scene = &world;
	m_camera = &cam;

    resizeRenderLayer(m_camera->getWidth(),m_camera->getHeight());

    for (uint32_t y = 0; y < m_renderLayer.getHeight(); ++y) {
        std::clog << "\rScanlines remaining: " << (m_renderLayer.getHeight() - y)<< ' ' << std::flush;
        for (uint32_t x = 0; x < m_renderLayer.getWidth(); ++x) {
            pixel current_pixel(0.0f,0.0f,0.0f,0.0f);
            Ray r;
            for (uint32_t sam = 0; sam < m_renderSettings.samples_per_pixel; ++sam) {
                r = m_camera->getRay(x, y);
                current_pixel += castRay(r,m_renderSettings.max_bounces);
           }
            current_pixel /= static_cast<float>(m_renderSettings.samples_per_pixel);

            current_pixel = glm::sqrt(current_pixel);

            m_renderLayer.savePixelData(current_pixel);
        }
    }
}

pixel Renderer::castRay(const Ray& r,const int& depth){
    HitRecord rec;

    if (m_scene->hittableGroup.hit(r, 0.001f, infinity, rec)) {
        Ray scattered;
        color attenuation(1.0f, 1.0f, 1.0f);
        //  Normal Data
        //glm::vec3 normal = 0.5f * (rec.normal + color(1,1,1));
        //  Depth Data
        //data.depth = color(rec.t);

        if (m_scene->materials[rec.mat_idx]->scatter(r, rec, attenuation, scattered))
        {
            return pixel(attenuation * reflectRay(scattered, depth - 1),1.0f);
            //  Albedo Data
            //data.albedo = attenuation;
        }
        return pixel(0.0f,0.0f,0.0f,1.0f);
    }
    if (m_renderSettings.transparent){
        return pixel(0.0f);
    }
    const glm::vec3 unit_direction = glm::normalize(r.direction());
    const float t = 0.5f * (unit_direction.y + 1.0f);
    return pixel((1.0f - t) * color(1.0f, 1.0f, 1.0f) + t * color(0.5f, 0.7f, 1.0f),1.0f);
}

color Renderer::reflectRay(const Ray& r,const int& depth){
    HitRecord rec;

    if (depth <= 0) {
        return color(0.0f, 0.0f, 0.0f);
    }

    if (m_scene->hittableGroup.hit(r, 0.001f, infinity, rec)) {
        Ray scattered;
        color attenuation(1.0f,1.0f,1.0f);
        if (m_scene->materials[rec.mat_idx]->scatter(r, rec, attenuation, scattered))
        {
            return attenuation * reflectRay(scattered,depth - 1);
        }
        return color(0.0f,0.0f,0.0f);
    }
    const glm::vec3 unit_direction = glm::normalize(r.direction());
    const float t = 0.5f * (unit_direction.y + 1.0f);
    return (1.0f - t) * color(1.0f, 1.0f, 1.0f) + t * color(0.5f, 0.7f, 1.0f);
}

void Renderer::resizeRenderLayer(const uint32_t& width,const uint32_t& height){
    
    if(m_renderLayer.getWidth() == width && m_renderLayer.getHeight() == height){
        return;
    }
    m_renderLayer.resize(width,height);
}

RenderLayer Renderer::getRenderLayer(){
    return m_renderLayer;
}