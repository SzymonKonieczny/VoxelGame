#pragma once
#include "ITerrainGenerator.h"
class ChunkManager;

class BasicTerrainGenerator : public ITerrainGenerator {
public:
	BasicTerrainGenerator(std::shared_ptr<ChunkManager> ChunkManagerRef) : ITerrainGenerator(ChunkManagerRef)
	{}
	void generateTerrain(std::shared_ptr<ChunkColumn> chunkColumn)override;

	// Inherited via ITerrainGenerator
	void addIcing(std::shared_ptr<ChunkColumn> chunkColumn) override;

};


