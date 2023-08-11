#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
class Window {

public :
	Window() {};
	void Init();
	void SwapBuffers();
	void PullEvents();
	void Shutdown();
	GLFWwindow* window;
private:
};
