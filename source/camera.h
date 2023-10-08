#ifndef CAMERA_H
#define CAMERA_H

#include "rtweekend.h"

class camera {
    public:
        camera(
            const point3& lookfrom,
            const point3& lookat,
            const glm::vec3& vup,
            const float& vfov,
            const float& aspect_ratio,
            const float& aperture,
            const int& width,
            const int& height,
            const float& focus_dist = -1.0f
        );

        ray get_ray(const int& i,const int& j) const;

    private:
        point3 origin;
        point3 direction;
        point3 lower_left_corner;
        glm::vec3 horizontal;
        glm::vec3 vertical;
        glm::vec3 u, v, w;
        float lens_radius = 0.0f;
        int image_width;
        int image_height;
};
#endif