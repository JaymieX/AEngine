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

	inline GLFWwindow* GetWindow() const { return window; }

	inline std::pair<GLuint, GLuint> GetDimensions() const
	{ return std::make_pair(width, height); }

	inline void SetVSync(bool vsyncEnabled) const
	{ if (vsyncEnabled) glfwSwapInterval(1); else glfwSwapInterval(0); }

private:
	GLuint width, height;
	GLFWwindow* window;
	std::string name;
};
