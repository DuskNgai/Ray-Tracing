#include <material/isotropic.hpp>

RAY_TRACING_NAMESPACE_BEGIN

Isotropic::Isotropic(std::shared_ptr<Texture> const& albedo)
    : albedo{ albedo } {}

Isotropic::Isotropic(Color3f const& albedo)
    : albedo{ std::make_shared<SolidColor>(albedo) } {}

bool Isotropic::scatter(Ray const& ray, Interaction const& interaction, RandomNumberGenerator& rng, Color3f* attenuation, Ray* scattered) const {
    *attenuation = this->albedo->sample(interaction.u, interaction.v, interaction.hit_point);
    *scattered = { interaction.hit_point, glm::normalize(random_vector3f_in_unit_sphere(rng)), ray.time_point };
    return true;
}

RAY_TRACING_NAMESPACE_END
