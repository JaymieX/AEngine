#pragma once

class Window
{
public:
	Window();
	~Window();

	Window(const Window&) = delete;
	Window(Window&&) = delete;
	Window& operator=(const Window&) = delete;
	Window& operator=(Window&&) = delete;

	// ====================================================

	bool Create(std::string, std::pair<GLuint, GLuint>);

	// ====================================================

	[[nodiscard]] inline GLFWwindow* GetWindow() const { return window; }
	[[nodiscard]] inline GLuint GetWidth() const { return width; }
	[[nodiscard]] inline GLuint GetHeight() const { return height; }

	[[nodiscard]] inline void SetDimensions(std::pair<GLuint, GLuint> dimensions)
	{
		width = dimensions.first; height = dimensions.second;
	}

	inline void SetVSync(bool vsyncEnabled) const
	{
		if (vsyncEnabled) glfwSwapInterval(1); else glfwSwapInterval(0);
	}

private:
	GLuint width, height;
	GLFWwindow* window;
	std::string name;
};

