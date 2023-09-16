#ifndef _RAY_TRACING_TEXTURE_BASE_TEXTURE_HPP_
#define _RAY_TRACING_TEXTURE_BASE_TEXTURE_HPP_

#include <vector3.hpp>

RAY_TRACING_NAMESPACE_BEGIN

/// @brief The abstract class for all textures.
class Texture {
public:
    virtual ~Texture() = default;

public:
    /// @brief Get the color value of the texture at the given point.
    virtual Color3f sample(Float u, Float v, Point3f const& p) const = 0;

    /// @brief Create a texture object based on given configuration.
    static std::shared_ptr<Texture> create(nlohmann::json const& config);
};

RAY_TRACING_NAMESPACE_END

#endif // !_RAY_TRACING_TEXTURE_BASE_TEXTURE_HPP_
