#include <geometry/sphere.hpp>

RAY_TRACING_NAMESPACE_BEGIN

Sphere::Sphere(Point3f const& center, Float radius, std::shared_ptr<Material> const& mat_ptr)
    : center{ center }
    , radius{ radius }
    , mat_ptr{ mat_ptr } {
    this->bounding_box = {
        Point3f{ this->center - this->radius },
        Point3f{ this->center + this->radius }
    };
}

bool Sphere::hit(Ray const& ray, Interval ray_t, Interaction* interaction) const {
    auto center_at_time{ this->get_center(ray.time_point) };
    Vector3f oc{ ray.origin - center_at_time };

    // Convert to a quadratic equation.
    Float a{ glm::length2(ray.direction) };
    Float b_half{ glm::dot(oc, ray.direction) };
    Float c{ glm::length2(oc) - this->radius * this->radius };
    Float discriminant{ b_half * b_half - a * c };

    if (discriminant < 0.0_f) {
        return false;
    }

    // Find and check the root.
    Float sqrt_discriminant{ std::sqrt(discriminant) };
    Float t{ (-b_half - sqrt_discriminant) / a };
    if (not ray_t.surrounds(t)) {
        t = (-b_half + sqrt_discriminant) / a;
        if (not ray_t.surrounds(t)) {
            return false;
        }
    }

    // Record this interaction.
    interaction->t = t;
    interaction->hit_point = ray.at(t);
    interaction->set_face_normal(ray, (interaction->hit_point - center) / this->radius);
    std::tie(interaction->u, interaction->v) = this->get_uv(interaction->normal);
    interaction->mat_ptr = this->mat_ptr;
    return true;
}

Float Sphere::pdf(Point3f const& origin, Vector3f const& direction) const {
    Interaction interaction;
    if (not this->hit(Ray{ origin, direction }, Interval{ 1e-3_f, INF<Float> }, &interaction)) {
        return 0.0_f;
    }

    auto cos_theta_max{ std::sqrt(1.0_f - this->radius * this->radius / glm::length2(origin - this->center)) };
    auto solid_angle{ 2.0_f * glm::pi<Float>() * (1.0_f - cos_theta_max) };
    return 1.0_f / solid_angle;
}

Vector3f Sphere::generate(Point3f const& origin, RandomNumberGenerator& rng) const {
    Vector3f direction{ this->center - origin };
    auto distance_squared{ glm::length2(direction) };

    auto s{ rng() }, t{ rng() };
    auto phi{ 2.0_f * glm::pi<Float>() * s };
    auto z{ 1.0_f + t * (std::sqrt(1.0_f - this->radius * this->radius / distance_squared) - 1.0_f) };
    auto x{ std::cos(phi) * std::sqrt(1.0_f - z * z) };
    auto y{ std::sin(phi) * std::sqrt(1.0_f - z * z) };

    Vector3f new_direction{ x, y, z };
    Vector3f up{
        std::abs(x) > 0.9_f ? Vector3f{0.0_f, 1.0_f, 0.0_f}
                            : Vector3f{1.0_f, 0.0_f, 0.0_f}
    };
    Vector3f v{ glm::normalize(glm::cross(direction, up)) };
    Vector3f u{ glm::cross(direction, v) };
    Vector3f target_direction{ new_direction.x * u + new_direction.y * v + new_direction.z * direction };
    return target_direction;
}

Point3f Sphere::get_center(Float) const {
    return this->center;
}

std::pair<Float, Float> Sphere::get_uv(Vector3f const& p) const {
    auto theta{ std::acos(-p.y) };
    auto phi{ std::atan2(-p.z, p.x) + glm::pi<Float>() };
    return { phi / (2.0_f * glm::pi<Float>()), theta / glm::pi<Float>() };
}

RAY_TRACING_NAMESPACE_END
