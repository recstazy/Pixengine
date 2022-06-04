#include <stdexcept>
#include "DeviceInfo.h"
#include "ValidationLayers.h"

void DeviceInfo::Setup(const VkInstance& vkInstance, PhysicalDevicePicker& const picker)
{
    physicalDevice = VK_NULL_HANDLE;
    logicalDevice = VK_NULL_HANDLE;

    this->picker = picker;
    bool isDevicePicked = picker.TryPickDevice(physicalDevice, vkInstance);

    if (!isDevicePicked)
        throw std::runtime_error("Device info couldn't be created because Device Picker couldn't pick a Physical Device");

    queueFamilyIndices = picker.GetQueueFamilyIndices(physicalDevice);
    bool isCreatedLogicalDevice = CreateLogicalDevice(vkInstance);

    if (!isCreatedLogicalDevice)
        throw std::runtime_error("Failed to create Vulkan Logical Device!");
}

void DeviceInfo::Dispose()
{
    if (logicalDevice != VK_NULL_HANDLE)
        vkDestroyDevice(logicalDevice, nullptr);
}

bool DeviceInfo::CreateLogicalDevice(const VkInstance& vkInstance)
{
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

    auto result = vkCreateDevice(physicalDevice, &createInfo, nullptr, &logicalDevice);
    return result == VK_SUCCESS;
}

QueueFamilyIndices DeviceInfo::GetQueueFamilyindices()
{
    return queueFamilyIndices;
}

VkPhysicalDevice DeviceInfo::GetPhysicalDevice()
{
    return physicalDevice;
}

VkDevice DeviceInfo::GetlogicalDevice()
{
    return logicalDevice;
}

void DeviceInfo::GetGraphicsQueue(VkQueue& queue)
{
    vkGetDeviceQueue(logicalDevice, queueFamilyIndices.GraphicsFamily.value(), 0, &queue);
}
