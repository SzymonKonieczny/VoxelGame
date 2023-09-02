#pragma once
#include "Chunk.h"
#include "Global.h"
class ChunkColumn {
public:
	ChunkColumn(glm::ivec2 Pos) : m_Position(Pos) {
		for (int i = 0; i < ChunksInColumn; i++) {
			m_Chunks.emplace_back((glm::ivec3(Pos.x, i, Pos.y)));
		}
	}

	glm::ivec2 m_Position;
	std::vector<Chunk>  m_Chunks;
};
