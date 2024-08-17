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

    private:
        point3 origin;
        point3 direction;
        point3 lower_left_corner;
        glm::vec3 horizontal;
        glm::vec3 vertical;
        glm::vec3 u, v, w;
        float lens_radius = 0.0f;
        uint32_t image_width;
        uint32_t image_height;
};
#endif