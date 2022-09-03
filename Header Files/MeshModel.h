#pragma once

#include <vector>

#include <glm/glm.hpp>
#include <assimp/scene.h>

#include "Mesh.h"

using namespace std;

class MeshModel
{
public:
	MeshModel(vector<Mesh> newMeshList);

	size_t getMeshCount();
	Mesh* getMesh(size_t index);

	glm::mat4 getModel();
	void setModel(glm::mat4 newModel);

	void destroyMeshModel();

	static vector<string> LoadMaterials(const aiScene* scene);
	static vector<Mesh> LoadNode(VkPhysicalDevice newPhysicalDevice, VkDevice newDevice, VkQueue transferQueue, VkCommandPool transferCommandPool, aiNode* node, const aiScene* scene, vector<int> matToTex);
	static Mesh LoadMesh(VkPhysicalDevice newPhysicalDevice, VkDevice newDevice, VkQueue transferQueue, VkCommandPool transferCommandPool, aiMesh* mesh, const aiScene* scene, vector<int> matToTex);

private:
	vector<Mesh> meshList;
	glm::mat4 model;
};

