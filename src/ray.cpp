#include <ray.hpp>

RAY_TRACING_NAMESPACE_BEGIN

Ray::Ray(Point3f const& origin, Vector3f const& direction)
    : origin{ origin }
    , direction{ direction } {}

Point3f Ray::at(Float t) const {
    return this->origin + this->direction * t;
}

RAY_TRACING_NAMESPACE_END
