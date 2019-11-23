#include <Core/AEpch.h>
#include "MouseEventListener.h"
#include "Core/AEApplication.h"

glm::vec2 MouseEventListener::previousMousePosition = glm::vec2();
glm::vec2 MouseEventListener::currentMousePosition = glm::vec2();
glm::vec2 MouseEventListener::offsetMousePosition = glm::vec2();
glm::vec2 MouseEventListener::scrollPosition = glm::vec2();
bool MouseEventListener::firstGather = true;

void MouseEventListener::RegisterCallbacks(GLFWwindow* window)
{
	glfwSetCursorPosCallback(window, MouseMovedCallback);
	glfwSetMouseButtonCallback(window, MouseButtonCallback);
	glfwSetScrollCallback(window, MouseScrollCallback);
	glfwSetCursorPos(window, 
					 AEApplication::GetInstance()->GetWindowSize().x / 2, 
					 AEApplication::GetInstance()->GetWindowSize().y / 2);
}

void MouseEventListener::MouseMovedCallback(GLFWwindow* window, double x, double y)
{
	auto temp = glm::vec2(static_cast<float>(x), static_cast<float>(y));
	temp.y = AEApplication::GetInstance()->GetWindowSize().y - temp.y;

	if (firstGather)
	{
		previousMousePosition = temp;
		currentMousePosition = temp;
		firstGather = false;
	}
	else 
	{
		previousMousePosition = currentMousePosition;
		currentMousePosition = temp;
	}

	offsetMousePosition.x = currentMousePosition.x - previousMousePosition.x;
	offsetMousePosition.y = previousMousePosition.y - currentMousePosition.y;

	//std::cout << glm::to_string(offsetMousePosition) << std::endl;

}

void MouseEventListener::MouseButtonCallback(GLFWwindow* window, int btn, int action, int mods)
{
	if(action == GLFW_PRESS)
		MousePressedEvent(btn);
	else if(action == GLFW_RELEASE)
		MouseReleasedEvent(btn);
}

void MouseEventListener::MouseScrollCallback(GLFWwindow* window, double x, double y)
{
	scrollPosition.x = static_cast<float>(x);
	scrollPosition.y = static_cast<float>(y);

	//std::cout << glm::to_string(scrollPosition) << std::endl;
}

void MouseEventListener::MousePressedEvent(int button)
{
	if(button == GLFW_MOUSE_BUTTON_RIGHT)
		std::cout << "Right Mouse Button Clicked" << std::endl;
	else if(button == GLFW_MOUSE_BUTTON_LEFT)
		std::cout << "Left Mouse Button Clicked" << std::endl;
}

void MouseEventListener::MouseReleasedEvent(int button)
{
	if(button == GLFW_MOUSE_BUTTON_RIGHT)
		std::cout << "Right Mouse Button Released" << std::endl;
	else if(button == GLFW_MOUSE_BUTTON_LEFT)
		std::cout << "Left Mouse Button Released" << std::endl;
}





