#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>
#include <vector>

#include "../Header Files/VulkanRenderer.h";

using namespace std;

GLFWwindow* window;
VulkanRenderer vulkanRenderer;

void initWindow(string wName = "Test Window", const int width = 800, const int height = 600) {
	glfwInit();

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	
	window = glfwCreateWindow(width, height, wName.c_str(), nullptr, nullptr);
}

int main() {
	initWindow("Test Window", 800, 600);

	vulkanRenderer.init(window);

	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}