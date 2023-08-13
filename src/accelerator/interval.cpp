#include <accelerator/interval.hpp>

RAY_TRACING_NAMESPACE_BEGIN

Interval::Interval(Float min, Float max)
    : min{ min }
    , max{ max } {}

bool Interval::contains(Float value) const {
    return this->min <= value && value <= this->max;
}

bool Interval::surrounds(Float value) const {
    return this->min < value && value < this->max;
}

const Interval Interval::empty{ INF<Float>, -INF<Float> };
const Interval Interval::universe{ -INF<Float>, INF<Float> };

RAY_TRACING_NAMESPACE_END
