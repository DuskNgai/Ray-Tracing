#include <accelerator/bvh.hpp>

RAY_TRACING_NAMESPACE_BEGIN

IntegerRNG BVH::rng{ 0, 2 };

BVH::BVH(std::vector<std::shared_ptr<Geometry>> const& objects) {
    auto obj_copy{ objects };
    auto num_objs{ obj_copy.size() };
    auto axis{ BVH::rng() };

    if (num_objs == 1) {
        this->left = obj_copy[0];
        this->right = obj_copy[0];
    }
    else if (num_objs == 2) {
        if (BVH::box_compare(obj_copy[0], obj_copy[1], axis)) {
            this->left = obj_copy[0];
            this->right = obj_copy[1];
        }
        else {
            this->left = obj_copy[1];
            this->right = obj_copy[0];
        }
    }
    else {
        auto middle{ obj_copy.begin() + num_objs / 2 };
        std::nth_element(obj_copy.begin(), middle, obj_copy.end(), [axis](auto const& lhs, auto const& rhs) {
            return BVH::box_compare(lhs, rhs, axis);
        });

        this->left = std::make_shared<BVH>(std::vector<std::shared_ptr<Geometry>>{ obj_copy.begin(), middle });
        this->right = std::make_shared<BVH>(std::vector<std::shared_ptr<Geometry>>{ middle, obj_copy.end() });
    }

    this->bounding_box = AABB::merge(this->left->get_bounding_box(), this->right->get_bounding_box());
}

bool BVH::hit(Ray const& ray, Interval ray_t, Interaction* interaction) const {
    if (not this->get_bounding_box().hit(ray, ray_t))
        return false;

    bool hit_left{ this->left->hit(ray, ray_t, interaction) };
    bool hit_right{ this->right->hit(ray, { ray_t.min, (hit_left ? interaction->t : ray_t.max) }, interaction) };

    return hit_left || hit_right;
}

bool BVH::box_compare(std::shared_ptr<Geometry> const& lhs, std::shared_ptr<Geometry> const& rhs, std::size_t axis) {
    return lhs->get_bounding_box()[axis].min < rhs->get_bounding_box()[axis].min;
}

RAY_TRACING_NAMESPACE_END
