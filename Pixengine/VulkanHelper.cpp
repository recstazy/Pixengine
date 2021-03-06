#include "VulkanHelper.h"
#include "PhysicalDevicePicker.h"
#include "ValidationLayers.h"
#include <stdexcept>
#include <vector>
#include <iostream>

VkResult VulkanHelper::CreateVulkanInstance(VkInstance* instance)
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
    
    ValidationLayers validationLayers;
    validationLayers.ApplyLayers(createInfo);
    return vkCreateInstance(&createInfo, nullptr, instance);
}

void VulkanHelper::GetDeviceName(const VkPhysicalDevice& device, std::string& name)
{
    VkPhysicalDeviceProperties deviceProperties;
    vkGetPhysicalDeviceProperties(device, &deviceProperties);
    name = deviceProperties.deviceName;
}

void VulkanHelper::LogGlfwExtensions(uint32_t extensionCount, const char** glfwExtensions)
{
    std::vector<VkExtensionProperties> extensions(extensionCount);
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());

    std::cout << "GLFW Requried extensions:\n";

    for (const auto& extension : extensions)
    {
        std::cout << '\t' << extension.extensionName << std::endl;
    }
}
