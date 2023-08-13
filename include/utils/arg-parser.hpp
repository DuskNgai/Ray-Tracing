#ifndef _RAY_TRACING_UTILS_ARG_PARSER_HPP_
#define _RAY_TRACING_UTILS_ARG_PARSER_HPP_

#include <args.hxx>
#include <filesystem>

#include <common.hpp>

RAY_TRACING_NAMESPACE_BEGIN

/// @brief The arguments parsed required from command line.
struct Arguments {
    uint32_t image_width;
    uint32_t image_height;
    uint32_t spp;
    uint32_t ray_tracing_depth;
    std::filesystem::path config_file_path;
    std::filesystem::path output_file_path;
};

/// @brief Parse the arguments from command line.
Arguments parse_args(int argc, char** argv);

RAY_TRACING_NAMESPACE_END

#endif // !_RAY_TRACING_UTILS_ARG_PARSER_HPP_
