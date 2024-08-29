#ifndef CAMERA_H
#define CAMERA_H

#include "../rtweekend.h"

class Camera {
    public:
        Camera(
            const point3& look_from,
            const point3& look_at,
            const glm::vec3& view_up,
            const float& vertical_field_of_view,
            const float& aspect_ratio,
            const float& aperture,
            const uint32_t& width,
            const uint32_t& height,
            const float& focus_dist = -1.0f
        );

        Ray getRay(const uint32_t& x_pos,const uint32_t& y_pos) const;

        Ray getNonRandomRay(const uint32_t& x_pos,const uint32_t& y_pos) const;
        
        point3 defocusDiskSample() const;

    private:
        point3 origin;
        point3 direction;
        glm::vec3 u, v, w;
        float lens_radius = 0.0f;
        uint32_t image_width;
        uint32_t image_height;
        glm::vec3 defocus_disk_u;
        glm::vec3 defocus_disk_v;
        glm::vec3 pixel_delta_u;
        glm::vec3 pixel_delta_v;
        point3 pixel00_loc;
        float m_aperture;
};
#endif