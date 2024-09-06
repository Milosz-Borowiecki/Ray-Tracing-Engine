#include "metal.h"

Metal::Metal(const color& a, float f) : albedo(a), fuzz(f < 1 ? f : 1) {}

bool Metal::scatter(
    const Ray& r_in, const HitRecord& rec, color& attenuation, Ray& scattered
) const {
    const glm::vec3 reflected = reflect(glm::normalize(r_in.direction()), rec.normal);
    scattered = Ray(rec.p, glm::normalize(reflected) + (fuzz * randomInUnitSphere()));
    attenuation = albedo;
    return (glm::dot(scattered.direction(), rec.normal) > 0.0f);
}
