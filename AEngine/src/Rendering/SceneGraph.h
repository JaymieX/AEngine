#pragma once

class SceneGraph
{
public:
	SceneGraph() = default;
	SceneGraph(const SceneGraph&) = delete;
	SceneGraph(SceneGraph&&) = delete;
	SceneGraph& operator=(const SceneGraph&) = delete;
	SceneGraph& operator=(SceneGraph) = delete;

	static SceneGraph* GetInstance();
private:
	static std::unique_ptr<SceneGraph> instance;
};