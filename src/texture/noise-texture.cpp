#include <texture/noise-texture.hpp>

#include <array>
#include <algorithm>

#include <utils/random-number-generator.hpp>

RAY_TRACING_NAMESPACE_BEGIN

NoiseTexture::NoiseTexture(Float scale)
    : random_floats(NoiseTexture::POINT_COUNT)
    , perm_x(NoiseTexture::POINT_COUNT)
    , perm_y(NoiseTexture::POINT_COUNT)
    , perm_z(NoiseTexture::POINT_COUNT)
    , scale{ scale } {
    RandomNumberGenerator rng{};
    std::generate(random_floats.begin(), random_floats.end(), [&rng]() {
        return random_vector3f(rng, -1.0_f, 1.0_f);
    });

    std::iota(this->perm_x.begin(), this->perm_x.end(), 0);
    std::iota(this->perm_y.begin(), this->perm_y.end(), 0);
    std::iota(this->perm_z.begin(), this->perm_z.end(), 0);

    std::shuffle(this->perm_x.begin(), this->perm_x.end(), rng.get_generator());
    std::shuffle(this->perm_y.begin(), this->perm_y.end(), rng.get_generator());
    std::shuffle(this->perm_z.begin(), this->perm_z.end(), rng.get_generator());
}

Color3f NoiseTexture::sample([[maybe_unused]] Float u, [[maybe_unused]] Float v, Point3f const& p) const {
    auto s{ this->scale * p };
    return Color3f{ 0.5_f } * (1.0_f + std::sin(s.z + 10.0_f * this->turbulence(p)));
}

Float NoiseTexture::noise(Point3f const& p) const {
    auto i{ static_cast<int32_t>(std::floor(p.x)) };
    auto j{ static_cast<int32_t>(std::floor(p.y)) };
    auto k{ static_cast<int32_t>(std::floor(p.z)) };

    auto u{ p.x - i };
    auto v{ p.y - j };
    auto w{ p.z - k };

    // Hermite cubic interpolation.
    u = u * u * (3 - 2 * u);
    v = v * v * (3 - 2 * v);
    w = w * w * (3 - 2 * w);

    auto c{ std::array<std::array<std::array<Vector3f, 2>, 2>, 2>{} };
    for (auto di{ 0 }; di < 2; ++di) {
        for (auto dj{ 0 }; dj < 2; ++dj) {
            for (auto dk{ 0 }; dk < 2; ++dk) {
                c[di][dj][dk] = this->random_floats[this->perm_x[(i + di) & (NoiseTexture::POINT_COUNT - 1)] ^ this->perm_y[(j + dj) & (NoiseTexture::POINT_COUNT - 1)] ^ this->perm_z[(k + dk) & (NoiseTexture::POINT_COUNT - 1)]];
            }
        }
    }

    // Hermite cubic interpolation.
    auto uu{ u * u * (3 - 2 * u) };
    auto vv{ v * v * (3 - 2 * v) };
    auto ww{ w * w * (3 - 2 * w) };

    // Trilinear interpolation.
    auto acc{ 0.0_f };
    for (auto di{ 0 }; di < 2; ++di) {
        for (auto dj{ 0 }; dj < 2; ++dj) {
            for (auto dk{ 0 }; dk < 2; ++dk) {
                Vector3f weight{ u - di, v - dj, w - dk };
                acc += (di * uu + (1 - di) * (1 - uu)) * (dj * vv + (1 - dj) * (1 - vv)) * (dk * ww + (1 - dk) * (1 - ww)) * glm::dot(c[di][dj][dk], weight);
            }
        }
    }
    return acc;
}

Float NoiseTexture::turbulence(Point3f const& p, int32_t depth) const {
    auto acc{ 0.0_f };
    auto temp_p{ p };
    auto weight{ 1.0_f };

    for (auto i{ 0 }; i < depth; ++i) {
        acc += weight * this->noise(temp_p);
        weight *= 0.5_f;
        temp_p *= 2.0_f;
    }
    return std::abs(acc);
}

RAY_TRACING_NAMESPACE_END
