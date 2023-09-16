#ifndef _RAY_TRACING_PDF_SPHERE_PDF_HPP_
#define _RAY_TRACING_PDF_SPHERE_PDF_HPP_

#include <pdf/base-pdf.hpp>

RAY_TRACING_NAMESPACE_BEGIN

/// @brief Sampling a direction from a sphere.
struct SpherePDF : public PDF {
    virtual Float value(Vector3f const& direction) const override;
    virtual Vector3f generate(RandomNumberGenerator& rng) const override;
};

RAY_TRACING_NAMESPACE_END

#endif // !_RAY_TRACING_PDF_SPHERE_HPP_
