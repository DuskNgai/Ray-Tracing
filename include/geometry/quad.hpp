#ifndef _RAY_TRACING_GEOMETRY_QUAD_HPP_
#define _RAY_TRACING_GEOMETRY_QUAD_HPP_

#include <geometry/base-geometry.hpp>

RAY_TRACING_NAMESPACE_BEGIN

/// @brief A quad or a parallelogram.
class Quad : public Geometry {
private:
    Point3f base_point;
    Vector3f edge_a, edge_b;
    Vector3f normal;
    Float D;    // Plane equation: Ax + By + Cz + D = 0.
    Vector3f w; // unnormalized_normal / glm::length2(unnormalized_normal)
    std::shared_ptr<Material> mat_ptr;

public:
    Quad(Point3f const& base_point, Vector3f const& edge_a, Vector3f const& edge_b, std::shared_ptr<Material> const& mat_ptr);

public:
    virtual bool hit(Ray const& ray, Interval ray_t, Interaction* interaction) const override;
};

RAY_TRACING_NAMESPACE_END

#endif // !_RAY_TRACING_GEOMETRY_QUAD_HPP_
