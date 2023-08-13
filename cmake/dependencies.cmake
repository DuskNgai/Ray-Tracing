CPMAddPackage(
    NAME args
    GIT_TAG 6.4.6
    GITHUB_REPOSITORY Taywee/args
    OPTIONS
        "ARGS_BUILD_EXAMPLE OFF"
        "ARGS_BUILD_UNITTESTS OFF"
)

CPMAddPackage("gh:fmtlib/fmt#9.1.0")

CPMAddPackage("gh:g-truc/glm#0.9.9.8")

CPMAddPackage(
    NAME nlohmann_json
    VERSION 3.11.2
    GITHUB_REPOSITORY nlohmann/json
    OPTIONS
        "JSON_BuildTests OFF"
)

CPMAddPackage(
    NAME stb
    GIT_REPOSITORY https://github.com/nothings/stb.git
    GIT_TAG master
    DOWNLOAD_ONLY YES
)

if (stb_ADDED)
    add_library(stb INTERFACE)
    target_include_directories(stb INTERFACE ${stb_SOURCE_DIR})
endif()
