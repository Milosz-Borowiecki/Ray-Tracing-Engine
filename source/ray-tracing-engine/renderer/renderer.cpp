#include "renderer.h"

void Renderer::render(const Camera& cam,const HittableList& world){

    m_scene = &world;
	m_camera = &cam;

    m_renderLayer = RenderLayer(m_options.image_width,m_options.image_height);
    
    for (uint32_t y = 0; y < m_renderLayer.getHeight(); ++y) {
        std::clog << "\rScanlines remaining: " << (m_options.image_height - y)<< ' ' << std::flush;
        for (uint32_t x = 0; x < m_renderLayer.getWidth(); ++x) {
            pixel current_pixel(0.0f,0.0f,0.0f,0.0f);
            Ray r;
            for (int sam = 0; sam < m_options.samples_per_pixel; ++sam) {
                r = cam.getRay(x, y);
                current_pixel += castRay(r,m_options.max_bounces);
           }
            current_pixel /= static_cast<float>(m_options.samples_per_pixel);

            m_renderLayer.savePixelData(current_pixel,x + (y * m_renderLayer.getWidth()));
        }
    }
}

pixel Renderer::castRay(const Ray& r,const int& depth){
    HitRecord rec;

    if (m_scene->hit(r, 0.001f, infinity, rec)) {
        Ray scattered;
        color attenuation(1.0f, 1.0f, 1.0f);
        //  Normal Data
        //glm::vec3 normal = 0.5f * (rec.normal + color(1,1,1));
        //  Depth Data
        //data.depth = color(rec.t);

        if (rec.mat_ptr->scatter(r, rec, attenuation, scattered))
        {
            return pixel(attenuation * reflectRay(scattered, depth - 1),1.0f);
            //  Albedo Data
            //data.albedo = attenuation;
        }
        return pixel(0.0f,0.0f,0.0f,1.0f);
    }
    if (m_options.transparent){
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

    if (m_scene->hit(r, 0.001f, infinity, rec)) {
        Ray scattered;
        color attenuation(1.0f,1.0f,1.0f);
        if (rec.mat_ptr->scatter(r, rec, attenuation, scattered))
        {
            return attenuation * reflectRay(scattered,depth - 1);
        }
        return color(0.0f,0.0f,0.0f);
    }
    const glm::vec3 unit_direction = glm::normalize(r.direction());
    const float t = 0.5f * (unit_direction.y + 1.0f);
    return (1.0f - t) * color(1.0f, 1.0f, 1.0f) + t * color(0.5f, 0.7f, 1.0f);
}

RenderLayer Renderer::getRenderLayer(){
    return m_renderLayer;
}

Renderer::Renderer(const RenderOptions& options) : m_options(options){}