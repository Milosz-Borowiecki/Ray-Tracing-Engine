#include "renderer.h"

renderLayer renderer::render(const camera& cam,const hittable& world){

    m_scene = &world;
	m_camera = &cam;

    renderLayer r_layer_final = renderLayer(m_options.image_width,m_options.image_height);
    
    uint32_t index = 0;
    for (int j = m_options.image_height-1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < m_options.image_width; ++i) {
            pixelData pixel_obj;

            ray r;
            for (int s = 0; s < m_options.samples_per_pixel; ++s) {
                r = cam.getRay(i, j);
                pixel_obj += castRay(r,m_options.max_bounces);
            }

            pixel_obj = preparePixelToWrite(pixel_obj,m_options.scale);

            r_layer_final.savePixelData(pixel_obj,index);

            index += m_options.channels;
        }
    }
    return r_layer_final;
}

pixelData renderer::castRay(const ray& r,const int& depth){
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