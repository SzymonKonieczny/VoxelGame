
#include "Game.h"
#include "Input.h"

//int Game::CHUNK_SIZE = 16;
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
	

	FillBlockTable();

	//world.chunkManager.GenWorld();
	double previousTime = glfwGetTime();
	double deltaTime;
	double currentTime = 0;
	glfwSwapInterval(0);
	while (!glfwWindowShouldClose(Renderer::window.GetHandle()))
	{
		currentTime = glfwGetTime();
		deltaTime = currentTime - previousTime;
		previousTime = currentTime;
		{
			std::string FPS = std::to_string((1.0 / deltaTime));
			std::string newTitle = "Voxelini Kowalini  " + FPS + " FPS";
			glfwSetWindowTitle(Renderer::window.GetHandle(), newTitle.c_str());
		}

		Update(deltaTime);
		Renderer::BeginScene(world.player.getCamera());

		RenderWorld(world);

		Renderer::EndScene();
		Renderer::window.SwapBuffers();

		Renderer::window.PullEvents();
	}

}

void Game::RenderWorld(World& world)
{
	for (auto& chunkCol : world.chunkManager->getChunks())
	{
		if (isChunkColumnInFrustum(chunkCol.second))
		{
			for (auto& chunk : chunkCol.second->m_Chunks) {
				if (chunk->isGPU_BufferOutdated() && chunk->isMeshed() )
				{
					chunk->getMesh().UpdateObjectsOnGPU();
					chunk->setIsGPU_BufferOutdated(false);
				}
				Renderer::Submit(chunk->getMesh());
			}
		}

	}
}



bool Game::isChunkColumnInFrustum(std::shared_ptr<ChunkColumn> col)
{
	glm::vec2 playerPos(world.player.getPositon().x/ChunkSize, world.player.getPositon().z/ ChunkSize);//first check if in render distance, later actual frustum
	glm::vec2 colPos(col->m_Position.x, col->m_Position.y);
	if(RenderDistance > glm::distance(colPos, playerPos))return true; //fcked up logic but it works xd
	else return false;

}

void Game::FillBlockTable()
{

	BlockTable.push_back(BlockInfo({ 0.8f,0.f },BlockModelType::Cube, true, false,false)); //AIR
	BlockTable.push_back(BlockInfo({ 0.f,0.f }, { 0.2f,0.6f }, { 0.6f,0.f }, BlockModelType::Cube, false, true)); //Grass
	BlockTable.push_back(BlockInfo({ 0.2f,0.f }, BlockModelType::Cube, false, true,true)); //Ore
	BlockTable.push_back(BlockInfo({ 0.4f,0.f }, BlockModelType::Cube, false, true, true)); //Stone
	BlockTable.push_back(BlockInfo({ 0.6f,0.f }, BlockModelType::Cube, false, true, true)); //Dirt
	BlockTable.push_back(BlockInfo({ 0.8f,0.f }, BlockModelType::Cube, false, false, true,10)); //Wood
	BlockTable.push_back(BlockInfo({ 0.8f,0.4f }, BlockModelType::X, false, false, true)); //Rose
	BlockTable.push_back(BlockInfo({ 0.2f,0.2f }, BlockModelType::Cube, false, true, true)); //Sand


	
}

void Game::Update(double dt)
{
	world.TickWorld(dt);
}
