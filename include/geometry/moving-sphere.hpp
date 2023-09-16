#ifndef _RAY_TRACING_GEOMETRY_MOVING_SPHERE_HPP_
#define _RAY_TRACING_GEOMETRY_MOVING_SPHERE_HPP_

#include <geometry/sphere.hpp>

RAY_TRACING_NAMESPACE_BEGIN

/// @brief The definition of a moving sphere.
struct MovingSphere : public Sphere {
    Vector3f center_vector;

    MovingSphere(Point3f const& start_center, Point3f const& end_center, Float radius, std::shared_ptr<Material> const& mat_ptr);

    virtual Point3f get_center(Float time_point) const override;
};

RAY_TRACING_NAMESPACE_END

#endif // !_RAY_TRACING_GEOMETRY_MOVING_SPHERE_HPP_
