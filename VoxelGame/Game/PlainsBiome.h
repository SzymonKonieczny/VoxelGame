#pragma once
#include "IBiome.h"
class PlainsBiome : public IBiome {
public:
	// Inherited via IBiome
	virtual void generateLandmass(std::shared_ptr<ChunkColumn> chunkColumn, std::shared_ptr<ChunkManager> chunkManager) override;
	virtual void addIcing(std::shared_ptr<ChunkColumn> chunkColumn, std::shared_ptr<ChunkManager> chunkManager) override;
	virtual void addDecoration(std::shared_ptr<ChunkColumn> chunk, std::shared_ptr<ChunkManager> chunkManager) override;
	virtual void generateFeatures(std::shared_ptr<ChunkColumn> chunk, std::shared_ptr<ChunkManager> chunkManager) override;
};