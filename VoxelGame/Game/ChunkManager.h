#pragma once
#include "Chunk.h"
#include "TerrainGeneratorTest.h"
#include <list>
class ChunkManager{
public:
	ChunkManager(): Generator(new TerrainGeneratorTest()) 
	{
		
	
	}
	void GenWorld() {
		for (int i = 0; i < 10; i++)
			for (int k = 0; k < 10; k++)
			{
				TestChunks.emplace_back(glm::ivec3( i, 0, k ));
			}
		for (auto& chunk : TestChunks)
		{
			Generator->generateTerrain(chunk);
			chunk.GenerateMesh();
		}
	}
	std::list<Chunk> TestChunks;
	ITerrainGenerator* Generator;
	std::list<Chunk>& getChunks() { return TestChunks; }
};
