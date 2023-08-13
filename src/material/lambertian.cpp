#include <material/lambertian.hpp>

RAY_TRACING_NAMESPACE_BEGIN

Lambertian::Lambertian(Color3f const& albedo)
    : albedo{ albedo } {}

bool Lambertian::scatter([[maybe_unused]] Ray const& ray, Interaction const& interaction, RandomNumberGenerator& rng, Color3f* attenuation, Ray* scattered) const {
    auto target_direction{ interaction.normal + glm::normalize(random_vector3f_in_unit_sphere(rng)) };

    // Catch degenerate scatter direction.
    if (glm::epsilonEqual(glm::length(target_direction), 0.0_f, EPSILON<Float>)) {
        target_direction = interaction.normal;
    }

    *attenuation = this->albedo;
    *scattered = { interaction.hit_point, target_direction };
    return true;
}

RAY_TRACING_NAMESPACE_END
