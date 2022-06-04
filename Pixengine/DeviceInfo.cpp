#include <stdexcept>
#include <set>
#include "DeviceInfo.h"
#include "ValidationLayers.h"

DeviceInfo::DeviceInfo(const VkInstance& vkInstance, const PhysicalDevicePicker& devicePicker)
{
    physicalDevice = VK_NULL_HANDLE;
    logicalDevice = VK_NULL_HANDLE;

    picker = &devicePicker;
    bool isDevicePicked = picker->TryPickDevice(physicalDevice);

    if (!isDevicePicked)
        throw std::runtime_error("Device info couldn't be created because Device Picker couldn't pick a Physical Device");

    queueFamilyIndices = picker->GetQueueFamilyIndices(physicalDevice);
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
    std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
    std::set<uint32_t> uniqueQueueFamilies;
    queueFamilyIndices.IndicesToSet(uniqueQueueFamilies);
    
    float queuePriority = 1.0f;

    for (uint32_t queueFamily : uniqueQueueFamilies) 
    {
        VkDeviceQueueCreateInfo queueCreateInfo{};
        queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        queueCreateInfo.queueFamilyIndex = queueFamily;
        queueCreateInfo.queueCount = 1;
        queueCreateInfo.pQueuePriorities = &queuePriority;
        queueCreateInfos.push_back(queueCreateInfo);
    }

    VkPhysicalDeviceFeatures deviceFeatures{};
    VkDeviceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    createInfo.pQueueCreateInfos = queueCreateInfos.data();
    createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
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

void DeviceInfo::GetPresentationQueue(VkQueue& queue)
{
    vkGetDeviceQueue(logicalDevice, queueFamilyIndices.PresentationFamily.value(), 0, &queue);
}
