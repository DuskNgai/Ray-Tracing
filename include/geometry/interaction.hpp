#ifndef _RAY_TRACING_GEOMETRY_INTERACTION_HPP_
#define _RAY_TRACING_GEOMETRY_INTERACTION_HPP_

#include <material/base-material.hpp>
#include <ray.hpp>

RAY_TRACING_NAMESPACE_BEGIN

/// @brief The record for interaction between a ray and an object.
struct Interaction {
    Float t;
    Point3f hit_point;
    Vector3f normal;
    Float u, v;
    bool is_outer_face;
    std::shared_ptr<Material> mat_ptr;

    void set_face_normal(Ray const& ray, Vector3f const& outward_normal) {
        this->is_outer_face = glm::dot(ray.direction, outward_normal) < 0.0_f;
        this->normal = this->is_outer_face ? outward_normal : -outward_normal;
    }
};

RAY_TRACING_NAMESPACE_END

#endif // !_RAY_TRACING_GEOMETRY_INTERACTION_HPP_
