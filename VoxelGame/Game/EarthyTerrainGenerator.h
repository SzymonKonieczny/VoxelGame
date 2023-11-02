
#pragma once
#include "ITerrainGenerator.h"
#include "Biomes/PlainsBiome.h"
#include "Biomes/DesertBiome.h"

class EarthyTerrainGenerator : public ITerrainGenerator {
	// Inherited via ITerrainGenerator
public:
	PlainsBiome Plains;
	DesertBiome Desert;
	EarthyTerrainGenerator(std::shared_ptr<ChunkManager> ChunkManagerRef) : ITerrainGenerator(ChunkManagerRef) {};
	virtual void generateTerrain(std::shared_ptr<ChunkColumn> chunkColumn) override;
	void generateCaves(std::shared_ptr<ChunkColumn>& chunkColumn);
};
