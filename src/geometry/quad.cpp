#include <geometry/quad.hpp>

RAY_TRACING_NAMESPACE_BEGIN

Quad::Quad(Point3f const& base_point, Vector3f const& edge_a, Vector3f const& edge_b, std::shared_ptr<Material> const& mat_ptr)
    : base_point{ base_point }
    , edge_a{ edge_a }
    , edge_b{ edge_b }
    , mat_ptr{ mat_ptr } {
    auto unnormalized_normal = glm::cross(edge_a, edge_b);
    this->normal = glm::normalize(unnormalized_normal);
    this->area = glm::length(unnormalized_normal);
    this->D = glm::dot(this->normal, base_point);
    this->w = unnormalized_normal / glm::length2(unnormalized_normal);

    this->bounding_box = AABB::expand(
        { this->base_point, this->base_point + this->edge_a + this->edge_b }
    );
}

bool Quad::hit(Ray const& ray, Interval ray_t, Interaction* interaction) const {
    auto denominator = glm::dot(this->normal, ray.direction);

    // Ray is parallel to the plane.
    if (std::abs(denominator) < EPSILON<Float>) {
        return false;
    }

    // Ray is outside its interval.
    auto t{ (this->D - glm::dot(this->normal, ray.origin)) / denominator };
    if (not ray_t.contains(t)) {
        return false;
    }

    // Ray is behind the plane.
    auto intersection{ ray.at(t) };
    auto coordinate{ intersection - this->base_point };
    auto alpha{ glm::dot(this->w, glm::cross(coordinate, this->edge_b)) };
    auto beta{ glm::dot(this->w, glm::cross(this->edge_a, coordinate)) };

    static const Interval zerone{ 0.0_f, 1.0_f };
    if (not zerone.contains(alpha) or not zerone.contains(beta)) {
        return false;
    }

    interaction->t = t;
    interaction->hit_point = intersection;
    interaction->u = alpha;
    interaction->v = beta;
    interaction->set_face_normal(ray, this->normal);
    interaction->mat_ptr = this->mat_ptr;
    return true;
}

Float Quad::pdf(Point3f const& origin, Vector3f const& direction) const {
    Interaction interaction;
    if (this->hit({ origin, direction }, { 1e-3_f, INF<Float> }, &interaction)) {
        auto direction_squared{ glm::length2(direction) };
        auto distance_squared{ interaction.t * interaction.t * direction_squared };
        auto cosine{ std::abs(glm::dot(direction, this->normal)) / std::sqrt(direction_squared) };
        return distance_squared / (cosine * this->area);
    }
    else {
        return 0.0_f;
    }
}

Vector3f Quad::generate(Point3f const& origin, RandomNumberGenerator& rng) const {
    auto random_point{ this->base_point + rng() * this->edge_a + rng() * this->edge_b };
    return random_point - origin;
}

RAY_TRACING_NAMESPACE_END
