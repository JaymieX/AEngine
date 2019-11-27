#include <Core/AEpch.h>
#include "Core/AEApplication.h"
#include "MouseEvent.h"

std::unique_ptr<MouseEventDispatcher> MouseEventDispatcher::dispatcher(nullptr);

MouseEventDispatcher* MouseEventDispatcher::GetDispatcher()
{
	if(!dispatcher) dispatcher = std::make_unique<MouseEventDispatcher>();
	return dispatcher.get();
}

void MouseEventDispatcher::RegisterCallbacks(GLFWwindow* window)
{
	BindListeners();
	SetGlfwMouseCallbacks(window);

	const auto windowDimensions = AEApplication::GetInstance()->GetWindowSize();
	glfwSetCursorPos(window, windowDimensions.x / 2, windowDimensions.y / 2);
}

void MouseEventDispatcher::BindListeners()
{
	mouseEventListener.Listen(mousePollUpdateEvent, &MouseEventListener::OnMousePollEvent);
	mouseEventListener.Listen(mouseMovedEvent, &MouseEventListener::OnMouseMovedEvent);
	mouseEventListener.Listen(mouseButtonEvent, &MouseEventListener::OnMouseButtonEvent);
	mouseEventListener.Listen(mouseScrollEvent, &MouseEventListener::OnMouseScrollEvent);
	mouseEventListener.Listen(mouseButtonPressedEvent, &MouseEventListener::OnMousePressedEvent);
	mouseEventListener.Listen(mouseButtonReleasedEvent, &MouseEventListener::OnMouseReleasedEvent);
}

void MouseEventDispatcher::SetGlfwMouseCallbacks(GLFWwindow* window)
{
	glfwSetCursorPosCallback(window, [](GLFWwindow* w, double x, double y){ GetDispatcher()->mouseMovedEvent.Execute(x, y); });
	glfwSetMouseButtonCallback(window, [](GLFWwindow* w, int b, int a, int m){ GetDispatcher()->mouseButtonEvent.Execute(b, a ,m); });
	glfwSetScrollCallback(window, [](GLFWwindow* w, double x, double y){ GetDispatcher()->mouseScrollEvent.Execute(y);});
}

void MouseEventDispatcher::MousePollUpdate(const float dt)
{
	mousePollUpdateEvent.Execute(dt);
}

glm::vec2 MouseEventListener::previousMousePosition = glm::vec2();
glm::vec2 MouseEventListener::currentMousePosition = glm::vec2();
glm::vec2 MouseEventListener::offsetMousePosition = glm::vec2();
glm::vec2 MouseEventListener::mousePosition = glm::vec2();
float MouseEventListener::scrollPosition = 0.0f;
bool MouseEventListener::firstGather = true;

void MouseEventListener::OnMouseMovedEvent(double x, double y)
{
	mousePosition = glm::vec2(static_cast<float>(x), static_cast<float>(y));
}

void MouseEventListener::OnMouseButtonEvent(int btn, int action, int mods)
{
	if(action == GLFW_PRESS)
		OnMousePressedEvent(btn);
	else if(action == GLFW_RELEASE)
		OnMouseReleasedEvent(btn);
}

void MouseEventListener::OnMouseScrollEvent(double y)
{
	scrollPosition += static_cast<float>(y);
}

void MouseEventListener::OnMousePressedEvent(int button)
{
	if(button == GLFW_MOUSE_BUTTON_RIGHT)
		std::cout << "Right Mouse Button Clicked" << std::endl;
	else if(button == GLFW_MOUSE_BUTTON_LEFT)
		std::cout << "Left Mouse Button Clicked" << std::endl;
}

void MouseEventListener::OnMouseReleasedEvent(int button)
{
	if(button == GLFW_MOUSE_BUTTON_RIGHT)
		std::cout << "Right Mouse Button Released" << std::endl;
	else if(button == GLFW_MOUSE_BUTTON_LEFT)
		std::cout << "Left Mouse Button Released" << std::endl;
}

void MouseEventListener::OnMousePollEvent(float dt)
{
	auto temp = mousePosition;
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
}






