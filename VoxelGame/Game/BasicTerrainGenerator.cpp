#include "BasicTerrainGenerator.h"
#include <FastNoise/FastNoise.h>
#include <queue>
void BasicTerrainGenerator::generateTerrain(std::shared_ptr<ChunkColumn> chunkColumn)
{

	// Far lands type EwApXA8+GgABDQAEAAAAexQOQAkAAHsUrj4BEACPwvW/EwCPwvU9//8AAADNzCxAAQMA16NwPw==

	//cool dziurawy Amplified EwDNzEw9IQANAAQAAAB7FA5ACQAAexSuPgEQAI/C9b8TAI/C9T3//wAAAM3MLEAEAI/CdT0AAAAAcT26wHsUrj8AAAAACtejvAAAAAAAAAAAAArXIzw=
	
	// With actual bottom. Good base !:
	// EwDFILC9GQANAAQAAAB7FA5ACQAAexSuPgAAAAAAAQQAAAAAAAAAAAAAAIA/AAAAAAAAAAAAAAAAAACAPwAAAAA=
	//EwCuR2G+DQAPAAAAhetRQCAADQAEAAAAexQOQAkAAHsUrj4AAAAAAAEEAAAAAAAAAAAACtcDQAAAAAAAAAAAAAAAAAAAgD8AAAAAAM3MzD0APQrXvgAAACBA
	
	
	for (int nr = 0; nr<ChunksInColumn-1;nr++)
	{
		auto chunk = chunkColumn->m_Chunks[nr];
		FastNoise::SmartNode<> fnGenerator = FastNoise::NewFromEncodedNodeTree("GQANAAQAAAB7FA5ACQAAexSuPgAAAAAAAQQAAAAAAAAAAADNzEy+AAAAAAAAAAAAAAAAAAAgQQAAAAA=");

		std::vector<float> noiseOutput(16 * 16 * 16);
		glm::ivec3 ChunkPos =chunk->m_ChunkPos;

		fnGenerator->GenUniformGrid3D(noiseOutput.data(), ChunkPos.x*ChunkSize, ChunkPos.z * ChunkSize, ChunkPos.y * ChunkSize, 
			ChunkSize, ChunkSize, ChunkSize, 0.2f, 1337);

		int index = 0;

		for (int i = 0; i < chunk->blocks.size(); i++)
		{
			chunk->blocks[i] = noiseOutput[index++] < 0.0f ? (int)BlockName::Stone : (int)BlockName::Air;
		}

	}


}

void BasicTerrainGenerator::addIcing(std::shared_ptr<ChunkColumn> chunkColumn)
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
