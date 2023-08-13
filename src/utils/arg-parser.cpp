#include <utils/arg-parser.hpp>

#include <cstdlib>

#include <fmt/core.h>

RAY_TRACING_NAMESPACE_BEGIN

Arguments parse_args(int argc, char** argv) {
    // clang-format off
    args::ArgumentParser parser{"A simple ray tracing."};

    args::HelpFlag help{ parser, "help", "Display this help menu.", { 'h', "help" } };

    args::Group defaulted{ parser, "This group of arguments has default value.", args::Group::Validators::DontCare };
    args::ValueFlag<uint32_t> width_flag{ defaulted, "WIDTH", "Resolution width of the output image, default to 960.", { "width" }, 960 };
    args::ValueFlag<uint32_t> height_flag{ defaulted, "HEIGHT", "Resolution height of the output image, default to 540.", { "height" }, 540 };
    args::ValueFlag<uint32_t> spp_flag{ defaulted, "SAMPLE_PER_PIXEL", "Number of samples per pixel, default to 100.", { "spp", "sample-per-pixels" }, 100 };
    args::ValueFlag<uint32_t> depth_flag{ defaulted, "RAY_TRACE_DEPTH", "The depth to tracing a ray, default to 50.", { "depth", "ray-tracing-depth" }, 50 };

    args::Group required{ parser, "This group of arguments is all required from command line.", args::Group::Validators::All };
    args::ValueFlag<std::string> config_file_path_flag{ required, "CONFIG_FILE_PATH", "Path to the config file.", { "config-file-path" } };
    args::ValueFlag<std::string> output_file_path_flag{ required, "OUTPUT_FILE_PATH", "Path to the output image file.", { "output-file-path" } };
    // clang-format on

    try {
        parser.ParseCLI(argc, argv);
    }
    catch (args::Help const&) {
        std::fprintf(stderr, "%s", parser.Help().c_str());
        std::exit(0);
    }
    catch (args::ParseError const& e) {
        std::fprintf(stderr, "%s\n", e.what());
        std::fprintf(stderr, "%s", parser.Help().c_str());
        std::exit(-1);
    }
    catch (args::ValidationError const& e) {
        std::fprintf(stderr, "%s\n", e.what());
        std::fprintf(stderr, "%s", parser.Help().c_str());
        std::exit(-2);
    }

    std::filesystem::path config_file_path{ args::get(config_file_path_flag) };
    if (not std::filesystem::exists(config_file_path)) {
        fmt::print("[Error] The config file path {:s} does not exist, process terminate.\n", config_file_path.string());
        std::exit(-3);
    }

    std::filesystem::path output_file_path{ args::get(output_file_path_flag) };
    if (not std::filesystem::exists(output_file_path.parent_path())) {
        fmt::print("[Error] The directory of the output file path {:s} does not exist, process terminate.\n", output_file_path.string());
        std::exit(-3);
    }

    return {
        args::get(width_flag),
        args::get(height_flag),
        args::get(spp_flag),
        args::get(depth_flag),
        config_file_path,
        output_file_path,
    };
}

RAY_TRACING_NAMESPACE_END
