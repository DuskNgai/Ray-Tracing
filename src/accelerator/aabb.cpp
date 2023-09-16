#include <accelerator/aabb.hpp>

RAY_TRACING_NAMESPACE_BEGIN

AABB::AABB(Interval x, Interval y, Interval z)
    : intervals{ x, y, z } {}

AABB::AABB(Point3f const& minimum, Point3f const& maximum)
    : intervals{
        {std::min(minimum.x, maximum.x), std::max(minimum.x, maximum.x)},
        {std::min(minimum.y, maximum.y), std::max(minimum.y, maximum.y)},
        {std::min(minimum.z, maximum.z), std::max(minimum.z, maximum.z)}
} {}

bool AABB::hit(Ray const& ray, Interval ray_t) const {
    for (int i = 0; i < 3; ++i) {
        Float inv_d{ 1.0_f / ray.direction[i] };
        Float t0{ (this->intervals[i].min - ray.origin[i]) * inv_d };
        Float t1{ (this->intervals[i].max - ray.origin[i]) * inv_d };

        if (inv_d < 0.0_f) {
            std::swap(t0, t1);
        }

        if (t0 > ray_t.min) {
            ray_t.min = t0;
        }
        if (t1 < ray_t.max) {
            ray_t.max = t1;
        }
        if (ray_t.max <= ray_t.min) {
            return false;
        }
    }
    return true;
}

Interval const& AABB::operator[](std::size_t index) const {
    return this->intervals[index];
}

AABB AABB::merge(AABB const& a, AABB const& b) {
    return {
        Interval::merge(a[0], b[0]),
        Interval::merge(a[1], b[1]),
        Interval::merge(a[2], b[2])
    };
}

AABB AABB::expand(AABB const& aabb, Float min_width) {
    return {
        aabb[0].size() < min_width ? Interval::expand(aabb[0], min_width) : aabb[0],
        aabb[1].size() < min_width ? Interval::expand(aabb[1], min_width) : aabb[1],
        aabb[2].size() < min_width ? Interval::expand(aabb[2], min_width) : aabb[2]
    };
}

RAY_TRACING_NAMESPACE_END
