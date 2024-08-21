//#define STB_IMAGE_WRITE_IMPLEMENTATION
//#include <stb_image/stb_image_write.h>
#include <chrono>
#include "Renderer/camera.h"
#include "hittableList.h"
#include "rtweekend.h"
#include "finalRender.h"
#include "Renderer/renderer.h"

int main() {

    constexpr float aspect_ratio = 16.0f / 9.0f;
    constexpr uint32_t image_width = 640;
    constexpr uint32_t image_height = static_cast<uint32_t>(image_width / aspect_ratio);

    RenderOptions options;
    options.samples_per_pixel = 50;
    options.max_bounces = 8;
    options.image_width = image_width;
    options.image_height = image_height;
    options.transparent = 0;

#if 0
    HittableList world = complexScene();

    constexpr point3 lookfrom(13,2,3);
    constexpr point3 lookat(0,0,0);
    constexpr point3 vup(0,1,0);
    constexpr auto dist_to_focus = 10.0f;
    constexpr auto aperture = 0.1f;
#else
    HittableList world = simpleScene();

    constexpr point3 lookfrom(3,3,2);
    constexpr point3 lookat(0,0,-1);
    constexpr glm::vec3 vup(0,1,0);
    const auto dist_to_focus = glm::length((lookfrom - lookat));
    constexpr auto aperture = 0.1f;
#endif

    Camera cam(lookfrom, lookat, vup, 20, aspect_ratio, aperture,image_width,image_height,dist_to_focus);

    Renderer render_obj(options);

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    auto start = std::chrono::high_resolution_clock::now();
 
    render_obj.render(cam,world);

    auto stop = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

    std::cerr << "Time taken to render: "<< duration.count() << " milliseconds\n";

    std::cerr << "\nDone.\n";
}