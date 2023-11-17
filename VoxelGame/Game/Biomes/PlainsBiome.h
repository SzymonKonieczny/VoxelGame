#pragma once
#include "IBiome.h"

class PlainsBiome : public IBiome {
public:
		int BaseGround =90;
		int Variation = 60;

	PlainsBiome() {
		topToBottomSpecialBlocks;

		topToBottomSpecialBlocks.push(BlockName::Grass);
		topToBottomSpecialBlocks.push(BlockName::Dirt);
		topToBottomSpecialBlocks.push(BlockName::Dirt);
		topToBottomSpecialBlocks.push(BlockName::Dirt);
	}
	std::queue<BlockName> topToBottomSpecialBlocks;

	// Inherited via IBiome
	virtual void generateLandmass(std::shared_ptr<ChunkColumn> chunkColumn, std::shared_ptr<ChunkManager> chunkManager) override;
	virtual void addIcing(std::shared_ptr<ChunkColumn> chunkColumn, std::shared_ptr<ChunkManager> chunkManager) override;
	virtual void addDecoration(std::shared_ptr<ChunkColumn> chunk, std::shared_ptr<ChunkManager> chunkManager) override;
	virtual void generateFeatures(std::shared_ptr<ChunkColumn> chunk, std::shared_ptr<ChunkManager> chunkManager) override;
	virtual void generateJustHeightmap(std::shared_ptr<ChunkColumn> chunkColumn, std::vector<float>& Output) override;
	virtual void addIcingRow(std::shared_ptr<ChunkColumn> chunkColumn, std::shared_ptr<ChunkManager> chunkManager, glm::vec2 LocCoords) override;
	virtual void addDecorationRow(std::shared_ptr<ChunkColumn> chunk, std::shared_ptr<ChunkManager> chunkManager, glm::vec2 LocCoords) override;

};