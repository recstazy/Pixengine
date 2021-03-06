#include "MainApplication.h"
#include "VulkanHelper.h"
#include <string>
#include <stdexcept>
#include <vector>
#include <iostream>
#include "PhysicalDevicePicker.h"

void MainApplication::Run()
{
	InitWindow();
	InitVulkan();
	CheckMemberVariables();
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

	auto surfacereateResult = glfwCreateWindowSurface(vkInstance, window, nullptr, &mainSurface);
	if (surfacereateResult != VK_SUCCESS)
		throw std::runtime_error("Failed to create Vulkan surface!");

	PhysicalDevicePicker mainDevicePicker = PhysicalDevicePicker(vkInstance, mainSurface);
	mainDevice = new DeviceInfo(vkInstance, mainDevicePicker);

	std::string deviceName;
	helper.GetDeviceName(mainDevice->GetPhysicalDevice(), deviceName);
	std::cout << "Main Physical Device: " << deviceName << std::endl;
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
	if (mainDevice != nullptr)
		mainDevice->Dispose();

	vkDestroySurfaceKHR(vkInstance, mainSurface, nullptr);
	vkDestroyInstance(vkInstance, nullptr);
	glfwDestroyWindow(window);
	glfwTerminate();
}

void MainApplication::CheckMemberVariables()
{
	const char* isMainDeviceValid = &mainDevice != nullptr ? "true" : "false";
	std::cout << "Main Device is valid: " << isMainDeviceValid << std::endl;
}
