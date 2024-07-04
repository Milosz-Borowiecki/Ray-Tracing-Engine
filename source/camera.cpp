#include "camera.h"

camera::camera(
            const point3& lookfrom,
            const point3& lookat,
            const glm::vec3& vup,
            const float& vfov,
            const float& aspect_ratio,
            const float& aperture,
            const int& width,
            const int& height,
            const float& focus_dist
        ) {
            const auto theta = degreesToRadians(vfov);
            const auto h = tan(theta / 2);
            const auto viewport_height = 2.0f * h;
            const auto viewport_width = aspect_ratio * viewport_height;

            w = glm::normalize(lookfrom - lookat);
            u = glm::normalize(glm::cross(vup, w));
            v = glm::cross(w, u);

            origin = lookfrom;
            direction = lookat;
            image_height = height;
            image_width = width;
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

ray camera::getRay (const int& i,const int& j) const {

            const auto s = (i + randomFloat()) / (image_width - 1);
            const auto t = (j + randomFloat()) / (image_height - 1);
            if (lens_radius != 0.0f) {
                const glm::vec3 rd = lens_radius * randomInUnitDisk();
                const glm::vec3 offset = u * rd.x + v * rd.y;

                return ray(
                    origin + offset,
                    lower_left_corner + s * horizontal + t * vertical - origin - offset
                );
            }

            return ray(origin, lower_left_corner + s * horizontal + t * vertical - origin);
}