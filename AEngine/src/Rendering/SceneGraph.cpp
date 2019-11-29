#include <Core/AEpch.h>
#include "SceneGraph.h"

std::unique_ptr<SceneGraph> SceneGraph::instance(nullptr);

SceneGraph* SceneGraph::GetInstance()
{
	if(!instance) instance = std::make_unique<SceneGraph>();
	return instance.get();
}
