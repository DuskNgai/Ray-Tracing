#include <texture/checker-texture.hpp>
#include <texture/solid-color.hpp>

RAY_TRACING_NAMESPACE_BEGIN

CheckerTexture::CheckerTexture(Float scale, Color3f const& even, Color3f const& odd)
    : CheckerTexture{ scale, std::make_shared<SolidColor>(even), std::make_shared<SolidColor>(odd) } {}

CheckerTexture::CheckerTexture(Float scale, std::shared_ptr<Texture> const& odd, std::shared_ptr<Texture> const& even)
    : inv_scale{ 1.0f / scale }
    , odd{ odd }
    , even{ even } {}

Color3f CheckerTexture::sample(Float u, Float v, Point3f const& p) const {
    auto x{ static_cast<int64_t>(std::floor(p.x * this->inv_scale)) };
    auto y{ static_cast<int64_t>(std::floor(p.y * this->inv_scale)) };
    auto z{ static_cast<int64_t>(std::floor(p.z * this->inv_scale)) };
    auto is_even{ (x + y + z) % 2 == 0 };
    return is_even ? this->even->sample(u, v, p) : this->odd->sample(u, v, p);
}

RAY_TRACING_NAMESPACE_END
