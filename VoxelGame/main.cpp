#include <iostream>
#include <Windows.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Renderer/Renderer.h"
#include "Renderer/Shader.h"
int main()
{
	
	std::cout << "Hello swiat xd\n";
	Renderer::Init();
	GLfloat verts[3 * 3] = {
	0.0f,0.0f,0.0f,
	0.0f,0.5f,0.0f,
	0.5f,0.5f,0.0f,
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
	

	unsigned int VBO,VAO; 

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);


	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);


	glBufferData(GL_VERTEX_ARRAY, sizeof(verts), verts, GL_STATIC_DRAW);


	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);





	

	while (!glfwWindowShouldClose(Renderer::window.window))
	{
		// Specify the color of the background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// Clean the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT);
		// Tell OpenGL which Shader Program we want to use
		prog.Bind();
		// Bind the VAO so OpenGL knows to use it
		glBindVertexArray(VAO);
		// Draw the triangle using the GL_TRIANGLES primitive
		glDrawArrays(GL_TRIANGLES, 0, 3);
		// Swap the back buffer with the front buffer
		Renderer::window.SwapBuffers();
		// Take care of all GLFW events
		//Renderer::window.PullEvents();
	}




	int a = 0;
	std::cin >> a;

	Renderer::Shutdown();
	return 0;
}