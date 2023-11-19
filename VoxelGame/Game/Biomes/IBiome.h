#pragma once

#include "../Global.h"
#include "../ChunkColumn.h"
#include <queue>
class ChunkManager;

class IBiome {
public:
	virtual void generateLandmass(std::shared_ptr<ChunkColumn> chunkColumn, std::shared_ptr<ChunkManager> chunkManager) = 0;
	virtual void addIcing(std::shared_ptr<ChunkColumn> chunkColumn, std::shared_ptr<ChunkManager> chunkManager) = 0;
	virtual void addDecoration(std::shared_ptr<ChunkColumn> chunk, std::shared_ptr<ChunkManager> chunkManager) = 0;
	virtual void addIcingRow(std::shared_ptr<ChunkColumn> chunkColumn, std::shared_ptr<ChunkManager> chunkManager,glm::vec2 LocCoords) = 0;
	virtual void addDecorationRow(std::shared_ptr<ChunkColumn> chunk, std::shared_ptr<ChunkManager> chunkManager, glm::vec2 LocCoords) = 0;
	virtual void generateFeatures(std::shared_ptr<ChunkColumn> chunk, std::shared_ptr<ChunkManager> chunkManager) = 0;
	virtual void generateJustHeightmap(std::shared_ptr<ChunkColumn> chunkColumn, std::vector<float>& Output) = 0;
	virtual void getHeightAtWorldCoords(glm::vec2 WorldPos, float* Output) = 0;

};