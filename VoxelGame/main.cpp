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
	UniformDataUnion t;
	t.Float2 = glm::vec2(-0.2, -0.4);
	m.getShader()->updateUniform("testUni",t );
	m.Verticies = {
	0.0f,0.0f,0.0f,		1.0f,0.0f,0.0f,
	0.0f,0.5f,0.0f,		0.0f,1.0f,0.0f,
	0.5f,0.5f,0.0f,		0.0f,0.0f,1.0f,
	};
	m.UpdateGLObjs();
	m.GetVertexArray().SetLayout(Layout);
	while (!glfwWindowShouldClose(Renderer::window.GetHandle()))
	{



		Renderer::Submit(m);
		Renderer::EndScene();
		Renderer::window.SwapBuffers();
		Renderer::window.PullEvents();
	}




	Renderer::Shutdown();
	return 0;
}