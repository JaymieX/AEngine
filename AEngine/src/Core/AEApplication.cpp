#include <Core/AEpch.h>
#include "AEApplication.h"
#include "Window/Window.h"
#include "Core/Timer.h"
#include "Systems/EntityComponent.h"

AEApplication::AEApplication()
{ 

}

AEApplication::~AEApplication() 
{  
	entityManager.reset();
	windowPtr.reset();
	glfwTerminate();
}

bool AEApplication::Initialize() 
{
	if (glfwInit() == GLFW_FALSE)
	{
		std::cout << "Failed to initialize GLFW" << std::endl;
		return false;
	}

	entityManager = std::make_unique<EntityManager>();
	windowPtr = std::make_unique<Window>();
	windowPtr->Create("AEngine", std::make_pair(800, 600));

	graphicsTimerPtr = std::make_unique<Timer>(60.0);
	graphicsTimerPtr->SetTimerAction(&AEApplication::Update, this);

	//audioTimerPtr = std::make_unique<Timer>(400.0);
	//audioTimerPtr->SetTimerAction(&AEApplication::AudioUpdate, this);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return false;
	}
}

void AEApplication::Run() 
{
	while (!glfwWindowShouldClose(windowPtr->GetWindow()))
	{
		graphicsTimerPtr->Update();
		//audioTimerPtr->Update();
	}
}

void AEApplication::Update()
{
	glfwPollEvents();
	glfwSwapBuffers(windowPtr->GetWindow());
	entityManager->Update();
	entityManager->SeekAndDestroy();
}

void AEApplication::AudioUpdate()
{

}

void AEApplication::Render()
{
	entityManager->Render();
}