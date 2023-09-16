#ifndef _RAY_TRACING_ACCELERATOR_AABB_HPP_
#define _RAY_TRACING_ACCELERATOR_AABB_HPP_

#include <accelerator/interval.hpp>
#include <ray.hpp>

RAY_TRACING_NAMESPACE_BEGIN

/// @brief Axis-aligned bounding box.
struct AABB {
    Interval intervals[3];

    AABB(Interval x = {}, Interval y = {}, Interval z = {});
    AABB(Point3f const& minimum, Point3f const& maximum);

    bool hit(Ray const& ray, Interval ray_t) const;

    Interval const& operator[](std::size_t index) const;

    /// @brief Create a smallest `AABB` that contains both `a` and `b`.
    static AABB merge(AABB const& a, AABB const& b);

    /// @brief Create a new `AABB` that no side narrower than `min_width`.
    static AABB expand(AABB const& aabb, Float min_width = 1e-4_f);
};


RAY_TRACING_NAMESPACE_END

#endif // !_RAY_TRACING_ACCELERATOR_AABB_HPP_
