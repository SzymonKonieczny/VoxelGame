#pragma once
#include "../Renderer/Mesh.h"
#include "../Game/FaceBuilder.h"

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
	
	Mesh& getMesh() { return m_ChunkSolidMesh; };
	void GenerateMesh();
	std::vector<unsigned int> blocks;
	static std::shared_ptr<Shader>  ChunkSolidShader;
private:
	glm::vec3 IndexToVec3(int i);
	int Vec3ToIndex(glm::vec3 pos);
	bool hasTransparentBlocks = false;
	bool isGenerated = false;
	Mesh m_ChunkSolidMesh;
	glm::ivec3 m_ChunkPos;

};
