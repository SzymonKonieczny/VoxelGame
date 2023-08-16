#include <iostream>
#include <Windows.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Game/Renderer.h"
int main()
{




	/*
	
	
	
		TO DO BOARD:
		 zrzucic Vertex Array Object na VertexArray.h/cpp
		 Textury
		Framebuffery
	
	
	*/
	std::cout << "Hello swiat xd\n";
	Renderer::Init();
	GLfloat verts[3 * 3] = {
	0.0f,0.0f,0.0f,
	0.0f,0.5f,0.0f,
	0.5f,0.5f,0.0f,
	};
	struct Vert {
		glm::vec3 pos;
	};
	std::vector<Vert> vertvec = {
		{{1.0f,0.0f,0.0f}},
		{{0.5f,0.5f,0.0f}},
		{{0.0f,0.5f,0.0f}}
	};

	glViewport(0, 0, 800, 800);
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	const char* vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\0";
	const char* fragmentShaderSource = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"   FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
		"}\n\0";


	Shader prog = Shader(std::string(vertexShaderSource), std::string(fragmentShaderSource));
	VertexArray VAO;
	VAO.SetVertexBuffer(new VertexBuffer());
	BufferLayout Layout = {
		{ShaderDataType::Float3,"aPos"}
	};
	VAO.UpdateVertexData((float*)vertvec.data(), sizeof(Vert)* vertvec.size());
	std::cout << "sizeof verts :" << sizeof(Vert) * vertvec.size() << "\n";
	VAO.SetLayout(Layout);
	

	while (!glfwWindowShouldClose(Renderer::window.GetHandle()))
	{

		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		prog.Bind();
		VAO.Bind();
		glDrawArrays(GL_TRIANGLES, 0, 3);
		Renderer::window.SwapBuffers();
		Renderer::window.PullEvents();
	}




	Renderer::Shutdown();
	return 0;
}