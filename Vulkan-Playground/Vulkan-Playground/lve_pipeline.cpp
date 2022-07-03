#include "lve_pipeline.h"
#include <fstream>
#include <stdexcept>
#include <iostream>

namespace lve {
	LvePipeline::LvePipeline(const string& vertFilePath, const string& fragFilePath)
	{
		createGraphicsPipeline(vertFilePath, fragFilePath);
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

	void LvePipeline::createGraphicsPipeline(const string& vertFilePath, const string& fragFilePath) {
		auto vertCode = readFile(vertFilePath);
		auto fragCode = readFile(fragFilePath);

		cout << "Vertex Shader size: " << vertCode.size() << "\n";
		cout << "Fragment Shader size: " << fragCode.size() << "\n";
	}
}