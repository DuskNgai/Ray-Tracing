#include <texture/solid-color.hpp>

RAY_TRACING_NAMESPACE_BEGIN

SolidColor::SolidColor(Color3f const& color)
    : color{ color } {}

Color3f SolidColor::sample([[maybe_unused]] Float u, [[maybe_unused]] Float v, [[maybe_unused]] Point3f const& p) const {
    return this->color;
}

RAY_TRACING_NAMESPACE_END
