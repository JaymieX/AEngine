#include <Core/AEpch.h>
#include "MouseEventListener.h"

glm::vec2 MouseEventListener::oldMousePosition = glm::vec2();
glm::vec2 MouseEventListener::currentMousePosition = glm::vec2();
glm::vec2 MouseEventListener::offsetMousePosition = glm::vec2();
glm::vec2 MouseEventListener::scrollPosition = glm::vec2();

void MouseEventListener::RegisterCallbacks(GLFWwindow* window)
{
	glfwSetCursorPosCallback(window, MouseMovedCallback);
	glfwSetMouseButtonCallback(window, MouseButtonCallback);
	glfwSetScrollCallback(window, MouseScrollCallback);
}

void MouseEventListener::MouseMovedCallback(GLFWwindow* window, double x, double y)
{
	oldMousePosition = currentMousePosition;
	currentMousePosition.x = static_cast<float>(x);
	currentMousePosition.y = static_cast<float>(y);
	offsetMousePosition = oldMousePosition - currentMousePosition;
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





