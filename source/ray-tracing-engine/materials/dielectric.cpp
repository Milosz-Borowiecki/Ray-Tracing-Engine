#include "dielectric.h"

bool Dielectric::scatter(
    const Ray& r_in, const HitRecord& rec, color& attenuation, Ray& scattered
) const {
    attenuation = albedo;
    const float refraction_ratio = rec.front_face ? (1.0f/ir) : ir;

    const glm::vec3 unit_direction = glm::normalize(r_in.direction());
    const float cos_theta = fmin(dot(-unit_direction, rec.normal), 1.0f);
    const float sin_theta = sqrt(1.0f - cos_theta * cos_theta);

    const bool cannot_refract = refraction_ratio * sin_theta > 1.0f;
    glm::vec3 direction;

    if (cannot_refract || reflectance(cos_theta, refraction_ratio) > randomFloat()){
        direction = reflect(unit_direction, rec.normal);
    }else{
        direction = refract(unit_direction, rec.normal, refraction_ratio);
    }

    scattered = Ray(rec.p, direction);
    return true;
}

float Dielectric::reflectance(float cosine, float ref_idx) {
            auto r0 = (1 - ref_idx) / (1 + ref_idx);
            r0 = r0 * r0;
            return r0 + (1 - r0) * powf((1 - cosine),5.0f);
}
