#include "DesertBiome.h"
void DesertBiome::generateLandmass(std::shared_ptr<ChunkColumn> chunkColumn, std::shared_ptr<ChunkManager> chunkManager)
{

}

void DesertBiome::addIcing(std::shared_ptr<ChunkColumn> chunkColumn, std::shared_ptr<ChunkManager> chunkManager)
{



	for (int z = 0; z < ChunkSize; z++)
		for (int x = 0; x < ChunkSize; x++)
		{
			std::queue<BlockName> topToBottomSpecialBlocksCopy(topToBottomSpecialBlocks);
			for (int y = (chunkColumn->m_Chunks.size() * ChunkSize) - 1; y >= 0; y--)
			{
				if (chunkColumn->getBlockInColumn({ x,y,z }) != BlockName::Air)
				{
					chunkColumn->setBlockInColumn({ x,y,z }, topToBottomSpecialBlocksCopy.front());
					topToBottomSpecialBlocksCopy.pop();
					if (topToBottomSpecialBlocksCopy.empty()) break;
				}
			}
		}
}

void DesertBiome::addDecoration(std::shared_ptr<ChunkColumn> chunk, std::shared_ptr<ChunkManager> chunkManager)
{
}

void DesertBiome::generateFeatures(std::shared_ptr<ChunkColumn> chunk, std::shared_ptr<ChunkManager> chunkManager)
{
}

void DesertBiome::addIcingRow(std::shared_ptr<ChunkColumn> chunkColumn, std::shared_ptr<ChunkManager> chunkManager, glm::vec2 LocCoords)
{
	std::queue<BlockName> topToBottomSpecialBlocksCopy(topToBottomSpecialBlocks);
	for (int y = (chunkColumn->m_Chunks.size() * ChunkSize) - 1; y >= 0; y--)
	{
		if (chunkColumn->getBlockInColumn({ LocCoords.x,y,LocCoords.y }) != BlockName::Air)
		{
			chunkColumn->setBlockInColumn({ LocCoords.x,y,LocCoords.y }, topToBottomSpecialBlocksCopy.front());
			topToBottomSpecialBlocksCopy.pop();
			if (topToBottomSpecialBlocksCopy.empty()) break;
		}
	}

}

void DesertBiome::addDecorationRow(std::shared_ptr<ChunkColumn> chunk, std::shared_ptr<ChunkManager> chunkManager, glm::vec2 LocCoords)
{
}

void DesertBiome::generateJustHeightmap(std::shared_ptr<ChunkColumn> chunkColumn, std::vector<float>& Output)
{
}
