#ifndef _RAY_TRACING_VECTOR3_HPP_
#define _RAY_TRACING_VECTOR3_HPP_

#include <iostream>
#include <optional>

#include <glm/glm.hpp>
#include <glm/gtx/norm.hpp>
#include <nlohmann/json.hpp>

#include <math-utils.hpp>
#include <utils/random-number-generator.hpp>

RAY_TRACING_NAMESPACE_BEGIN

template <typename T>
using Vector3 = glm::vec<3, T, glm::defaultp>;
using Vector3f = Vector3<Float>;
using Color3f = Vector3f;
using Point3f = Vector3f;

/// @brief Refract the incoming direction `v` respect to the normal `n`.
/// @param v The incoming direction, required to be normalized.
/// @param n The normal, required to be normalized.
template <typename T>
std::optional<Vector3<T>> constexpr refract(Vector3<T> const& v, Vector3<T> const& n, T rior) {
    auto cos_theta{ std::min(glm::dot(-v, n), 1.0_f) };
    auto sin_theta{ std::sqrt(1.0_f - cos_theta * cos_theta) };

    // Total internal reflection.
    if (rior * sin_theta > 1.0_f) {
        return std::nullopt;
    }

    // Refract component that are perpendicular/parallel to the normal.
    Vector3<T> perp{ (v + cos_theta * n) * rior };
    Vector3<T> para{ -std::sqrt(std::abs(1.0_f - glm::length2(perp))) * n };
    return perp + para;
}

/// @brief A random vector in [min, max]^3.
Vector3f inline random_vector3f(RandomNumberGenerator& rng, Float min = 0.0_f, Float max = 1.0_f) {
    return Vector3f{ rng(), rng(), rng() } * (max - min) + Vector3f{ min, min, min };
}

/// @brief A random vector who is in a unit sphere.
Vector3f inline random_vector3f_in_unit_sphere(RandomNumberGenerator& rng) {
    while (true) {
        Vector3f p{ random_vector3f(rng, -1.0_f, 1.0_f) };
        if (glm::length2(p) <= 1.0_f) {
            return p;
        }
    }
}

/// @brief A random vector who is in a unit circle.
Vector3f inline random_vector3f_in_unit_circle(RandomNumberGenerator& rng) {
    while (true) {
        Vector3f p{
            Vector3f{rng(), rng(), 0.0_f}
            * 2.0_f - Vector3f{1.0_f, 1.0_f, 0.0_f}
        };
        if (glm::length2(p) <= 1.0_f) {
            return p;
        }
    }
}

/// @brief Convert array in configuration file to `Vector3f`.
Vector3f inline from_json(nlohmann::json const& config) {
    Vector3f v;
    for (int i{ 0 }; i < 3; ++i) {
        v[i] = config[i];
    }
    return v;
}

RAY_TRACING_NAMESPACE_END

#endif // !_RAY_TRACING_VECTOR3_HPP_
