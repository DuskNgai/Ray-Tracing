#include <geometry/rotation.hpp>

RAY_TRACING_NAMESPACE_BEGIN

YRotation::YRotation(std::shared_ptr<Geometry> const& geometry, Float angle)
    : geometry{ geometry }
    , sin_theta{ std::sin(glm::radians(angle)) }
    , cos_theta{ std::cos(glm::radians(angle)) } {
    this->bounding_box = this->geometry->get_bounding_box();
    Point3f min{ INF<Float>, INF<Float>, INF<Float> };
    Point3f max{ -INF<Float>, -INF<Float>, -INF<Float> };
    for (auto i{ 0 }; i < 2; ++i) {
        for (auto j{ 0 }; j < 2; ++j) {
            for (auto k{ 0 }; k < 2; ++k) {
                auto x{ i * this->bounding_box[0].max + (1 - i) * this->bounding_box[0].min };
                auto y{ j * this->bounding_box[1].max + (1 - j) * this->bounding_box[1].min };
                auto z{ k * this->bounding_box[2].max + (1 - k) * this->bounding_box[2].min };
                auto new_x{ this->cos_theta * x + this->sin_theta * z };
                auto new_z{ -this->sin_theta * x + this->cos_theta * z };

                Vector3f tester{ new_x, y, new_z };
                for (auto c{ 0 }; c < 3; ++c) {
                    min[c] = std::min(min[c], tester[c]);
                    max[c] = std::max(max[c], tester[c]);
                }
            }
        }
    }
    this->bounding_box = { min, max };
}

bool YRotation::hit(Ray const& ray, Interval ray_t, Interaction* interaction) const {
    // Change the ray from world space to object space.
    auto origin{ ray.origin };
    auto direction{ ray.direction };

    origin.x = this->cos_theta * ray.origin.x - this->sin_theta * ray.origin.z;
    origin.z = this->sin_theta * ray.origin.x + this->cos_theta * ray.origin.z;

    direction.x = this->cos_theta * ray.direction.x - this->sin_theta * ray.direction.z;
    direction.z = this->sin_theta * ray.direction.x + this->cos_theta * ray.direction.z;

    Ray rotated_ray{ origin, direction, ray.time_point };

    // Determine where (if any) an intersection occurs in object space.
    if (!this->geometry->hit(rotated_ray, ray_t, interaction)) {
        return false;
    }

    // Change the intersection point from object space to world space.
    auto hit_point{ interaction->hit_point };
    auto normal{ interaction->normal };

    hit_point.x = this->cos_theta * interaction->hit_point.x + this->sin_theta * interaction->hit_point.z;
    hit_point.z = -this->sin_theta * interaction->hit_point.x + this->cos_theta * interaction->hit_point.z;

    normal.x = this->cos_theta * interaction->normal.x + this->sin_theta * interaction->normal.z;
    normal.z = -this->sin_theta * interaction->normal.x + this->cos_theta * interaction->normal.z;

    interaction->hit_point = hit_point;
    interaction->normal = normal;

    return true;
}

RAY_TRACING_NAMESPACE_END
