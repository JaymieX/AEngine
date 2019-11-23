#pragma once

class AEApplication;

struct MouseEventListener
{
	static void RegisterCallbacks(GLFWwindow*);
	static void MouseMovedCallback(GLFWwindow*, double, double);
	static void MouseButtonCallback(GLFWwindow*, int, int, int);
	static void MouseScrollCallback(GLFWwindow*, double, double);

	static glm::vec2 previousMousePosition;
	static glm::vec2 currentMousePosition;
	static glm::vec2 offsetMousePosition;
	static glm::vec2 scrollPosition;
	static bool firstGather;

	static void MousePressedEvent(int button);
	static void MouseReleasedEvent(int button);
};