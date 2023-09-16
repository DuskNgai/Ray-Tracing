#include <utils/random-number-generator.hpp>

RAY_TRACING_NAMESPACE_BEGIN

RandomNumberGenerator::RandomNumberGenerator()
    : generator{ std::random_device{}() }
    , distribution{} {}

Float RandomNumberGenerator::operator()() {
    return distribution(generator);
}

std::mt19937_64& RandomNumberGenerator::get_generator() {
    return generator;
}

IntegerRNG::IntegerRNG(std::size_t min, std::size_t max)
    : generator{ std::random_device{}() }
    , distribution{ min, max } {}

std::size_t IntegerRNG::operator()() {
    return distribution(generator);
}

RAY_TRACING_NAMESPACE_END
