#ifndef CAMERA_H
#define CAMERA_H

#include "rtweekend.h"
#include <glm/vec3.hpp>

class camera {
    public:
        camera(
            point3 lookfrom,
            point3 lookat,
            glm::vec3 vup,
            float vfov,
            float aspect_ratio,
            float aperture,
            float focus_dist = -1.0f
        );

        ray get_ray(float s, float t) const;

    private:
        point3 origin;
        point3 lower_left_corner;
        glm::vec3 horizontal;
        glm::vec3 vertical;
        glm::vec3 u, v, w;
        float lens_radius = 0.0f;
};
#endif