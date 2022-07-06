#include "lve_pipeline.h"
#include <fstream>
#include <stdexcept>
#include <iostream>

using namespace std;

namespace lve {
	LvePipeline::LvePipeline(LveDevice& device, const string& vertFilePath, const string& fragFilePath, const PipelineConfigInfo& configInfo) : lveDevice{ device }
	{
		createGraphicsPipeline(vertFilePath, fragFilePath, configInfo);
	}

	PipelineConfigInfo LvePipeline::defaultPipelineConfigInfo(uint32_t width, uint32_t height)
	{
		PipelineConfigInfo configInfo{};
		return configInfo;
	}

	vector<char> LvePipeline::readFile(const string& filePath) {
		ifstream file{ filePath, ios::ate | ios::binary };

		if (!file.is_open()) {
			throw runtime_error("Failed to open file" + filePath);
		}

		size_t fileSize = static_cast<size_t>(file.tellg());
		vector<char> buffer(fileSize);

		file.seekg(0);
		file.read(buffer.data(), fileSize);
		file.close();
		return buffer;
	}

	void LvePipeline::createGraphicsPipeline(const string& vertFilePath, const string& fragFilePath, const PipelineConfigInfo& configInfo) {
		auto vertCode = readFile(vertFilePath);
		auto fragCode = readFile(fragFilePath);

		cout << "Vertex Shader size: " << vertCode.size() << "\n";
		cout << "Fragment Shader size: " << fragCode.size() << "\n";
	}
	void LvePipeline::createShaderModule(const vector<char>& code, VkShaderModule* shaderModule)
	{
		VkShaderModuleCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
		createInfo.codeSize = code.size();
		createInfo.pCode = reinterpret_cast<const uint32_t*> (code.data());

		if (vkCreateShaderModule(lveDevice.device(), &createInfo, nullptr, shaderModule) != VK_SUCCESS) {
			throw runtime_error("failed to create shader module");
		}
	}
}