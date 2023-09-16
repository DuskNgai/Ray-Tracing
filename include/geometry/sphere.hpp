#ifndef _RAY_TRACING_GEOMETRY_SPHERE_HPP_
#define _RAY_TRACING_GEOMETRY_SPHERE_HPP_

#include <geometry/base-geometry.hpp>

RAY_TRACING_NAMESPACE_BEGIN

/// @brief The definition of a sphere.
struct Sphere : public Geometry {
    Point3f center;
    Float radius;
    std::shared_ptr<Material> mat_ptr;

    Sphere(Point3f const& center, Float radius, std::shared_ptr<Material> const& mat_ptr);

    virtual bool hit(Ray const& ray, Interval ray_t, Interaction* interaction) const override;

    virtual Float pdf(Point3f const& origin, Vector3f const& direction) const override;

    virtual Vector3f generate(Point3f const& origin, RandomNumberGenerator& rng) const override;

    virtual Point3f get_center(Float time_point) const;

    std::pair<Float, Float> get_uv(Vector3f const& p) const;
};

RAY_TRACING_NAMESPACE_END

#endif // !_RAY_TRACING_GEOMETRY_SPHERE_HPP_
