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

VkResult VulkanHelper::CreateLogicalDevice(const VkPhysicalDevice& physicalDevice, VkDevice* deviceInstance)
{
    PhysicalDevicePicker physicalDevicePicker;
    auto queueFamilyIndices = physicalDevicePicker.GetQueueFamilyIndices(physicalDevice);
    float queuePriority = 1.0f;

    VkDeviceQueueCreateInfo queueCreateInfo{};
    queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    queueCreateInfo.queueFamilyIndex = queueFamilyIndices.GraphicsFamily.value();
    queueCreateInfo.queueCount = 1;
    queueCreateInfo.pQueuePriorities = &queuePriority;

    VkPhysicalDeviceFeatures deviceFeatures{};
    VkDeviceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    createInfo.pQueueCreateInfos = &queueCreateInfo;
    createInfo.queueCreateInfoCount = 1;
    createInfo.pEnabledFeatures = &deviceFeatures;
    createInfo.enabledExtensionCount = 0;

    ValidationLayers validationLayers;
    validationLayers.ApplyLayers(createInfo);

    return vkCreateDevice(physicalDevice, &createInfo, nullptr, deviceInstance);
}

bool VulkanHelper::TryPickPhysicalDevice(VkPhysicalDevice& device, const VkInstance& instance)
{
    PhysicalDevicePicker picker;
    return picker.TryPickDevice(device, instance);
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

    std::cout << "available extensions:\n";

    for (const auto& extension : extensions)
    {
        std::cout << '\t' << extension.extensionName << '\n';
    }
}
