#ifndef _RAY_TRACING_TEXTURE_CHECKER_TEXTURE_HPP_
#define _RAY_TRACING_TEXTURE_CHECKER_TEXTURE_HPP_

#include <memory>

#include <texture/base-texture.hpp>

RAY_TRACING_NAMESPACE_BEGIN

/// @brief The checker texture returns a color determined by the checker pattern.
class CheckerTexture : public Texture {
private:
    Float inv_scale;
    std::shared_ptr<Texture> odd;
    std::shared_ptr<Texture> even;

public:
    CheckerTexture(Float scale, Color3f const& even, Color3f const& odd);
    CheckerTexture(Float scale, std::shared_ptr<Texture> const& odd, std::shared_ptr<Texture> const& even);

public:
    virtual Color3f sample(Float u, Float v, Point3f const& p) const override;
};

RAY_TRACING_NAMESPACE_END

#endif // !_RAY_TRACING_TEXTURE_CHECKER_TEXTURE_HPP_
