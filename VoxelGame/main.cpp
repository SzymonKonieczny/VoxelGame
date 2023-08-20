#include <iostream>
#include <Windows.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Game/Renderer.h"
int main()
{




	std::cout << "Hello swiat xd\n";
	Renderer::Init();


	const char* vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"layout (location = 1) in vec3 aCol;\n"
		"out vec3 Col;\n"
		"void main()\n"
		"{\n"
		"   Col = aCol;\n"
		"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\0";
	const char* fragmentShaderSource = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"in vec3 Col;\n"
		"void main()\n"
		"{\n"
		"   FragColor = vec4(Col, 1.0f);\n"
		"}\n\0";


	Shader prog = Shader(std::string(vertexShaderSource), std::string(fragmentShaderSource));
	BufferLayout Layout = {
		{ShaderDataType::Float3,"aPos"},
		{ShaderDataType::Float3,"aCol"}

	};
	Mesh m;
	m.Verticies = {
	0.0f,0.0f,0.0f,		1.0f,0.0f,0.0f,
	0.0f,0.5f,0.0f,		0.0f,1.0f,0.0f,
	0.5f,0.5f,0.0f,		0.0f,0.0f,1.0f,
	};
	m.UpdateGLObjs();
	m.SetShader(new Shader(std::string(vertexShaderSource), std::string(fragmentShaderSource)));
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