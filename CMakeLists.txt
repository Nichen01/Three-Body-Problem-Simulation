cmake_minimum_required(VERSION 3.20)
project(ThreeBody_Problem LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)
add_library(glad STATIC external/glad/src/gl.c)
target_include_directories(glad PUBLIC external/glad/include)

add_executable(ThreeBody src/main.cpp)

include(FetchContent)
FetchContent_Declare(glfw GIT_REPOSITORY https://github.com/glfw/glfw.git GIT_TAG 3.4 GIT_SHALLOW TRUE)
FetchContent_Declare(glm GIT_REPOSITORY https://github.com/g-truc/glm.git GIT_TAG 1.0.1 GIT_SHALLOW TRUE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(glfw glm)

# Warnings for our own code only (not the libraries).
if(MSVC)
    target_compile_options(ThreeBody PRIVATE /W4 /permissive-)
else()
    target_compile_options(ThreeBody PRIVATE -Wall -Wextra -Wpedantic)
endif()

target_link_libraries(ThreeBody PRIVATE glfw glad glm)

