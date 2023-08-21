#include <iostream>
#include <Windows.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Game/Renderer.h"
int main()
{




	std::cout << "Hello swiat xd\n";
	Renderer::Init();





	BufferLayout Layout = {
		{ShaderDataType::Float3,"aPos"},
		{ShaderDataType::Float3,"aCol"}

	};
	Mesh m;
	m.SetShader(new Shader("Game/Shaders/test.vert", "Game/Shaders/test.frag"));
	m.getShader()->AddUniform("testUni", UniformType::Float2);

	m.getShader()->updateUniform("testUni", glm::vec2(0.1,-0.2));
	m.Verticies = {
	0.0f,0.0f,0.0f,		1.0f,0.0f,0.0f,
	0.0f,0.5f,0.0f,		0.0f,1.0f,0.0f,
	0.5f,0.5f,0.0f,		0.0f,0.0f,1.0f,
	};
	m.UpdateGLObjs();
	m.GetVertexArray().SetLayout(Layout);

	double previousTime = glfwGetTime();
	double deltaTime;
	while (!glfwWindowShouldClose(Renderer::window.GetHandle()))
	{
		double currentTime = glfwGetTime();
		deltaTime = currentTime - previousTime;
		previousTime = currentTime;
		
		Renderer::Submit(m);
		Renderer::EndScene();
		Renderer::window.SwapBuffers();
		Renderer::window.PullEvents();
	}




	Renderer::Shutdown();
	return 0;
}