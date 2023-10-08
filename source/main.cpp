#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image/stb_image_write.h>
#include "camera.h"
#include "hittable_list.h"
#include "rtweekend.h"
#include "final_render.h"
#include "renderer.h"

int main() {

    constexpr float aspect_ratio = 16.0f / 9.0f;
    constexpr int image_width = 640;
    constexpr int image_height = static_cast<int>(image_width / aspect_ratio);

    render_options options;
    options.aspect_ratio = aspect_ratio;
    options.channels = 3;
    options.samples_per_pixel = 50;
    options.max_depth = 8;
    options.scale = 1.0f / options.samples_per_pixel;
    options.image_width = image_width;
    options.image_height = image_height;

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
    constexpr auto aperture = 0.1f;
#endif

    camera cam(lookfrom, lookat, vup, 20, aspect_ratio, aperture,image_width,image_height,dist_to_focus);

    renderer render_obj(options);

    std::cout << "P3 " << image_width << ' ' << image_height << '\n';

    image image_obj = render_obj.render(cam,world);

    stbi_write_png("image.png",image_obj.width,image_obj.height,image_obj.channels, image_obj.color_image.data(), image_obj.width * image_obj.channels);
    stbi_write_png("image_albedo.png",image_obj.width,image_obj.height,image_obj.channels, image_obj.albedo_image.data(), image_obj.width * image_obj.channels);
    stbi_write_png("image_normal.png",image_obj.width,image_obj.height,image_obj.channels, image_obj.normal_image.data(), image_obj.width * image_obj.channels);

    std::cerr << "\nDone.\n";
}