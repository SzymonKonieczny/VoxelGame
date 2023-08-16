#include "Renderer.h"
Window Renderer::window; //constructor static call
glm::mat4 Renderer::ViewProjectionMatrix;
void Renderer::Init()
{
	window.Init();
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return;
	}
	glfwSetWindowSizeCallback(window.GetHandle(), OnWindowResize);
}

void Renderer::Shutdown()
{
	window.Shutdown();
}

void Renderer::OnWindowResize(GLFWwindow* window, int width, int height)
{

}

void Renderer::BeginScene(Camera& camera)
{
	ViewProjectionMatrix = camera.GetViewMatrix() * camera.GetProjectionMatrix();
}

void Renderer::EndScene()
{
}

void Renderer::Submit()
{
}
