#ifndef _RAY_TRACING_GEOMETRY_TRANSLATION_HPP_
#define _RAY_TRACING_GEOMETRY_TRANSLATION_HPP_

#include <geometry/base-geometry.hpp>

RAY_TRACING_NAMESPACE_BEGIN

/// @brief The translation of a geometry.
class Translation : public Geometry {
private:
    std::shared_ptr<Geometry> geometry;
    Vector3f offset;

public:
    Translation(std::shared_ptr<Geometry> const& geometry, Vector3f const& offset);

    virtual bool hit(Ray const& ray, Interval ray_t, Interaction* interaction) const override;
};

RAY_TRACING_NAMESPACE_END

#endif // !_RAY_TRACING_GEOMETRY_TRANSLATION_HPP_
