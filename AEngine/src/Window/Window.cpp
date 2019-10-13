#include <Core/AEpch.h>
#include "Window.h"

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

	this->window = glfwCreateWindow(width, height, name.c_str(), nullptr, nullptr);

	if (!window)
	{
		std::cout << "Failed to create Window" << std::endl;
		return false;
	}

	glfwMakeContextCurrent(window);
	SetVSync(true);

	return true;
}