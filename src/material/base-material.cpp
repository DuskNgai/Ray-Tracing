#include <material/material.hpp>

RAY_TRACING_NAMESPACE_BEGIN

std::shared_ptr<Material> Material::create(nlohmann::json const& config) {
    std::string type{ config.at("type") };

    if (type == "Lambertian") {
        return std::make_shared<Lambertian>(from_json(config.at("albedo")));
    }
    else if (type == "Metal") {
        return std::make_shared<Metal>(from_json(config.at("albedo")), config.at("fuzz"));
    }
    else if (type == "Dielectric") {
        return std::make_shared<Dielectric>(config.at("rior"));
    }
    else {
        throw std::runtime_error{ "Unknown material type: " + type };
    }
}

RAY_TRACING_NAMESPACE_END
