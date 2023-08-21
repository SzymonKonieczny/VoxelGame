#pragma once
#include "../Renderer/Mesh.h"
#include <glm/glm.hpp>

class Chunk {
public:
	Chunk(glm::ivec3 pos);
	
	
	void GenerateMesh();
	std::vector<unsigned int> blocks;
	static std::shared_ptr<Shader>  ChunkSolidShader;
private:
	bool hasTransparentBlocks = false;
	bool isGenerated = false;
	Mesh m_ChunkSolidMesh;
	glm::ivec3 m_ChunkPos;

};
