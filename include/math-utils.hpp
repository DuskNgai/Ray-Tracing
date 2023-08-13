#ifndef _RAY_TRACING_MATH_UTILS_HPP_
#define _RAY_TRACING_MATH_UTILS_HPP_

#include <cmath>
#include <limits>

#include <common.hpp>

RAY_TRACING_NAMESPACE_BEGIN

using Float = float;

inline Float constexpr operator""_f(long double x) {
	return static_cast<Float>(x);
}

template <typename FloatingPoint>
FloatingPoint constexpr INF = std::numeric_limits<FloatingPoint>::infinity();
template <typename FloatingPoint>
FloatingPoint constexpr EPSILON = std::numeric_limits<FloatingPoint>::epsilon();

RAY_TRACING_NAMESPACE_END

#endif // !_RAY_TRACING_MATH_UTILS_HPP_
