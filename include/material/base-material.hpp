#ifndef _RAY_TRACING_MATERIAL_BASE_MATERIAL_HPP_
#define _RAY_TRACING_MATERIAL_BASE_MATERIAL_HPP_

#include <geometry/interaction.hpp>
#include <material/material-record.hpp>

RAY_TRACING_NAMESPACE_BEGIN

/// @brief The abstract material class that defines the material of a geometry object.
struct Material {
    /// @brief Produce a scattered ray once the ray hits the geometry object.
    /// @return True if there is a scattered ray.
    virtual bool scatter(Ray const& ray, Interaction const& interaction, RandomNumberGenerator& rng, MaterialRecord* record) const = 0;

    /// @brief Get the emitted color from light source.
    virtual Color3f emitted(Interaction const& interaction) const;

    /// @brief Get the bidirectional (anything) distribution function value
    /// at the given interaction position.
    virtual Float bxdf(Ray const& ray, Interaction const& interaction, Ray const& scattered) const;

    /// @brief Create a material object based on given configuration.
    static std::shared_ptr<Material> create(nlohmann::json const& config);
};

RAY_TRACING_NAMESPACE_END

#endif // !_RAY_TRACING_MATERIAL_BASE_MATERIAL_HPP_
