#ifndef _RAY_TRACING_MATERIAL_DIFFUSE_LIGHT_HPP_
#define _RAY_TRACING_MATERIAL_DIFFUSE_LIGHT_HPP_

#include <material/base-material.hpp>
#include <texture/texture.hpp>

RAY_TRACING_NAMESPACE_BEGIN

/// @brief The `DiffuseLight` materials emit light.
class DiffuseLight : public Material {
private:
    std::shared_ptr<Texture> emit;

public:
    explicit DiffuseLight(Color3f const& emit);
    explicit DiffuseLight(std::shared_ptr<Texture> const& emit);

public:
    virtual bool scatter(Ray const& ray, Interaction const& interaction, RandomNumberGenerator& rng, Color3f* attenuation, Ray* scattered) const override;

    virtual Color3f emitted(Interaction const& interaction) const override;
};

RAY_TRACING_NAMESPACE_END

#endif // !_RAY_TRACING_MATERIAL_DIFFUSE_LIGHT_HPP_
