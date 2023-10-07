#include "renderer.h"

image renderer::render(const camera& cam,const hittable& world){

    m_scene = &world;
	m_camera = &cam;

    image img = image(m_options.image_width,m_options.image_height,m_options.channels);
    
    unsigned int index = 0;
    for (int j = m_options.image_height-1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < m_options.image_width; ++i) {
            pixel_data pixel;

            ray r;
            for (int s = 0; s < m_options.samples_per_pixel; ++s) {
                r = cam.get_ray(i, j);
                pixel += super_ray(r,m_options.max_depth);
            }

            pixel = prepare_pixel_to_write(pixel,m_options.scale);

            img.save_pixel_data(pixel,index);

            index += m_options.channels;
        }
    }

    return img;
}

pixel_data renderer::super_ray(const ray& r,const int& depth){
    hit_record rec;
    pixel_data data;

    if (m_scene->hit(r, 0.0001f, infinity, rec)) {
        ray scattered;
        color attenuation;
        data.normal = 0.5f * (rec.normal + color(1,1,1));
        if (rec.mat_ptr->scatter(r, rec, attenuation, scattered))
        {
            data.color = attenuation * ray_color(scattered, depth - 1);
            data.albedo = attenuation;
        }
        return data;
    }
    const glm::vec3 unit_direction = glm::normalize(r.direction());
    const float t = 0.5f * (unit_direction.y + 1.0f);
    return pixel_data((1.0f - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0));
}

color renderer::ray_color(const ray& r,const int& depth){
    hit_record rec;

    if (depth <= 0) {
        return color(0, 0, 0);
    }

    if (m_scene->hit(r, 0.0001f, infinity, rec)) {
        ray scattered;
        color attenuation;
        if (rec.mat_ptr->scatter(r, rec, attenuation, scattered))
        {
            return attenuation * ray_color(scattered,depth - 1);
        }
        return color(0,0,0);
    }
        const glm::vec3 unit_direction = glm::normalize(r.direction());
        const float t = 0.5f * (unit_direction.y + 1.0f);
        return (1.0f - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}