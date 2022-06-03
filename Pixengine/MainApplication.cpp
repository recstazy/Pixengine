#include "MainApplication.h"
#include <stdexcept>
#include <vector>
#include <iostream>

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
    CreateVulkanInstance();
}

void MainApplication::MainLoop()
{
    while (!glfwWindowShouldClose(window)) 
    {
        glfwPollEvents();
    }
}

void MainApplication::Cleanup()
{
    vkDestroyInstance(vkInstance, nullptr);
    glfwDestroyWindow(window);
    glfwTerminate();
    window = nullptr;
}

void MainApplication::CreateVulkanInstance()
{
    VkApplicationInfo appInfo{};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "Pixengine";
    appInfo.applicationVersion = VK_MAKE_VERSION(0, 1, 0);
    appInfo.pEngineName = "No Engine";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_API_VERSION_1_0;

    uint32_t glfwExtensionCount = 0;
    const char** glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
    LogGlfwExtensions(glfwExtensionCount, glfwExtensions);

    VkInstanceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;

    createInfo.enabledExtensionCount = glfwExtensionCount;
    createInfo.ppEnabledExtensionNames = glfwExtensions;
    createInfo.enabledLayerCount = 0;

    VkResult result = vkCreateInstance(&createInfo, nullptr, &vkInstance);

    if (result != VK_SUCCESS)
    {
        throw std::runtime_error("failed to create instance!");
    }
}

void MainApplication::LogGlfwExtensions(uint32_t extensionCount, const char** glfwExtensions)
{
    std::vector<VkExtensionProperties> extensions(extensionCount);
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());

    std::cout << "available extensions:\n";

    for (const auto& extension : extensions) 
    {
        std::cout << '\t' << extension.extensionName << '\n';
    }
}
