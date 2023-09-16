#include <texture/texture.hpp>

RAY_TRACING_NAMESPACE_BEGIN

std::shared_ptr<Texture> Texture::create(nlohmann::json const& config) {
    auto type = config["type"].get<std::string>();
    if (type == "SolidColor") {
        return std::make_shared<SolidColor>(from_json(config.at("color")));
    }
    else if (type == "CheckerTexture") {
        return std::make_shared<CheckerTexture>(
            config.at("scale"),
            from_json(config.at("even")),
            from_json(config.at("odd"))
        );
    }
    else if (type == "ImageTexture") {
        return std::make_shared<ImageTexture>(config.at("path"));
    }
    else if (type == "NoiseTexture") {
        return std::make_shared<NoiseTexture>(config.at("scale"));
    }
    else {
        throw std::runtime_error{ "Unknown texture type: " + type };
    }
}

RAY_TRACING_NAMESPACE_END
