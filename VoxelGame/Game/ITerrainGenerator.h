#pragma once
#include "Global.h"
#include "ChunkCol.h"
class ITerrainGenerator {
public:
	virtual void generateTerrain(Chunk& chunk)=0;
};
