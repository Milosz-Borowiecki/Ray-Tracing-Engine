#ifndef FINAL_RENDER
#define FINAL_RENDER

#include "hittableList.h"
#include "rtweekend.h"
#include "shapes/sphere.h"
#include "materials/materials.h"
#include "scene.h"
#include "shapes/triangle.h"


static Scene complexScene() {
    Scene world;

    world.materials.push_back(make_shared<Lambertian>(color(0.5f, 0.5f, 0.5f)));
    world.hittableGroup.add(make_shared<Sphere>(point3(0.0f,-1000.0f,0.0f), 1000.0f,0));

    uint32_t index = 0;

    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            const auto choose_mat = randomFloat();
            const point3 center(a + 0.9f*randomFloat(), 0.2f, b + 0.9f*randomFloat());
    
            if (glm::length(center - point3(4, 0.2, 0)) > 0.9f) {
                shared_ptr<Material> sphere_material;
    
                if (choose_mat < 0.8) {
                    // diffuse
                    auto albedo = random() * random();
                    world.materials.push_back(make_shared<Lambertian>(albedo));
                    index++;
                    world.hittableGroup.add(make_shared<Sphere>(center,0.2f,index));
                } else if (choose_mat < 0.95) {
                    // metal
                    auto albedo2 = random(0.5f, 1.0f);
                    auto fuzz = randomFloat(0.0f, 0.5f);
                    world.materials.push_back(make_shared<Metal>(albedo2,fuzz));
                    index++;
                    world.hittableGroup.add(make_shared<Sphere>(center,0.2f,index));
                } else {
                    // glass
                    world.materials.push_back(make_shared<Dielectric>(color(1.0f,1.0f,1.0f),1.5f));
                    index++;
                    world.hittableGroup.add(make_shared<Sphere>(center,0.2f,index));
                }
            }
        }
    }

    world.materials.push_back(make_shared<Dielectric>(color(1.0f,1.0f,1.0f),1.5f));
    index++;
    world.hittableGroup.add(make_shared<Sphere>(point3(0,1,0),1.0f,index));
    
    world.materials.push_back(make_shared<Lambertian>(color(0.4f,0.2f,0.1f)));
    index++;
    world.hittableGroup.add(make_shared<Sphere>(point3(-4,1,0),1.0f,index));
    
    world.materials.push_back(make_shared<Metal>(color(0.7f,0.6f,0.5f),0.0f));
    index++;
    world.hittableGroup.add(make_shared<Sphere>(point3(4,1,0),1.0f,index));

    return world;
}

static Scene simpleScene(){
    Scene world;

    world.materials.push_back(make_shared<Lambertian>(color(0.8f,0.8f,0.0f)));
    world.materials.push_back(make_shared<Lambertian>(color(0.1f,0.2f,0.5f)));
    world.materials.push_back(make_shared<Dielectric>(color(1.0f,1.0f,1.0f),1.5f));
    world.materials.push_back(make_shared<Metal>(color(0.8f,0.6f,0.2f),0.3f));
    
    world.hittableGroup.add(make_shared<Sphere>(point3( 0.0f,-100.5f,-1.0f),100.0f,0));
    world.hittableGroup.add(make_shared<Sphere>(point3( 0.0f,0.0f,-1.0f),0.5f,1));
    world.hittableGroup.add(make_shared<Sphere>(point3(-1.0f,0.0f,-1.0f),0.5f,2));
    world.hittableGroup.add(make_shared<Sphere>(point3(-1.0f,0.0f,-1.0f),-0.45f,2));
    world.hittableGroup.add(make_shared<Sphere>(point3( 1.0f,0.0f,-1.0f),0.5f,3));

    return world;
}

static Scene triangleScene(){
    Scene world;

    world.materials.push_back(make_shared<Lambertian>(color(1.0f,0.0f,0.0f)));
    std::array<point3,3> cord = {
        point3(1.0f,0.0f,0.0f),
        point3(0.0f,1.5f,0.0f),
        point3(-1.0f,0.0f,1.0f)
    };
    world.hittableGroup.add(make_shared<Triangle>(cord,0));

    return world;
}
#endif