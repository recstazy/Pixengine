#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include "QueueFamilyIndices.h"

class PhysicalDevicePicker
{
public: 
	bool TryPickDevice(VkPhysicalDevice& deviceResult, const VkInstance& instance);
	QueueFamilyIndices GetQueueFamilyIndices(const VkPhysicalDevice& device);

private:
	int RatePhysicalDevice(const VkPhysicalDevice& device);
};

