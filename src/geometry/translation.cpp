#include <geometry/translation.hpp>

RAY_TRACING_NAMESPACE_BEGIN

Translation::Translation(std::shared_ptr<Geometry> const& geometry, Vector3f const& offset)
    : geometry{ geometry }
    , offset{ offset } {
    this->bounding_box = {
        {this->geometry->get_bounding_box()[0].min + this->offset.x, this->geometry->get_bounding_box()[0].max + this->offset.x},
        {this->geometry->get_bounding_box()[1].min + this->offset.y, this->geometry->get_bounding_box()[1].max + this->offset.y},
        {this->geometry->get_bounding_box()[2].min + this->offset.z, this->geometry->get_bounding_box()[2].max + this->offset.z}
    };
}

bool Translation::hit(Ray const& ray, Interval ray_t, Interaction* interaction) const {
    // Move the ray backwards by the offset.
    Ray moved_ray{ ray.origin - this->offset, ray.direction, ray.time_point };

    // Determine where (if any) an intersection occurs along the offset ray.
    if (!this->geometry->hit(moved_ray, ray_t, interaction)) {
        return false;
    }

    // Move the intersection point forwards by the offset.
    interaction->hit_point += this->offset;
    return true;
}

RAY_TRACING_NAMESPACE_END
