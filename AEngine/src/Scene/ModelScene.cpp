#include <Core/AEpch.h>
#include "Scene/ModelScene.h"
#include "Graphics/Camera.h"
#include "Components/Transform.h"
#include "Graphics/Light.h"
#include "Events/MouseEvent.h"
#include "Physics/BoundingBox.h"
#include "Graphics/ShaderHandler.h"
#include "Rendering/SceneGraph.h"
#include "Physics/CollisionHandler.h"

bool ModelScene::Initialize()
{
	sceneEntityManagerPtr = std::make_unique<EntityManager>();
	cameraEntityPtr = sceneEntityManagerPtr->CreateAndAddEntity();
	lightEntityPtr = sceneEntityManagerPtr->CreateAndAddEntity();

	//Adding Components To Light Object
	lightEntityPtr->AddComponent<Transform>(glm::vec3(10.0f, 10.0f, -5.0f));
	lightEntityPtr->AddComponent<Light>(0.5f, 0.5f, glm::vec3(1.0f, 1.0f, 1.0f));

	//Adding Components To Camera Object
	cameraEntityPtr->AddComponent<Transform>(glm::vec3(0.0f));
	cameraEntityPtr->AddComponent<Camera>(45.0f, glm::vec2(0.2f, 50.0f), false)->AddLight(lightEntityPtr);

	//Models
	const ModelData appleModelData { cameraEntityPtr, ShaderHandler::GetInstance()->GetShaderProgram("TextureShader"), "src/Resources/Models/Apple.obj", "src/Resources/Models/Apple.mtl" };
	const auto appleModelPtr = new Model(appleModelData);
	const ModelData diceModelData { cameraEntityPtr, ShaderHandler::GetInstance()->GetShaderProgram("TextureShader"), "src/Resources/Models/Dice.obj", "src/Resources/Models/Dice.mtl" };
	const auto diceModelPtr = new Model(diceModelData);
	
	//Creating Collision Handle
	CollisionHandler::GetInstance()->CreateHandler(cameraEntityPtr->GetComponent<Camera>());

	//Adding Models & GameObjects to SceneGraph
	SceneGraph::GetInstance()->AddModel(appleModelPtr);
	SceneGraph::GetInstance()->AddModel(diceModelPtr);
	SceneGraph::GetInstance()->AddGameObject(new GameObject(sceneEntityManagerPtr.get(), TransformData{glm::vec3(2.0f, 0.0f, 2.0f)}, appleModelPtr), "Apple");
	SceneGraph::GetInstance()->AddGameObject(new GameObject(sceneEntityManagerPtr.get(), TransformData{glm::vec3(-2.0f, 0.0f, 2.0f)}, diceModelPtr), "Dice");

	//Subscribing to Mouse Released Event
	MouseEventDispatcher::GetDispatcher()->mouseButtonReleasedEvent.Subscribe<ModelScene>(this, &ModelScene::HandleMouseReleasedEvent);
	
	return true;
}

void ModelScene::Destroy() const
{
	cameraEntityPtr->Destroy();
	lightEntityPtr->Destroy();
	SceneGraph::GetInstance()->Destroy();
	sceneEntityManagerPtr->SeekAndDestroy();
}

void ModelScene::Update(const float dt)
{
	SceneGraph::GetInstance()->Update(dt);
	
	cameraEntityPtr->Update(dt);
	
	MouseEventDispatcher::GetDispatcher()->MousePollUpdate(dt);
	auto cameraTransform = cameraEntityPtr->GetComponent<Transform>();
	cameraTransform->position = glm::vec3(0,0, MouseEventListener::scrollPosition);

	static auto cameraXPos = 0.0f;
	static auto cameraYPos = 0.0f;
	
	cameraXPos += MouseEventListener::offsetMousePosition.x * 0.001f;
	cameraYPos += MouseEventListener::offsetMousePosition.y * 0.001f;

	//std::cout << "Camera Position: " << glm::to_string(cameraTransform->position) << std::endl;
	//std::cout << "Camera Rotation: [" << cameraXPos << ", " << cameraYPos << "]" << std::endl;

	cameraTransform->position.y = -2.0f;
	cameraTransform->rotation = glm::quat(glm::vec3(cameraYPos, cameraXPos, 0));
}

void ModelScene::Render() const
{
	SceneGraph::GetInstance()->Render();
}

void ModelScene::ResizeUpdate() const
{
	sceneEntityManagerPtr->ResizeUpdate();
}

void ModelScene::HandleMouseReleasedEvent(const int button)
{
	CollisionHandler::GetInstance()->Update(MouseEventListener::mousePosition, button);
}

