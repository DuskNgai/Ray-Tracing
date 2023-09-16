#ifndef _RAY_TRACING_GEOMETRY_VOLUME_HPP_
#define _RAY_TRACING_GEOMETRY_VOLUME_HPP_

#include <geometry/base-geometry.hpp>
#include <material/isotropic.hpp>
#include <utils/random-number-generator.hpp>

RAY_TRACING_NAMESPACE_BEGIN

/// @brief A constant medium that scatters light in volume rendering.
class ConstantMedium : public Geometry {
private:
    std::shared_ptr<Geometry> boundary;
    std::shared_ptr<Material> phase_function;
    Float neg_inv_density;
    mutable RandomNumberGenerator rng{};

public:
    ConstantMedium(std::shared_ptr<Geometry> const& boundary, std::shared_ptr<Texture> const& texture, Float density);
    ConstantMedium(std::shared_ptr<Geometry> const& boundary, Color3f color, Float density);

    virtual bool hit(Ray const& ray, Interval ray_t, Interaction* interaction) const override;
    virtual AABB const& get_bounding_box() const override;
};

RAY_TRACING_NAMESPACE_END

#endif // !_RAY_TRACING_GEOMETRY_VOLUME_HPP_
