#include "Chunk.h"
std::shared_ptr<Shader>  ChunkSolidShader;
Chunk::Chunk(glm::ivec3 pos) : m_ChunkPos(pos)
{
	BufferLayout ChunkSolidLayout = {
		{ShaderDataType::Float3,"chunkPos"},
		{ShaderDataType::Float2,"TextureCoord"},
		{ShaderDataType::Float3,"Color"}
	};
	m_ChunkSolidMesh.GetVertexArray().SetLayout(ChunkSolidLayout);
	m_ChunkSolidMesh.SetShader(Chunk::ChunkSolidShader);


	blocks = {0,1,1,1,1};
}

void Chunk::GenerateMesh()
{
}
