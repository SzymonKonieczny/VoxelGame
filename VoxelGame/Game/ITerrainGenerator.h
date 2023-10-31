#pragma once
#include "Global.h"
#include "ChunkColumn.h"
class ChunkManager;
class ITerrainGenerator {
public:
	std::shared_ptr<ChunkManager> chunkManager;
	ITerrainGenerator(std::shared_ptr<ChunkManager> chunkManagerRef) : chunkManager(chunkManagerRef){};
	virtual void generateTerrain(std::shared_ptr<ChunkColumn> chunkColumn)=0;


};





