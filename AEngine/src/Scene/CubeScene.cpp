#include <Core/AEpch.h>
#include "Core/Logger.h"
#include "CubeScene.h"
#include "Systems/EntityComponent.h"
#include "Graphics/Mesh.h"

CubeScene::CubeScene()
{
	
}

CubeScene::~CubeScene()
{

}

bool CubeScene::Initialize()
{
	sceneEntityManagerPtr = std::make_unique<EntityManager>();
	Entity cube = sceneEntityManagerPtr->CreateAndAddEntity();

	return true;
}

void CubeScene::Update(const float dt)
{
	sceneEntityManagerPtr->Update();
	sceneEntityManagerPtr->SeekAndDestroy();
}

void CubeScene::Render() const
{
	sceneEntityManagerPtr->Render();
}

