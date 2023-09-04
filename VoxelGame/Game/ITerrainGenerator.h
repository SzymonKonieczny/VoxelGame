#pragma once
#include "Global.h"
#include "ChunkColumn.h"
class ITerrainGenerator {
public:
	virtual void generateTerrain(std::shared_ptr<Chunk> chunk)=0;
};
