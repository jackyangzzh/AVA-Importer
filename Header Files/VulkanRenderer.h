#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <stdexcept>
#include <vector>

class VulkanRenderer
{
public:
	VulkanRenderer();

	int init(GLFWwindow* newWindow);

	~VulkanRenderer();

private:
	GLFWwindow* window;

	VkInstance instance;

	void createInstance();

};

