#pragma once
#include "ITerrainGenerator.h"
#include "Biomes/PlainsBiome.h"
class ChunkManager;

class HeavenTerrainGenerator : public ITerrainGenerator {
public:
	HeavenTerrainGenerator(std::shared_ptr<ChunkManager> ChunkManagerRef) : ITerrainGenerator(ChunkManagerRef)
	{}
	void generateTerrain(std::shared_ptr<ChunkColumn> chunkColumn)override;
	PlainsBiome Plains;
};


