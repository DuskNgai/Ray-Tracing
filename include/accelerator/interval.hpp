#ifndef _RAY_TRACING_ACCELERATOR_INTERVAL_HPP_
#define _RAY_TRACING_ACCELERATOR_INTERVAL_HPP_

#include <common.hpp>
#include <math-utils.hpp>

RAY_TRACING_NAMESPACE_BEGIN

struct Interval {
    Float min, max;

    Interval(Float min = -INF<Float>, Float max = INF<Float>);

    /// @brief True if `value` in [`min`, `max`].
    bool contains(Float value) const;

    /// @brief True if `value` in (`min`, `max`).
    bool surrounds(Float value) const;

    static const Interval empty;
    static const Interval universe;
};

RAY_TRACING_NAMESPACE_END

#endif // !_RAY_TRACING_ACCELERATOR_INTERVAL_HPP_
