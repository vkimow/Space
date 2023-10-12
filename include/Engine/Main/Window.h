#pragma once

#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace Engine
{
	class Window final
	{
	public:
		Window(const char *title, unsigned int width, unsigned int height);
		Window() = delete;
		Window(const Window &rhs) = delete;
		Window(Window &&rhs) = delete;
		~Window();

	public:
		bool IsActive();
		GLFWwindow *const GetInnerWindow();

	public:
		void Resize(unsigned int width, unsigned int height);

	private:
		static void FramebufferResizeCallback(GLFWwindow *window, int width, int height);

	private:
		bool isActive;
		GLFWwindow * glfwWindow;
	};
}
