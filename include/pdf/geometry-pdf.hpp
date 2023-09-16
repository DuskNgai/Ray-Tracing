#ifndef _RAY_TRACING_PDF_GEOMETRY_PDF_HPP_
#define _RAY_TRACING_PDF_GEOMETRY_PDF_HPP_

#include <geometry/base-geometry.hpp>
#include <pdf/base-pdf.hpp>

RAY_TRACING_NAMESPACE_BEGIN

/// @brief Sampling a direction from a geometry surface.
struct GeometryPDF : public PDF {
    std::shared_ptr<Geometry> geometry;
    Point3f origin;

    GeometryPDF(std::shared_ptr<Geometry> const& geometry, Point3f const& origin);

    virtual Float value(Vector3f const& direction) const override;

    virtual Vector3f generate(RandomNumberGenerator& rng) const override;
};

RAY_TRACING_NAMESPACE_END

#endif // !_RAY_TRACING_PDF_GEOMETRY_PDF_HPP_
