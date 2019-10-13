#include <Core/AEpch.h>
#include "AEApplication.h"
#include "Window/Window.h"
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
		glfwPollEvents();
		glfwSwapBuffers(windowPtr->GetWindow());
	}
}

void AEApplication::Update()
{
	entityManager->Update();
	entityManager->SeekAndDestroy();
}

void AEApplication::Render()
{
	entityManager->Render();
}