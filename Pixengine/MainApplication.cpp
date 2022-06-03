#include "MainApplication.h"
#include "VulkanHelper.h"
#include <string>
#include <stdexcept>
#include <vector>
#include <iostream>

void MainApplication::run()
{
	InitWindow();
	InitVulkan();
	MainLoop();
	Cleanup();
}

void MainApplication::InitWindow()
{
	glfwInit();

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr);
}

void MainApplication::InitVulkan()
{
	VulkanHelper helper;
	auto instanceCreateResult = helper.CreateVulkanInstance(&vkInstance);

	if (instanceCreateResult != VK_SUCCESS)
		throw std::runtime_error("Failed to create Vulkan instance!");

	VkPhysicalDevice physicalDevice;
	bool hasCompatableDevice = helper.TryPickPhysicalDevice(physicalDevice, vkInstance);

	if (!hasCompatableDevice)
		throw std::runtime_error("No suitable physical device found!");

	std::string deviceName;
	helper.GetDeviceName(physicalDevice, deviceName);
	std::cout << "Physical device to run: " << deviceName << "\n";

	auto deviceCreateResult = helper.CreateLogicalDevice(physicalDevice, &logicalDevice);

	if (instanceCreateResult != VK_SUCCESS)
		throw std::runtime_error("Failed to create Vulkan Logical Device!");
}

void MainApplication::MainLoop()
{
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
	}
}

void MainApplication::Cleanup()
{
	vkDestroyDevice(logicalDevice, nullptr);
	vkDestroyInstance(vkInstance, nullptr);
	glfwDestroyWindow(window);
	glfwTerminate();
}
