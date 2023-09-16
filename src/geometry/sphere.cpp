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

Point3f Sphere::get_center(Float) const {
    return this->center;
}

std::pair<Float, Float> Sphere::get_uv(Vector3f const& p) const {
    auto theta{ std::acos(-p.y) };
    auto phi{ std::atan2(-p.z, p.x) + glm::pi<Float>() };
    return { phi / (2.0_f * glm::pi<Float>()), theta / glm::pi<Float>() };
}

RAY_TRACING_NAMESPACE_END
