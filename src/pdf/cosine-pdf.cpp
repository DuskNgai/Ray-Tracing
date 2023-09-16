#include <pdf/cosine-pdf.hpp>

RAY_TRACING_NAMESPACE_BEGIN

CosinePDF::CosinePDF(Vector3f const& normal)
    : normal{ normal } {}

Float CosinePDF::value(Vector3f const& direction) const {
    auto cosine{ glm::dot(this->normal, glm::normalize(direction)) };
    return cosine < 0.0_f ? 0.0_f : cosine / glm::pi<Float>();
}

Vector3f CosinePDF::generate(RandomNumberGenerator& rng) const {
    // Sample a random direction in the hemisphere.
    auto s{ rng() }, t{ rng() };
    auto phi{ 2.0_f * glm::pi<Float>() * s };
    Vector3f random_direction{ std::cos(phi) * std::sqrt(t), std::sin(phi) * std::sqrt(t), std::sqrt(1.0_f - t) };

    // Rotate the new direction from (0, 0, 1) to normal using orthonormal basis.
    Vector3f up{
        std::abs(this->normal.x) > 0.9_f ? Vector3f{0.0_f, 1.0_f, 0.0_f}
                                         : Vector3f{1.0_f, 0.0_f, 0.0_f}
    };
    Vector3f v{ glm::normalize(glm::cross(this->normal, up)) };
    Vector3f u{ glm::cross(this->normal, v) };
    Vector3f target_direction{ random_direction.x * u + random_direction.y * v + random_direction.z * this->normal };

    return target_direction;
}

RAY_TRACING_NAMESPACE_END
