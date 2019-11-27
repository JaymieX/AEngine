#include <Core/AEpch.h>
#include "Scene/ModelScene.h"
#include "Graphics/Mesh.h"
#include "Graphics/Shader.h"
#include "Graphics/Camera.h"
#include "Components/Transform.h"
#include "Graphics/Light.h"
#include "Events/MouseEvent.h"
#include "Physics/BoundingBox.h"

bool ModelScene::Initialize()
{
	static const float DISTANCE_TO_MODEL = 5.0f;
	
	sceneEntityManagerPtr = std::make_unique<EntityManager>();
	
	modelEntityPtr = sceneEntityManagerPtr->CreateAndAddEntity();
	cameraEntityPtr = sceneEntityManagerPtr->CreateAndAddEntity();
	lightEntityPtr = sceneEntityManagerPtr->CreateAndAddEntity();


	//Adding Components To Light Object
	lightEntityPtr->AddComponent<Transform>(glm::vec3(10.0f, 10.0f, -5.0f));
	lightEntityPtr->AddComponent<Light>(0.5f, 0.5f, glm::vec3(1.0f, 1.0f, 1.0f));

	//Adding Components To Camera Object
	cameraEntityPtr->AddComponent<Transform>(glm::vec3(0.0f, 0.0f, DISTANCE_TO_MODEL));
	cameraEntityPtr->AddComponent<Camera>(45.0f, glm::vec2(0.2f, 50.0f), false)->AddLight(lightEntityPtr);
	
	MouseEventListener::scrollPosition = DISTANCE_TO_MODEL;
	
	//Adding Components To Cube Object
	modelEntityPtr->AddComponent<Transform>(glm::vec3(0.0f, -2.0f, 0.0f));
	modelEntityPtr->AddComponent<Shader>("cubeTextureShader", "vertTextureCubeShader.glsl", "fragTextureCubeShader.glsl");
	modelEntityPtr->AddComponent<MeshFilter>(new Mesh("src/Resources/Models/Apple.obj"));
	modelEntityPtr->AddComponent<MeshRenderer>(cameraEntityPtr, GL_TRIANGLES);
	modelEntityPtr->AddComponent<BoundingBox>();
	return true;
}

void ModelScene::Update(const float dt)
{
	MouseEventDispatcher::GetDispatcher()->MousePollUpdate(dt);
	
	sceneEntityManagerPtr->Update();
	sceneEntityManagerPtr->SeekAndDestroy();

	cameraEntityPtr->GetComponent<Transform>()->position =
		glm::vec3(0,0, MouseEventListener::scrollPosition);

	static auto cameraXPos = 0.0f;
	static auto cameraYPos = 0.0f;
	cameraXPos += MouseEventListener::offsetMousePosition.x * 0.001f;
	cameraYPos += MouseEventListener::offsetMousePosition.y * 0.001f;

	std::cout << "Camera Rotation: [" << cameraXPos << ", " << cameraYPos << "]" << std::endl;
	
	cameraEntityPtr->GetComponent<Transform>()->rotation = glm::quat(glm::vec3(cameraYPos, cameraXPos, 0));

	static auto angle = 0.0f;
	modelEntityPtr->GetComponent<Transform>()->rotation = glm::quat(glm::vec3(0.0f, glm::radians(++angle), 0.0f));
}

void ModelScene::Render() const
{
	sceneEntityManagerPtr->Render();
}

void ModelScene::ResizeUpdate() const
{
	sceneEntityManagerPtr->ResizeUpdate();
}

