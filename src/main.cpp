// Gravity Lab: entry point.
//
// You will write the window and OpenGL setup here yourself,
// following "Tutorial 1: Your CMake file and your first window".
#include <glad/gl.h>       // must come before GLFW
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <iostream>
#include <cstdlib>


namespace
{
    // Window settings
    constexpr int kWindowWidth = 1280;
    constexpr int kWindowHeight = 720;
    constexpr const char* kWindowTitle = "Gravity Lab";

    // Background colour (red, green, blue, alpha), each from 0.0 to 1.0
    constexpr float kClearColor[4] = { 0.02f, 0.03f, 0.08f, 1.0f };

    // GLFW calls this whenever something goes wrong inside GLFW.
    void glfwErrorCallback(int errorCode, const char* description)
    {
        std::cerr << "GLFW error " << errorCode << ": " << description << '\n';
    }
}

int main()
{
    glfwSetErrorCallback(glfwErrorCallback);   // before glfwInit, so init errors are reported too
    if (!glfwInit())
    {
        std::cerr << "Failed to initialise GLFW\n";
        return EXIT_FAILURE;
    }
    return 0;
}
