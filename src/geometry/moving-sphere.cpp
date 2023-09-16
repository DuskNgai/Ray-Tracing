#include <geometry/moving-sphere.hpp>

RAY_TRACING_NAMESPACE_BEGIN

MovingSphere::MovingSphere(Point3f const& start_center, Point3f const& end_center, Float radius, std::shared_ptr<Material> const& mat_ptr)
    : Sphere{ start_center, radius, mat_ptr }
    , center_vector{ end_center - start_center } {
    this->bounding_box = AABB::merge(
        { Point3f{ this->center - this->radius }, Point3f{ this->center + this->radius } },
        { Point3f{ this->center + this->center_vector - this->radius }, Point3f{ this->center + this->center_vector + this->radius } }
    );
}

Point3f MovingSphere::get_center(Float time_point) const {
    return this->center + this->center_vector * time_point;
}

RAY_TRACING_NAMESPACE_END
