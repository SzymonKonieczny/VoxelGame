#pragma once
#include "../Renderer/Mesh.h"
#include "../Game/FaceBuilder.h"
#include "Util.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <mutex>
struct chunkVerex {
	glm::vec3 Position;
	glm::vec2 UV;
	glm::vec3 Color;
};

class Chunk {
public:
	std::mutex blockMutex;
	std::mutex MeshMutex;


	Chunk(glm::ivec3 pos);
	glm::ivec3 m_ChunkPos;
		Mesh& getMesh() { return m_ChunkSolidMesh; };
	void GenerateMesh();
	
	std::vector<unsigned int> blocks;
	static std::shared_ptr<Shader>  ChunkSolidShader;
	void setIsGenerated(bool flag) { m_isGenerated = flag; }
	void setIsMeshed(bool flag) { m_isMeshed = flag; m_ChunkSolidMesh.setReadyForDraw(flag); }
	bool isMeshed() { return m_isMeshed; }
private:
	bool isValidPosition(glm::vec3 pos);
	bool isSolidBlock(glm::vec3 pos);
	bool m_hasTransparentBlocks = false;
	bool m_isGenerated = false;
	bool m_isMeshed = false;

	Mesh m_ChunkSolidMesh;

};
