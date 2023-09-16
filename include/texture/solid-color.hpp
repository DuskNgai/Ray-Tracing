#ifndef _RAY_TRACING_TEXTURE_SOLID_COLOR_HPP_
#define _RAY_TRACING_TEXTURE_SOLID_COLOR_HPP_

#include <texture/base-texture.hpp>

RAY_TRACING_NAMESPACE_BEGIN

/// @brief The solid texture always returns a constant color.
class SolidColor : public Texture {
private:
    Color3f color;

public:
    explicit SolidColor(Color3f const& color);

public:
    virtual Color3f sample(Float u, Float v, Point3f const& p) const override;
};

RAY_TRACING_NAMESPACE_END

#endif // !_RAY_TRACING_TEXTURE_SOLID_COLOR_HPP_
