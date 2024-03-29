#pragma once
#include "Chunk.h"
#include "Global.h"
#include "BlockInfo.h"
#include <mutex>	
class ChunkManager;
class ChunkColumn {
	std::shared_ptr<ChunkManager> m_chunkManager;
public:
	unsigned int nrOfRemeshes;

	ChunkColumn(glm::ivec2 Pos, std::shared_ptr<ChunkManager> chunkManager) : m_Position(Pos), m_chunkManager(chunkManager){
		for (int i = 0; i < ChunksInColumn; i++) {
			m_Chunks.emplace_back(new Chunk(glm::ivec3(Pos.x, i, Pos.y), m_chunkManager));
		}
	}
	std::shared_ptr<Chunk>& getChunk(int index) {
		return m_Chunks[index];
	}
	
	std::vector<std::shared_ptr<Chunk>>  m_Chunks;
	glm::ivec2 m_Position;
	BlockName getBlockInColumn(glm::vec3 Pos) 
	{
		int chunkIndex = Pos.y / ChunkSize;
		m_Chunks[chunkIndex]->blockMutex.lock();
		BlockName name = (BlockName)m_Chunks[chunkIndex]->getBlock(Util::Vec3ToIndex({ Pos.x,(int)Pos.y % ChunkSize,Pos.z }));
		m_Chunks[chunkIndex]->blockMutex.unlock();
		return name;

	}
	void setBlockInColumn(glm::vec3 Pos, BlockName block) 
	{

		int chunkIndex = Pos.y / ChunkSize;
		m_Chunks[chunkIndex]->blockMutex.lock();
		m_Chunks[chunkIndex]->setBlock(block, Util::Vec3ToIndex({ Pos.x,(int)Pos.y % ChunkSize,Pos.z }));
		m_Chunks[chunkIndex]->blockMutex.unlock();


	}
};


