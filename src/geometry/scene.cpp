#include <geometry/scene.hpp>

#include <unordered_map>

#include <material/material.hpp>

RAY_TRACING_NAMESPACE_BEGIN

Scene::Scene(std::vector<std::shared_ptr<Geometry>> const& objects)
    : objects{ objects } {}

void Scene::add_object(std::shared_ptr<Geometry> const& object) {
    this->objects.push_back(object);
}

void Scene::clear_objects() {
    this->objects.clear();
}

std::vector<std::shared_ptr<Geometry>> const& Scene::get_objects() const {
    return this->objects;
}

bool Scene::hit(Ray const& ray, Interval ray_t, Interaction* interaction) const {
    bool hit_anything{ false };
    Float closest_so_far{ ray_t.max };
    Interaction local_interaction;
    for (auto const& object : this->objects) {
        // Update to the closest interaction.
        if (object->hit(ray, { ray_t.min, closest_so_far }, &local_interaction)) {
            hit_anything = true;
            closest_so_far = local_interaction.t;
            *interaction = local_interaction;
        }
    }
    return hit_anything;
}

std::shared_ptr<Scene> Scene::create(nlohmann::json const& config) {
    // Store materials.
    std::unordered_map<std::string, std::shared_ptr<Material>> materials;
    for (auto const& [name, material] : config.at("Materials").items()) {
        materials[name] = Material::create(material);
    }

    // Store geometries.
    std::vector<std::shared_ptr<Geometry>> objects;
    for (auto const& c : config.at("Geometries")) {
        auto new_objects{ Geometry::create(c, materials) };
        objects.insert(objects.end(), new_objects.begin(), new_objects.end());
    }

    return std::make_shared<Scene>(objects);
}

RAY_TRACING_NAMESPACE_END
