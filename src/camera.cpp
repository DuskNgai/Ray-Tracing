#include <camera.hpp>

RAY_TRACING_NAMESPACE_BEGIN

Camera::Camera(
    Point3f const& look_from,
    Point3f const& look_to,
    Vector3f const& ref_up,
    Float y_field_of_view,
    Float focal_length,
    Float aspect_ratio,
    Float defocus_angle
)
    : look_from{ look_from }
    , look_to{ look_to }
    , ref_up{ ref_up }
    , y_field_of_view{ y_field_of_view }
    , focal_length{ focal_length }
    , aspect_ratio{ aspect_ratio }
    , defocus_radius{ this->focal_length * std::tan(glm::radians(defocus_angle / 2.0_f)) } {
    this->look_front = glm::normalize(this->look_to - this->look_from);
    this->look_right = glm::normalize(glm::cross(this->look_front, this->ref_up));
    this->look_up = glm::cross(this->look_right, this->look_front);

    auto viewport_height_half{ std::tan(glm::radians(this->y_field_of_view / 2.0_f)) * this->focal_length };
    auto viewport_width_half{ viewport_height_half * this->aspect_ratio };

    this->vertical = this->look_up * viewport_height_half;
    this->horizontal = this->look_right * viewport_width_half;
}

void Camera::set_film(std::unique_ptr<Film> film) {
    this->film = std::move(film);
}

Film const& Camera::get_film() const {
    return *this->film;
}

void Camera::set_pixel(uint32_t i, uint32_t j, Color3f const& color) const {
    this->film->set_pixel(i, j, color);
}

Ray Camera::generate_ray(uint32_t i, uint32_t j, RandomNumberGenerator& rng) const {
    auto [u, v]{ this->get_offset_uv(i, j, rng) };
    return this->generate_ray(u, v, rng);
}

Ray Camera::generate_stratified_ray(uint32_t i, uint32_t j, uint32_t sx, uint32_t sy, Float inv_sqrt_spp, RandomNumberGenerator& rng) const {
    auto [u, v]{ this->get_stratified_offset_uv(i, j, sx, sy, inv_sqrt_spp, rng) };
    return this->generate_ray(u, v, rng);
}

std::shared_ptr<Camera> Camera::create(nlohmann::json const& config) {
    return std::make_shared<Camera>(
        from_json(config.at("look_from")),
        from_json(config.at("look_to")),
        from_json(config.at("ref_up")),
        config.at("y_field_of_view"),
        config.at("focal_length"),
        config.at("aspect_ratio"),
        config.at("defocus_angle")
    );
}

std::pair<Float, Float> Camera::get_offset_uv(uint32_t i, uint32_t j, RandomNumberGenerator& rng) const {
    // Shoot ray to the center of the pixel.
    Float u{ (2.0_f * (static_cast<Float>(i) + rng()) / static_cast<Float>(this->film->width)) - 1.0_f };
    Float v{ (2.0_f * (static_cast<Float>(j) + rng()) / static_cast<Float>(this->film->height)) - 1.0_f };
    return { u, v };
}

std::pair<Float, Float> Camera::get_stratified_offset_uv(uint32_t i, uint32_t j, uint32_t sx, uint32_t sy, Float inv_sqrt_spp, RandomNumberGenerator& rng) const {
    // Shoot ray to the subpixel.
    Float du{ (static_cast<Float>(sx) + rng()) * inv_sqrt_spp };
    Float dv{ (static_cast<Float>(sy) + rng()) * inv_sqrt_spp };

    Float u{ (2.0_f * (static_cast<Float>(i) + du) / static_cast<Float>(this->film->width)) - 1.0_f };
    Float v{ (2.0_f * (static_cast<Float>(j) + dv) / static_cast<Float>(this->film->height)) - 1.0_f };
    return { u, v };
}

Ray Camera::generate_ray(Float u, Float v, RandomNumberGenerator& rng) const {
    Point3f origin{ this->look_from };
    Vector3f direction{ this->horizontal * u + this->vertical * v + this->look_front * this->focal_length };

    if (this->defocus_radius > 0.0_f) {
        Vector3f random_direction{ this->defocus_radius * random_vector3f_in_unit_circle(rng) };
        Vector3f offset{ this->look_right * random_direction.x + this->look_up * random_direction.y };
        origin += offset;
        direction -= offset;
    }
    return { origin, direction, rng() };
}

RAY_TRACING_NAMESPACE_END
