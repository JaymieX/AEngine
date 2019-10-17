#include <Core/AEpch.h>
#include "Mesh.h"
#include "Model.h"

Model::Model() : meshRenderers(std::vector<MeshRenderer*>()) { }

Model::~Model()
{
	meshRenderers.clear();
}

void Model::Render()
{
	for (auto mr : meshRenderers)
		if (mr) mr->Render();
}