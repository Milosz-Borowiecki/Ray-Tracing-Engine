#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image/stb_image_write.h>
#include "rtweekend.h"
#include <glm/geometric.hpp>
#include "color.h"
#include "hittable_list.h"
#include "sphere.h"
#include "camera.h"
#include "Materials/materials.h"
#include "final_render.h"
#include <array>
#include <iostream>
#include <memory>

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
    constexpr int channels = 3;
    constexpr auto scale = 1.0f / samples_per_pixel;

    auto image_array = std::make_unique<std::array<uint8_t,3 * image_height * image_width>>();


#if 0
    hittable_list world = complex_scene();

    constexpr point3 lookfrom(13,2,3);
    constexpr point3 lookat(0,0,0);
    constexpr point3 vup(0,1,0);
    constexpr auto dist_to_focus = 10.0f;
    constexpr auto aperture = 0.1f;
#else
    hittable_list world = simple_scene();

    constexpr point3 lookfrom(3,3,2);
    constexpr point3 lookat(0,0,-1);
    constexpr glm::vec3 vup(0,1,0);
    const auto dist_to_focus = glm::length((lookfrom-lookat));
    constexpr auto aperture = 2.0f;
#endif

    camera cam(lookfrom, lookat, vup, 20, aspect_ratio, aperture,dist_to_focus);

    std::cout << "P3 " << image_width << ' ' << image_height << '\n';

    unsigned int index = 0;
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

            color final_color = prepare_color_to_write(pixel_color,scale);

            image_array->data()[index] = static_cast<uint8_t>(final_color.x);
            index++;
            image_array->data()[index] = static_cast<uint8_t>(final_color.y);
            index++;
            image_array->data()[index] = static_cast<uint8_t>(final_color.z);
            index++;

            //write_color(pixel_color);
        }
    }

    stbi_write_png("image.png",image_width,image_height,channels,image_array.get(),image_width * channels);

    std::cerr << "\nDone.\n";
}