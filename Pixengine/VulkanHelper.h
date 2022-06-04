#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <string>

class VulkanHelper
{
public: 
	VkResult CreateVulkanInstance(VkInstance* instance);
	void GetDeviceName(const VkPhysicalDevice& device, std::string& name);

private:
	void LogGlfwExtensions(uint32_t extensionCount, const char** glfwExtensions);
};

