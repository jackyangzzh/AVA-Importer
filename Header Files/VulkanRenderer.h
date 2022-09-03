#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <stdexcept>
#include <vector>
#include <set>
#include <algorithm>
#include <array>

#include "Mesh.h"
#include "MeshModel.h"
#include "Utilities.h"
#include "VulkanValidation.h"
#include "stb_image.h"

using namespace std;

class VulkanRenderer
{
public:
	VulkanRenderer();

	int init(GLFWwindow* newWindow);
	void updateModel(int modelId, glm::mat4 newModel);
	void draw();
	void cleanup();

	int createMeshModel(string modelFile);

	~VulkanRenderer();

private:
	GLFWwindow* window;

	int currentFrame = 0;

	// Scene objects
	vector<MeshModel> modelList;

	struct UboViewProjection {
		glm::mat4 projection;
		glm::mat4 view;
	} uboViewProjection;

	VkInstance instance;
	VkDebugReportCallbackEXT callback;
	struct {
		VkPhysicalDevice physicalDevice;
		VkDevice logicalDevice;
	} mainDevice;
	VkQueue graphicsQueue;
	VkQueue presentationQueue;
	VkSurfaceKHR surface;
	VkSwapchainKHR swapchain;

	vector<SwapchainImage> swapChainImages;
	vector<VkFramebuffer> swapChainFramebuffers;
	vector<VkCommandBuffer> commandBuffers;

	VkImage depthBufferImage;
	VkDeviceMemory depthBufferImageMemory;
	VkImageView depthBufferImageView;

	VkSampler textureSampler;

	VkPushConstantRange pushConstantRange;
	VkDescriptorSetLayout descriptorSetLayout;
	VkDescriptorSetLayout samplerSetLayout;
	VkDescriptorPool descriptorPool;
	VkDescriptorPool samplerDescriptorPool;
	vector<VkDescriptorSet> descriptorSets;
	vector<VkDescriptorSet> samplerDescriptorSets;

	vector<VkBuffer> vpUniformBuffer;
	vector<VkDeviceMemory> vpUniformBufferMemory;
	vector<VkBuffer> modelUniformBuffer;
	vector<VkDeviceMemory> modelUniformBufferMemory;

	vector<VkImage> textureImages;
	vector<VkDeviceMemory> textureImageMemory;
	vector<VkImageView> textureImageViews;

	VkPipeline graphicsPipeline;
	VkPipelineLayout pipelineLayout;
	VkRenderPass renderPass;

	VkCommandPool graphicsCommandPool;

	VkFormat swapChainImageFormat;
	VkExtent2D swapChainExtent;

	vector<VkSemaphore> imageAvailable;
	vector<VkSemaphore> renderFinished;
	vector<VkFence> drawFences;

	void createInstance();
	void createDebugCallback();
	void createLogicalDevice();
	void createSurface();
	void createSwapChain();
	void createRenderPass();
	void createDescriptorSetLayout();
	void createPushConstantRange();
	void createGraphicsPipeline();
	void createDepthBufferImage();
	void createFramebuffers();
	void createCommandPool();
	void createCommandBuffers();
	void createSynchronization();
	void createTextureSampler();
	void createUniformBuffers();
	void createDescriptorPool();
	void createDescriptorSets();

	void updateUniformBuffers(uint32_t imageIndex);

	void recordCommands(uint32_t currentImage);

	void getPhysicalDevice();

	bool checkInstanceExtensionSupport(vector<const char*>* checkExtensions);
	bool checkDeviceExtensionSupport(VkPhysicalDevice device);
	bool checkValidationLayerSupport();
	bool checkDeviceSuitable(VkPhysicalDevice device);

	QueueFamilyIndices getQueueFamilies(VkPhysicalDevice device);
	SwapChainDetails getSwapChainDetails(VkPhysicalDevice device);

	VkSurfaceFormatKHR chooseBestSurfaceFormat(const vector<VkSurfaceFormatKHR>& formats);
	VkPresentModeKHR chooseBestPresentationMode(const vector<VkPresentModeKHR> presentationModes);
	VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& surfaceCapabilities);
	VkFormat chooseSupportedFormat(const vector<VkFormat>& formats, VkImageTiling tiling, VkFormatFeatureFlags featureFlags);

	VkImage createImage(uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling, VkImageUsageFlags useFlags, VkMemoryPropertyFlags proFlags, VkDeviceMemory* imageMemory);
	VkImageView createImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags);
	VkShaderModule createShaderModule(const vector<char>& code);

	int createTextureImage(string fileName);
	int createTexture(string fileName);
	int createTextureDescriptor(VkImageView textureImage);

	stbi_uc* loadTextureFile(string fileName, int* width, int* height, VkDeviceSize* imageSize);
};

