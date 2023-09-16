#include <geometry/volume.hpp>

RAY_TRACING_NAMESPACE_BEGIN

ConstantMedium::ConstantMedium(std::shared_ptr<Geometry> const& boundary, std::shared_ptr<Texture> const& texture, Float density)
    : boundary{ boundary }
    , phase_function{ std::make_shared<Isotropic>(texture) }
    , neg_inv_density{ -1.0_f / density } {
}

ConstantMedium::ConstantMedium(std::shared_ptr<Geometry> const& boundary, Color3f color, Float density)
    : boundary{ boundary }
    , phase_function{ std::make_shared<Isotropic>(color) }
    , neg_inv_density{ -1.0_f / density } {
}

bool ConstantMedium::hit(Ray const& ray, Interval ray_t, Interaction* interaction) const {
    // Print occasional samples when debugging. To enable, set enableDebug true.
    Interaction interaction_1, interaction_2;

    if (not this->boundary->hit(ray, Interval::universe, &interaction_1)) {
        return false;
    }

    if (not this->boundary->hit(ray, { interaction_1.t + 0.0001_f, INF<Float> }, &interaction_2)) {
        return false;
    }

    if (interaction_1.t < ray_t.min) {
        interaction_1.t = ray_t.min;
    }
    if (interaction_2.t > ray_t.max) {
        interaction_2.t = ray_t.max;
    }

    if (interaction_1.t >= interaction_2.t) {
        return false;
    }

    if (interaction_1.t < 0.0_f) {
        interaction_1.t = 0.0_f;
    }

    auto ray_length{ glm::length(ray.direction) };
    auto distance_inside_boundary{ (interaction_2.t - interaction_1.t) * ray_length };
    auto hit_distance{ this->neg_inv_density * std::log(this->rng()) };

    if (hit_distance > distance_inside_boundary) {
        return false;
    }

    interaction->t = interaction_1.t + hit_distance / ray_length;
    interaction->hit_point = ray.at(interaction->t);
    interaction->normal = Vector3f{ 1.0_f, 0.0_f, 0.0_f }; // arbitrary
    interaction->is_outer_face = true;                     // arbitrary
    interaction->mat_ptr = this->phase_function;
    return true;
}

AABB const& ConstantMedium::get_bounding_box() const {
    return this->boundary->get_bounding_box();
}

RAY_TRACING_NAMESPACE_END
