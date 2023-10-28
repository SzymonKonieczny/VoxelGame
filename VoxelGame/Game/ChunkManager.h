#pragma once
#include "ChunkColumn.h"
#include "TerrainGeneratorTest.h"
#include <map>
#include <unordered_set>

#include <glm/gtx/hash.hpp>
#include <queue>
#include <thread>
#include "BlockInfo.h"
class ChunkManager{
public:
	ChunkManager(): Generator(new TerrainGeneratorTest()) 
	{
		
	
	}
	
	void SetBlockAtPosition(glm::vec3 Position, BlockName name);

	void GenerateChunksFromQueue(int amount);
	void MeshChunksFromQueue(int amount);

	void AsyncGenerateChunks(std::list<glm::ivec2> List, bool& isChunkGenerationThreadDoneFlag);
	void AsyncMeshChunks(std::list<glm::ivec3> List, bool& isChunkMeshThreadDoneFlag);

	bool isChunkGenerationThreadDone=true;
	bool isChunkMeshThreadDone=true;

	void UpdateLoadedChunkMap(glm::vec2 CenterPoint);
	void AddToMeshQueue(glm::ivec3 Coord);

	std::unordered_map<glm::ivec2,std::shared_ptr<ChunkColumn>> ChunkMap; // change it into shared ptr to ChunkColumn
	std::queue<glm::ivec2> ChunksGenerationQueue;
	std::queue<glm::ivec3> ChunksMeshingQueue;
	std::unordered_set<glm::ivec3> ChunksInMeshQueue;


	std::shared_ptr<ITerrainGenerator> Generator;
	std::unordered_map<glm::ivec2, std::shared_ptr<ChunkColumn>>& getChunks() { return ChunkMap; }
};
