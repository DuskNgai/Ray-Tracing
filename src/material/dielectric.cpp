#include <material/dielectric.hpp>

RAY_TRACING_NAMESPACE_BEGIN

Dielectric::Dielectric(Float rior)
    : rior{ rior } {}

bool Dielectric::scatter(Ray const& ray, Interaction const& interaction, RandomNumberGenerator& rng, MaterialRecord* record) const {
    auto unit_dir{ glm::normalize(ray.direction) };
    auto rior_actual{ interaction.is_outer_face ? 1.0_f / this->rior : this->rior };
    auto refracted{ refract(unit_dir, interaction.normal, rior_actual) };

    // Schlick's approximation.
    auto schlick{
        [](Float cosine, Float rior) {
            auto r0 = (1.0_f - rior) / (1.0_f + rior);
            r0 = r0 * r0;
            return r0 + (1.0_f - r0) * std::pow((1.0_f - cosine), 5.0_f);
        }
    };

    Vector3f target_direction;
    if (not refracted.has_value() or schlick(glm::dot(-unit_dir, interaction.normal), rior) > rng()) {
        target_direction = glm::reflect(unit_dir, interaction.normal);
    }
    else {
        target_direction = refracted.value();
    }

    record->attenuation = { 1.0_f, 1.0_f, 1.0_f };
    record->pdf_ptr = nullptr;
    record->specular_ray = { interaction.hit_point, target_direction, ray.time_point };
    record->is_specular = true;
    return true;
}

RAY_TRACING_NAMESPACE_END
