#include "hittableList.h"

bool HittableList::hit(const Ray& r,const float& t_min,const float& t_max, HitRecord& rec) const {
    HitRecord temp_rec;
    bool hit_anything = false;
    float closest_so_far = t_max;

    for (const auto& object : objects) {
        if (object->hit(r, t_min, closest_so_far, temp_rec)) {
            hit_anything = true;
            closest_so_far = temp_rec.t;
            rec = temp_rec;
        }
    }

    return hit_anything;
}

HittableList::HittableList(shared_ptr<Hittable> object) { 
    add(object);
}

void HittableList::clear() { 
    objects.clear();
    objects.shrink_to_fit();
}
void HittableList::add(shared_ptr<Hittable> object) {
    objects.push_back(object);
}