#ifndef _RAY_TRACING_MATERIAL_LAMBERTIAN_HPP_
#define _RAY_TRACING_MATERIAL_LAMBERTIAN_HPP_

#include <material/base-material.hpp>

RAY_TRACING_NAMESPACE_BEGIN

/// @brief The `Lambertian` materials scatter the incoming rays randomly.
class Lambertian : public Material {
private:
    Color3f albedo;

public:
    explicit Lambertian(Color3f const& albedo);

public:
    virtual bool scatter(Ray const& ray, Interaction const& interaction, RandomNumberGenerator& rng, Color3f* attenuation, Ray* scattered) const override;
};

RAY_TRACING_NAMESPACE_END

#endif // !_RAY_TRACING_MATERIAL_LAMBERTIAN_HPP_
