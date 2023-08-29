#pragma once
#include <GLFW/glfw3.h>
#include "Global.h"
class Input {
public:
	static GLFWwindow* windowptr;
	static bool isPressed( int GLFW_Key) {
		if (glfwGetKey(windowptr, GLFW_Key) == GLFW_PRESS)
		{
			return true;
		}
	}
	static void getMouseMove(double* mouseX, double* mouseY) {
		glfwGetCursorPos(windowptr, mouseX, mouseY);
		glfwSetCursorPos(windowptr, (screenWidth / 2), (screenHeight / 2));

	}

}; 
