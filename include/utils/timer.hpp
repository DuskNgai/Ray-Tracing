#ifndef _RAY_TRACING_UTILS_TIMER_HPP_
#define _RAY_TRACING_UTILS_TIMER_HPP_

#include <chrono>

#include <common.hpp>

RAY_TRACING_NAMESPACE_BEGIN

class Timer {
private:
    std::chrono::time_point<std::chrono::steady_clock> start_time{};
    std::chrono::time_point<std::chrono::steady_clock> end_time{};

public:
    Timer() = default;
    Timer(Timer const&) = delete;
    Timer(Timer&&) = delete;
    Timer& operator=(Timer const&) = delete;
    Timer& operator=(Timer&&) = delete;

public:
    void start();

    void stop();

    /// @brief A template member function for representing time in various formats.
    /// @return The elapsed time in milliseconds.
    template <typename duration_t = std::chrono::milliseconds>
    int64_t get_elapsed_time() const {
        return std::chrono::duration_cast<duration_t, int64_t>(this->end_time - this->start_time).count();
    }
};

RAY_TRACING_NAMESPACE_END

#endif // !_RAY_TRACING_UTILS_TIMER_HPP_
