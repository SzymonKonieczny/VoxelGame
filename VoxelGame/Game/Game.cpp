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
	


	world.chunkManager.GenWorld();
	double previousTime = glfwGetTime();
	double deltaTime;
	double currentTime = 0;
	int counter = 0;
	while (!glfwWindowShouldClose(Renderer::window.GetHandle()))
	{
		currentTime = glfwGetTime();
		deltaTime = currentTime - previousTime;
		previousTime = currentTime;
		counter++;
		{
			std::string FPS = std::to_string((1.0 / deltaTime) * counter);
			std::string newTitle = "Voxelini Kowalini  " + FPS + " FPS";
			glfwSetWindowTitle(Renderer::window.GetHandle(), newTitle.c_str());

		}

		player.Update(deltaTime);
		Renderer::BeginScene(player.getCamera());
		for (auto& chunk : world.chunkManager.getChunks())
		{
			Renderer::Submit(chunk.getMesh());
		}
		Renderer::EndScene();
		Renderer::window.SwapBuffers();

		Renderer::window.PullEvents();
	}

}

void Game::Update(float dt)
{
	player.Update(dt);
}
