#include "ValidationLayers.h"
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <cstring>
#include <iostream>

bool ValidationLayers::IsGlobalValidationEnabled()
{
#ifdef NDEBUG
    return false;
#else
    return true;;
#endif
}

bool ValidationLayers::IsAllLayersSupported()
{
    uint32_t layerCount;
    vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

    std::vector<VkLayerProperties> availableLayers(layerCount);
    vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

    for (const char* layerName : VALIDATION_LAYERS) 
    {
        bool layerFound = false;

        for (const auto& layerProperties : availableLayers) 
        {
            if (strcmp(layerName, layerProperties.layerName) == 0) 
            {
                layerFound = true;
                break;
            }
        }

        if (!layerFound)
            return false;
    }

    return true;
}

void ValidationLayers::ApplyLayers(VkInstanceCreateInfo& createInfo)
{
    std::cout << "Applying validation to VkInstance..." << "\n";

    auto layersCount = CheckValidationEnabledAndGetLayersCount();
    createInfo.enabledLayerCount = layersCount;

    if (layersCount > 0)
        createInfo.ppEnabledLayerNames = VALIDATION_LAYERS.data();
}

void ValidationLayers::ApplyLayers(VkDeviceCreateInfo& createInfo)
{
    std::cout << "Applying validation to VkLogicalDevice..." << "\n";

    auto layersCount = CheckValidationEnabledAndGetLayersCount();
    createInfo.enabledLayerCount = layersCount;

    if (layersCount > 0)
        createInfo.ppEnabledLayerNames = VALIDATION_LAYERS.data();
}

uint32_t ValidationLayers::CheckValidationEnabledAndGetLayersCount()
{
    bool isValidationEnabled = IsGlobalValidationEnabled();
    std::cout << "Validation is globally " << (isValidationEnabled ? "ENABLED" : "DISABLED") << "\n";

    if (!isValidationEnabled)
        return 0;

    if (!IsAllLayersSupported())
    {
        std::cout << "Not all the validation layers are supported, validation is DISABLED" << "\n";
        return 0;
    }

    return static_cast<uint32_t>(VALIDATION_LAYERS.size());
}

