cmake_minimum_required(VERSION 3.24)

# Set C++ compiler flags before `project`
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Set the project name.
set(PROJECT_NAME "Ray-Tracing")
project(${PROJECT_NAME} LANGUAGES C CXX)

# Set compiler flags.
if(MSVC)
    set(CMAKE_CXX_FLAGS "/W3 /permissive- /EHsc")
    add_compile_definitions("_CRT_SECURE_NO_WARNINGS")
else()
    set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror -Wpedantic")
endif()

include(CheckIPOSupported)
check_ipo_supported(RESULT is_ipo_supported)
if(is_ipo_supported)
    message(STATUS "Turn on INTERPROCEDURAL_OPTIMIZATION")
    set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)
endif()

# Set output directories.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}")

# Include cmake scripts
include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/CPM.cmake")
include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/dependencies.cmake")

# Set the include directories.
list(APPEND RAY_TRACING_INCLUDES
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Set the linking libraries.
list(APPEND RAY_TRACING_LIBRARIES
    args
    fmt::fmt
    glm::glm
    nlohmann_json::nlohmann_json
    stb
)

# Set the source files.
aux_source_directory(src SRC_FILES)
aux_source_directory(src/accelerator SRC_FILES)
aux_source_directory(src/geometry SRC_FILES)
aux_source_directory(src/material SRC_FILES)
aux_source_directory(src/texture SRC_FILES)
aux_source_directory(src/utils SRC_FILES)

add_executable(${PROJECT_NAME} ${SRC_FILES})
target_include_directories(${PROJECT_NAME} PRIVATE ${RAY_TRACING_INCLUDES})
target_link_libraries(${PROJECT_NAME} PRIVATE ${RAY_TRACING_LIBRARIES})
