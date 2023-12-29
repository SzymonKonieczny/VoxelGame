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
		return false;
	}
	static bool mouseIsPressed(int GLFW_Key) {
		if (glfwGetMouseButton(windowptr, GLFW_Key) == GLFW_PRESS)
		{
			return true;
		}
		return false;
	}
	static bool mouseIsReleased(int GLFW_Key) {
		if (glfwGetMouseButton(windowptr, GLFW_Key) == GLFW_RELEASE)
		{
			return true;
		}
		return false;
	}
	static bool isReleased(int GLFW_Key) {
		if (glfwGetKey(windowptr, GLFW_Key) == GLFW_RELEASE)
		{
			return true;
		}
		return false;

	}
	static void getMouseMove(double* mouseX, double* mouseY) {
		glfwGetCursorPos(windowptr, mouseX, mouseY);
		glfwSetCursorPos(windowptr, (screenWidth / 2), (screenHeight / 2));

	}
	static void getMousePosNormalized(double* mouseX, double* mouseY) {
		glfwGetCursorPos(windowptr, mouseX, mouseY);
		*mouseY = (((float)*mouseY / screenHeight) - 1) * -1;
		*mouseX = (float)*mouseX / screenWidth;

	}

}; 
