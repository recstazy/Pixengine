#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

class VulkanHelper
{
public: 
	VkResult CreateVulkanInstance(VkInstance* instance);

private:
	void LogGlfwExtensions(uint32_t extensionCount, const char** glfwExtensions);

};

