#pragma once

class Model
{
public:
	Model();
   ~Model();

   inline void AddMesh(class MeshRenderer* mr) { meshRenderers.push_back(mr); }

   void Render();

private:
	std::vector<class MeshRenderer*> meshRenderers;
};