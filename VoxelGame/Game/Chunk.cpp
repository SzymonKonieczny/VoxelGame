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
	m_ChunkSolidMesh.AddUniform("modelMatrix",UniformType::Mat4);
	m_ChunkSolidMesh.AddUniform("viewProjMatrix", UniformType::Mat4);
	m_ChunkSolidMesh.AddUniform("tex0", UniformType::Int);

	m_ChunkSolidMesh.updateUniform("tex0", 0);
	m_ChunkSolidMesh.updateUniform("modelMatrix", glm::translate(glm::mat4(1.0), glm::vec3(pos.x * Game::CHUNK_SIZE,
		pos.y * Game::CHUNK_SIZE, pos.z * Game::CHUNK_SIZE)));


	m_ChunkSolidMesh.SetTexture(Game::BlockTextureAtlas);
	m_ChunkSolidMesh.hasTexture = true;

	blocks = {0,1,1,1,1};
}

void Chunk::GenerateMesh()
{
	std::vector<float>  verts= {
		// Pos					UV				Color
		0.f,0.f,0.f ,		0.f,0.f,		1.f,1.f,1.f,
		1.f,0.f,0.f ,		1.f,0.f,		1.f,1.f,1.f,
		1.f,1.f,0.f ,		1.f,1.f,		1.f,1.f,1.f,
							
		1.f,1.f,0.f ,		1.f,1.f,		1.f,1.f,1.f,
		0.f,1.f,0.f ,		0.f,1.f,		1.f,1.f,1.f,
		0.f,0.f,0.f ,		0.f,0.f,		1.f,1.f,1.f
	};
	
	FaceBuilder::BuildFace(m_ChunkSolidMesh, {}, BlockFace::NORTH);
	for (auto i : verts) {
		m_ChunkSolidMesh.Verticies.push_back(i);

	}
}
