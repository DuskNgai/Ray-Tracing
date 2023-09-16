#ifndef _RAY_TRACING_MATERIAL_DIELECTRIC_HPP_
#define _RAY_TRACING_MATERIAL_DIELECTRIC_HPP_

#include <material/base-material.hpp>

RAY_TRACING_NAMESPACE_BEGIN

class Dielectric : public Material {
private:
    Float rior; // Relative index of refraction.

public:
    explicit Dielectric(Float rior);

public:
    virtual bool scatter(Ray const& ray, Interaction const& interaction, RandomNumberGenerator& rng, MaterialRecord* record) const override;
};

RAY_TRACING_NAMESPACE_END

#endif // !_RAY_TRACING_MATERIAL_DIELECTRIC_HPP_
