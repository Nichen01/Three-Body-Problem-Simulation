# Minimum CMake version we rely on (FetchContent_MakeAvailable needs 3.14+).
cmake_minimum_required(VERSION 3.20)

project(GravityLab LANGUAGES C CXX)

# Use C++17 everywhere, and don't fall back to compiler-specific dialects.
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ---------------------------------------------------------------------------
# Dependencies
# FetchContent downloads each library the first time you configure, then
# builds it as part of this project. Nothing has to be installed on the PC.
# ---------------------------------------------------------------------------
include(FetchContent)

# GLFW: creates the window and the OpenGL context, and reads keyboard/mouse.
set(GLFW_BUILD_DOCS     OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS    OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL        OFF CACHE BOOL "" FORCE)
FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG        3.4
    GIT_SHALLOW    TRUE
)

# GLM: vector and matrix maths (glm::vec2, glm::mat4, ...). Header-only.
FetchContent_Declare(
    glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG        1.0.1
    GIT_SHALLOW    TRUE
)

FetchContent_MakeAvailable(glfw glm)

# GLAD: loads the OpenGL 3.3 Core functions at runtime.
# These files were generated once with the glad2 generator and committed,
# because they never change unless we target a different OpenGL version.
add_library(glad STATIC external/glad/src/gl.c)
target_include_directories(glad PUBLIC external/glad/include)

# ---------------------------------------------------------------------------
# Our application
# ---------------------------------------------------------------------------
add_executable(GravityLab
    src/main.cpp
)

target_link_libraries(GravityLab PRIVATE glfw glad glm::glm)

# Turn on useful warnings. Warnings are often bugs waiting to happen.
if(MSVC)
    target_compile_options(GravityLab PRIVATE /W4 /permissive-)
    # Make GravityLab the project that runs when you press F5 in Visual Studio.
    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT GravityLab)
else()
    target_compile_options(GravityLab PRIVATE -Wall -Wextra -Wpedantic)
endif()
