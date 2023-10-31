#include "BasicTerrainGenerator.h"
#include <FastNoise/FastNoise.h>
#include <queue>
void BasicTerrainGenerator::generateTerrain(std::shared_ptr<ChunkColumn> chunkColumn)
{

	// Far lands type EwApXA8+DQAEAAAAexQOQAkAAHsUrj4BEACPwvW/EwCPwvU9//8AAADNzCxA


	for (int nr = 0; nr<8;nr++)
	{
		auto chunk = chunkColumn->m_Chunks[nr];
		FastNoise::SmartNode<> fnGenerator = FastNoise::NewFromEncodedNodeTree("EwApXA8+DQAEAAAAexQOQAkAAHsUrj4BEACPwvW/EwCPwvU9//8AAADNzCxA");

		std::vector<float> noiseOutput(16 * 16 * 16);
		glm::ivec3 ChunkPos =chunk->m_ChunkPos;

		fnGenerator->GenUniformGrid3D(noiseOutput.data(), ChunkPos.x*ChunkSize, ChunkPos.z * ChunkSize, ChunkPos.y * ChunkSize, 
			ChunkSize, ChunkSize, ChunkSize, 0.2f, 1337);

		int index = 0;

		for (int i = 0; i < chunk->blocks.size(); i++)
		{
			chunk->blocks[i] = noiseOutput[index++] > 0.07f ? (int)BlockName::Stone : (int)BlockName::Air;
		}

	}


}

void BasicTerrainGenerator::addIcing(std::shared_ptr<ChunkColumn> chunkColumn)
{
	std::queue<BlockName> topToBottomSpecialBlocks;
	(Util::random(1,10) ==2)? topToBottomSpecialBlocks.push(BlockName::BlueRose): topToBottomSpecialBlocks.push(BlockName::Air);

	topToBottomSpecialBlocks.push(BlockName::Grass);
	topToBottomSpecialBlocks.push(BlockName::Dirt);
	topToBottomSpecialBlocks.push(BlockName::Dirt);
	topToBottomSpecialBlocks.push(BlockName::Dirt);


	for (int z = 0; z < ChunkSize; z++)
		for (int x = 0; x < ChunkSize; x++)
		{
			std::queue<BlockName> topToBottomSpecialBlocksCopy(topToBottomSpecialBlocks);
			for (int y = (chunkColumn->m_Chunks.size() * ChunkSize) -1; y >= 0; y--)
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
