#include <utils/timer.hpp>

RAY_TRACING_NAMESPACE_BEGIN

void Timer::start() {
    this->start_time = std::chrono::steady_clock::now();
}

void Timer::stop() {
    this->end_time = std::chrono::steady_clock::now();
}

RAY_TRACING_NAMESPACE_END
