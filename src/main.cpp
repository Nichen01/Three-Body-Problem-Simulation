// Step 1: open an OpenGL 3.3 Core window and clear it to a colour.
//
// Order matters here:
//   1. Start GLFW.
//   2. Ask GLFW for an OpenGL 3.3 Core context, then create the window.
//   3. Make that context "current" so OpenGL calls go to this window.
//   4. Load the OpenGL functions with GLAD (only possible once a context exists).
//   5. Run the render loop until the window is closed.
//   6. Clean up.

// GLAD must be included before GLFW, because GLFW checks whether an
// OpenGL header has already been included.
#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <cstdlib>
#include <iostream>

namespace
{
    constexpr int kWindowWidth  = 1280;
    constexpr int kWindowHeight = 720;

    // GLFW calls this whenever something goes wrong inside GLFW.
    void glfwErrorCallback(int errorCode, const char* description)
    {
        std::cerr << "GLFW error " << errorCode << ": " << description << '\n';
    }

    // GLFW calls this whenever the window's framebuffer changes size
    // (for example when you drag the window edge). We tell OpenGL to draw
    // into the whole new area.
    void framebufferSizeCallback(GLFWwindow* /*window*/, int width, int height)
    {
        glViewport(0, 0, width, height);
    }

    void processInput(GLFWwindow* window)
    {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        {
            glfwSetWindowShouldClose(window, GLFW_TRUE);
        }
    }
}

int main()
{
    // 1. Start GLFW.
    glfwSetErrorCallback(glfwErrorCallback);
    if (!glfwInit())
    {
        std::cerr << "Failed to initialise GLFW\n";
        return EXIT_FAILURE;
    }

    // 2. Window hints are settings for the *next* window we create.
    //    We ask for OpenGL 3.3 with the Core profile (no deprecated functions).
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE); // required on macOS
#endif

    GLFWwindow* window = glfwCreateWindow(kWindowWidth, kWindowHeight, "Gravity Lab", nullptr, nullptr);
    if (window == nullptr)
    {
        std::cerr << "Failed to create the GLFW window\n";
        glfwTerminate();
        return EXIT_FAILURE;
    }

    // 3. Make this window's OpenGL context current on this thread.
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
    glfwSwapInterval(1); // vsync: wait for the monitor refresh before swapping

    // 4. Load OpenGL functions. glfwGetProcAddress looks up each function
    //    in your graphics driver. gladLoadGL returns 0 on failure.
    const int glVersion = gladLoadGL(glfwGetProcAddress);
    if (glVersion == 0)
    {
        std::cerr << "Failed to load OpenGL functions with GLAD\n";
        glfwDestroyWindow(window);
        glfwTerminate();
        return EXIT_FAILURE;
    }
    std::cout << "Loaded OpenGL " << GLAD_VERSION_MAJOR(glVersion) << '.' << GLAD_VERSION_MINOR(glVersion) << '\n';
    std::cout << "Renderer: " << glGetString(GL_RENDERER) << '\n';

    // The framebuffer can differ from the window size on high-DPI screens,
    // so ask for the real framebuffer size for the first viewport.
    int framebufferWidth = 0;
    int framebufferHeight = 0;
    glfwGetFramebufferSize(window, &framebufferWidth, &framebufferHeight);
    glViewport(0, 0, framebufferWidth, framebufferHeight);

    // 5. The render loop: one pass = one frame.
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        // Pick the clear colour (a dark navy "space" colour), then clear.
        glClearColor(0.02f, 0.03f, 0.08f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // We drew into the hidden back buffer. Swap it with the visible
        // front buffer so the new frame appears all at once.
        glfwSwapBuffers(window);

        // Let GLFW handle window events (close button, resize, keys...).
        glfwPollEvents();
    }

    // 6. Clean up in reverse order of creation.
    glfwDestroyWindow(window);
    glfwTerminate();
    return EXIT_SUCCESS;
}
