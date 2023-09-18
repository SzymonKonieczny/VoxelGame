#pragma once
#include "Chunk.h"
#include "Global.h"
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
	glm::ivec2 m_Position;
	std::vector<std::shared_ptr<Chunk>>  m_Chunks;
};
