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

	double previousTime = glfwGetTime();
	double deltaTime;
	while (!glfwWindowShouldClose(Renderer::window.GetHandle()))
	{
		double currentTime = glfwGetTime();
		deltaTime = currentTime - previousTime;
		previousTime = currentTime;
		Renderer::BeginScene(cam);

		Renderer::Submit(chunk.getMesh());
		Renderer::EndScene();
		Renderer::window.SwapBuffers();
		Renderer::window.PullEvents();
	}




	Renderer::Shutdown();
	return 0;
}