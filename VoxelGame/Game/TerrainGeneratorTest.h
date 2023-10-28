#pragma once
#include "ITerrainGenerator.h"
class TerrainGeneratorTest : public ITerrainGenerator{
	 void generateTerrain(std::shared_ptr<ChunkColumn> chunk)override;

};