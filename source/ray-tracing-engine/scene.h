#ifndef SCENE_H
#define SCENE_H

#include "vec3.h"
#include "hittableList.h"

struct Scene {
    HittableList hittableGroup;
    std::vector<std::shared_ptr<Material>> materials;
};

#endif