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
	const PhysicalDevicePicker* picker;

public:
	DeviceInfo(const VkInstance& vkInstance, const PhysicalDevicePicker& devicePicker);
	void Dispose();
	QueueFamilyIndices GetQueueFamilyindices();
	VkPhysicalDevice GetPhysicalDevice();
	VkDevice GetlogicalDevice();
	void GetGraphicsQueue(VkQueue& queue);
	void GetPresentationQueue(VkQueue& queue);

private:
	bool CreateLogicalDevice(const VkInstance& vkInstance);
};

