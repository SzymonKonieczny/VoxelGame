#include "Chunk.h"
#include "Game.h"
std::shared_ptr<Shader>  Chunk::ChunkSolidShader;
Chunk::Chunk(glm::ivec3 pos) : m_ChunkPos(pos)
{
	BufferLayout ChunkSolidLayout = {
		{ShaderDataType::Float3,"aPos"},
		{ShaderDataType::Float2,"aTexCoord"},
		{ShaderDataType::Float3,"aCol"}
	};
	m_ChunkSolidMesh.GetVertexArray().SetLayout(ChunkSolidLayout);
	m_ChunkSolidMesh.SetShader(Chunk::ChunkSolidShader);
	m_ChunkSolidMesh.AddUniform("modelMatrix", UniformType::Mat4);
	m_ChunkSolidMesh.AddUniform("viewProjMatrix", UniformType::Mat4);
	m_ChunkSolidMesh.AddUniform("tex0", UniformType::Int);

	m_ChunkSolidMesh.updateUniform("tex0", 0);
	m_ChunkSolidMesh.updateUniform("modelMatrix", glm::translate(glm::mat4(1.0), glm::vec3(pos.x * Game::CHUNK_SIZE,
		pos.y * Game::CHUNK_SIZE, pos.z * Game::CHUNK_SIZE)));


	m_ChunkSolidMesh.SetTexture(Game::BlockTextureAtlas);
	m_ChunkSolidMesh.hasTexture = true;

}

void Chunk::GenerateMesh()
{

	for (int i =0; i< blocks.size(); i++)
	{
		glm::vec3 pos = IndexToVec3(i);
		if(isSolidBlock(pos+glm::vec3(1.f,0.f,0.f)))
		FaceBuilder::BuildFace(m_ChunkSolidMesh,IndexToVec3(i) ,BlockFace::EAST);
		if (isSolidBlock(pos + glm::vec3(-1.f, 0.f, 0.f)))
			FaceBuilder::BuildFace(m_ChunkSolidMesh,IndexToVec3(i) , BlockFace::WEST);
		if (isSolidBlock(pos + glm::vec3(0.f, 0.f, -1.f)))
			FaceBuilder::BuildFace(m_ChunkSolidMesh,IndexToVec3(i) , BlockFace::SOUTH);
		if (isSolidBlock(pos + glm::vec3(0.f, 0.f, 1.f)))
			FaceBuilder::BuildFace(m_ChunkSolidMesh,IndexToVec3(i) , BlockFace::NORTH);
		if (isSolidBlock(pos + glm::vec3(0.f, 1.f, 0.f)))
			FaceBuilder::BuildFace(m_ChunkSolidMesh, IndexToVec3(i), BlockFace::UP);
		if (isSolidBlock(pos + glm::vec3(0.f, -1.f, 0.f)))
			FaceBuilder::BuildFace(m_ChunkSolidMesh, IndexToVec3(i), BlockFace::DOWN);

	}

}

bool Chunk::isValidPosition(glm::vec3 pos)
{

	//if (Vec3ToIndex(pos) > blocks.size()) return false;
	if (pos.x < 0 || pos.x > Game::CHUNK_SIZE) return false;
	if (pos.y < 0 || pos.y > Game::CHUNK_SIZE) return false;
	if (pos.z < 0 || pos.z > Game::CHUNK_SIZE) return false;

	return true;
}

bool Chunk::isSolidBlock(glm::vec3 pos)
{
	//if (!isValidPosition(pos)) return false;
	return true;
}

glm::vec3 Chunk::IndexToVec3(int i)
{
	//order is as follows
	/*
	^
	|
  z	|
	|ChunkSize+1,ChunkSize+2 ...
	|0,1,2,3,4,5, ... ChunkSize
	---------------->
		x

	*/
	int remainder = 0;
	int y = i / (Game::CHUNK_SIZE* Game::CHUNK_SIZE);
	remainder = i% (Game::CHUNK_SIZE * Game::CHUNK_SIZE);
	int z = remainder / ( Game::CHUNK_SIZE);
	remainder = remainder % (Game::CHUNK_SIZE);

	int x = remainder;

	return glm::vec3(x,y,z);
}

int Chunk::Vec3ToIndex(glm::vec3 pos)
{ 
	return Game::CHUNK_SIZE * Game::CHUNK_SIZE * pos.y + Game::CHUNK_SIZE * pos.z + pos.x;;
}
