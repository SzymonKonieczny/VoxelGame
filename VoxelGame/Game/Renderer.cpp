#include "Renderer.h"
Window Renderer::window; //constructor static call
glm::mat4 Renderer::ViewProjectionMatrix;
std::list<Mesh> Renderer::Meshes;
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
	for (auto& m : Meshes)
	{
		switch (m.getType())
		{
		case MeshType::Indexed:
			RendererCommand::DrawIndexed(m);
			break;
		case MeshType::Unindexed:
			RendererCommand::DrawNotIndexed(m);
			break;
		}
	}
	Meshes.clear();
}

void Renderer::Submit(Mesh& m)
{
	Meshes.push_back(m);
	//RendererCommand::DrawNotIndexed(m);
}
