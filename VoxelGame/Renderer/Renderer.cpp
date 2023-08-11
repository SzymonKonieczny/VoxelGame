#include "Renderer.h"
Window Renderer::window; //constructor static call

void Renderer::Init()
{
	window.Init();
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return;
	}
}

void Renderer::Shutdown()
{
	window.Shutdown();
}

void Renderer::OnWindowResize(uint32_t width, uint32_t height)
{
}

void Renderer::BeginScene(Camera& camera)
{
}

void Renderer::EndScene()
{
}

void Renderer::Submit()
{
}
