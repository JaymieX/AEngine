#include <Core/AEpch.h>
#include "CubeScene.h"
#include "Graphics/Mesh.h"
#include "Graphics/Shader.h"
#include "Graphics/Camera.h"
#include "Graphics/TextureHandler.h"
#include "Components/Transform.h"
#include "Graphics/Light.h"

bool CubeScene::Initialize()
{
	sceneEntityManagerPtr = std::make_unique<EntityManager>();
	
	cubeEntityPtr = sceneEntityManagerPtr->CreateAndAddEntity();
	cameraEntityPtr = sceneEntityManagerPtr->CreateAndAddEntity();
	auto lightEntityPtr = sceneEntityManagerPtr->CreateAndAddEntity();

	TextureHandler::GetInstance()->CreateTexture("checkerboard", "src/Resources/Textures/CheckerboardTexture.png");

	Vertex v{};

	std::vector<Vertex> vertList;

	v.position = glm::vec3(-0.5f, -0.5f, -0.5f);
	v.normal = glm::vec3(0.0f, 0.0f, -1.0f);
	v.uvCoords = glm::vec2(0.0f, 0.0f);
	v.color = glm::vec3(0.583f, 0.771f, 0.014f);
	vertList.push_back(v);

	v.position = glm::vec3(0.5f, -0.5f, -0.5f);
	v.normal = glm::vec3(0.0f, 0.0f, -1.0f);
	v.uvCoords = glm::vec2(1.0f, 0.0f);
	v.color = glm::vec3(0.609f, 0.115f, 0.436f);
	vertList.push_back(v);

	v.position = glm::vec3(0.5f, 0.5f, -0.5f);
	v.normal = glm::vec3(0.0f, 0.0f, -1.0f);
	v.uvCoords = glm::vec2(1.0f, 1.0f);
	v.color = glm::vec3(0.327f, 0.483f, 0.844f);
	vertList.push_back(v);

	v.position = glm::vec3(0.5f, 0.5f, -0.5f);
	v.normal = glm::vec3(0.0f, 0.0f, -1.0f);
	v.uvCoords = glm::vec2(1.0f, 1.0f);
	v.color = glm::vec3(0.822f, 0.569f, 0.201f);
	vertList.push_back(v);

	v.position = glm::vec3(-0.5f, 0.5f, -0.5f);
	v.normal = glm::vec3(0.0f, 0.0f, -1.0f);
	v.uvCoords = glm::vec2(0.0f, 1.0f);
	v.color = glm::vec3(0.435f, 0.602f, 0.223f);
	vertList.push_back(v);

	v.position = glm::vec3(-0.5f, -0.5f, -0.5f);
	v.normal = glm::vec3(0.0f, 0.0f, -1.0f);
	v.uvCoords = glm::vec2(0.0f, 0.0f);
	v.color = glm::vec3(0.310f, 0.747f, 0.185f);
	vertList.push_back(v);

	v.position = glm::vec3(-0.5f, -0.5f, 0.5f);
	v.normal = glm::vec3(0.0f, 0.0f, 1.0f);
	v.uvCoords = glm::vec2(0.0f, 0.0f);
	v.color = glm::vec3(0.597f, 0.770f, 0.761f);
	vertList.push_back(v);

	v.position = glm::vec3(0.5f, -0.5f, 0.5f);
	v.normal = glm::vec3(0.0f, 0.0f, 1.0f);
	v.uvCoords = glm::vec2(1.0f, 0.0f);
	v.color = glm::vec3(0.559f, 0.436f, 0.730f);
	vertList.push_back(v);

	v.position = glm::vec3(0.5f, 0.5f, 0.5f);
	v.normal = glm::vec3(0.0f, 0.0f, 1.0f);
	v.uvCoords = glm::vec2(1.0f, 1.0f);
	v.color = glm::vec3(0.359f, 0.583f, 0.152f);
	vertList.push_back(v);

	v.position = glm::vec3(0.5f, 0.5f, 0.5f);
	v.normal = glm::vec3(0.0f, 0.0f, 1.0f);
	v.uvCoords = glm::vec2(1.0f, 1.0f);
	v.color = glm::vec3(0.483f, 0.596f, 0.789f);
	vertList.push_back(v);

	v.position = glm::vec3(-0.5f, 0.5f, 0.5f);
	v.normal = glm::vec3(0.0f, 0.0f, 1.0f);
	v.uvCoords = glm::vec2(0.0f, 1.0f);
	v.color = glm::vec3(0.559f, 0.861f, 0.639f);
	vertList.push_back(v);

	v.position = glm::vec3(-0.5f, -0.5f, 0.5f);
	v.normal = glm::vec3(0.0f, 0.0f, 1.0f);
	v.uvCoords = glm::vec2(0.0f, 0.0f);
	v.color = glm::vec3(0.195f, 0.548f, 0.859f);
	vertList.push_back(v);

	v.position = glm::vec3(-0.5f, 0.5f, 0.5f);
	v.normal = glm::vec3(-1.0f, 0.0f, 0.0f);
	v.uvCoords = glm::vec2(0.0f, 0.0f);
	v.color = glm::vec3(0.014f, 0.184f, 0.576f);
	vertList.push_back(v);

	v.position = glm::vec3(-0.5f, 0.5f, -0.5f);
	v.normal = glm::vec3(-1.0f, 0.0f, 0.0f);
	v.uvCoords = glm::vec2(1.0f, 0.0f);
	v.color = glm::vec3(0.771f, 0.328f, 0.970f);
	vertList.push_back(v);

	v.position = glm::vec3(-0.5f, -0.5f, -0.5f);
	v.normal = glm::vec3(-1.0f, 0.0f, 0.0f);
	v.uvCoords = glm::vec2(1.0f, 1.0f);
	v.color = glm::vec3(0.406f, 0.615f, 0.116f);
	vertList.push_back(v);

	v.position = glm::vec3(-0.5f, -0.5f, -0.5f);
	v.normal = glm::vec3(-1.0f, 0.0f, 0.0f);
	v.uvCoords = glm::vec2(1.0f, 1.0f);
	v.color = glm::vec3(0.676f, 0.977f, 0.133f);
	vertList.push_back(v);

	v.position = glm::vec3(-0.5f, -0.5f, 0.5f);
	v.normal = glm::vec3(-1.0f, 0.0f, 0.0f);
	v.uvCoords = glm::vec2(0.0f, 1.0f);
	v.color = glm::vec3(0.971f, 0.572f, 0.833f);
	vertList.push_back(v);

	v.position = glm::vec3(-0.5f, 0.5f, 0.5f);
	v.normal = glm::vec3(-1.0f, 0.0f, 0.0f);
	v.uvCoords = glm::vec2(0.0f, 0.0f);
	v.color = glm::vec3(0.140f, 0.616f, 0.489f);
	vertList.push_back(v);

	v.position = glm::vec3(0.5f, 0.5f, 0.5f);
	v.normal = glm::vec3(1.0f, 0.0f, 0.0f);
	v.uvCoords = glm::vec2(0.0f, 0.0f);
	v.color = glm::vec3(0.997f, 0.513f, 0.064f);
	vertList.push_back(v);

	v.position = glm::vec3(0.5f, 0.5f, -0.5f);
	v.normal = glm::vec3(1.0f, 0.0f, 0.0f);
	v.uvCoords = glm::vec2(1.0f, 0.0f);
	v.color = glm::vec3(0.945f, 0.719f, 0.592f);
	vertList.push_back(v);

	v.position = glm::vec3(0.5f, -0.5f, -0.5f);
	v.normal = glm::vec3(1.0f, 0.0f, 0.0f);
	v.uvCoords = glm::vec2(1.0f, 1.0f);
	v.color = glm::vec3(0.543f, 0.021f, 0.978f);
	vertList.push_back(v);

	v.position = glm::vec3(0.5f, -0.5f, -0.5f);
	v.normal = glm::vec3(1.0f, 0.0f, 0.0f);
	v.uvCoords = glm::vec2(1.0f, 1.0f);
	v.color = glm::vec3(0.279f, 0.317f, 0.505f);
	vertList.push_back(v);

	v.position = glm::vec3(0.5f, -0.5f, 0.5f);
	v.normal = glm::vec3(1.0f, 0.0f, 0.0f);
	v.uvCoords = glm::vec2(0.0f, 1.0f);
	v.color = glm::vec3(0.167f, 0.620f, 0.077f);
	vertList.push_back(v);

	v.position = glm::vec3(0.5f, 0.5f, 0.5f);
	v.normal = glm::vec3(1.0f, 0.0f, 0.0f);
	v.uvCoords = glm::vec2(0.0f, 0.0f);
	v.color = glm::vec3(0.347f, 0.857f, 0.137f);
	vertList.push_back(v);

	v.position = glm::vec3(-0.5f, -0.5f, -0.5f);
	v.normal = glm::vec3(0.0f, -1.0f, 0.0f);
	v.uvCoords = glm::vec2(0.0f, 0.0f);
	v.color = glm::vec3(0.055f, 0.953f, 0.042f);
	vertList.push_back(v);

	v.position = glm::vec3(0.5f, -0.5f, -0.5f);
	v.normal = glm::vec3(0.0f, -1.0f, 0.0f);
	v.uvCoords = glm::vec2(1.0f, 0.0f);
	v.color = glm::vec3(0.714f, 0.505f, 0.345f);
	vertList.push_back(v);

	v.position = glm::vec3(0.5f, -0.5f, 0.5f);
	v.normal = glm::vec3(0.0f, -1.0f, 0.0f);
	v.uvCoords = glm::vec2(1.0f, 1.0f);
	v.color = glm::vec3(0.783f, 0.290f, 0.734f);
	vertList.push_back(v);

	v.position = glm::vec3(0.5f, -0.5f, 0.5f);
	v.normal = glm::vec3(0.0f, -1.0f, 0.0f);
	v.uvCoords = glm::vec2(1.0f, 1.0f);
	v.color = glm::vec3(0.722f, 0.645f, 0.174f);
	vertList.push_back(v);

	v.position = glm::vec3(-0.5f, -0.5f, 0.5f);
	v.normal = glm::vec3(0.0f, -1.0f, 0.0f);
	v.uvCoords = glm::vec2(0.0f, 1.0f);
	v.color = glm::vec3(0.302f, 0.455f, 0.848f);
	vertList.push_back(v);

	v.position = glm::vec3(-0.5f, -0.5f, -0.5f);
	v.normal = glm::vec3(0.0f, -1.0f, 0.0f);
	v.uvCoords = glm::vec2(0.0f, 0.0f);
	v.color = glm::vec3(0.225f, 0.587f, 0.040f);
	vertList.push_back(v);

	v.position = glm::vec3(-0.5f, 0.5f, -0.5f);
	v.normal = glm::vec3(0.0f, 1.0f, 0.0f);
	v.uvCoords = glm::vec2(0.0f, 0.0f);
	v.color = glm::vec3(0.517f, 0.713f, 0.338f);
	vertList.push_back(v);

	v.position = glm::vec3(0.5f, 0.5f, -0.5f);
	v.normal = glm::vec3(0.0f, 1.0f, 0.0f);
	v.uvCoords = glm::vec2(1.0f, 0.0f);
	v.color = glm::vec3(0.053f, 0.959f, 0.120f);
	vertList.push_back(v);

	v.position = glm::vec3(0.5f, 0.5f, 0.5f);
	v.normal = glm::vec3(0.0f, 1.0f, 0.0f);
	v.uvCoords = glm::vec2(1.0f, 1.0f);
	v.color = glm::vec3(0.393f, 0.621f, 0.362f);
	vertList.push_back(v);

	v.position = glm::vec3(0.5f, 0.5f, 0.5f);
	v.normal = glm::vec3(0.0f, 1.0f, 0.0f);
	v.uvCoords = glm::vec2(1.0f, 1.0f);
	v.color = glm::vec3(0.673f, 0.211f, 0.457f);
	vertList.push_back(v);

	v.position = glm::vec3(-0.5f, 0.5f, 0.5f);
	v.normal = glm::vec3(0.0f, 1.0f, 0.0f);
	v.uvCoords = glm::vec2(0.0f, 1.0f);
	v.color = glm::vec3(0.820f, 0.883f, 0.371f);
	vertList.push_back(v);

	v.position = glm::vec3(-0.5f, 0.5f, -0.5f);
	v.normal = glm::vec3(0.0f, 1.0f, 0.0f);
	v.uvCoords = glm::vec2(0.0f, 0.0f);
	v.color = glm::vec3(0.982f, 0.099f, 0.879f);
	vertList.push_back(v);

	//Adding Components To Light Object
	lightEntityPtr->AddComponent<Transform>(glm::vec3(10.0f, 10.0f, -5.0f));
	lightEntityPtr->AddComponent<Light>(0.5f, 0.5f, glm::vec3(1.0f, 1.0f, 1.0f));

	//Adding Components To Camera Object
	cameraEntityPtr->AddComponent<Transform>(glm::vec3(0.0f, 0.0f, -5.0f));
	auto cameraComponent = cameraEntityPtr->AddComponent<Camera>(45.0f, glm::vec2(0.2f, 50.0f));
	cameraComponent->AddLight(lightEntityPtr);
	
	//Adding Components To Cube Object
	cubeEntityPtr->AddComponent<Transform>();
	cubeEntityPtr->AddComponent<Shader>("cubeTextureShader", "vertTextureCubeShader.glsl", "fragTextureCubeShader.glsl");
	//cubeEntityPtr->AddComponent<MeshFilter>();
	//cubeEntityPtr->AddComponent<MeshRenderer>(cameraEntityPtr, 
	//										  GL_TRIANGLES);
	return true;
}

void CubeScene::Update(const float dt)
{
	cubeEntityPtr->GetComponent<Transform>()->angle += 1.0f;
	
	sceneEntityManagerPtr->Update();
	sceneEntityManagerPtr->SeekAndDestroy();
}

void CubeScene::Render() const
{
	sceneEntityManagerPtr->Render();
}

void CubeScene::ResizeUpdate() const
{
	sceneEntityManagerPtr->ResizeUpdate();
}

