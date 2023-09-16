#ifndef _RAY_TRACING_TEXTURE_NOISE_TEXTURE_HPP_
#define _RAY_TRACING_TEXTURE_NOISE_TEXTURE_HPP_

#include <vector>

#include <texture/base-texture.hpp>

RAY_TRACING_NAMESPACE_BEGIN

/// @brief The noise texture returns a color determined by the Perlin noise.
class NoiseTexture : public Texture {
private:
    static constexpr std::size_t POINT_COUNT{ 256 };
    std::vector<Vector3f> random_floats;
    std::vector<int32_t> perm_x;
    std::vector<int32_t> perm_y;
    std::vector<int32_t> perm_z;
    Float scale;

public:
    NoiseTexture(Float scale);

public:
    virtual Color3f sample(Float u, Float v, Point3f const& p) const override;

private:
    Float noise(Point3f const& p) const;

    Float turbulence(Point3f const& p, int32_t depth = 7) const;
};

RAY_TRACING_NAMESPACE_END

#endif // !_RAY_TRACING_TEXTURE_NOISE_TEXTURE_HPP_
