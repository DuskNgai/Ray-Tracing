#include <integrator.hpp>

#include <atomic>
#include <cstdio>
#include <thread>
#include <vector>

#include <fmt/core.h>
#include <glm/gtx/compatibility.hpp>

RAY_TRACING_NAMESPACE_BEGIN

Integrator::Integrator(uint32_t spp, uint32_t ray_tracing_depth)
    : spp{ spp }
    , ray_tracing_depth{ ray_tracing_depth } {}

void Integrator::render(std::shared_ptr<Scene> const& scene, std::shared_ptr<Camera> const& camera) {
    std::atomic<uint32_t> scanline_finished{ 0 };

    auto single_thread_render_func = [&]() {
        auto image_width{ camera->get_film().width };
        auto image_height{ camera->get_film().height };
        // Per thread rng for non-competitive access.
        RandomNumberGenerator rng{};

        for (uint32_t j{ scanline_finished.fetch_add(1, std::memory_order_relaxed) }; j < image_height; j = scanline_finished.fetch_add(1, std::memory_order_relaxed)) {
            fmt::print("\rScanlines remaining: {:d} ", image_height - j - 1);
            std::fflush(stdout);

            for (uint32_t i{ 0 }; i < image_width; ++i) {
                Color3f pixel_color{ 0.0_f, 0.0_f, 0.0_f };
                for (uint32_t s{ 0 }; s < this->spp; ++s) {
                    Ray ray{ camera->generate_ray(i, j, rng) };
                    pixel_color += this->radiance(scene, ray, rng, 0);
                }
                camera->set_pixel(i, j, pixel_color / static_cast<Float>(this->spp));
            }
        }
    };

    // Create and launch the threads.
    std::vector<std::thread> threads;
    auto num_threads{ std::thread::hardware_concurrency() };
    fmt::print("Number of threads: {:d}.\n", num_threads);
    for (uint32_t _{ 0 }; _ < num_threads; ++_) {
        threads.emplace_back(single_thread_render_func);
    }
    for (auto&& t : threads) {
        t.join();
    }
}

Color3f Integrator::radiance(std::shared_ptr<Scene> const& scene, Ray const& ray, RandomNumberGenerator& rng, uint32_t current_depth) {
    if (current_depth > this->ray_tracing_depth) {
        return {};
    }

    Interaction interaction;
    // `t_min` < 5e-5 is not a good choice for avoiding self shadow acne.
    if (scene->hit(ray, { 1e-3_f, INF<Float> }, &interaction)) {
        Ray scattered;
        Color3f attenuation;
        if (interaction.mat_ptr->scatter(ray, interaction, rng, &attenuation, &scattered)) {
            return attenuation * this->radiance(scene, scattered, rng, current_depth + 1);
        }
        else {
            return {};
        }
    }

    auto unit_dir{ glm::normalize(ray.direction) };
    auto t{ (unit_dir.y + 1.0_f) * 0.5_f };
    // return glm::lerp(Color3f{ 1.0_f, 1.0_f, 1.0_f }, Color3f{ 0.5_f, 0.7_f, 1.0_f }, t);
    return Color3f{ 1.0_f, 1.0_f, 1.0_f } - Color3f{ 0.5_f, 0.3_f, 0.0_f } * t;
}

RAY_TRACING_NAMESPACE_END
