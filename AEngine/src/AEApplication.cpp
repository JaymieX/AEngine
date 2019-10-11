#include <AEpch.h>
#include "AEApplication.h"

AEApplication::AEApplication()
{ }

AEApplication::~AEApplication() 
{  
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