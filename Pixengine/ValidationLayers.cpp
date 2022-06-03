#include "ValidationLayers.h"
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <cstring>

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

