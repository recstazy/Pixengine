#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

class PhysicalDevicePicker
{
public: 
	bool TryPickDevice(VkPhysicalDevice& deviceResult, const VkInstance& instance);

private:
	int RatePhysicalDevice(const VkPhysicalDevice& device);
};

