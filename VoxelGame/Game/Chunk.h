#pragma once
#include "../Renderer/Mesh.h"
#include <glm/glm.hpp>

class Chunk {
public:
	Chunk(glm::ivec3 pos);

private:
	bool hasTransparentBlocks = false;
	bool isGenerated = false;
	Mesh m_ChunkMesh;
	glm::ivec3 m_ChunkPos;

};
