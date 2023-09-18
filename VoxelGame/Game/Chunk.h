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
	bool isDirty() { return m_isDirty; }
	void setIsDirty(bool flag) { m_isDirty=flag; }


private:
	bool isValidPosition(glm::vec3 pos);
	bool isSolidBlock(glm::vec3 pos);
	bool m_hasTransparentBlocks = false;
	bool m_isGenerated = false;
	bool m_isDirty = true; //Means that the mesh doesnt match the blocks vector

	bool m_isMeshed = false; //is meshing complete, is the Mesh ready to be drawn

	Mesh m_ChunkSolidMesh;

};
