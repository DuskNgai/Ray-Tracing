#include <integrator.hpp>

#include <atomic>
#include <cstdio>
#include <thread>
#include <vector>

#include <fmt/core.h>
#include <glm/gtx/compatibility.hpp>

#include <material/material.hpp>
#include <pdf/pdf.hpp>

RAY_TRACING_NAMESPACE_BEGIN

Integrator::Integrator(uint32_t spp, uint32_t ray_tracing_depth, nlohmann::json const& config)
    : spp{ spp }
    , ray_tracing_depth{ ray_tracing_depth } {
    this->enable_stratified_sampling = config.at("enable stratified sampling");
    if (this->enable_stratified_sampling) {
        this->sqrt_spp = static_cast<uint32_t>(std::sqrt(this->spp));
        this->inv_sqrt_spp = 1.0_f / static_cast<Float>(this->sqrt_spp);
        if (this->sqrt_spp * this->sqrt_spp != this->spp) {
            fmt::print("Warning: The spp {:d} is not a perfect square.\n", this->spp);
        }
    }
    this->enable_background_color = config.at("enable background color");
    if (this->enable_background_color) {
        this->background_color = from_json(config.at("background color"));
    }
}

void Integrator::render(std::shared_ptr<Scene> const& scene, std::shared_ptr<Scene> const& lights, std::shared_ptr<Camera> const& camera) {
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
                if (this->enable_stratified_sampling) {
                    for (uint32_t sx{ 0 }; sx < this->sqrt_spp; ++sx) {
                        for (uint32_t sy{ 0 }; sy < this->sqrt_spp; ++sy) {
                            Ray ray{ camera->generate_stratified_ray(i, j, sx, sy, this->inv_sqrt_spp, rng) };
                            pixel_color += this->radiance(scene, lights, ray, rng, 0);
                        }
                    }
                }
                else {
                    for (uint32_t s{ 0 }; s < this->spp; ++s) {
                        Ray ray{ camera->generate_ray(i, j, rng) };
                        pixel_color += this->radiance(scene, lights, ray, rng, 0);
                    }
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

Color3f Integrator::radiance(std::shared_ptr<Scene> const& scene, std::shared_ptr<Scene> const& lights, Ray const& ray, RandomNumberGenerator& rng, uint32_t current_depth) {
    if (current_depth > this->ray_tracing_depth) {
        return {};
    }

    Interaction interaction;
    // `t_min` < 5e-5 is not a good choice for avoiding self shadow acne.
    if (scene->hit(ray, { 1e-3_f, INF<Float> }, &interaction)) {
        MaterialRecord record;
        Color3f emitted{ interaction.mat_ptr->emitted(interaction) };

        if (interaction.mat_ptr->scatter(ray, interaction, rng, &record)) {
            if (record.is_specular) {
                return record.attenuation * this->radiance(scene, lights, record.specular_ray, rng, current_depth + 1);
            }

            // Sampling light or bxdf and get its pdf.
            MixturePDF mix_pdf{
                std::make_shared<GeometryPDF>(lights, interaction.hit_point),
                record.pdf_ptr
            };

            Ray scattered{ interaction.hit_point, mix_pdf.generate(rng), ray.time_point };
            Float pdf{ mix_pdf.value(scattered.direction) };

            // Get bxdf value.
            Float bxdf{ interaction.mat_ptr->bxdf(ray, interaction, scattered) };

            // Next event estimation.
            Color3f reflected{ record.attenuation * this->radiance(scene, lights, scattered, rng, current_depth + 1) * bxdf / pdf };
            return emitted + reflected;
        }
        else {
            return emitted;
        }
    }

    if (this->enable_background_color) {
        return this->background_color;
    }
    else {
        auto unit_dir{ glm::normalize(ray.direction) };
        auto t{ (unit_dir.y + 1.0_f) * 0.5_f };
        // return glm::lerp(Color3f{ 1.0_f, 1.0_f, 1.0_f }, Color3f{ 0.5_f, 0.7_f, 1.0_f }, t);
        return Color3f{ 1.0_f, 1.0_f, 1.0_f } - Color3f{ 0.5_f, 0.3_f, 0.0_f } * t;
    }
}

RAY_TRACING_NAMESPACE_END
