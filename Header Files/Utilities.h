#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <fstream>
#include <glm/glm.hpp>

using namespace std;

const int MAX_FRAME_DRAWS = 2;

const vector<const char*> deviceExtensions = {
	VK_KHR_SWAPCHAIN_EXTENSION_NAME
};

struct Vertex {
	glm::vec3 pos;
	glm::vec3 col;
};

struct QueueFamilyIndices {
	int graphicsFamily = -1;
	int presentationFamily = -1;

	bool isValid() {
		return graphicsFamily >= 0 && presentationFamily >= 0;
	}
};

struct SwapChainDetails {
	VkSurfaceCapabilitiesKHR surfaceCapabilities;
	vector<VkSurfaceFormatKHR> formats;
	vector<VkPresentModeKHR> presentationModes;
};

struct SwapchainImage {
	VkImage image;
	VkImageView imageView;
};

static vector<char> readFile(const string &filename) {
	ifstream file(filename, ios::binary | ios::ate);
	if (!file.is_open()) {
		throw runtime_error("Failed to open a file.");
	}

	size_t fileSize = (size_t)file.tellg();
	vector<char> fileBuffer(fileSize);
	file.seekg(0);
	file.read(fileBuffer.data(), fileSize);
	file.close();

	return fileBuffer;
}


static uint32_t findMemoryTypeIndex(VkPhysicalDevice physicalDevice, uint32_t allowedTypes, VkMemoryPropertyFlags properties) {
	VkPhysicalDeviceMemoryProperties memoryProperties;
	vkGetPhysicalDeviceMemoryProperties(physicalDevice, &memoryProperties);

	for (uint32_t i = 0; i < memoryProperties.memoryTypeCount; ++i) {

		if ((allowedTypes & (1 << i)) && (memoryProperties.memoryTypes[i].propertyFlags & properties) == properties) {
			return i;
		}
	}
}


static void createBuffer(VkPhysicalDevice physicalDevice, VkDevice device, VkDeviceSize bufferSize, VkBufferUsageFlags bufferUsage, VkMemoryPropertyFlags bufferProperties, VkBuffer *buffer, VkDeviceMemory *bufferMemory) {
	VkBufferCreateInfo bufferInfo = {};
	bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
	bufferInfo.size = bufferSize;
	bufferInfo.usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
	bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

	VkResult result = vkCreateBuffer(device, &bufferInfo, nullptr, buffer);
	if (result != VK_SUCCESS) {
		throw runtime_error("Failed to create Vertex Buffer");
	}

	VkMemoryRequirements memoryRequirements;
	vkGetBufferMemoryRequirements(device, *buffer, &memoryRequirements);

	VkMemoryAllocateInfo memoryAllocInfo = {};
	memoryAllocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
	memoryAllocInfo.allocationSize = memoryRequirements.size;
	memoryAllocInfo.memoryTypeIndex = findMemoryTypeIndex(physicalDevice, memoryRequirements.memoryTypeBits, bufferProperties);

	result = vkAllocateMemory(device, &memoryAllocInfo, nullptr, bufferMemory);
	if (result != VK_SUCCESS) {
		throw runtime_error("Failed to allocate Vertex Buffer Memory.");
	}
	 
	vkBindBufferMemory(device, *buffer, *bufferMemory, 0);
}

static void copyBuffer(VkDevice device, VkQueue transferQueue, VkCommandPool transferCommandPool, VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize bufferSize) {
	VkCommandBuffer transferCommandBuffer;

	VkCommandBufferAllocateInfo allocInfo = {};
	allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	allocInfo.commandPool = transferCommandPool;
	allocInfo.commandBufferCount = 1;

	vkAllocateCommandBuffers(device, &allocInfo, &transferCommandBuffer);

	VkCommandBufferBeginInfo beginInfo = {};
	beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
	beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

	vkBeginCommandBuffer(transferCommandBuffer, &beginInfo);

	VkBufferCopy bufferCopyRegion = {};
	bufferCopyRegion.srcOffset = 0;
	bufferCopyRegion.dstOffset = 0;
	bufferCopyRegion.size = bufferSize;

	vkCmdCopyBuffer(transferCommandBuffer, srcBuffer, dstBuffer, 1, &bufferCopyRegion);
	vkEndCommandBuffer(transferCommandBuffer);

	VkSubmitInfo submitInfo = {};
	submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
	submitInfo.commandBufferCount = 1;
	submitInfo.pCommandBuffers = &transferCommandBuffer;

	vkQueueSubmit(transferQueue, 1, &submitInfo, VK_NULL_HANDLE);
	vkQueueWaitIdle(transferQueue);

	vkFreeCommandBuffers(device, transferCommandPool, 1, &transferCommandBuffer);

}