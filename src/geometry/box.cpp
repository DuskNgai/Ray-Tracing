#include <geometry/box.hpp>

#include <vector>

#include <geometry/quad.hpp>

RAY_TRACING_NAMESPACE_BEGIN

Box::Box(Point3f const& minimum, Point3f const& maximum, std::shared_ptr<Material> const& mat_ptr) {
    this->bounding_box = { minimum, maximum };

    Vector3f dx{ this->bounding_box[0].size(), 0.0_f, 0.0_f };
    Vector3f dy{ 0.0_f, this->bounding_box[1].size(), 0.0_f };
    Vector3f dz{ 0.0_f, 0.0_f, this->bounding_box[2].size() };

    std::vector<std::shared_ptr<Geometry>> quads{
        std::make_shared<Quad>(Point3f{ this->bounding_box[0].min, this->bounding_box[1].min, this->bounding_box[2].min }, dy, dx, mat_ptr),   // back
        std::make_shared<Quad>(Point3f{ this->bounding_box[0].min, this->bounding_box[1].min, this->bounding_box[2].min }, dz, dy, mat_ptr),   // left
        std::make_shared<Quad>(Point3f{ this->bounding_box[0].min, this->bounding_box[1].min, this->bounding_box[2].min }, dx, dz, mat_ptr),   // bottom
        std::make_shared<Quad>(Point3f{ this->bounding_box[0].max, this->bounding_box[1].max, this->bounding_box[2].max }, -dx, -dy, mat_ptr), // front
        std::make_shared<Quad>(Point3f{ this->bounding_box[0].max, this->bounding_box[1].max, this->bounding_box[2].max }, -dy, -dz, mat_ptr), // right
        std::make_shared<Quad>(Point3f{ this->bounding_box[0].max, this->bounding_box[1].max, this->bounding_box[2].max }, -dz, -dx, mat_ptr)  // top
    };

    this->faces = std::make_shared<Scene>(quads);
}

bool Box::hit(Ray const& ray, Interval ray_t, Interaction* interaction) const {
    return this->faces->hit(ray, ray_t, interaction);
}

RAY_TRACING_NAMESPACE_END
