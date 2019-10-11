#include <AEpch.h>
#include "Mesh.h"
#include "Model.h"

Model::Model() : meshes(std::vector<Mesh*>()) { }

Model::~Model()
{
	for (auto mesh : meshes)
		delete mesh;
	meshes.clear();
}

void Model::Render()
{
	for (auto mesh : meshes)
		if (mesh) mesh->Render();
}