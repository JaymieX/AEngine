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
	MouseEventListener::scrollPosition = DISTANCE_TO_MODEL;
	
	sceneEntityManagerPtr = std::make_unique<EntityManager>();
	
	modelEntityPtr = sceneEntityManagerPtr->CreateAndAddEntity();
	cameraEntityPtr = sceneEntityManagerPtr->CreateAndAddEntity();
	lightEntityPtr = sceneEntityManagerPtr->CreateAndAddEntity();

	//Adding Components To Light Object
	lightEntityPtr->AddComponent<Transform>(glm::vec3(10.0f, 10.0f, -5.0f));
	lightEntityPtr->AddComponent<Light>(0.5f, 0.5f, glm::vec3(1.0f, 1.0f, 1.0f));

	//Adding Components To Camera Object
	cameraEntityPtr->AddComponent<Transform>(glm::vec3(0.0f, 100.0f, DISTANCE_TO_MODEL));
	cameraEntityPtr->AddComponent<Camera>(45.0f, glm::vec2(0.2f, 50.0f), false)->AddLight(lightEntityPtr);
	
	//Adding Model Component;
	ModelData model = {"cubeTextureShader", "vertTextureCubeShader.glsl", "fragTextureCubeShader.glsl"};
	model.objPath = std::string("src/Resources/Models/Apple.obj");
	model.cameraEntity = cameraEntityPtr;
	modelEntityPtr->AddComponent<Model>(model);
	
	return true;
}

void ModelScene::Update(const float dt)
{
	MouseEventDispatcher::GetDispatcher()->MousePollUpdate(dt);
	
	sceneEntityManagerPtr->Update();
	sceneEntityManagerPtr->SeekAndDestroy();

	auto cameraTransform = cameraEntityPtr->GetComponent<Transform>();
	cameraTransform->position = glm::vec3(0,0, MouseEventListener::scrollPosition);

	static auto cameraXPos = 0.0f;
	static auto cameraYPos = 0.0f;
	cameraXPos += MouseEventListener::offsetMousePosition.x * 0.001f;
	cameraYPos += MouseEventListener::offsetMousePosition.y * 0.001f;

	std::cout << "Camera Rotation: [" << cameraXPos << ", " << cameraYPos << "]" << std::endl;

	cameraTransform->position.y = -2.0f;
	cameraTransform->rotation = glm::quat(glm::vec3(cameraYPos, cameraXPos, 0));

	static auto angle = 0.0f;
	modelEntityPtr->GetComponent<Transform>()->position.z = -10.0f;
	modelEntityPtr->GetComponent<Transform>()->rotation = glm::quat(glm::vec3(0.0f, glm::radians(++angle), 0.0f));
	//modelEntityPtr->GetComponent<Transform>()->scale += glm::vec3(0.001f, -0.001f, 0.001f); 
	//modelEntityPtr->GetComponent<BoundingBox>()->PrintT();
}

void ModelScene::Render() const
{
	sceneEntityManagerPtr->Render();
}

void ModelScene::ResizeUpdate() const
{
	sceneEntityManagerPtr->ResizeUpdate();
}

