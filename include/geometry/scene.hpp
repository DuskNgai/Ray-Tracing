#ifndef _RAY_TRACING_GEOMETRY_SCENE_HPP_
#define _RAY_TRACING_GEOMETRY_SCENE_HPP_

#include <vector>

#include <geometry/base-geometry.hpp>

RAY_TRACING_NAMESPACE_BEGIN

/// @brief The scene class that contains all geometry objects.
/// Also, this class is a geometry object itself, which can be added to another scene.
class Scene : public Geometry {
private:
    std::vector<std::shared_ptr<Geometry>> objects;

public:
    explicit Scene(std::vector<std::shared_ptr<Geometry>> const& objects);
    Scene(Scene const& other) = delete;
    Scene(Scene&& other) = default;
    Scene& operator=(Scene const& other) = delete;
    Scene& operator=(Scene&& other) = default;

public:
    void add_object(std::shared_ptr<Geometry> const& object);
    void clear_objects();
    std::vector<std::shared_ptr<Geometry>> const& get_objects() const;

    virtual bool hit(Ray const& ray, Interval ray_t, Interaction* interaction) const override;

    /// @brief Create a scene object based on given configuration.
    static std::shared_ptr<Scene> create(nlohmann::json const& config);
};

RAY_TRACING_NAMESPACE_END

#endif // !_RAY_TRACING_GEOMETRY_SCENE_HPP_
