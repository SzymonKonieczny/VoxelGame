#pragma once
#include "ChunkColumn.h"
#include "TerrainGeneratorTest.h"
#include <map>
#include <glm/gtx/hash.hpp>
#include <queue>
#include <thread>

class ChunkManager{
public:
	ChunkManager(): Generator(new TerrainGeneratorTest()) 
	{
		
	
	}
	
	void GenerateChunksFromQueue(int amount);
	void MeshChunksFromQueue(int amount);

	void AsyncGenerateChunks(std::list<glm::ivec2> List, bool& isChunkGenerationThreadDoneFlag);
	void AsyncMeshChunks(std::list<glm::ivec2> List, bool& isChunkMeshThreadDoneFlag);

	bool isChunkGenerationThreadDone=true;
	bool isChunkMeshThreadDone=true;

	void UpdateLoadedChunkMap(glm::vec2 CenterPoint);
	void AddToMeshQueue(glm::ivec2 Coord);

	std::unordered_map<glm::ivec2,ChunkColumn> ChunkMap;
	std::queue<glm::ivec2> ChunksGenerationQueue;
	std::queue<glm::ivec2> ChunksMeshingQueue;

	std::shared_ptr<ITerrainGenerator> Generator;
	std::unordered_map<glm::ivec2, ChunkColumn>& getChunks() { return ChunkMap; }
};
