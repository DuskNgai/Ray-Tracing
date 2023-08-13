#ifndef _RAY_TRACING_UTILS_RANDOM_NUMBER_GENERATOR_HPP_
#define _RAY_TRACING_UTILS_RANDOM_NUMBER_GENERATOR_HPP_

#include <random>

#include <math-utils.hpp>

RAY_TRACING_NAMESPACE_BEGIN

/// @brief A random number generator which uniformly generates a number in [0, 1).
class RandomNumberGenerator {
private:
    std::mt19937_64 generator;
    std::uniform_real_distribution<Float> distribution;

public:
    RandomNumberGenerator();

public:
    /// @brief Get a random number in [0, 1).
    Float operator()();
};

RAY_TRACING_NAMESPACE_END

#endif // !_RAY_TRACING_UTILS_RANDOM_NUMBER_GENERATOR_HPP_
