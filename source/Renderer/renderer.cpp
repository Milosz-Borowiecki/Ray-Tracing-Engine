#include "renderer.h"

void Renderer::render(const Camera& cam,const HittableList& world){

    m_scene = &world;
	m_camera = &cam;

    m_renderLayer = RenderLayer(m_options.image_width,m_options.image_height);
    
    size_t index = 0;
    for (int j = m_renderLayer.getHeight()-1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < m_renderLayer.getWidth(); ++i) {
            pixel current_pixel(0.0f,0.0f,0.0f,0.0f);
            Ray r;
            for (int s = 0; s < m_options.samples_per_pixel; ++s) {
                r = cam.getRay(i, j);
                current_pixel += castRay(r,m_options.max_bounces);
           }

            current_pixel /= static_cast<float>(m_options.samples_per_pixel);

            m_renderLayer.savePixelData(current_pixel,index);
            index++;
        }
    }
}

pixel Renderer::castRay(const Ray& r,const int& depth){
    HitRecord rec;

    if (m_scene->hit(r, 0.0001f, infinity, rec)) {
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

    if (m_scene->hit(r, 0.0001f, infinity, rec)) {
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