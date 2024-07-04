#include "lambertian.h"

lambertian::lambertian(const color& a) : albedo(a) {}

bool lambertian::scatter(const ray& r_in, const hitRecord& rec, color& attenuation, ray& scattered) const {
    glm::vec3 scatter_direction = rec.normal + randomUnitVector();

    if (nearZero(scatter_direction)){
        scatter_direction = rec.normal;
    }

    scattered = ray(rec.p, scatter_direction);
    attenuation = albedo;
    return true;
}
