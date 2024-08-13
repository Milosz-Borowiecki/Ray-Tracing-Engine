#include "renderer.h"

void renderer::render(const camera& cam,const hittable& world){

    m_scene = &world;
	m_camera = &cam;

    m_renderLayer = renderLayer(m_options.image_width,m_options.image_height);
    
    size_t index = 0;
    for (int j = m_renderLayer.getHeight()-1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < m_renderLayer.getWidth(); ++i) {
            pixel current_pixel;

            ray r;
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

pixel renderer::castRay(const ray& r,const int& depth){
    hitRecord rec;
    color data;

    if (m_scene->hit(r, 0.0001f, infinity, rec)) {
        ray scattered;
        color attenuation;
        //  Normal Data
        //glm::vec3 normal = 0.5f * (rec.normal + color(1,1,1));
        //  Depth Data
        //data.depth = color(rec.t);

        if (rec.mat_ptr->scatter(r, rec, attenuation, scattered))
        {
            data = attenuation * reflectRay(scattered, depth - 1);
            //  Albedo Data
            //data.albedo = attenuation;
        }
        return pixel(data,1.0f);
    }
    if (m_options.transparent){
        return pixel(0.0f);
    }
    const glm::vec3 unit_direction = glm::normalize(r.direction());
    const float t = 0.5f * (unit_direction.y + 1.0f);
    return pixel((1.0f - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0),1.0f);
}

color renderer::reflectRay(const ray& r,const int& depth){
    hitRecord rec;

    if (depth <= 0) {
        return color(0, 0, 0);
    }

    if (m_scene->hit(r, 0.0001f, infinity, rec)) {
        ray scattered;
        color attenuation;
        if (rec.mat_ptr->scatter(r, rec, attenuation, scattered))
        {
            return attenuation * reflectRay(scattered,depth - 1);
        }
        return color(0,0,0);
    }
        const glm::vec3 unit_direction = glm::normalize(r.direction());
        const float t = 0.5f * (unit_direction.y + 1.0f);
        return (1.0f - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}

renderLayer renderer::getRenderLayer(){
    return m_renderLayer;
}

renderer::renderer(const renderOptions& options) : m_options(options){}