#ifndef _RAY_TRACING_TEXTURE_IMAGE_TEXTURE_HPP_
#define _RAY_TRACING_TEXTURE_IMAGE_TEXTURE_HPP_

#include <vector>

#include <texture/base-texture.hpp>

RAY_TRACING_NAMESPACE_BEGIN

/// @brief The image texture returns a color determined by the image.
class ImageTexture : public Texture {
private:
    int32_t width;
    int32_t height;
    int32_t channel;
    std::vector<uint8_t> data;

public:
    ImageTexture(std::string const& filename);

public:
    virtual Color3f sample(Float u, Float v, Point3f const& p) const override;
};

RAY_TRACING_NAMESPACE_END

#endif // !_RAY_TRACING_TEXTURE_IMAGE_TEXTURE_HPP_
