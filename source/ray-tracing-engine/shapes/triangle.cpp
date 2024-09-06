#include "triangle.h"

Triangle::Triangle(std::array<point3,3> p_vertexes,uint32_t m) : vertices(p_vertexes),mat_idx(m) {
    point3 edgeAB = vertices[1] - vertices[0];
    point3 edgeAC = vertices[2] - vertices[0];
    normal = glm::cross(edgeAB,edgeAC);
};

bool Triangle::hit(const Ray& r,const float& t_min_s,const float& t_max_s, HitRecord& rec) const {
    const float discriminant = -glm::dot(r.dir,normal);
    if (discriminant < 1e-6f) {
        return false;
    }

    const point3 ao = r.orig - vertices[0];
    const point3 dao = glm::cross(ao,r.dir);
    const float invDet = 1.0f / discriminant;
    const float dst = glm::dot(ao,normal) * invDet;

    if(dst < 0){
        return false;
    }

    const float u = glm::dot(vertices[2] - vertices[0],dao) * invDet;
    const float v = -glm::dot(vertices[1] - vertices[0],dao) * invDet;
    const float w = 1 - u - v;
    
    if (u < 0 || v < 0 || w < 0) {
        return false;
    }

    rec.t = dst;
    rec.p = r.at(rec.t);
    rec.normal = glm::normalize(normal * w + normal * u + normal * v);
    rec.mat_idx = mat_idx;
    
    return true;
}