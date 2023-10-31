#include "PlainsBiome.h"

void PlainsBiome::generateLandmass(std::shared_ptr<ChunkColumn> chunkColumn, std::shared_ptr<ChunkManager> chunkManager)
{

	// Far lands type EwApXA8+GgABDQAEAAAAexQOQAkAAHsUrj4BEACPwvW/EwCPwvU9//8AAADNzCxAAQMA16NwPw==

	//cool dziurawy Amplified EwDNzEw9IQANAAQAAAB7FA5ACQAAexSuPgEQAI/C9b8TAI/C9T3//wAAAM3MLEAEAI/CdT0AAAAAcT26wHsUrj8AAAAACtejvAAAAAAAAAAAAArXIzw=

	// With actual bottom. Good base !:
	// EwDFILC9GQANAAQAAAB7FA5ACQAAexSuPgAAAAAAAQQAAAAAAAAAAAAAAIA/AAAAAAAAAAAAAAAAAACAPwAAAAA=
	//EwCuR2G+DQAPAAAAhetRQCAADQAEAAAAexQOQAkAAHsUrj4AAAAAAAEEAAAAAAAAAAAACtcDQAAAAAAAAAAAAAAAAAAAgD8AAAAAAM3MzD0APQrXvgAAACBA


}

void PlainsBiome::addIcing(std::shared_ptr<ChunkColumn> chunkColumn, std::shared_ptr<ChunkManager> chunkManager)
{
	std::queue<BlockName> topToBottomSpecialBlocks;

	topToBottomSpecialBlocks.push(BlockName::Grass);
	topToBottomSpecialBlocks.push(BlockName::Dirt);
	topToBottomSpecialBlocks.push(BlockName::Dirt);
	topToBottomSpecialBlocks.push(BlockName::Dirt);


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

void PlainsBiome::addDecoration(std::shared_ptr<ChunkColumn> chunk, std::shared_ptr<ChunkManager> chunkManager)
{
}

void PlainsBiome::generateFeatures(std::shared_ptr<ChunkColumn> chunk, std::shared_ptr<ChunkManager> chunkManager)
{
}
