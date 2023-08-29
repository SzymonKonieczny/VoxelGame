#pragma once
#include "Chunk.h"
#include "TerrainGeneratorTest.h"
class ChunkManager{
public:
	ChunkManager(): Generator(new TerrainGeneratorTest()) 
	{
		
	
	}
	void GenWorld() {
		for (int i = 0; i < 5; i++)
			for (int k = 0; k < 5; k++)
			{
				TestChunks.push_back(Chunk({ i, 0, k }));
			}
		for (auto& chunk : TestChunks)
		{
			Generator->generateTerrain(chunk);
			chunk.GenerateMesh();
		}
	}
	std::vector<Chunk> TestChunks;
	ITerrainGenerator* Generator;
	std::vector<Chunk>& getChunks() { return TestChunks; }
};
