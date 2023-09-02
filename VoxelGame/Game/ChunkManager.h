#pragma once
#include "ChunkColumn.h"
#include "TerrainGeneratorTest.h"
#include <map>
#include <glm/gtx/hash.hpp>
#include <queue>
class ChunkManager{
public:
	ChunkManager(): Generator(new TerrainGeneratorTest()) 
	{
		
	
	}
	
	void GenerateChunksFromQueue(int amount);
	void UpdateLoadedChunkMap(glm::vec2 CenterPoint);
	std::unordered_map<glm::ivec2,ChunkColumn> ChunkMap;
	std::queue<glm::ivec2> ChunksGenerationQueue;
	std::unique_ptr<ITerrainGenerator> Generator;
	std::unordered_map<glm::ivec2, ChunkColumn>& getChunks() { return ChunkMap; }
};
