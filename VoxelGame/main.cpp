#include <iostream>
#include <Windows.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Game/Renderer.h"
#include "Game/Game.h"
int main()
{

	std::cout << "Hello swiat xd\n";
	Renderer::Init();
	Game  game;
	game.Init();
	Chunk chunk({0,0,0});
	chunk.GenerateMesh();
	Camera cam;
	cam.SetPosition({ 0,0,2 });
	cam.SetRotation({ 0,0,-1 });

	cam.UpdateMatricies();
	double previousTime = glfwGetTime();
	double deltaTime;



	while (!glfwWindowShouldClose(Renderer::window.GetHandle()))
	{
		double currentTime = glfwGetTime();
		deltaTime = currentTime - previousTime;
		previousTime = currentTime;
		glm::mat4 modelMat = chunk.getMesh().GetUniformData()["modelMatrix"].data.Mat4;
		chunk.getMesh().updateUniform("modelMatrix", glm::rotate(modelMat, (float)glm::radians(deltaTime * 50), glm::vec3(0, 1, 0)));
		Renderer::BeginScene(cam);

		Renderer::Submit(chunk.getMesh());
		Renderer::EndScene();
		Renderer::window.SwapBuffers();

		Renderer::window.PullEvents();
	}




	Renderer::Shutdown();
	return 0;
}