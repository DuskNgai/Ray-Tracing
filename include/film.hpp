#ifndef _RAY_TRACING_FILM_HPP_
#define _RAY_TRACING_FILM_HPP_

#include <string>
#include <filesystem>
#include <vector>

#include <vector3.hpp>

RAY_TRACING_NAMESPACE_BEGIN

/// @brief A film is a 2D array of pixels.
struct Film {
    uint32_t width;
    uint32_t height;
    std::vector<Color3f> pixels;
    bool enable_gamma_correction;

    /// @brief Create a new film.
    Film(uint32_t width, uint32_t height, bool enable_gamma_correction);
    Film(Film const&) = delete;
    Film(Film&&) = delete;
    Film& operator=(Film const&) = delete;
    Film& operator=(Film&&) = delete;

    /// @brief Get the aspect ratio of a film.
    Float get_aspect_ratio() const;

    /// @brief Get the color of a pixel.
    Color3f get_pixel(uint32_t i, uint32_t j) const;

    /// @brief Set the color of a pixel.
    void set_pixel(uint32_t i, uint32_t j, Color3f const& color);

    /// @brief Save a film to a file.
    void save(std::filesystem::path const& file_name) const;

private:
    /// @brief Get the index of 2 dimensional array.
    uint32_t get_pixel_index(uint32_t i, uint32_t j) const;
};

RAY_TRACING_NAMESPACE_END

#endif // !_RAY_TRACING_FILM_HPP_
