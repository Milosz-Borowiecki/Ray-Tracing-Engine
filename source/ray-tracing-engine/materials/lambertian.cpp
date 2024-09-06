#include "lambertian.h"

Lambertian::Lambertian(const color& a) : albedo(a) {}

bool Lambertian::scatter(const Ray& r_in, const HitRecord& rec, color& attenuation, Ray& scattered) const {
    glm::vec3 scatter_direction = rec.normal + randomUnitVector();

    if (nearZero(scatter_direction)){
        scatter_direction = rec.normal;
    }

    scattered = Ray(rec.p, scatter_direction);
    attenuation = albedo;
    return true;
}
