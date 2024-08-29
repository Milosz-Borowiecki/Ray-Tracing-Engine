#include "camera.h"

Camera::Camera(
            const point3& look_from,
            const point3& look_at,
            const glm::vec3& view_up,
            const float& vertical_field_of_view,
            const float& aspect_ratio,
            const float& aperture,
            const uint32_t& width,
            const uint32_t& height,
            const float& focus_dist
        ) {
            image_height = height;
            image_width = width;
            origin = look_from;
            direction = look_at;
            m_aperture = aperture;
            const auto theta = degreesToRadians(vertical_field_of_view);
            const auto h = tan(theta / 2.0f);
            const auto viewport_height = 2.0f * h * focus_dist;
            const auto viewport_width = viewport_height * (static_cast<float>(image_width)/static_cast<float>(image_height));

            w = glm::normalize(origin - direction);
            u = glm::normalize(glm::cross(view_up, w));
            v = glm::cross(w, u);

            glm::vec3 viewport_u = viewport_width * u;
            glm::vec3 viewport_v = viewport_height * -v;  

            pixel_delta_u = viewport_u / static_cast<float>(image_width);
            pixel_delta_v = viewport_v / static_cast<float>(image_height);

            auto viewport_upper_left = origin - (focus_dist * w) - viewport_u/2.0f - viewport_v/2.0f;
            pixel00_loc = viewport_upper_left + 0.5f * (pixel_delta_u + pixel_delta_v);

            auto defocus_radius = focus_dist * std::tan(degreesToRadians(m_aperture / 2.0f));
            defocus_disk_u = u * defocus_radius;
            defocus_disk_v = v * defocus_radius;
        }

Ray Camera::getRay (const uint32_t& x_pos,const uint32_t& y_pos) const {
            auto pixel_sample = pixel00_loc
                              + ((x_pos + (randomFloat() - 0.5f)) * pixel_delta_u)
                              + ((y_pos + (randomFloat() - 0.5f)) * pixel_delta_v);

            auto ray_origin = (m_aperture <= 0) ? origin : defocusDiskSample();
            auto ray_direction = pixel_sample - ray_origin;

            return Ray(ray_origin, ray_direction);
}

Ray Camera::getNonRandomRay (const uint32_t& x_pos,const uint32_t& y_pos) const {
            auto pixel_sample = pixel00_loc
                              + (static_cast<float>(x_pos) * pixel_delta_u)
                              + (static_cast<float>(y_pos) * pixel_delta_v);

            auto ray_origin = (m_aperture <= 0) ? origin : defocusDiskSample();
            auto ray_direction = pixel_sample - ray_origin;

            return Ray(ray_origin, ray_direction);
}

point3 Camera::defocusDiskSample() const {
        auto p = randomInUnitDisk();
        return origin + (p[0] * defocus_disk_u) + (p[1] * defocus_disk_v);
    }
