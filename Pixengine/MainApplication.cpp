#include "MainApplication.h"

void MainApplication::run()
{
    InitWindow();
    InitVulkan();
    MainLoop();
    Cleanup();
}

void MainApplication::InitWindow()
{
    glfwInit();

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr);
}

void MainApplication::InitVulkan()
{
}

void MainApplication::MainLoop()
{
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
    }
}

void MainApplication::Cleanup()
{
    glfwDestroyWindow(window);
    glfwTerminate();
    window = nullptr;
}
