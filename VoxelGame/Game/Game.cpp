#include "Game.h"
#include "Input.h"
int Game::CHUNK_SIZE = 16;
std::shared_ptr<Texture> Game::BlockTextureAtlas;

void Game::Init()
{
	Renderer::Init();
	Input::windowptr = Renderer::window.GetHandle();

	BlockTextureAtlas.reset(new Texture("Game/Textures/Atlas.png"));
	Chunk::ChunkSolidShader.reset(new Shader("Game/Shaders/ChunkShader.vert", "Game/Shaders/ChunkShader.frag"));

	
}

void Game::Start()
{
	Chunk chunk({ 0,0,0 });
	chunk.GenerateMesh();
	




	double previousTime = glfwGetTime();
	double deltaTime;

	while (!glfwWindowShouldClose(Renderer::window.GetHandle()))
	{
		double currentTime = glfwGetTime();
		deltaTime = currentTime - previousTime;
		previousTime = currentTime;
		glm::mat4 modelMat = chunk.getMesh().GetUniformData()["modelMatrix"].data.Mat4;
		chunk.getMesh().updateUniform("modelMatrix", glm::rotate(modelMat, (float)glm::radians(deltaTime * 50), glm::vec3(1, 1, 1)));
		player.Update(deltaTime);
		Renderer::BeginScene(player.getCamera());

		Renderer::Submit(chunk.getMesh());
		Renderer::EndScene();
		Renderer::window.SwapBuffers();

		Renderer::window.PullEvents();
	}

}

void Game::Update(float dt)
{
	player.Update(dt);
}
