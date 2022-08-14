#pragma once

#include <fstream>

using namespace std;

const int MAX_FRAME_DRAWS = 2;

const vector<const char*> deviceExtensions = {
	VK_KHR_SWAPCHAIN_EXTENSION_NAME
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