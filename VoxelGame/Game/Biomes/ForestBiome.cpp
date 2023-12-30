#include "ForestBiome.h"
#include <FastNoise/FastNoise.h>
#include "../ChunkManager.h"
void ForestBiome::generateLandmass(std::shared_ptr<ChunkColumn> chunkColumn, std::shared_ptr<ChunkManager> chunkManager)
{
}

void ForestBiome::addIcing(std::shared_ptr<ChunkColumn> chunkColumn, std::shared_ptr<ChunkManager> chunkManager)
{
}

void ForestBiome::addDecoration(std::shared_ptr<ChunkColumn> chunk, std::shared_ptr<ChunkManager> chunkManager)
{
}

void ForestBiome::generateFeatures(std::shared_ptr<ChunkColumn> chunk, std::shared_ptr<ChunkManager> chunkManager)
{
	for (int i = 0; i < 6; i++)
	{
		if(Util::random(1,100) > 30)
			generateTree(glm::vec2(Util::random(1, 15), Util::random(1, 15)), chunk, chunkManager);

	}
}

void ForestBiome::addIcingRow(std::shared_ptr<ChunkColumn> chunkColumn, std::shared_ptr<ChunkManager> chunkManager, glm::vec2 LocCoords)
{
	std::queue<BlockName> topToBottomSpecialBlocksCopy(topToBottomSpecialBlocks);
	for (int y = (chunkColumn->m_Chunks.size() * ChunkSize) - 1; y >= 0; y--)
	{
		if (chunkColumn->getBlockInColumn({ LocCoords.x,y,LocCoords.y }) == BlockName::Stone)
		{
			chunkColumn->setBlockInColumn({ LocCoords.x,y,LocCoords.y }, topToBottomSpecialBlocksCopy.front());
			topToBottomSpecialBlocksCopy.pop();
			if (topToBottomSpecialBlocksCopy.empty()) break;
		}
	}

}

void ForestBiome::addDecorationRow(std::shared_ptr<ChunkColumn> chunkColumn, std::shared_ptr<ChunkManager> chunkManager, glm::vec2 LocCoords)
{
	for (int y = (chunkColumn->m_Chunks.size() * ChunkSize) - 1; y >= 0; y--)
	{
		if (chunkColumn->getBlockInColumn({ LocCoords.x,y,LocCoords.y }) == BlockName::Grass)
		{
			if (Util::random(1, 15) == 1)
				chunkColumn->setBlockInColumn({ LocCoords.x,y + 1,LocCoords.y }, BlockName::Aliceline);
			break;
		}
	}
}

void ForestBiome::generateJustHeightmap(std::shared_ptr<ChunkColumn> chunkColumn, std::vector<float>& Output)
{
}

void ForestBiome::getHeightAtWorldCoords(glm::vec2 WorldPos, float* Output)
{
	FastNoise::SmartNode<> fnGenerator = FastNoise::NewFromEncodedNodeTree(EncodedTree.c_str());

	float temp[MinFastNoiseDim * MinFastNoiseDim];
	fnGenerator->GenUniformGrid2D(temp, WorldPos.x, WorldPos.y,
		MinFastNoiseDim, MinFastNoiseDim, 0.2f, WorldSeed);
	int index = 0;// MinFastNoiseDim * MinFastNoiseDim - 1;
	temp[index] *= Variation;
	temp[index] += BaseGround;
	*Output = temp[index];
}

void ForestBiome::generateTree(glm::vec2 LocCoords, std::shared_ptr<ChunkColumn>& chunkColumn, std::shared_ptr<ChunkManager>& chunkManager)
{
	glm::vec3 WorldPos = { 0,0,0 };
	bool metGrass = false;
	for (int y = (chunkColumn->m_Chunks.size() * ChunkSize) - 1; y >= 0; y--)
	{
		if (chunkColumn->getBlockInColumn({ LocCoords.x,y,LocCoords.y }) == BlockName::Grass)
		{
			float localY = Util::WorldPosToLocalPos({ 0.f, (float)y, 0.f }).y;
			WorldPos = Util::LocPosAndChunkPosToWorldPos({ LocCoords.x,localY,LocCoords.y }, chunkColumn->m_Chunks[y / ChunkSize]->m_ChunkPos);
			metGrass = true;
			break;
		}

	}
	if (!metGrass) return;
	for (int i = 0; i < Util::random(4, 6); i++)
	{
		WorldPos += glm::vec3(0,1,0);
		chunkManager->SetBlockAtPosition(WorldPos , BlockName::Wood);
	}
	for (int y = 1; y <= 3; y++)
		for (int z = -2; z <= 2; z++)
		{
			for (int x = -2; x <= 2; x++)
			{
				if (!(std::abs(x) == 2 && std::abs(z) == 2))
				chunkManager->SetBlockAtPosition(WorldPos + glm::vec3(x, y, z), BlockName::Leaves);


			}
		}
	chunkManager->SetBlockAtPosition(WorldPos , BlockName::Wood);
	chunkManager->SetBlockAtPosition(WorldPos + glm::vec3(0, 1, 0), BlockName::Wood);
}
