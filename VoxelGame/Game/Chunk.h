#pragma once
#include "../Renderer/Mesh.h"
#include "../Game/FaceBuilder.h"
#include "Util.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
struct chunkVerex {
	glm::vec3 Position;
	glm::vec2 UV;
	glm::vec3 Color;
};

class Chunk {
public:
	Chunk(glm::ivec3 pos);
	glm::ivec3 m_ChunkPos;
	
	Mesh& getMesh() { return m_ChunkSolidMesh; };
	void GenerateMesh();
	
	std::vector<unsigned int> blocks;
	static std::shared_ptr<Shader>  ChunkSolidShader;
	void setIsGenerated(bool flag) { isGenerated = flag; }
private:
	bool isValidPosition(glm::vec3 pos);
	bool isSolidBlock(glm::vec3 pos);
	bool hasTransparentBlocks = false;
	bool isGenerated = false;
	bool isMeshed = false;

	Mesh m_ChunkSolidMesh;

};
