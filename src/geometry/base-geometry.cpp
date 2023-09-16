#include <geometry/geometry.hpp>

#include <unordered_map>

#include <accelerator/bvh.hpp>
#include <material/material.hpp>

RAY_TRACING_NAMESPACE_BEGIN

AABB const& Geometry::get_bounding_box() const {
    return this->bounding_box;
}

Float Geometry::pdf([[maybe_unused]] Point3f const& origin, [[maybe_unused]] Vector3f const& direction) const {
    return 0.0_f;
}

Vector3f Geometry::generate([[maybe_unused]] Point3f const& origin, [[maybe_unused]] RandomNumberGenerator& rng) const {
    return { 1.0_f, 0.0_f, 0.0_f };
}

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
    else if (type == "MovingSphere") {
        return {
            std::make_shared<MovingSphere>(
                from_json(config.at("start_center")),
                from_json(config.at("end_center")),
                config.at("radius"),
                materials.at(config.at("material"))
            )
        };
    }
    else if (type == "Quad") {
        return {
            std::make_shared<Quad>(
                from_json(config.at("base_point")),
                from_json(config.at("edge_a")),
                from_json(config.at("edge_b")),
                materials.at(config.at("material"))
            )
        };
    }
    else if (type == "Box") {
        std::shared_ptr<Geometry> box{ std::make_shared<Box>(
            from_json(config.at("minimum")),
            from_json(config.at("maximum")),
            materials.at(config.at("material"))
        ) };
        if (config.contains("y rotation")) {
            box = std::make_shared<YRotation>(box, config.at("y rotation"));
        }
        if (config.contains("translation")) {
            box = std::make_shared<Translation>(box, from_json(config.at("translation")));
        }
        return { box };
    }
    else if (type == "ConstantMedium") {
        return {
            std::make_shared<ConstantMedium>(
                Geometry::create(config.at("boundary"), materials)[0],
                from_json(config.at("phase function")),
                config.at("density")
            )
        };
    }
    else if (type == "RandomScene") {
        return Geometry::create_random_scene();
    }
    else if (type == "FinalScene") {
        return Geometry::create_final_scene();
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
                    objects.push_back(std::make_shared<MovingSphere>(center, center + Vector3f{ 0.0_f, rng() * 0.5_f, 0.0_f }, 0.2_f, sphere_material));
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

std::vector<std::shared_ptr<Geometry>> Geometry::create_final_scene() {
    RandomNumberGenerator rng{};
    auto ground{ std::make_shared<Lambertian>(Color3f{ 0.48_f, 0.83_f, 0.53_f }) };

    std::vector<std::shared_ptr<Geometry>> boxes;
    auto boxes_per_side{ 20 };
    for (int32_t i{ 0 }; i < boxes_per_side; ++i) {
        for (int32_t j{ 0 }; j < boxes_per_side; ++j) {
            auto w{ 100.0_f };
            auto x0{ -1000.0_f + i * w };
            auto z0{ -1000.0_f + j * w };
            auto y0{ 0.0_f };
            auto x1{ x0 + w };
            auto y1{ rng() * 100.0_f + 1.0_f };
            auto z1{ z0 + w };

            boxes.push_back(std::make_shared<Box>(Point3f{ x0, y0, z0 }, Point3f{ x1, y1, z1 }, ground));
        }
    }

    std::vector<std::shared_ptr<Geometry>> box_of_spheres;
    auto white{ std::make_shared<Lambertian>(Color3f{ 0.73_f, 0.73_f, 0.73_f }) };
    auto ns{ 1000 };
    for (int32_t j{ 0 }; j < ns; ++j) {
        box_of_spheres.push_back(std::make_shared<Sphere>(random_vector3f(rng, 0.0_f, 165.0_f), 10.0_f, white));
    }

    return {
        std::make_shared<BVH>(boxes),
        std::make_shared<Translation>(std::make_shared<YRotation>(std::make_shared<BVH>(box_of_spheres), 15.0_f), Vector3f{ -100.0_f, 270.0_f, 395.0_f })
    };
}

RAY_TRACING_NAMESPACE_END
