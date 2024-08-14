#include "camera.h"

Camera::Camera(
            const point3& look_from,
            const point3& look_at,
            const glm::vec3& view_up,
            const float& vertical_field_of_view,
            const float& aspect_ratio,
            const float& aperture,
            const int& width,
            const int& height,
            const float& focus_dist
        ) {
            const auto theta = degreesToRadians(vertical_field_of_view);
            const auto h = tan(theta / 2);
            const auto viewport_height = 2.0f * h;
            const auto viewport_width = aspect_ratio * viewport_height;

            w = glm::normalize(look_from - look_at);
            u = glm::normalize(glm::cross(view_up, w));
            v = glm::cross(w, u);

            origin = look_from;
            direction = look_at;
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

Ray Camera::getRay (const int& x_pos,const int& y_pos) const {
            const auto s = (x_pos + randomFloat()) / (image_width - 1);
            const auto t = (y_pos + randomFloat()) / (image_height - 1);
            if (lens_radius != 0.0f) {
                const glm::vec3 rd = lens_radius * randomInUnitDisk();
                const glm::vec3 offset = u * rd.x + v * rd.y;

                return Ray(
                    origin + offset,
                    lower_left_corner + s * horizontal + t * vertical - origin - offset
                );
            }

            return Ray(origin, lower_left_corner + s * horizontal + t * vertical - origin);
}