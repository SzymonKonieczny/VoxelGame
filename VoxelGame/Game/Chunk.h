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
	glm::ivec3 m_ChunkPos;
	
	Mesh& getMesh() { return m_ChunkSolidMesh; };
	void GenerateMesh()
	{

		for (int i = 0; i< blocks.size(); i++)
		{

			glm::vec3 pos = IndexToVec3(i);
			if (!isSolidBlock(pos + glm::vec3(1.f, 0.f, 0.f)))
				FaceBuilder::BuildFace(m_ChunkSolidMesh, IndexToVec3(i), BlockFace::EAST, { blocks[i] / (float)5, blocks[i] / (float)5 });
			if (!isSolidBlock(pos + glm::vec3(-1.f, 0.f, 0.f)))
				FaceBuilder::BuildFace(m_ChunkSolidMesh, IndexToVec3(i), BlockFace::WEST, { blocks[i] / (float)5, blocks[i] / (float)5 });
			if (!isSolidBlock(pos + glm::vec3(0.f, 0.f, -1.f)))
				FaceBuilder::BuildFace(m_ChunkSolidMesh, IndexToVec3(i), BlockFace::SOUTH, { blocks[i] / (float)5, blocks[i] / (float)5 });
			if (!isSolidBlock(pos + glm::vec3(0.f, 0.f, 1.f)))
				FaceBuilder::BuildFace(m_ChunkSolidMesh, IndexToVec3(i), BlockFace::NORTH, { blocks[i] / (float)5, blocks[i] / (float)5 });
			if (!isSolidBlock(pos + glm::vec3(0.f, 1.f, 0.f)))
				FaceBuilder::BuildFace(m_ChunkSolidMesh, IndexToVec3(i), BlockFace::UP, { blocks[i] / (float)5, blocks[i] / (float)5 });
			if (!isSolidBlock(pos + glm::vec3(0.f, -1.f, 0.f)))
				FaceBuilder::BuildFace(m_ChunkSolidMesh, IndexToVec3(i), BlockFace::DOWN, { blocks[i] / (float)5, blocks[i] / (float)5 });

		}

	}
	std::vector<unsigned int> blocks;
	static std::shared_ptr<Shader>  ChunkSolidShader;
private:
	bool isValidPosition(glm::vec3 pos);
	bool isSolidBlock(glm::vec3 pos);
	glm::vec3 IndexToVec3(int i);
	int Vec3ToIndex(glm::vec3 pos);
	bool hasTransparentBlocks = false;
	bool isGenerated = false;
	Mesh m_ChunkSolidMesh;

};
