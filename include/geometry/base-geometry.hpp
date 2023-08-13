#ifndef _RAY_TRACING_GEOMETRY_BASE_GEOMETRY_HPP_
#define _RAY_TRACING_GEOMETRY_BASE_GEOMETRY_HPP_

#include <accelerator/interval.hpp>
#include <geometry/interaction.hpp>
#include <ray.hpp>

RAY_TRACING_NAMESPACE_BEGIN

/// @brief The abstract class for all \eometry objects.
struct Geometry {
    /// @brief True if the ray intersects with the geometry.
    virtual bool hit(Ray const& ray, Interval ray_t, Interaction* interaction) const = 0;

    /// @brief Create a geometry object based on given configuration.
    static std::vector<std::shared_ptr<Geometry>> create(nlohmann::json const& config, std::unordered_map<std::string, std::shared_ptr<Material>> const& materials);

    /// @brief Book 1 final scene.
    static std::vector<std::shared_ptr<Geometry>> create_random_scene();
};

RAY_TRACING_NAMESPACE_END

#endif // !_RAY_TRACING_GEOMETRY_BASE_GEOMETRY_HPP_
