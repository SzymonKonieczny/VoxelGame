#pragma once
#include "ITerrainGenerator.h"
#include "PlainsBiome.h"
class EarthyTerrainGenerator : public ITerrainGenerator {
	// Inherited via ITerrainGenerator
	PlainsBiome Plains;
	EarthyTerrainGenerator(std::shared_ptr<ChunkManager> ChunkManagerRef) : ITerrainGenerator(ChunkManagerRef) {};
	virtual void generateTerrain(std::shared_ptr<ChunkColumn> chunkColumn) override;
};

