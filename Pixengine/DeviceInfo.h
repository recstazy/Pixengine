#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include "QueueFamilyIndices.h"
#include "PhysicalDevicePicker.h"

class DeviceInfo
{
private:
	VkPhysicalDevice physicalDevice;
	VkDevice logicalDevice;
	QueueFamilyIndices queueFamilyIndices;
	PhysicalDevicePicker picker;

public:
	void Setup(const VkInstance& vkInstance, PhysicalDevicePicker& const picker);
	void Dispose();
	QueueFamilyIndices GetQueueFamilyindices();
	VkPhysicalDevice GetPhysicalDevice();
	VkDevice GetlogicalDevice();

private:
	bool CreateLogicalDevice(const VkInstance& vkInstance);
};

