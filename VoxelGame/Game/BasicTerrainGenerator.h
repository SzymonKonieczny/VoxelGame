#pragma once
#include "ITerrainGenerator.h"


class BasicTerrainGenerator : ITerrainGenerator {
	void generateTerrain(std::shared_ptr<ChunkColumn> chunk)override;


};


