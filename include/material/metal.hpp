#ifndef _RAY_TRACING_MATERIAL_METAL_HPP_
#define _RAY_TRACING_MATERIAL_METAL_HPP_

#include <material/base-material.hpp>

RAY_TRACING_NAMESPACE_BEGIN

class Metal : public Material {
private:
    Color3f albedo;
    Float fuzz;

public:
    Metal(Color3f const& albedo, Float fuzz);

public:
    virtual bool scatter(Ray const& ray, Interaction const& interaction, RandomNumberGenerator& rng, MaterialRecord* record) const override;
};

RAY_TRACING_NAMESPACE_END

#endif // !_RAY_TRACING_MATERIAL_METAL_HPP_
