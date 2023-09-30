#include "rtweekend.h"

#include <glm/geometric.hpp>
#include "color.h"
#include "hittable_list.h"
#include "sphere.h"
#include "camera.h"
#include "Materials/materials.h"
#include "final_render.h"

#include <iostream>

color ray_color(const ray& r, const hittable& world, int depth) {
    hit_record rec;

    if (depth <= 0) {
        return color(0, 0, 0);
    }

    if (world.hit(r, 0.0001f, infinity, rec)) {
        ray scattered;
        color attenuation;
        if (rec.mat_ptr->scatter(r, rec, attenuation, scattered))
        {
            return attenuation * ray_color(scattered, world, depth - 1);
        }
        return color(0,0,0);
    }
        const glm::vec3 unit_direction = glm::normalize(r.direction());
        const float t = 0.5f * (unit_direction.y + 1.0f);
        return (1.0f - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}

int main() {

    constexpr auto aspect_ratio = 16.0f / 9.0f;
    constexpr int image_width = 400;
    constexpr int image_height = static_cast<int>(image_width / aspect_ratio);
    constexpr int samples_per_pixel = 50;
    constexpr int max_depth = 8;

    hittable_list world = random_scene();

    constexpr point3 lookfrom(13,2,3);
    constexpr point3 lookat(0,0,0);
    constexpr glm::vec3 vup(0,1,0);
    constexpr auto dist_to_focus = 10.0f;
    constexpr auto aperture = 0.1f;

    camera cam(lookfrom, lookat, vup, 20, aspect_ratio, aperture,dist_to_focus);

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = image_height-1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i) {
            color pixel_color(0, 0, 0);
            for (int s = 0; s < samples_per_pixel; ++s) {
                const auto u = (i + random_float()) / (image_width-1);
                const auto v = (j + random_float()) / (image_height-1);
                ray r = cam.get_ray(u, v);
                pixel_color += ray_color(r, world, max_depth);
            }
            write_color(std::cout, pixel_color, samples_per_pixel);
        }
    }

    std::cerr << "\nDone.\n";
}