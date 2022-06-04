#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include "DeviceInfo.h"

class MainApplication
{
private:
    const int WIDTH = 640;
    const int HEIGHT = 480;
    GLFWwindow* window;
    VkInstance vkInstance;
    DeviceInfo mainDevice;

public:
    void run();

private:
    void InitWindow();
    void InitVulkan();
    void MainLoop();
    void Cleanup();
    void CheckMemberVariables();
};

