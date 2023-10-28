#pragma once
#include "ITerrainGenerator.h"
class BasicTerrainGenerator : public ITerrainGenerator {
	void generateTerrain(std::shared_ptr<ChunkColumn> chunk)override;


};


