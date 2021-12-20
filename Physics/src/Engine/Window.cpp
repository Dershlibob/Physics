#include "Window.h"

#include <GLFW/glfw3.h>

Window::Window()
{  
	/* Initialize the library */
	if (!glfwInit())
		__debugbreak();

	/* Create a windowed mode window and its OpenGL context */

	window = glfwCreateWindow(WIN_WIDTH, WIN_HEIGHT, "Space Defender", NULL, NULL);
	glfwSetWindowPos(window, 500, 100);

	if (!window)
	{
		glfwTerminate();
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	glfwSwapInterval(1);
}


void Window::HideMouse(bool bHide)
{
	if (bHide)
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	else
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

Window* Window::instance = 0;

Window* Window::getInstance()
{
	if (instance == 0)
	{
		instance = new Window();
	}

	return instance;
}