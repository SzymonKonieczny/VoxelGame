#pragma once
#include "Chunk.h"
#include "Global.h"
#include "BlockInfo.h"
#include <mutex>	
class ChunkManager;
class ChunkColumn {
	std::shared_ptr<ChunkManager> m_chunkManager;
public:
	ChunkColumn(glm::ivec2 Pos, std::shared_ptr<ChunkManager> chunkManager) : m_Position(Pos), m_chunkManager(chunkManager){
		for (int i = 0; i < ChunksInColumn; i++) {
			m_Chunks.emplace_back(new Chunk(glm::ivec3(Pos.x, i, Pos.y), m_chunkManager));
		}
	}
	std::shared_ptr<Chunk>& getChunk(int index) {
		return m_Chunks[index];
	}
	
	BlockName getBlockInColumn(glm::vec3 Pos) 
	{
		int chunkIndex = Pos.y / ChunkSize;
		m_Chunks[chunkIndex]->blockMutex.lock();
		BlockName name = (BlockName)m_Chunks[chunkIndex]->blocks[Util::Vec3ToIndex({ Pos.x,(int)Pos.y % ChunkSize,Pos.z })];
		m_Chunks[chunkIndex]->blockMutex.unlock();
		return name;

	}
	void setBlockInColumn(glm::vec3 Pos, BlockName block) 
	{

		int chunkIndex = Pos.y / ChunkSize;
		m_Chunks[chunkIndex]->blockMutex.lock();
		m_Chunks[chunkIndex]->blocks[Util::Vec3ToIndex({ Pos.x,(int)Pos.y % ChunkSize,Pos.z })] = (unsigned int)block;
		m_Chunks[chunkIndex]->blockMutex.unlock();


	}
	glm::ivec2 m_Position;
	std::vector<std::shared_ptr<Chunk>>  m_Chunks;
};


