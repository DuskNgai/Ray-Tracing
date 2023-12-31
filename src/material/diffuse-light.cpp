#include <material/diffuse-light.hpp>

RAY_TRACING_NAMESPACE_BEGIN

DiffuseLight::DiffuseLight(Color3f const& emit)
    : emit{ std::make_shared<SolidColor>(emit) } {}

DiffuseLight::DiffuseLight(std::shared_ptr<Texture> const& emit)
    : emit{ emit } {}

bool DiffuseLight::scatter([[maybe_unused]] Ray const& ray, [[maybe_unused]] Interaction const& interaction, [[maybe_unused]] RandomNumberGenerator& rng, [[maybe_unused]] MaterialRecord* record) const {
    return false;
}

Color3f DiffuseLight::emitted(Interaction const& interaction) const {
    if (not interaction.is_outer_face) {
        return {};
    }
    return this->emit->sample(interaction.u, interaction.v, interaction.hit_point);
}

RAY_TRACING_NAMESPACE_END
