#pragma once

#include "IEvent.h"

class MouseEventListener : public EventListener<MouseEventListener>
{
public: 
	void OnMouseMovedEvent(double, double);
	void OnMouseButtonEvent(int, int, int);
	void OnMouseScrollEvent(double);
	void OnMousePressedEvent(int button);
	void OnMouseReleasedEvent(int button);
	void OnMousePollEvent(float dt);

	static glm::vec2 previousMousePosition;
	static glm::vec2 currentMousePosition;
	static glm::vec2 offsetMousePosition;
	static glm::vec2 mousePosition;
	static float scrollPosition;
	static bool firstGather;
};

struct MouseEventDispatcher
{
	MouseEventDispatcher() = default;
	MouseEventDispatcher(const MouseEventDispatcher&) = delete;
	MouseEventDispatcher(MouseEventDispatcher&&) = delete;
	MouseEventDispatcher& operator=(const MouseEventDispatcher&) = delete;
	MouseEventDispatcher& operator=(MouseEventDispatcher) = delete;

	static MouseEventDispatcher* GetDispatcher();

	void MousePollUpdate(float dt);
	void RegisterCallbacks(GLFWwindow*);

	Event<double, double> mouseMovedEvent;
	Event<int, int, int> mouseButtonEvent;
	Event<int> mouseButtonPressedEvent;
	Event<int> mouseButtonReleasedEvent;
	Event<double> mouseScrollEvent;
	Event<float> mousePollUpdateEvent;
private:
	static std::unique_ptr<MouseEventDispatcher> dispatcher;
	MouseEventListener mouseEventListener;

	void BindListeners();
	void SetGlfwMouseCallbacks(GLFWwindow*);
};


