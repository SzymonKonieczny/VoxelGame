#pragma once
#include "ITerrainGenerator.h"
class ChunkManager;
class TerrainGeneratorTest : public ITerrainGenerator{
public:
	TerrainGeneratorTest(std::shared_ptr<ChunkManager> ChunkManagerRef) : ITerrainGenerator(ChunkManagerRef)
	{}
	 void generateTerrain(std::shared_ptr<ChunkColumn> chunk)override;

};