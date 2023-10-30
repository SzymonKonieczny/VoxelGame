#pragma once
#include "Global.h"
#include "ChunkColumn.h"
class ChunkManager;
class ITerrainGenerator {
	std::shared_ptr<ChunkManager> chunkManager;
public:
	ITerrainGenerator(std::shared_ptr<ChunkManager> chunkManagerRef) : chunkManager(chunkManagerRef){};
	virtual void generateTerrain(std::shared_ptr<ChunkColumn> chunkColumn)=0;
	virtual void addIcing(std::shared_ptr<ChunkColumn> chunkColumn) = 0;
	//virtual void addDecoration(std::shared_ptr<ChunkColumn> chunk) = 0;
	//virtual void generateFeatures(std::shared_ptr<ChunkColumn> chunk) = 0;


};





