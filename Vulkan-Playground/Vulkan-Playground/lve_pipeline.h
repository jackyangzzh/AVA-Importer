#pragma once
#include <string>
#include <vector>
using namespace std;

namespace lve {
	class LvePipeline {
	public: 
		LvePipeline(const string& vertFilePath, const string& fragFilePath);

	private:
		static vector<char> readFile(const string& filePath);

		void createGraphicsPipeline(const string& vertFilePath, const string& fragFilePath);
	};
}