#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <stdexcept>
#include <vector>
#include <set>

#include "Utilities.h"
#include "VulkanValidation.h"

using namespace std;

class VulkanRenderer
{
public:
	VulkanRenderer();

	int init(GLFWwindow* newWindow);
	void cleanup();

	~VulkanRenderer();

private:
	GLFWwindow* window;

	VkInstance instance;
	VkDebugReportCallbackEXT callback;
	struct {
		VkPhysicalDevice physicalDevice;
		VkDevice logicalDevice;
	} mainDevice;
	VkQueue graphicsQueue;
	VkQueue presentationQueue;
	VkSurfaceKHR surface;

	void createInstance();
	void createDebugCallback();
	void createLogicalDevice();
	void createSurface();
	void createSwapChain();

	void getPhysicalDevice();

	bool checkInstanceExtensionSupport(vector<const char*>* checkExtensions);
	bool checkDeviceExtensionSupport(VkPhysicalDevice device);
	bool checkValidationLayerSupport();
	bool checkDeviceSuitable(VkPhysicalDevice device);

	QueueFamilyIndices getQueueFamilies(VkPhysicalDevice device);
	SwapChainDetails getSwapChainDetails(VkPhysicalDevice device);

	VkSurfaceFormatKHR chooseBestSurfaceFormat(const vector<VkSurfaceFormatKHR>& formats);
};

