#include "dielectric.h"

bool dielectric::scatter(
    const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered
) const {
    attenuation = color(1.0, 1.0, 1.0);
    const float refraction_ratio = rec.front_face ? (1.0f/ir) : ir;

    const glm::vec3 unit_direction = glm::normalize(r_in.direction());
    const float cos_theta = fmin(dot(-unit_direction, rec.normal), 1.0f);
    const float sin_theta = sqrt(1.0f - cos_theta*cos_theta);

    const bool cannot_refract = refraction_ratio * sin_theta > 1.0f;
    glm::vec3 direction;

    if (cannot_refract){
        direction = reflect(unit_direction, rec.normal);
    }else{
        direction = refract(unit_direction, rec.normal, refraction_ratio);
    }

    scattered = ray(rec.p, direction);
    return true;
}

float dielectric::reflectance(float cosine, float ref_idx) {
            auto r0 = (1-ref_idx) / (1+ref_idx);
            r0 = r0*r0;
            return r0 + (1-r0)*powf((1 - cosine),5.0f);
}
