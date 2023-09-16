#include <pdf/geometry-pdf.hpp>

RAY_TRACING_NAMESPACE_BEGIN

GeometryPDF::GeometryPDF(std::shared_ptr<Geometry> const& geometry, Point3f const& origin)
    : geometry{ geometry }
    , origin{ origin } {}

Float GeometryPDF::value(Vector3f const& direction) const {
    return this->geometry->pdf(this->origin, direction);
}

Vector3f GeometryPDF::generate(RandomNumberGenerator& rng) const {
    return this->geometry->generate(this->origin, rng);
}

RAY_TRACING_NAMESPACE_END
