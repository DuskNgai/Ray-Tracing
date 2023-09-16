#include <material/isotropic.hpp>
#include <pdf/sphere-pdf.hpp>

RAY_TRACING_NAMESPACE_BEGIN

Isotropic::Isotropic(std::shared_ptr<Texture> const& albedo)
    : albedo{ albedo } {}

Isotropic::Isotropic(Color3f const& albedo)
    : albedo{ std::make_shared<SolidColor>(albedo) } {}

bool Isotropic::scatter(Ray const& ray, Interaction const& interaction, RandomNumberGenerator& rng, MaterialRecord* record) const {
    record->attenuation = this->albedo->sample(interaction.u, interaction.v, interaction.hit_point);
    record->pdf_ptr = std::make_shared<SpherePDF>();
    record->is_specular = false;
    return true;
}

Float Isotropic::bxdf([[maybe_unused]] Ray const& ray, [[maybe_unused]] Interaction const& interaction, [[maybe_unused]] Ray const& scattered) const {
    return 0.25_f / glm::pi<Float>();
}

RAY_TRACING_NAMESPACE_END
