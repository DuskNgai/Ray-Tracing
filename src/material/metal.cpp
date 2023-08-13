#include <material/metal.hpp>

RAY_TRACING_NAMESPACE_BEGIN

Metal::Metal(Color3f const& albedo, Float fuzz)
    : albedo{ albedo }
    , fuzz{ fuzz < 1.0_f ? fuzz : 1.0_f } {}

bool Metal::scatter(Ray const& ray, Interaction const& interaction, RandomNumberGenerator& rng, Color3f* attenuation, Ray* scattered) const {
    auto reflected{ glm::reflect(glm::normalize(ray.direction), interaction.normal) };

    *attenuation = this->albedo;
    *scattered = { interaction.hit_point, reflected + this->fuzz * glm::normalize(random_vector3f_in_unit_sphere(rng)) };
    return glm::dot(scattered->direction, interaction.normal) > 0;
}

RAY_TRACING_NAMESPACE_END
