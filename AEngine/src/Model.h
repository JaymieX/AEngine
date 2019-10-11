#pragma once

class Mesh;

class Model
{
public:
	Model();
   ~Model();

   inline void AddMesh(Mesh* mesh) { meshes.push_back(mesh); }

   void Render();

private:
	std::vector<Mesh*> meshes;
};