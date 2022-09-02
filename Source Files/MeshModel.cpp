#include "../Header Files/MeshModel.h"

MeshModel::MeshModel(vector<Mesh> newMeshList)
{
	meshList = newMeshList;
	model = glm::mat4(1.0f);
}

size_t MeshModel::getMeshCount()
{
	return meshList.size();
}

Mesh* MeshModel::getMesh(size_t index)
{
	if (index >= meshList.size()) {
		throw runtime_error("Accessing invalid Mesh index");
	}
	return &meshList[index];
}

glm::mat4 MeshModel::getModel()
{
	return model;
}

void MeshModel::setModel(glm::mat4 newModel)
{
	model = newModel;
}

void MeshModel::destroyMeshModel()
{
	for (auto& mesh : meshList) {
		mesh.destroyBuffers();
	}
}

vector<string> MeshModel::LoadMaterials(const aiScene* scene)
{
	vector<string> textureList(scene->mNumMaterials);

	for (size_t i = 0; i < scene->mNumMaterials; ++i) {
		aiMaterial* material = scene->mMaterials[i];
		textureList[i] = "";
		if (material->GetTextureCount(aiTextureType_DIFFUSE)) {
			aiString path;
			if (material->GetTexture(aiTextureType_DIFFUSE, 0, &path) == AI_SUCCESS) {
				int idx = string(path.data).rfind("\\");
				string fileName = string(path.data).substr(idx + 1);
				textureList[i] = fileName;
			}
		}
	}

	return textureList;
}

vector<Mesh> MeshModel::LoadNode(VkPhysicalDevice newPhysicalDevice, VkDevice newDevice, VkQueue transferQueue, VkCommandPool transferCommandPool, aiNode* node, const aiScene* scene, vector<int> matToTex)
{
	vector<Mesh> meshList;

	for (size_t i = 0; i < node->mNumMeshes; ++i) {
		meshList.emplace_back(LoadMesh(newPhysicalDevice, newDevice, transferQueue, transferCommandPool, scene->mMeshes[node->mMeshes[i]], scene, matToTex));
	}

	for (size_t i = 0; i < node->mNumChildren; ++i) {
		vector<Mesh> newList = LoadNode(newPhysicalDevice, newDevice, transferQueue, transferCommandPool, node->mChildren[i], scene, matToTex);
		meshList.insert(meshList.end(), newList.begin(), newList.end());
	}

	return meshList;
}

Mesh MeshModel::LoadMesh(VkPhysicalDevice newPhysicalDevice, VkDevice newDevice, VkQueue transferQueue, VkCommandPool transferCommandPool, aiMesh* mesh, const aiScene* scene, vector<int> matToTex)
{
	vector<Vertex> vertices;
	vector<uint32_t> indices;

	vertices.resize(mesh->mNumVertices);

	for (size_t i = 0; i < mesh->mNumVertices; ++i) {
		vertices[i].pos = { mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z };

		if (mesh->mTextureCoords[0]) {
			vertices[i].tex = { mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y };
		}
		else {
			vertices[i].tex = { 0.0f, 0.0f };
		}

		vertices[i].col = { 1.0f, 1.0f, 1.0f };
	}

	for (size_t i = 0; i < mesh->mNumFaces; ++i) {
		aiFace face = mesh->mFaces[i];
		for (size_t j = 0; j < face.mNumIndices; ++j) {
			indices.emplace_back(face.mIndices[j]);
		}
	}

	Mesh newMesh = Mesh(newPhysicalDevice, newDevice, transferQueue, transferCommandPool, &vertices, &indices, matToTex[mesh->mMaterialIndex]);
	return newMesh;
}
