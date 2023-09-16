#ifndef _RAY_TRACING_RAY_HPP_
#define _RAY_TRACING_RAY_HPP_

#include <vector3.hpp>

RAY_TRACING_NAMESPACE_BEGIN

/// @brief A ray is a line segment with a starting point and a direction.
struct Ray {
    Point3f origin;
    Vector3f direction;
    Float time_point;

    Ray(Point3f const& origin = {}, Vector3f const& direction = {}, Float time_point = 0.0_f);

    /// @brief Evaluate the ray at a given ray parameter.
    Point3f at(Float t) const;
};

RAY_TRACING_NAMESPACE_END

#endif // !_RAY_TRACING_RAY_HPP_
