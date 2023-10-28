#pragma once
#include "Global.h"
#include "ChunkColumn.h"
class ITerrainGenerator {
public:
	virtual void generateTerrain(ChunkColumn& chunk)=0;
};
