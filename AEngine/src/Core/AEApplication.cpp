#include <Core/AEpch.h>
#include "AEApplication.h"
#include "Window/Window.h"
#include "Core/Timer.h"
#include "Scene/IScene.h"
#include "Scene/ModelScene.h"
#include "Events/MouseEvent.h"
#include "Graphics/ShaderHandler.h"
#include "Graphics/TextureHandler.h"

std::unique_ptr<AEApplication> AEApplication::instance(nullptr);

AEApplication* AEApplication::GetInstance()
{
	if (!instance) instance = std::unique_ptr<AEApplication>(new AEApplication());
	return instance.get();
}

AEApplication::~AEApplication() 
{  
	glfwTerminate();
}

glm::vec2 AEApplication::GetWindowSize() const
{
	return glm::vec2(windowPtr->GetWidth(), windowPtr->GetHeight());
}

bool AEApplication::Initialize() 
{	
	if (glfwInit() == GLFW_FALSE)
	{
		std::cout << "Failed to initialize GLFW" << std::endl;
		return false;
	}

	windowPtr = std::make_unique<Window>();
	windowPtr->Create("AEngine", std::make_pair(800, 600));

	if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return false;
	}

	glEnable(GL_DEPTH_TEST);
	glViewport(0, 0, windowPtr->GetWidth(), windowPtr->GetHeight());

	//Created Shader Instance
	ShaderHandler::GetInstance()->CreateProgram("BasicShader", "vert.glsl", "frag.glsl");
	ShaderHandler::GetInstance()->CreateProgram("TextureShader", "vertTextureShader.glsl", "fragTextureShader.glsl");
	
	MouseEventDispatcher::GetDispatcher()->RegisterCallbacks(windowPtr->GetWindow());

	BuildScene(new ModelScene());

	graphicsTimerPtr = std::make_unique<Timer>(90.0);
	graphicsTimerPtr->SetTimerAction(&AEApplication::Update, this);

	return true;
}

void AEApplication::Run() const
{
	while (!glfwWindowShouldClose(windowPtr->GetWindow()))
	{
		graphicsTimerPtr->Update();
		Render();
	}
}

void AEApplication::Update() const
{
	glfwPollEvents();

	if (sceneActive)
		scenePtr->Update(static_cast<float>(graphicsTimerPtr->GetDeltaTime()));
}

void AEApplication::Render() const
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (sceneActive) scenePtr->Render();

	glfwSwapBuffers(windowPtr->GetWindow());
}

void AEApplication::BuildScene(IScene* buildScene)
{
	scenePtr.reset(buildScene);
	sceneActive = scenePtr->Initialize();
}

void AEApplication::ResizeUpdate() const
{
	if (sceneActive) scenePtr->ResizeUpdate();
}

void AEApplication::Destroy() const
{
	if (scenePtr)
	{
		scenePtr->Destroy();
	}
	TextureHandler::GetInstance()->Destroy();
	ShaderHandler::GetInstance()->Destroy();
	glfwTerminate();
}
