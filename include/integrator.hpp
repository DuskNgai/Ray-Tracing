#ifndef _RAY_TRACING_INTEGRATOR_HPP_
#define _RAY_TRACING_INTEGRATOR_HPP_

#include <camera.hpp>
#include <geometry/scene.hpp>

RAY_TRACING_NAMESPACE_BEGIN

/// @brief The integrator is responsible for computing the radiance along a ray
/// and rendering the scene to camera film.
class Integrator {
private:
    uint32_t spp;
    uint32_t ray_tracing_depth;

public:
    /// @brief Construct a new Integrator object.
    Integrator(uint32_t spp, uint32_t ray_tracing_depth);

    /// @brief Render the scene with the given camera.
    void render(std::shared_ptr<Scene> const& scene, std::shared_ptr<Camera> const& camera);

    /// @brief The integrator is responsible for computing the radiance along a ray.
    /// @return The radiance along the ray.
    Color3f radiance(std::shared_ptr<Scene> const& scene, Ray const& ray, RandomNumberGenerator& rng, uint32_t current_depth);
};

RAY_TRACING_NAMESPACE_END

#endif // !_RAY_TRACING_INTEGRATOR_HPP_
