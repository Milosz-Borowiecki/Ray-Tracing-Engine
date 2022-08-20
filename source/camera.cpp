#include "camera.h"

camera::camera(
            point3 lookfrom,
            point3 lookat,
            glm::vec3 vup,
            float vfov,
            float aspect_ratio,
            float aperture,
            float focus_dist
        ) {
            auto theta = degrees_to_radians(vfov);
            auto h = tan(theta/2);
            auto viewport_height = 2.0f * h;
            auto viewport_width = aspect_ratio * viewport_height;

            w = glm::normalize(lookfrom - lookat);
            u = glm::normalize(glm::cross(vup, w));
            v = glm::cross(w, u);

            origin = lookfrom;
            if (focus_dist != -1.0f) {
                horizontal = focus_dist * viewport_width * u;
                vertical = focus_dist * viewport_height * v;
                lower_left_corner = origin - horizontal / 2.0f - vertical / 2.0f - focus_dist * w;
                lens_radius = aperture / 2;
            }
            else {
                horizontal = viewport_width * u;
                vertical = viewport_height * v;
                lower_left_corner = origin - horizontal / 2.0f - vertical / 2.0f - w;
            }
        }

ray camera::get_ray (float s, float t) const {
            if (lens_radius != 0.0f) {
                glm::vec3 rd = lens_radius * random_in_unit_disk();
                glm::vec3 offset = u * rd.x + v * rd.y;

                return ray(
                    origin + offset,
                    lower_left_corner + s * horizontal + t * vertical - origin - offset
                );
            }

            return ray(origin, lower_left_corner + s * horizontal + t * vertical - origin);
}