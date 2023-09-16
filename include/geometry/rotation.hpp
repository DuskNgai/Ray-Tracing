#ifndef _RAY_TRACING_GEOMETRY_ROTATION_HPP_
#define _RAY_TRACING_GEOMETRY_ROTATION_HPP_

#include <geometry/base-geometry.hpp>

RAY_TRACING_NAMESPACE_BEGIN

/// @brief The rotation of a geometry around the y-axis.
class YRotation : public Geometry {
private:
    std::shared_ptr<Geometry> geometry;
    Float sin_theta, cos_theta;

public:
    YRotation(std::shared_ptr<Geometry> const& geometry, Float angle);

    virtual bool hit(Ray const& ray, Interval ray_t, Interaction* interaction) const override;
};

RAY_TRACING_NAMESPACE_END

#endif // !_RAY_TRACING_GEOMETRY_ROTATION_HPP_
