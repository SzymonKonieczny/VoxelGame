
#include "Chunk.h"
#include "Game.h"
std::shared_ptr<Shader>  Chunk::ChunkSolidShader;
Chunk::Chunk(glm::ivec3 pos, std::shared_ptr<ChunkManager> chunkManager) : m_ChunkPos(pos), m_chunkManager(chunkManager)
{
	blocks.resize(ChunkSize* ChunkSize* ChunkSize);
	lightLevels.resize(ChunkSize * ChunkSize * ChunkSize);

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
	m_ChunkSolidMesh.Verticies.clear();
	for (int i = 0; i < blocks.size(); i++)
	{

		const BlockInfo& blockInfo = BlockTable[blocks[i]];
		if (blockInfo.isTransparent) continue;
		glm::vec3 pos = Util::IndexToVec3(i);
		
		switch (blockInfo.ModelType) {
		case BlockModelType::Cube:
			if (!isSolidBlock(pos + glm::vec3(1.f, 0.f, 0.f)))
				FaceBuilder::BuildFace(m_ChunkSolidMesh, Util::IndexToVec3(i), BlockFace::EAST, blockInfo.UVside,lightLevels[i]);
			if (!isSolidBlock(pos + glm::vec3(-1.f, 0.f, 0.f)))
				FaceBuilder::BuildFace(m_ChunkSolidMesh, Util::IndexToVec3(i), BlockFace::WEST, blockInfo.UVside, lightLevels[i]);
			if (!isSolidBlock(pos + glm::vec3(0.f, 0.f, -1.f)))
				FaceBuilder::BuildFace(m_ChunkSolidMesh, Util::IndexToVec3(i), BlockFace::SOUTH, blockInfo.UVside, lightLevels[i]);
			if (!isSolidBlock(pos + glm::vec3(0.f, 0.f, 1.f)))
				FaceBuilder::BuildFace(m_ChunkSolidMesh, Util::IndexToVec3(i), BlockFace::NORTH, blockInfo.UVside, lightLevels[i]);
			if (!isSolidBlock(pos + glm::vec3(0.f, 1.f, 0.f)))
				FaceBuilder::BuildFace(m_ChunkSolidMesh, Util::IndexToVec3(i), BlockFace::UP, blockInfo.UVtop, lightLevels[i]);
			if (!isSolidBlock(pos + glm::vec3(0.f, -1.f, 0.f)))
				FaceBuilder::BuildFace(m_ChunkSolidMesh, Util::IndexToVec3(i), BlockFace::DOWN, blockInfo.UVbottom, lightLevels[i]);

			break;
		case BlockModelType::X:
			FaceBuilder::BuildFace(m_ChunkSolidMesh, Util::IndexToVec3(i), BlockFace::X1, blockInfo.UVside, lightLevels[i]);
			FaceBuilder::BuildFace(m_ChunkSolidMesh, Util::IndexToVec3(i), BlockFace::X2, blockInfo.UVside, lightLevels[i]);

			break;
		}
		
	}

	//m_ChunkSolidMesh.UpdateObjectsOnGPU(); meshing happens on another thread, cant use GLcalls

	setIsGPU_BufferOutdated(true);
	setIsMeshed(true);
	setIsDirty(false);
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
	BlockName block;
	block = BlockName::Air;
	if (!isValidPosition(pos)) {
		if (pos.x > 15)
			block = m_chunkManager->GetBlockAtPosition(Util::LocPosAndChunkPosToWorldPos({ 0,pos.y,pos.z }, m_ChunkPos + glm::ivec3(1,0,0) ));
		if (pos.x <0)
			block = m_chunkManager->GetBlockAtPosition(Util::LocPosAndChunkPosToWorldPos({ 15,pos.y,pos.z }, m_ChunkPos + glm::ivec3(-1, 0, 0)));
		if (pos.z > 15)
			block = m_chunkManager->GetBlockAtPosition(Util::LocPosAndChunkPosToWorldPos({ pos.x,pos.y,0 }, m_ChunkPos + glm::ivec3(0, 0, 1)));
		if (pos.z < 0)
			block = m_chunkManager->GetBlockAtPosition(Util::LocPosAndChunkPosToWorldPos({ pos.x,pos.y,15 }, m_ChunkPos + glm::ivec3(0, 0, -1)));
		if (pos.y > 15)
			block = m_chunkManager->GetBlockAtPosition(Util::LocPosAndChunkPosToWorldPos({ pos.x,0,pos.z }, m_ChunkPos + glm::ivec3(0, 1, 0)));
		if (pos.y < 0)
			block = m_chunkManager->GetBlockAtPosition(Util::LocPosAndChunkPosToWorldPos({ pos.x,15,pos.z }, m_ChunkPos + glm::ivec3(0, -1, 0)));
	
		return BlockTable[(int)block].isSold;
		return false;
	}
	
	const BlockInfo& info = BlockTable[blocks[Util::Vec3ToIndex(pos)]];
	return info.isSold;
}


