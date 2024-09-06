#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "shapes/hittable.h"

#include <memory>
#include <vector>

using std::shared_ptr;
using std::make_shared;

class HittableList {
    public:
        HittableList() = default;
        HittableList(shared_ptr<Hittable> object);

        void clear();
        void add(shared_ptr<Hittable> object);

        bool hit(
            const Ray& r,const float& t_min,const float& t_max, HitRecord& rec) const;

    public:
        std::vector<shared_ptr<Hittable>> objects;
};
#endif