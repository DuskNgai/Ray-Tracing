#ifndef _RAY_TRACING_CAMERA_HPP_
#define _RAY_TRACING_CAMERA_HPP_

#include <memory>
#include <nlohmann/json.hpp>

#include <film.hpp>
#include <ray.hpp>
#include <utils/random-number-generator.hpp>

RAY_TRACING_NAMESPACE_BEGIN

/// @brief A camera that generates rays whose up direction is always positive y axis.
class Camera {
private:
    Point3f look_from;
    Point3f look_to;
    Vector3f ref_up;

    Float y_field_of_view;
    Float focal_length;
    Float aspect_ratio;
    Float defocus_radius;

    Vector3f look_front;
    Vector3f look_up;
    Vector3f look_right;

    Vector3f horizontal;
    Vector3f vertical;

    std::unique_ptr<Film> film{ nullptr };

public:
    /// @brief Create a camera.
    /// @param look_from The position of the camera.
    /// @param look_to The position of the object that the camera looks at.
    /// @param ref_up The reference up vector of the camera.
    /// @param y_field_of_view The y field of view of the camera, in degrees.
    /// @param focal_length The focal length of the camera.
    /// @param aspect_ratio The aspect ratio of the camera.
    /// @param aperture The aperture size of the camera.
    Camera(Point3f const& look_from, Point3f const& look_to, Vector3f const& ref_up, Float y_field_of_view, Float focal_length, Float aspect_ratio, Float aperture);
    Camera(Camera const& other) = delete;
    Camera(Camera&& other) = delete;
    Camera& operator=(Camera const& other) = delete;
    Camera& operator=(Camera&& other) = delete;

public:
    /// @brief Set the film of the camera, change the aspect radio of camera.
    void set_film(std::unique_ptr<Film> film);

    /// @brief Get the film of the camera.
    Film const& get_film() const;

    /// @brief Set the pixel color of the film.
    void set_pixel(uint32_t i, uint32_t j, Color3f const& color) const;

    /// @brief Generate a ray from the camera.
    Ray generate_ray(uint32_t i, uint32_t j, RandomNumberGenerator& rng) const;

    /// @brief Create a camera based on given configuration.
    static std::shared_ptr<Camera> create(nlohmann::json const& config);

private:
    /// @brief Get the offset inside the pixel.
    std::pair<Float, Float> get_offset_uv(uint32_t i, uint32_t j, RandomNumberGenerator& rng) const;

    /// @brief Get the origin-offseted ray.
    Ray generate_ray(Float u, Float v, RandomNumberGenerator& rng) const;
};

RAY_TRACING_NAMESPACE_END

#endif // !_RAY_TRACING_CAMERA_HPP_
