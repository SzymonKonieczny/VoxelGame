#pragma once
#include "Global.h"
#include "ChunkColumn.h"
class ITerrainGenerator {
public:
	virtual void generateTerrain(Chunk& chunk)=0;
};
