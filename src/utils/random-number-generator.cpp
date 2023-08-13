#include <utils/random-number-generator.hpp>

RAY_TRACING_NAMESPACE_BEGIN

RandomNumberGenerator::RandomNumberGenerator()
    : generator{ std::random_device{}() }
    , distribution{} {}

Float RandomNumberGenerator::operator()() {
    return distribution(generator);
}

RAY_TRACING_NAMESPACE_END
