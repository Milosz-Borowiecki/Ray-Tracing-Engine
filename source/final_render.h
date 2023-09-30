#ifndef FINAL_RENDER
#define FINAL_RENDER

#include "hittable_list.h"
#include "rtweekend.h"
#include "sphere.h"
#include "Materials/materials.h"


hittable_list random_scene() {
    hittable_list world;

    const auto ground_material = make_shared<lambertian>(color(0.5, 0.5, 0.5));
    world.add(make_shared<sphere>(point3(0,-1000,0), 1000.0f, ground_material));

    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            const auto choose_mat = random_float();
            const point3 center(a + 0.9f*random_float(), 0.2f, b + 0.9f*random_float());

            if (glm::length(center - point3(4, 0.2, 0)) > 0.9f) {
                shared_ptr<material> sphere_material;

                if (choose_mat < 0.8) {
                    // diffuse
                    auto albedo = random() * random();
                    sphere_material = make_shared<lambertian>(albedo);
                    world.add(make_shared<sphere>(center, 0.2f, sphere_material));
                } else if (choose_mat < 0.95) {
                    // metal
                    auto albedo = random(0.5f, 1.0f);
                    auto fuzz = random_float(0.0f, 0.5f);
                    sphere_material = make_shared<metal>(albedo, fuzz);
                    world.add(make_shared<sphere>(center, 0.2f, sphere_material));
                } else {
                    // glass
                    sphere_material = make_shared<dielectric>(1.5f);
                    world.add(make_shared<sphere>(center, 0.2f, sphere_material));
                }
            }
        }
    }

    const auto material1 = make_shared<dielectric>(1.5f);
    world.add(make_shared<sphere>(point3(0, 1, 0), 1.0f, material1));

    const auto material2 = make_shared<lambertian>(color(0.4, 0.2, 0.1f));
    world.add(make_shared<sphere>(point3(-4, 1, 0), 1.0f, material2));

    const auto material3 = make_shared<metal>(color(0.7, 0.6, 0.5), 0.0f);
    world.add(make_shared<sphere>(point3(4, 1, 0), 1.0f, material3));

    return world;
}
#endif