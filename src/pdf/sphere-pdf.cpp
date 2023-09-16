#include <pdf/sphere-pdf.hpp>

RAY_TRACING_NAMESPACE_BEGIN

Float SpherePDF::value([[maybe_unused]] Vector3f const& direction) const {
    return 0.25_f / glm::pi<Float>();
}

Vector3f SpherePDF::generate(RandomNumberGenerator& rng) const {
    return glm::normalize(random_vector3f_in_unit_sphere(rng));
}

RAY_TRACING_NAMESPACE_END
