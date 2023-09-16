#ifndef _RAY_TRACING_ACCELERATOR_BVH_HPP_
#define _RAY_TRACING_ACCELERATOR_BVH_HPP_

#include <utils/random-number-generator.hpp>

#include <geometry/geometry.hpp>
#include <geometry/scene.hpp>

RAY_TRACING_NAMESPACE_BEGIN

/// @brief A bounding volume hierarchy that partitions the scene into a binary tree.
class BVH : public Geometry {
private:
    std::shared_ptr<Geometry> left;
    std::shared_ptr<Geometry> right;
    static IntegerRNG rng;

public:
    BVH(std::vector<std::shared_ptr<Geometry>> const& objects);
    BVH(BVH const& other) = delete;
    BVH(BVH&& other) = default;
    BVH& operator=(BVH const& other) = delete;
    BVH& operator=(BVH&& other) = default;

    virtual bool hit(Ray const& ray, Interval ray_t, Interaction* interaction) const override;

private:
    static bool box_compare(std::shared_ptr<Geometry> const& lhs, std::shared_ptr<Geometry> const& rhs, std::size_t axis);
};

RAY_TRACING_NAMESPACE_END

#endif // !_RAY_TRACING_ACCELERATOR_BVH_HPP_
