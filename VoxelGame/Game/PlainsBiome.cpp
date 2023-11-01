#include "PlainsBiome.h"
#include <FastNoise/FastNoise.h>

void PlainsBiome::generateLandmass(std::shared_ptr<ChunkColumn> chunkColumn, std::shared_ptr<ChunkManager> chunkManager)
{

	for (std::shared_ptr<Chunk> chunk : chunkColumn->m_Chunks)
					chunk->setIsGenerated(false);

	FastNoise::SmartNode<> fnGenerator = FastNoise::NewFromEncodedNodeTree("FwAAAEDAAACAPwAAAAAAAIA/EwApXA8+EAAAAABAGQATAMP1KD8NAAIAAADNzJxACQAAUriePgBmZqY/AQQAAAAAAAAAAACamZk+AAAAAAAAAAAAAAAAAACgwAAAAAAAzcxMPg==");

	std::vector<float> noiseOutput(ChunkSize * ChunkSize);
	glm::ivec2 ColumnPos = chunkColumn->m_Position;

	fnGenerator->GenUniformGrid2D(noiseOutput.data(), ColumnPos.x * ChunkSize, ColumnPos.y * ChunkSize,
		ChunkSize, ChunkSize, 0.2f, 1337);
	int BaseGround = 60;
	int Variation = 50;
		
	int index = 0;
	for (int z = 0; z < ChunkSize; z++)
		for (int x = 0; x < ChunkSize; x++)
		{
			int height = BaseGround+ noiseOutput[index++] * Variation;
				for (int y = height-1; y >=0; y--)
				chunkColumn->setBlockInColumn({ x,y,z }, BlockName::Stone);
		}

		



	

	for (std::shared_ptr<Chunk> chunk : chunkColumn->m_Chunks)
			chunk->setIsGenerated(true);
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