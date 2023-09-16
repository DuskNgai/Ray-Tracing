#include <material/lambertian.hpp>
#include <pdf/cosine-pdf.hpp>

RAY_TRACING_NAMESPACE_BEGIN

Lambertian::Lambertian(Color3f const& albedo)
    : albedo{ std::make_shared<SolidColor>(albedo) } {}

Lambertian::Lambertian(std::shared_ptr<Texture> albedo)
    : albedo{ albedo } {}

bool Lambertian::scatter([[maybe_unused]] Ray const& ray, Interaction const& interaction, RandomNumberGenerator& rng, MaterialRecord* record) const {
    record->attenuation = this->albedo->sample(interaction.u, interaction.v, interaction.hit_point);
    record->pdf_ptr = std::make_shared<CosinePDF>(interaction.normal);
    record->is_specular = false;
    return true;
}

Float Lambertian::bxdf([[maybe_unused]] Ray const& ray, Interaction const& interaction, [[maybe_unused]] Ray const& scattered) const {
    auto cosine{ glm::dot(interaction.normal, glm::normalize(scattered.direction)) };
    return cosine < 0.0_f ? 0.0_f : cosine / glm::pi<Float>();
}

RAY_TRACING_NAMESPACE_END
