#include <Core/AEpch.h>
#include "Window.h"
#include "Core/Logger.h"
#include "Core/AEApplication.h"

Window::Window() : window(nullptr), width(0), height(0) { }

Window::~Window()
{
	glfwDestroyWindow(window);
}

bool Window::Create(std::string name, std::pair<GLuint, GLuint> dimensions)
{
	this->name = name;
	this->width = dimensions.first;
	this->height = dimensions.second;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	this->window = glfwCreateWindow(width, height, name.c_str(), nullptr, nullptr);

	if (!window)
	{
		LOG_ERROR("Failed to create Window", __FILE__, __LINE__);
		return false;
	}

	glfwSetFramebufferSizeCallback(window, [](GLFWwindow* glfwWindow, int width, int height) {
		auto window = static_cast<Window*>(glfwGetWindowUserPointer(glfwWindow));

		window->SetDimensions(std::make_pair(width, height));
		glViewport(0, 0, width, height);

		AEApplication::GetInstance()->ResizeUpdate();
	});
	
	glfwMakeContextCurrent(window);
	glfwSetWindowUserPointer(window, this);
	SetVSync(true);

	return true;
}