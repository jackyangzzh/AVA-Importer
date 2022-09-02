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

			}
		}

	}

	return vector<string>();
}
