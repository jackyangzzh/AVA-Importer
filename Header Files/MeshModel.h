#pragma once

#include <vector>
#include <glm/glm.hpp>

#include "Mesh.h"

using namespace std;

class MeshModel
{
public:
	MeshModel();
	MeshModel(vector<Mesh> newMeshList);

	size_t getMeshCount();
	Mesh* getMesh(size_t index);

	glm::mat4 getModel();
	void setModel(glm::mat4 newModel);

	void destroyMeshModel();

	~MeshModel();

private:
	vector<Mesh> meshList;
	glm::mat4 model;
};

