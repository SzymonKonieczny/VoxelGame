#include "Game.h"
int Game::CHUNK_SIZE = 16;
std::shared_ptr<Texture> Game::BlockTextureAtlas;

void Game::Init()
{
	BlockTextureAtlas.reset(new Texture("Game/Textures/Atlas.png"));
	Chunk::ChunkSolidShader.reset(new Shader("Game/Shaders/ChunkSolid.vert", "Game/Shaders/ChunkSolid.frag"));
	
	Chunk::ChunkSolidShader->AddUniform("ModelMatrix", UniformType::Mat4);
}

void Game::Update()
{
}
