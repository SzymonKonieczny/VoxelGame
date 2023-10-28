#pragma once
#include "ITerrainGenerator.h"
class TerrainGeneratorTest : public ITerrainGenerator{
	 void generateTerrain(ChunkColumn& chunk)override;

};