#include <Core/AEpch.h>
#include "Core/Logger.h"
#include "CubeScene.h"
#include "Systems/EntityComponent.h"
#include "Graphics/Mesh.h"
#include "Graphics/Shader.h"

CubeScene::~CubeScene()
{
	
}


bool CubeScene::Initialize()
{
	sceneEntityManagerPtr = std::make_unique<EntityManager>();
	
	auto cube = sceneEntityManagerPtr->CreateAndAddEntity();

	auto vert = std::vector<Vertex*>{
		new Vertex{vec3(-0.5f, -0.5f, 0.0f)},
		new Vertex{vec3(0.5f, -0.5f, 0.0f)},
		new Vertex{vec3(0.0f, 0.5f, 0.0f)},
	};

	cube->addComponent<Shader>("cubeShader", "vertCubeShader.glsl", "fragCubeShader.glsl");
	cube->addComponent<Mesh>(vert);
	cube->addComponent<MeshRenderer>(GL_TRIANGLES);

	return true;
}

void CubeScene::Update(const float dt)
{
	sceneEntityManagerPtr->Update();
	sceneEntityManagerPtr->SeekAndDestroy();
}

void CubeScene::Render() const
{
	//glPolygonMode(GL_FRONT, GL_POINTS);
	
	sceneEntityManagerPtr->Render();
}

