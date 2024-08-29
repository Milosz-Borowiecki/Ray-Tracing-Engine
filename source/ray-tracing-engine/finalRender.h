#ifndef FINAL_RENDER
#define FINAL_RENDER

#include "hittableList.h"
#include "rtweekend.h"
#include "shapes/sphere.h"
#include "materials/materials.h"


HittableList complexScene() {
    HittableList world;

    const auto ground_material = make_shared<Lambertian>(color(0.5f, 0.5f, 0.5f));
    world.add(make_shared<Sphere>(point3(0.0f,-1000.0f,0.0f), 1000.0f, ground_material));

    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            const auto choose_mat = randomFloat();
            const point3 center(a + 0.9f*randomFloat(), 0.2f, b + 0.9f*randomFloat());

            if (glm::length(center - point3(4, 0.2, 0)) > 0.9f) {
                shared_ptr<Material> sphere_material;

                if (choose_mat < 0.8) {
                    // diffuse
                    auto albedo = random() * random();
                    sphere_material = make_shared<Lambertian>(albedo);
                    world.add(make_shared<Sphere>(center, 0.2f, sphere_material));
                } else if (choose_mat < 0.95) {
                    // metal
                    auto albedo = random(0.5f, 1.0f);
                    auto fuzz = randomFloat(0.0f, 0.5f);
                    sphere_material = make_shared<Metal>(albedo, fuzz);
                    world.add(make_shared<Sphere>(center, 0.2f, sphere_material));
                } else {
                    // glass
                    sphere_material = make_shared<Dielectric>(color(1.0f, 1.0f, 1.0f),1.5f);
                    world.add(make_shared<Sphere>(center, 0.2f, sphere_material));
                }
            }
        }
    }

    const auto material1 = make_shared<Dielectric>(color(1.0f, 1.0f, 1.0f), 1.5f);
    world.add(make_shared<Sphere>(point3(0, 1, 0), 1.0f, material1));
    
    const auto material2 = make_shared<Lambertian>(color(0.4, 0.2, 0.1f));
    world.add(make_shared<Sphere>(point3(-4, 1, 0), 1.0f, material2));
    
    const auto material3 = make_shared<Metal>(color(0.7, 0.6, 0.5), 0.0f);
    world.add(make_shared<Sphere>(point3(4, 1, 0), 1.0f, material3));

    return world;
}

HittableList simpleScene(){

    HittableList world;

    auto material_ground = make_shared<Lambertian>(color(0.8, 0.8, 0.0));
    auto material_center = make_shared<Lambertian>(color(0.1, 0.2, 0.5));
    auto material_left   = make_shared<Dielectric>(color(1.0f, 1.0f, 1.0f),1.5f);
    auto material_right  = make_shared<Metal>(color(0.8, 0.6, 0.2), 0.3f);
    
    world.add(make_shared<Sphere>(point3( 0.0, -100.5, -1.0), 100.0f,material_ground));
    world.add(make_shared<Sphere>(point3( 0.0,    0.0, -1.0),   0.5f,material_center));
    world.add(make_shared<Sphere>(point3(-1.0,    0.0, -1.0),   0.5f,material_left));
    world.add(make_shared<Sphere>(point3(-1.0,    0.0, -1.0), -0.45f,material_left));
    world.add(make_shared<Sphere>(point3( 1.0,    0.0, -1.0),   0.5f,material_right));

    return world;

}
#endif