#ifndef _RAY_TRACING_PDF_BASE_PDF_HPP_
#define _RAY_TRACING_PDF_BASE_PDF_HPP_

#include <common.hpp>
#include <vector3.hpp>
#include <utils/random-number-generator.hpp>

RAY_TRACING_NAMESPACE_BEGIN

/// @brief The pdf when sampling a for next ray direction.
struct PDF {
    virtual ~PDF() = default;
    virtual Float value(const Vector3f& direction) const = 0;
    virtual Vector3f generate(RandomNumberGenerator& rng) const = 0;
};

RAY_TRACING_NAMESPACE_END

#endif // !_RAY_TRACING_PDF_BASE_PDF_HPP_
