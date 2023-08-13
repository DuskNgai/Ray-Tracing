#include <film.hpp>

#include <algorithm>
#include <fstream>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

RAY_TRACING_NAMESPACE_BEGIN

Film::Film(uint32_t width, uint32_t height, bool enable_gamma_correction)
    : width{ width }
    , height{ height }
    , pixels(width * height)
    , enable_gamma_correction{ enable_gamma_correction } {}

Float Film::get_aspect_ratio() const {
    return static_cast<Float>(this->width) / static_cast<Float>(this->height);
}

Color3f Film::get_pixel(uint32_t i, uint32_t j) const {
    return this->pixels[this->get_pixel_index(i, j)];
}

void Film::set_pixel(uint32_t i, uint32_t j, Color3f const& color) {
    this->pixels[this->get_pixel_index(i, j)] = color;
}

void Film::save(std::filesystem::path const& file_name) const {
    std::vector<uint8_t> buffer;
    buffer.reserve(this->pixels.size() * 3);

    /// @brief Gamma correction.
    auto gamma_correction = [&](Float x, Float gamma = 2.0_f) -> uint8_t {
        x = std::clamp(x, 0.0_f, 1.0_f);
        return this->enable_gamma_correction ? static_cast<uint8_t>(std::pow(x, 1.0_f / gamma) * 255.0_f) : static_cast<uint8_t>(x * 255.0_f);
    };

    for (auto const& color : this->pixels) {
        buffer.emplace_back(gamma_correction(color.x));
        buffer.emplace_back(gamma_correction(color.y));
        buffer.emplace_back(gamma_correction(color.z));
    }

    stbi_flip_vertically_on_write(true);
    stbi_write_png(file_name.string().c_str(), this->width, this->height, 3, buffer.data(), 0);
}

uint32_t Film::get_pixel_index(uint32_t i, uint32_t j) const {
    return j * this->width + i;
}

RAY_TRACING_NAMESPACE_END
