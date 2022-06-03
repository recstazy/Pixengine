#include "MainApplication.h"
#include "VulkanHelper.h"
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
	CreateVulkanInstance();
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
	vkDestroyInstance(vkInstance, nullptr);
	glfwDestroyWindow(window);
	glfwTerminate();
	window = nullptr;
}

void MainApplication::CreateVulkanInstance()
{
	VulkanHelper helper;
	VkResult result = helper.CreateVulkanInstance(&vkInstance);

	if (result != VK_SUCCESS)
	{
		throw std::runtime_error("failed to create instance!");
	}
}
