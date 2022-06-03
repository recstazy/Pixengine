#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

class MainApplication
{
private:
    const int WIDTH = 640;
    const int HEIGHT = 480;
    GLFWwindow* window;
    VkInstance vkInstance;

public:
    void run();

private:
    void InitWindow();
    void InitVulkan();
    void MainLoop();
    void Cleanup();
    void CreateVulkanInstance();
    void LogGlfwExtensions(uint32_t extensionsCount, const char** glfwExtensions);
};

