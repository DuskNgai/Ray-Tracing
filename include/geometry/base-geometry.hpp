#ifndef _RAY_TRACING_GEOMETRY_BASE_GEOMETRY_HPP_
#define _RAY_TRACING_GEOMETRY_BASE_GEOMETRY_HPP_

#include <accelerator/aabb.hpp>
#include <geometry/interaction.hpp>
#include <ray.hpp>

RAY_TRACING_NAMESPACE_BEGIN

/// @brief The abstract class for all \eometry objects.
class Geometry {
protected:
    AABB bounding_box;

public:
    /// @brief True if the ray intersects with the geometry.
    virtual bool hit(Ray const& ray, Interval ray_t, Interaction* interaction) const = 0;

    /// @brief Get the bounding box of the geometry.
    virtual AABB const& get_bounding_box() const;

    /// @brief Create geometry objects based on given configuration.
    static std::vector<std::shared_ptr<Geometry>> create(nlohmann::json const& config, std::unordered_map<std::string, std::shared_ptr<Material>> const& materials);

    /// @brief Book 1 final scene.
    static std::vector<std::shared_ptr<Geometry>> create_random_scene();

    /// @brief Book 2 final scene.
    static std::vector<std::shared_ptr<Geometry>> create_final_scene();
};

RAY_TRACING_NAMESPACE_END

#endif // !_RAY_TRACING_GEOMETRY_BASE_GEOMETRY_HPP_
