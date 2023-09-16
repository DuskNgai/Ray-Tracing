#ifndef _RAY_TRACING_ACCELERATOR_INTERVAL_HPP_
#define _RAY_TRACING_ACCELERATOR_INTERVAL_HPP_

#include <common.hpp>
#include <math-utils.hpp>

RAY_TRACING_NAMESPACE_BEGIN

/// @brief A closed interval in the form of [`min`, `max`].
struct Interval {
    Float min, max;

    Interval(Float min = INF<Float>, Float max = -INF<Float>);

    Float size() const;

    /// @brief True if `value` in [`min`, `max`].
    bool contains(Float value) const;

    /// @brief True if `value` in (`min`, `max`).
    bool surrounds(Float value) const;

    /// @brief Create a smallest `Interval` that contains both `a` and `b`.
    static Interval merge(Interval const& a, Interval const& b);

    /// @return A new `Interval` with size (`min` - `min_width / 2`, `max` + `min_width / 2`).
    static Interval expand(Interval const& interval, Float min_width);

    static const Interval empty;
    static const Interval universe;
};


RAY_TRACING_NAMESPACE_END

#endif // !_RAY_TRACING_ACCELERATOR_INTERVAL_HPP_
