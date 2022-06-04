#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include "QueueFamilyIndices.h"

class PhysicalDevicePicker
{
private:
	const VkInstance* instance;
	const VkSurfaceKHR* surface;

public: 
	PhysicalDevicePicker(const VkInstance& vkInstance, const VkSurfaceKHR& vkSurface);
	bool TryPickDevice(VkPhysicalDevice& deviceResult) const;
	QueueFamilyIndices GetQueueFamilyIndices(const VkPhysicalDevice& device) const;

private:
	int RatePhysicalDevice(const VkPhysicalDevice& device) const;
};

