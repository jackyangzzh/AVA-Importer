#pragma once 

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <iostream>

using namespace std;

namespace lve {
	class LveWindow {
	public:
		LveWindow(int w, int h, string name);
		~LveWindow();

		LveWindow(const LveWindow&) = delete;
		LveWindow& operator= (const LveWindow&) = delete;

		bool shouldClose() { return glfwWindowShouldClose(window); }

	private:
		void initWindow();

		const int width;
		const int height;

		string windowName;
		GLFWwindow* window;
	};
}