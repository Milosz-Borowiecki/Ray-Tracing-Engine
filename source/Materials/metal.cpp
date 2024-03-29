#include "metal.h"

metal::metal(const color& a, float f) : albedo(a), fuzz(f < 1 ? f : 1) {}

bool metal::scatter(
    const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered
) const {
    const glm::vec3 reflected = reflect(glm::normalize(r_in.direction()), rec.normal);
    scattered = ray(rec.p, reflected + fuzz*random_in_unit_sphere());
    attenuation = albedo;
    return (glm::dot(scattered.direction(), rec.normal) > 0.0f);
}
