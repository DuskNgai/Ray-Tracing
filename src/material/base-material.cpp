#include <material/material.hpp>
#include <texture/texture.hpp>

RAY_TRACING_NAMESPACE_BEGIN

Color3f Material::emitted([[maybe_unused]] Interaction const& interaction) const {
    return {};
}

std::shared_ptr<Material> Material::create(nlohmann::json const& config) {
    std::string type{ config.at("type") };

    if (type == "Lambertian") {
        if (config.at("albedo").is_object()) {
            return std::make_shared<Lambertian>(Texture::create(config.at("albedo")));
        }
        else {
            return std::make_shared<Lambertian>(from_json(config.at("albedo")));
        }
    }
    else if (type == "Metal") {
        return std::make_shared<Metal>(from_json(config.at("albedo")), config.at("fuzz"));
    }
    else if (type == "Dielectric") {
        return std::make_shared<Dielectric>(config.at("rior"));
    }
    else if (type == "DiffuseLight") {
        return std::make_shared<DiffuseLight>(from_json(config.at("emit")));
    }
    else {
        throw std::runtime_error{ "Unknown material type: " + type };
    }
}

RAY_TRACING_NAMESPACE_END
