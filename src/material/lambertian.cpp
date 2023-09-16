#include <material/lambertian.hpp>

RAY_TRACING_NAMESPACE_BEGIN

Lambertian::Lambertian(Color3f const& albedo)
    : albedo{ std::make_shared<SolidColor>(albedo) } {}

Lambertian::Lambertian(std::shared_ptr<Texture> albedo)
    : albedo{ albedo } {}

bool Lambertian::scatter(Ray const& ray, Interaction const& interaction, RandomNumberGenerator& rng, Color3f* attenuation, Ray* scattered) const {
    auto target_direction{ interaction.normal + glm::normalize(random_vector3f_in_unit_sphere(rng)) };

    // Catch degenerate scatter direction.
    if (glm::epsilonEqual(glm::length(target_direction), 0.0_f, EPSILON<Float>)) {
        target_direction = interaction.normal;
    }

    *attenuation = this->albedo->sample(interaction.u, interaction.v, interaction.hit_point);
    *scattered = { interaction.hit_point, target_direction, ray.time_point };
    return true;
}

RAY_TRACING_NAMESPACE_END
