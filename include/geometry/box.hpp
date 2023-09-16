#ifndef _RAY_TRACING_GEOMETRY_BOX_HPP_
#define _RAY_TRACING_GEOMETRY_BOX_HPP_

#include <geometry/base-geometry.hpp>
#include <geometry/scene.hpp>

RAY_TRACING_NAMESPACE_BEGIN

/// @brief A box that contains 6 faces.
class Box : public Geometry {
public:
    std::shared_ptr<Scene> faces{ nullptr };

public:
    Box(Point3f const& minimum, Point3f const& maximum, std::shared_ptr<Material> const& mat_ptr);

    virtual bool hit(Ray const& ray, Interval ray_t, Interaction* interaction) const override;
};

RAY_TRACING_NAMESPACE_END

#endif // !_RAY_TRACING_GEOMETRY_BOX_HPP_
