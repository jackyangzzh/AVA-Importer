#define GLFW_INCLUDE_VULKAN
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#define STB_IMAGE_IMPLEMENTATION

#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>
#include <vector>

#include "../Header Files/VulkanRenderer.h";

using namespace std;

GLFWwindow* window;
VulkanRenderer vulkanRenderer;

void initWindow(string wName = "Test Window", const int width = 1500, const int height = 1000) {
	glfwInit();

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	window = glfwCreateWindow(width, height, wName.c_str(), nullptr, nullptr);
}

int main() {
	initWindow("Test Window", 800, 600);

	if (vulkanRenderer.init(window) == EXIT_FAILURE) {
		return EXIT_FAILURE;
	}

	float angle = 0.0f;
	float deltaTime = 0.0f;
	float lastTime = 0.0f;

	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();

		float now = glfwGetTime();
		deltaTime = now - lastTime;
		lastTime = now;

		angle += 10.0f * deltaTime;
		if (angle > 360.0f) {
			angle -= 360.0f;
		}

		glm::mat4 firstModel(1.0f);
		glm::mat4 secondModel(1.0f);
	
		firstModel = glm::translate(firstModel, glm::vec3(-1.0f, 0.0f, -1.0f));
		firstModel = glm::rotate(firstModel, glm::radians(angle), glm::vec3(0.0f, 0.0f, 1.0f));
		secondModel = glm::translate(secondModel, glm::vec3(1.0f, 0.0f, -3.0f));
		secondModel = glm::rotate(secondModel, glm::radians(-angle * 20), glm::vec3(0.0f, 0.0f, 1.0f));

		vulkanRenderer.updateModel(0, firstModel);
		vulkanRenderer.updateModel(1, secondModel);
		vulkanRenderer.draw();
	}

	vulkanRenderer.cleanup();

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}