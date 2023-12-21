#pragma once
#include "IBiome.h"

class FallForestBiome : public IBiome {
public:
	int BaseGround = 20;
	int Variation = 80;
	FallForestBiome(std::string encodedTreeForTerraingGeneration) : IBiome(encodedTreeForTerraingGeneration) {
		topToBottomSpecialBlocks;

		topToBottomSpecialBlocks.push(BlockName::Sand);
		topToBottomSpecialBlocks.push(BlockName::Sand);
		topToBottomSpecialBlocks.push(BlockName::Sand);
	}
	std::queue<BlockName> topToBottomSpecialBlocks;

	// Inherited via IBiome
	virtual void generateLandmass(std::shared_ptr<ChunkColumn> chunkColumn, std::shared_ptr<ChunkManager> chunkManager) override;
	virtual void addIcing(std::shared_ptr<ChunkColumn> chunkColumn, std::shared_ptr<ChunkManager> chunkManager) override;
	virtual void addDecoration(std::shared_ptr<ChunkColumn> chunk, std::shared_ptr<ChunkManager> chunkManager) override;
	virtual void generateFeatures(std::shared_ptr<ChunkColumn> chunk, std::shared_ptr<ChunkManager> chunkManager) override;
	virtual void addIcingRow(std::shared_ptr<ChunkColumn> chunkColumn, std::shared_ptr<ChunkManager> chunkManager, glm::vec2 LocCoords)override;
	virtual void addDecorationRow(std::shared_ptr<ChunkColumn> chunk, std::shared_ptr<ChunkManager> chunkManager, glm::vec2 LocCoords) override;
	// Inherited via IBiome
	virtual void generateJustHeightmap(std::shared_ptr<ChunkColumn> chunkColumn, std::vector<float>& Output) override;

	// Inherited via IBiome
	virtual void getHeightAtWorldCoords(glm::vec2 WorldPos, float* Output) override;
};