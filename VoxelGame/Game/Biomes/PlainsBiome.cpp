#include "PlainsBiome.h"
#include <FastNoise/FastNoise.h>

void PlainsBiome::generateLandmass(std::shared_ptr<ChunkColumn> chunkColumn, std::shared_ptr<ChunkManager> chunkManager)
{

	for (std::shared_ptr<Chunk> chunk : chunkColumn->m_Chunks)
					chunk->setIsGenerated(false);

	std::vector<float> noiseOutput(ChunkSize * ChunkSize);
	
	generateJustHeightmap(chunkColumn, noiseOutput);

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

void PlainsBiome::generateJustHeightmap(std::shared_ptr<ChunkColumn> chunkColumn, std::vector<float>& Output)
{
	FastNoise::SmartNode<> fnGenerator = FastNoise::NewFromEncodedNodeTree("FwAAAEDAAACAPwAAAAAAAIA/EwApXA8+EAAAAABAGQATAMP1KD8NAAIAAADNzJxACQAAUriePgBmZqY/AQQAAAAAAAAAAACamZk+AAAAAAAAAAAAAAAAAACgwAAAAAAAzcxMPg==");

	glm::ivec2 ColumnPos = chunkColumn->m_Position;

	fnGenerator->GenUniformGrid2D(Output.data(), ColumnPos.x * ChunkSize, ColumnPos.y * ChunkSize,
		ChunkSize, ChunkSize, 0.2f, 1337);
}

void PlainsBiome::addIcingRow(std::shared_ptr<ChunkColumn> chunkColumn, std::shared_ptr<ChunkManager> chunkManager, glm::vec2 LocCoords)
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

void PlainsBiome::addDecorationRow(std::shared_ptr<ChunkColumn> chunkColumn, std::shared_ptr<ChunkManager> chunkManager, glm::vec2 LocCoords)
{

	for (int y = (chunkColumn->m_Chunks.size() * ChunkSize) - 1; y >= 0; y--)
	{
		if (chunkColumn->getBlockInColumn({ LocCoords.x,y,LocCoords.y }) != BlockName::Air)
		{
			if(Util::random(1,15) ==1)
			chunkColumn->setBlockInColumn({ LocCoords.x,y+1,LocCoords.y }, BlockName::BlueRose);
			 break;
		}
	}
}
