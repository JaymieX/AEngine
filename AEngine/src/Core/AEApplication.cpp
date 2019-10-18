#include <Core/AEpch.h>
#include "AEApplication.h"
#include "Window/Window.h"
#include "Core/Timer.h"
#include "Systems/EntityComponent.h"
#include "Core/Logger.h"
#include "Scene/IScene.h"
#include "Scene/CubeScene.h"

AEApplication::AEApplication()
{ 

}

AEApplication::~AEApplication() 
{  
	scenePtr.reset();
	entityManager.reset();
	windowPtr.reset();
	glfwTerminate();
}

bool AEApplication::Initialize() 
{
	LOG_INIT();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	if (glfwInit() == GLFW_FALSE)
	{
		std::cout << "Failed to initialize GLFW" << std::endl;
		return false;
	}

	entityManager = std::make_unique<EntityManager>();
	windowPtr = std::make_unique<Window>();
	windowPtr->Create("AEngine", std::make_pair(800, 600));

	graphicsTimerPtr = std::make_unique<Timer>(90.0);
	graphicsTimerPtr->SetTimerAction(&AEApplication::Update, this);

	//audioTimerPtr = std::make_unique<Timer>(256.0);
	//audioTimerPtr->SetTimerAction(&AEApplication::AudioUpdate, this);

	if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return false;
	}

	LOG_INFO(std::string(reinterpret_cast<const char* const>(glGetString(GL_VERSION))), "", 0);

	glViewport(0, 0, windowPtr->GetWidth(), windowPtr->GetHeight());

	scenes.push_back(new CubeScene());

	BuildScene();

	return true;
}

void AEApplication::Run() const
{
	while (!glfwWindowShouldClose(windowPtr->GetWindow()))
	{
		graphicsTimerPtr->Update();
		//audioTimerPtr->Update();
	}
}

void AEApplication::Update() const
{
	glfwPollEvents();
	glfwSwapBuffers(windowPtr->GetWindow());
	entityManager->Update();
	entityManager->SeekAndDestroy();

	if (sceneActive)
		scenePtr->Update(static_cast<float>(graphicsTimerPtr->GetDeltaTime()));

	Render();
}

void AEApplication::AudioUpdate() const
{
	//LOG_INFO("Audio Updating...", __FILE__, __LINE__);
}

void AEApplication::Render() const
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	
	entityManager->Render();

	if (sceneActive)
		scenePtr->Render();
}

void AEApplication::BuildScene(const unsigned int buildIndex)
{
	scenePtr.reset(scenes[buildIndex]);
	sceneActive = scenePtr->Initialize();
}