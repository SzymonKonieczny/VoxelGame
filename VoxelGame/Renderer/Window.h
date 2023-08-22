#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
class Window {

public :
	Window() {};
	void Init();
	void SwapBuffers();
	void PullEvents();
	void Shutdown();
	GLFWwindow* GetHandle() { return window; }
private:
	GLFWwindow* window;
};
