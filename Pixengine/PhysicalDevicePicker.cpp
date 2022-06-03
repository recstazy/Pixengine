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
	int score = 1;

	if (deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
		score += 1000;

	return score;
}
