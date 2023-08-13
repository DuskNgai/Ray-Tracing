#include <geometry/geometry.hpp>

#include <unordered_map>

#include <material/material.hpp>

RAY_TRACING_NAMESPACE_BEGIN

std::vector<std::shared_ptr<Geometry>> Geometry::create(nlohmann::json const& config, std::unordered_map<std::string, std::shared_ptr<Material>> const& materials) {
    std::string type{ config.at("type") };

    if (type == "Sphere") {
        return {
            std::make_shared<Sphere>(
                from_json(config.at("center")),
                config.at("radius"),
                materials.at(config.at("material"))
            )
        };
    }
    else if (type == "RandomScene") {
        return Geometry::create_random_scene();
    }
    else {
        throw std::runtime_error{ "Unknown geometry type: " + type };
    }
}

std::vector<std::shared_ptr<Geometry>> Geometry::create_random_scene() {
    std::vector<std::shared_ptr<Geometry>> objects;
    RandomNumberGenerator rng{};

    for (int32_t a = -11; a < 11; ++a) {
        for (int32_t b = -11; b < 11; ++b) {
            Float choose_mat{ rng() };
            Point3f center{ a + 0.9_f * rng(), 0.2_f, b + 0.9_f * rng() };

            if (glm::length(center - Point3f{ 4.0_f, 0.2_f, 0.0_f }) > 0.9_f) {
                std::shared_ptr<Material> sphere_material;

                if (choose_mat < 0.8_f) {
                    // Diffuse.
                    Color3f albedo{ random_vector3f(rng) * random_vector3f(rng) };
                    sphere_material = std::make_shared<Lambertian>(albedo);
                    objects.push_back(std::make_shared<Sphere>(center, 0.2_f, sphere_material));
                }
                else if (choose_mat < 0.95_f) {
                    // Metal.
                    auto albedo{ random_vector3f(rng, 0.5_f, 1.0_f) };
                    auto fuzz{ rng() * 0.5_f };
                    sphere_material = std::make_shared<Metal>(albedo, fuzz);
                    objects.push_back(std::make_shared<Sphere>(center, 0.2_f, sphere_material));
                }
                else {
                    // Glass.
                    sphere_material = std::make_shared<Dielectric>(1.5_f);
                    objects.push_back(std::make_shared<Sphere>(center, 0.2_f, sphere_material));
                }
            }
        }
    }
    return objects;
}

RAY_TRACING_NAMESPACE_END
