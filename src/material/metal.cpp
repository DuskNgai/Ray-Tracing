#include <material/metal.hpp>

RAY_TRACING_NAMESPACE_BEGIN

Metal::Metal(Color3f const& albedo, Float fuzz)
    : albedo{ albedo }
    , fuzz{ fuzz < 1.0_f ? fuzz : 1.0_f } {}

bool Metal::scatter(Ray const& ray, Interaction const& interaction, RandomNumberGenerator& rng, MaterialRecord* record) const {
    auto reflected{ glm::reflect(glm::normalize(ray.direction), interaction.normal) };

    record->attenuation = this->albedo;
    record->pdf_ptr = nullptr;
    record->specular_ray = { interaction.hit_point, reflected + this->fuzz * glm::normalize(random_vector3f_in_unit_sphere(rng)), ray.time_point };
    record->is_specular = true;
    return true;
}

RAY_TRACING_NAMESPACE_END
