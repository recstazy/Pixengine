#include "PhysicalDevicePicker.h"
#include <vector>
#include <map>

bool PhysicalDevicePicker::TryPickDevice(VkPhysicalDevice& deviceResult, const VkInstance& instance)
{
	deviceResult = VK_NULL_HANDLE;
	uint32_t deviceCount = 0;
	vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);

	if (deviceCount == 0)
		return false;

	std::vector<VkPhysicalDevice> devices(deviceCount);
	vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());

	std::multimap<int, VkPhysicalDevice> devicesRated;

	for (const auto& device : devices)
	{
		int deviceRating = RatePhysicalDevice(device);
		devicesRated.insert(std::make_pair(deviceRating, device));
	}

	auto bestRatedDevice = devicesRated.crbegin();

	if (bestRatedDevice->first > 0)
	{
		deviceResult = bestRatedDevice->second;
		return true;
	}

	return false;
}

int PhysicalDevicePicker::RatePhysicalDevice(const VkPhysicalDevice& device)
{
	VkPhysicalDeviceProperties deviceProperties;
	VkPhysicalDeviceFeatures deviceFeatures;
	vkGetPhysicalDeviceProperties(device, &deviceProperties);
	vkGetPhysicalDeviceFeatures(device, &deviceFeatures);
	auto queueFamilyIndices = GetQueueFamilyIndices(device);

	if (!queueFamilyIndices.IsAllFamiliesPresent())
		return 0;

	int score = 1;

	if (deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
		score += 1000;

	return score;
}

QueueFamilyIndices PhysicalDevicePicker::GetQueueFamilyIndices(const VkPhysicalDevice& device)
{
	QueueFamilyIndices indices;
	uint32_t queueFamilyCount = 0;
	vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

	std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
	vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

	int i = 0;
	for (const auto& queueFamily : queueFamilies) 
	{
		if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) 
			indices.GraphicsFamily = i;

		i++;
	}

	return indices;
}
