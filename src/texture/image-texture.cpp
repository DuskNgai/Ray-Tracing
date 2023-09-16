#include <texture/image-texture.hpp>

#include <algorithm>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

RAY_TRACING_NAMESPACE_BEGIN

ImageTexture::ImageTexture(std::string const& filename) {
    int32_t width, height, channel;
    auto data = stbi_load(filename.c_str(), &width, &height, &channel, 0);
    if (data == nullptr) {
        throw std::runtime_error{ stbi_failure_reason() };
    }
    this->width = width;
    this->height = height;
    this->channel = channel;
    this->data = std::vector<uint8_t>{ data, data + width * height * channel };
    stbi_image_free(data);
}

Color3f ImageTexture::sample([[maybe_unused]] Float u, [[maybe_unused]] Float v, [[maybe_unused]] Point3f const& p) const {
    u = std::clamp(u, 0.0_f, 1.0_f);
    v = 1.0_f - std::clamp(v, 0.0_f, 1.0_f);

    auto i{ static_cast<int32_t>(u * this->width) };
    auto j{ static_cast<int32_t>(v * this->height) };

    auto r{ static_cast<Float>(this->data[(j * this->width + i) * this->channel + 0]) / 255.0_f };
    auto g{ static_cast<Float>(this->data[(j * this->width + i) * this->channel + 1]) / 255.0_f };
    auto b{ static_cast<Float>(this->data[(j * this->width + i) * this->channel + 2]) / 255.0_f };
    return { r, g, b };
}

RAY_TRACING_NAMESPACE_END
