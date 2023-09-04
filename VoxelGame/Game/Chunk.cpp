
#include "Chunk.h"
#include "Game.h"
std::shared_ptr<Shader>  Chunk::ChunkSolidShader;
Chunk::Chunk(glm::ivec3 pos) : m_ChunkPos(pos)
{
	blocks.resize(ChunkSize* ChunkSize* ChunkSize);
	//for (auto& block : blocks) block = 2;


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
	m_ChunkSolidMesh.AddUniform("shadowDepthTexture", UniformType::Int);
	m_ChunkSolidMesh.AddUniform("lightSpaceMatrix", UniformType::Mat4);
	
	//m_ChunkSolidMesh.AddUniform("ViewPos", UniformType::Float3);
	//m_ChunkSolidMesh.AddUniform("lightPos", UniformType::Float3);

	



	m_ChunkSolidMesh.updateUniform("shadowDepthTexture", 7); //7 7th texture is reserved for the shadowmap

	m_ChunkSolidMesh.updateUniform("tex0", 0);
	m_ChunkSolidMesh.updateUniform("modelMatrix", glm::translate(glm::mat4(1.0), glm::vec3(pos.x * ChunkSize,
		pos.y * ChunkSize, pos.z * ChunkSize)));


	m_ChunkSolidMesh.SetTexture(0,Game::BlockTextureAtlas);
	m_ChunkSolidMesh.hasTexture = true;

}

void Chunk::GenerateMesh()
{
	MeshMutex.lock();
	setIsMeshed(false);
	for (int i = 0; i < blocks.size(); i++)
	{

		const BlockInfo& blockInfo = BlockTable[blocks[i]];
		if (blockInfo.isTransparent) continue;
		glm::vec3 pos = Util::IndexToVec3(i);
		if (!isSolidBlock(pos + glm::vec3(1.f, 0.f, 0.f)))
			FaceBuilder::BuildFace(m_ChunkSolidMesh, Util::IndexToVec3(i), BlockFace::EAST, blockInfo.UV);
		if (!isSolidBlock(pos + glm::vec3(-1.f, 0.f, 0.f)))
			FaceBuilder::BuildFace(m_ChunkSolidMesh, Util::IndexToVec3(i), BlockFace::WEST, blockInfo.UV);
		if (!isSolidBlock(pos + glm::vec3(0.f, 0.f, -1.f)))
			FaceBuilder::BuildFace(m_ChunkSolidMesh, Util::IndexToVec3(i), BlockFace::SOUTH, blockInfo.UV);
		if (!isSolidBlock(pos + glm::vec3(0.f, 0.f, 1.f)))
			FaceBuilder::BuildFace(m_ChunkSolidMesh, Util::IndexToVec3(i), BlockFace::NORTH, blockInfo.UV);
		if (!isSolidBlock(pos + glm::vec3(0.f, 1.f, 0.f)))
			FaceBuilder::BuildFace(m_ChunkSolidMesh, Util::IndexToVec3(i), BlockFace::UP, blockInfo.UV);
		if (!isSolidBlock(pos + glm::vec3(0.f, -1.f, 0.f)))
			FaceBuilder::BuildFace(m_ChunkSolidMesh, Util::IndexToVec3(i), BlockFace::DOWN, blockInfo.UV);

	}

	m_ChunkSolidMesh.UpdateObjectsOnGPU();
	setIsMeshed(true);
	MeshMutex.unlock();


}

bool Chunk::isValidPosition(glm::vec3 pos)
{

	if (Util::Vec3ToIndex(pos) >= blocks.size() || Util::Vec3ToIndex(pos) < 0) return false;
	if (pos.x < 0 || pos.x >= ChunkSize) return false;
	if (pos.y < 0 || pos.y >= ChunkSize) return false;
	if (pos.z < 0 || pos.z >= ChunkSize) return false;

	return true;
}

bool Chunk::isSolidBlock(glm::vec3 pos)
{
	if (!isValidPosition(pos)) return false;
	
	const BlockInfo& info = BlockTable[blocks[Util::Vec3ToIndex(pos)]];
	return info.isSold;
}


