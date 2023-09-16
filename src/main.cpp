#include <fstream>
#include <memory>
#include <string>

#include <fmt/core.h>

#include <geometry/geometry.hpp>
#include <integrator.hpp>
#include <material/material.hpp>
#include <utils/arg-parser.hpp>
#include <utils/timer.hpp>

using namespace rt;

int main(int argc, char** argv) {
    auto args{ parse_args(argc, argv) };

    fmt::print(
        "The image size is {:d} x {:d} pixels, with {:d} spp, depth of each ray is {:d}.\n",
        args.image_width, args.image_height, args.spp, args.ray_tracing_depth
    );

    nlohmann::json config = nlohmann::json::parse(std::ifstream{ args.config_file_path });

    // Create the camera.
    auto camera{ Camera::create(config.at("Camera")) };
    camera->set_film(std::make_unique<Film>(args.image_width, args.image_height, config.at("Enable gamma correction")));

    // Create the scene.
    auto scene{ Scene::create(config.at("Scene"), "Scene") };

    // Create the light.
    auto lights{ Scene::create(config.at("Light"), "Light") };

    // Render the image.
    Timer timer;
    timer.start();
    Integrator integrator{ args.spp, args.ray_tracing_depth, config.at("Integrator") };
    integrator.render(scene, lights, camera);
    fmt::print("\nRendering Done!\n");
    timer.stop();
    fmt::print("Elapsed time: {:d} ms.\n", timer.get_elapsed_time());

    // Output the image.
    camera->get_film().save(args.output_file_path);
    fmt::print("Image saving done!\n");

    return 0;
}
