#include "PlainsBiome.h"
#include <FastNoise/FastNoise.h>
#include "../ChunkManager.h"
void PlainsBiome::generateLandmass(std::shared_ptr<ChunkColumn> chunkColumn, std::shared_ptr<ChunkManager> chunkManager)
{

	//for (std::shared_ptr<Chunk> chunk : chunkColumn->m_Chunks) SHOULD BE DONE ABOVE IN THE CALLSTACK
	//				chunk->setIsGenerated(false);

	std::vector<float> noiseOutput(ChunkSize * ChunkSize);
	
	generateJustHeightmap(chunkColumn, noiseOutput);

		
	int index = 0;
	for (int z = 0; z < ChunkSize; z++)
		for (int x = 0; x < ChunkSize; x++)
		{
			int height = noiseOutput[index++];
				for (int y = height-1; y >=0; y--)
				chunkColumn->setBlockInColumn({ x,y,z }, BlockName::Stone);
		}

		
	// for (std::shared_ptr<Chunk> chunk : chunkColumn->m_Chunks) SHOULD BE DONE ABOVE IN THE CALLSTACK
	// 		chunk->setIsGenerated(true);
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

void PlainsBiome::generateFeatures(std::shared_ptr<ChunkColumn> chunkColumn, std::shared_ptr<ChunkManager> chunkManager)
{
	
	
}

void PlainsBiome::generateJustHeightmap(std::shared_ptr<ChunkColumn> chunkColumn, std::vector<float>& Output)
{
	FastNoise::SmartNode<> fnGenerator = FastNoise::NewFromEncodedNodeTree(EncodedTree.c_str());

	glm::ivec2 ColumnPos = chunkColumn->m_Position;

	fnGenerator->GenUniformGrid2D(Output.data(), ColumnPos.x * ChunkSize, ColumnPos.y * ChunkSize,
		ChunkSize, ChunkSize, 0.2f, WorldSeed);

	for (auto& val : Output)
	{
		val *= Variation;
		val += BaseGround;
	}
}

void PlainsBiome::addIcingRow(std::shared_ptr<ChunkColumn> chunkColumn, std::shared_ptr<ChunkManager> chunkManager, glm::vec2 LocCoords)
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

void PlainsBiome::addDecorationRow(std::shared_ptr<ChunkColumn> chunkColumn, std::shared_ptr<ChunkManager> chunkManager, glm::vec2 LocCoords)
{

	for (int y = (chunkColumn->m_Chunks.size() * ChunkSize) - 1; y >= 0; y--)
	{
		if (chunkColumn->getBlockInColumn({ LocCoords.x,y,LocCoords.y }) == BlockName::Grass)
		{
			if(Util::random(1,15) ==1)
			chunkColumn->setBlockInColumn({ LocCoords.x,y+1,LocCoords.y }, BlockName::BlueRose);
			 break;
		}
	}
}

void PlainsBiome::getHeightAtWorldCoords(glm::vec2 WorldPos, float* Output)
{
	FastNoise::SmartNode<> fnGenerator = FastNoise::NewFromEncodedNodeTree(EncodedTree.c_str());
	float temp[MinFastNoiseDim * MinFastNoiseDim];

	fnGenerator->GenUniformGrid2D(temp, WorldPos.x, WorldPos.y,
		MinFastNoiseDim, MinFastNoiseDim, 0.2f, WorldSeed);
	int index = 0;//MinFastNoiseDim * MinFastNoiseDim - 1;

	temp[index] *= Variation;
	temp[index] += BaseGround;
	*Output = temp[index];
}
