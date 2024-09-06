#include "sphere.h"

bool Sphere::hit(const Ray& r,const float& t_min_s,const float& t_max_s, HitRecord& rec) const {
    const glm::vec3 oc = r.origin() - center;
    const glm::vec3 pre_a = r.direction();
    const auto a = glm::dot(pre_a,pre_a);
    const auto half_b = glm::dot(oc,pre_a);
    const auto c = glm::dot(oc,oc) - radius*radius;
    
    const auto discriminant = half_b*half_b - a*c;
    if (discriminant < 0.0f) {
        return false;
    }
    const auto sqrtd = sqrt(discriminant);
    
    auto root = (-half_b - sqrtd) / a;
    if (root < t_min_s || t_max_s < root) {
        root = (-half_b + sqrtd) / a;
        if (root < t_min_s || t_max_s < root){
            return false;
        }
    }
    
    rec.t = root;
    rec.p = r.at(rec.t);
    glm::vec3 outward_normal = (rec.p - center) / radius;
    rec.setFaceNormal(r, outward_normal);
    rec.mat_idx = mat_idx;
    
    return true;
}