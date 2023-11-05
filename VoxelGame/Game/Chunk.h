#pragma once
#include "../Renderer/Mesh.h"
#include "../Game/FaceBuilder.h"
#include "Util.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <mutex>
#include <unordered_set>
#include <glm/gtx/hash.hpp>
class ChunkManager;
class Chunk {
	std::shared_ptr<ChunkManager> m_chunkManager;
public:
	std::mutex blockMutex;
	std::mutex MeshMutex;

	Chunk(glm::ivec3 pos, std::shared_ptr<ChunkManager> chunkManager);
	glm::ivec3 m_ChunkPos;
		Mesh& getMesh() { return m_ChunkSolidMesh; };
	void GenerateMesh();
	void GenerateLightmap();




	static std::shared_ptr<Shader>  ChunkSolidShader;
	void setIsGenerated(bool flag) { m_isGenerated = flag; }
	void setIsMeshed(bool flag) { m_isMeshed = flag; m_ChunkSolidMesh.setReadyForDraw(flag); }
	void setIsGPU_BufferOutdated(bool flag) { m_isGPU_BufferOutdated = flag; }



	bool isMeshed() { return m_isMeshed; }
	bool isDirty() { return m_isDirty; }
	bool isGPU_BufferOutdated() { return m_isGPU_BufferOutdated; }

	void setIsDirty(bool flag) { m_isDirty=flag; }
	bool hasTransparentBlocks() { return m_hasTransparentBlocks; }
	void setBlock(BlockName Block,int index );
	void setBlock(BlockName Block, glm::vec3 Position);

	unsigned int& getBlock(int index);
	unsigned int& getBlock(glm::vec3 Position);

	int getBlockVectorSize() { return blocks.size(); }

private:
	std::unordered_set<glm::vec3> LightPropagationMarkSet;
	void PropagateLight(glm::vec3 Pos, int strength);
	std::unordered_map<glm::vec3, int> lightSources;
	std::vector<unsigned int> blocks;
	std::vector<char> lightLevels;
	std::vector<char> sunLightLevels;
	bool isValidPosition(glm::vec3 pos);
	bool isSolidBlock(glm::vec3 pos);
	bool m_hasTransparentBlocks = false;
	bool m_isGenerated = false;
	bool m_isDirty = true; //Means that the mesh doesnt match the blocks vector

	bool m_isMeshed = false; //is meshing complete, is the Mesh ready to be drawn
	bool m_isGPU_BufferOutdated = true; // after meshing is complete we have to upload the buffer to the GPU FROM THE MAIN THREAD
	// this flag tells us wether the buffer on teh GPU is outdated




	Mesh m_ChunkSolidMesh;

};
