#ifndef _RAY_TRACING_MATERIAL_ISOTROPIC_HPP_
#define _RAY_TRACING_MATERIAL_ISOTROPIC_HPP_

#include <material/base-material.hpp>
#include <texture/texture.hpp>

RAY_TRACING_NAMESPACE_BEGIN

class Isotropic : public Material {
private:
    std::shared_ptr<Texture> albedo;

public:
    explicit Isotropic(std::shared_ptr<Texture> const& albedo);
    explicit Isotropic(Color3f const& albedo);

    virtual bool scatter(Ray const& ray, Interaction const& interaction, RandomNumberGenerator& rng, Color3f* attenuation, Ray* scattered) const;
};

RAY_TRACING_NAMESPACE_END

#endif // !_RAY_TRACING_MATERIAL_ISOTROPIC_HPP_
