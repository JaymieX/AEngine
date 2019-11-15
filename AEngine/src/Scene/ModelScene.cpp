#include <Core/AEpch.h>
#include "Scene/ModelScene.h"
#include "Graphics/Mesh.h"
#include "Graphics/Shader.h"
#include "Graphics/Camera.h"
#include "Graphics/TextureHandler.h"
#include "Components/Transform.h"
#include "Graphics/Light.h"

bool ModelScene::Initialize()
{
	sceneEntityManagerPtr = std::make_unique<EntityManager>();
	
	modelEntityPtr = sceneEntityManagerPtr->CreateAndAddEntity();
	cameraEntityPtr = sceneEntityManagerPtr->CreateAndAddEntity();
	lightEntityPtr = sceneEntityManagerPtr->CreateAndAddEntity();

	TextureHandler::GetInstance()->CreateTexture("checkerboard", "src/Resources/Textures/CheckerboardTexture.png");

	//Adding Components To Light Object
	lightEntityPtr->AddComponent<Transform>(glm::vec3(10.0f, 10.0f, -5.0f));
	lightEntityPtr->AddComponent<Light>(0.5f, 0.5f, glm::vec3(1.0f, 1.0f, 1.0f));

	//Adding Components To Camera Object
	cameraEntityPtr->AddComponent<Transform>(glm::vec3(0.0f, 0.0f, -5.0f));
	cameraEntityPtr->AddComponent<Camera>(45.0f, glm::vec2(0.2f, 50.0f))->AddLight(lightEntityPtr);
	
	//Adding Components To Cube Object
	modelEntityPtr->AddComponent<Transform>();
	modelEntityPtr->AddComponent<Shader>("cubeTextureShader", "vertTextureCubeShader.glsl", "fragTextureCubeShader.glsl");
	modelEntityPtr->AddComponent<Mesh>();
	modelEntityPtr->AddComponent<MeshRenderer>(cameraEntityPtr, 
											  GL_TRIANGLES, 
											  TextureHandler::GetInstance()->GetTextureId("checkerboard"));
	return true;
}

void ModelScene::Update(const float dt)
{
	sceneEntityManagerPtr->Update();
	sceneEntityManagerPtr->SeekAndDestroy();
}

void ModelScene::Render() const
{
	sceneEntityManagerPtr->Render();
}

void ModelScene::ResizeUpdate() const
{
	sceneEntityManagerPtr->ResizeUpdate();
}

