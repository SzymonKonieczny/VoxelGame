#pragma once
#include "Chunk.h"
#include "Global.h"
#include "BlockInfo.h"
#include <mutex>	
class ChunkColumn {

public:
	ChunkColumn(glm::ivec2 Pos) : m_Position(Pos) {
		for (int i = 0; i < ChunksInColumn; i++) {
			m_Chunks.emplace_back(new Chunk(glm::ivec3(Pos.x, i, Pos.y)));
		}
	}
	std::shared_ptr<Chunk>& getChunk(int index) {
		return m_Chunks[index];
	}

	void setBlockInColumn(glm::vec3 Pos, BlockName block) ///thread unsafe, use mutexes outside!
	{
		int chunkIndex = Pos.y / ChunkSize;

		m_Chunks[chunkIndex]->blocks[Util::Vec3ToIndex({ Pos.x,(int)Pos.y % ChunkSize,Pos.z })] = (unsigned int)block;
	

	}
	glm::ivec2 m_Position;
	std::vector<std::shared_ptr<Chunk>>  m_Chunks;
};


