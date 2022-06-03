#pragma once
#include <vector>
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

class ValidationLayers
{
public:
	const std::vector<const char*> VALIDATION_LAYERS = 
	{
		"VK_LAYER_KHRONOS_validation"
	};

public:
	bool IsGlobalValidationEnabled();
	bool IsAllLayersSupported();
	void ApplyLayers(VkInstanceCreateInfo& createInfo);
	void ApplyLayers(VkDeviceCreateInfo& createInfo);

private:
	uint32_t CheckValidationEnabledAndGetLayersCount();
};

