#pragma once
#include <string>
#include <vector>
#include "lve_device.h"

using namespace std;

namespace lve {
	struct PipelineConfigInfo {};

	class LvePipeline {
	public:
		LvePipeline(LveDevice& device, const string& vertFilePath, const string& fragFilePath, const PipelineConfigInfo& configInfo);
		~LvePipeline() {}

		LvePipeline(const LvePipeline&) = delete;
		void operator=(const LvePipeline&) = delete;

		static PipelineConfigInfo defaultPipelineConfigInfo(uint32_t width, uint32_t height);

	private:
		static vector<char> readFile(const string& filePath);

		void createGraphicsPipeline(const string& vertFilePath, const string& fragFilePath, const PipelineConfigInfo& configInfo);

		void createShaderModule(const vector<char>& code, VkShaderModule* shaderModule);

		LveDevice& lveDevice;
		VkPipeline graphicsPipeline;
		VkShaderModule vertShaderModule;
		VkShaderModule fragShaderModule;
	};
}