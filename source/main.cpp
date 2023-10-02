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
#include "image.h"
#include <array>
#include <iostream>
#include <memory>

color ray_color(const ray& r, const hittable& world,const int& depth) {
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

pixel_data super_ray(const ray& r, const hittable& world,const int& depth){
    hit_record rec;
    pixel_data data;

    if (world.hit(r, 0.0001f, infinity, rec)) {
        ray scattered;
        color attenuation;
        data.normal = 0.5f * (rec.normal + color(1,1,1));
        if (rec.mat_ptr->scatter(r, rec, attenuation, scattered))
        {
            data.color = attenuation * ray_color(scattered, world, depth - 1);
            data.albedo = attenuation;
        }
        return data;
    }
    const glm::vec3 unit_direction = glm::normalize(r.direction());
    const float t = 0.5f * (unit_direction.y + 1.0f);
    return pixel_data((1.0f - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0));
}

int main() {

    constexpr auto aspect_ratio = 16.0f / 9.0f;
    constexpr int image_width = 640;
    constexpr int image_height = static_cast<int>(image_width / aspect_ratio);
    constexpr int samples_per_pixel = 50;
    constexpr int max_depth = 8;
    constexpr int channels = 3;
    constexpr auto scale = 1.0f / samples_per_pixel;

    auto image_array = std::make_unique<std::array<uint8_t,channels * image_height * image_width>>();
    auto image_albedo = std::make_unique<std::array<uint8_t,channels * image_height * image_width>>();
    auto image_normal = std::make_unique<std::array<uint8_t,channels * image_height * image_width>>();


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
    const auto dist_to_focus = glm::length((lookfrom - lookat));
    constexpr auto aperture = 0.01f;
#endif

    camera cam(lookfrom, lookat, vup, 20, aspect_ratio, aperture,image_width,image_height,dist_to_focus);

    std::cout << "P3 " << image_width << ' ' << image_height << '\n';

    unsigned int index = 0;
    for (int j = image_height-1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i) {
            pixel_data pixel;

            ray r;
            for (int s = 0; s < samples_per_pixel; ++s) {
                r = cam.get_ray(i, j);
                pixel += super_ray(r, world, max_depth);
            }

            pixel.color = prepare_color_to_write(pixel.color,scale);
            pixel.albedo = prepare_color_to_write(pixel.albedo, scale);
            pixel.normal = prepare_color_to_write(pixel.normal, scale);

            image_array->data()[index] = static_cast<uint8_t>(pixel.color.x);
            image_albedo->data()[index] = static_cast<uint8_t>(pixel.albedo.x);
            image_normal->data()[index] = static_cast<uint8_t>(pixel.normal.x);
            index++;
            image_array->data()[index] = static_cast<uint8_t>(pixel.color.y);
            image_albedo->data()[index] = static_cast<uint8_t>(pixel.albedo.y);
            image_normal->data()[index] = static_cast<uint8_t>(pixel.normal.y);
            index++;
            image_array->data()[index] = static_cast<uint8_t>(pixel.color.z);
            image_albedo->data()[index] = static_cast<uint8_t>(pixel.albedo.z);
            image_normal->data()[index] = static_cast<uint8_t>(pixel.normal.z);
            index++;
        }
    }

    stbi_write_png("image.png",image_width,image_height,channels,image_array.get(), image_width * channels);
    stbi_write_png("image_albedo.png",image_width,image_height,channels,image_albedo.get(), image_width * channels);
    stbi_write_png("image_normal.png",image_width,image_height,channels,image_normal.get(), image_width * channels);

    std::cerr << "\nDone.\n";
}