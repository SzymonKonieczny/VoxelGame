#include "Window.h"
#include <iostream>
#include <GLFW/glfw3.h>
void Window::Init()
{
	
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(800, 800, "Voxelini Kowalini", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return;
	}
	glfwMakeContextCurrent(window);

}

void Window::SwapBuffers()
{
	std::cout << window << "\n";
	glfwSwapBuffers(window);

}

void Window::PullEvents()
{
	glfwPollEvents();

}

void Window::Shutdown()
{
	glfwDestroyWindow(window);
	glfwTerminate();
}
