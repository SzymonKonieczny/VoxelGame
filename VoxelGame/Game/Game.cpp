#include "Game.h"
int Game::CHUNK_SIZE = 16;
std::shared_ptr<Texture> Game::BlockTextureAtlas;

void Game::Init()
{
	//BlockTextureAtlas.reset(new Texture("Game/Textures/Atlas.png"));
	Chunk::ChunkSolidShader.reset(new Shader("Game/Shaders/ChunkShader.vert", "Game/Shaders/ChunkShader.frag"));

	
}

void Game::Update()
{
}
