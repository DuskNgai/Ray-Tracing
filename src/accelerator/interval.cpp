#include <algorithm>

#include <accelerator/interval.hpp>

RAY_TRACING_NAMESPACE_BEGIN

Interval::Interval(Float min, Float max)
    : min{ min }
    , max{ max } {}

Float Interval::size() const {
    return this->max - this->min;
}

bool Interval::contains(Float value) const {
    return this->min <= value && value <= this->max;
}

bool Interval::surrounds(Float value) const {
    return this->min < value && value < this->max;
}

Interval Interval::merge(Interval const& a, Interval const& b) {
    return {
        std::min(a.min, b.min), std::max(a.max, b.max)
    };
}

Interval Interval::expand(Interval const& interval, Float min_width) {
    auto padding{ min_width / 2.0_f };
    return {
        interval.min - padding, interval.max + padding
    };
}

const Interval Interval::empty{ INF<Float>, -INF<Float> };
const Interval Interval::universe{ -INF<Float>, INF<Float> };

RAY_TRACING_NAMESPACE_END
