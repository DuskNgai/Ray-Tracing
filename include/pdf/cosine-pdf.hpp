#ifndef _RAY_TRACING_PDF_COSINE_PDF_HPP_
#define _RAY_TRACING_PDF_COSINE_PDF_HPP_

#include <pdf/base-pdf.hpp>

RAY_TRACING_NAMESPACE_BEGIN

/// @brief Sampling a direction from a cosine distribution on a hemisphere.
struct CosinePDF : public PDF {
    Vector3f normal;

    CosinePDF(Vector3f const& normal);

    virtual Float value(Vector3f const& direction) const override;
    virtual Vector3f generate(RandomNumberGenerator& rng) const override;
};

RAY_TRACING_NAMESPACE_END

#endif // !_RAY_TRACING_PDF_COSINE_PDF_HPP_
