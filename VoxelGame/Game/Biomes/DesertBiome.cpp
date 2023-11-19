#include "DesertBiome.h"
#include <FastNoise/FastNoise.h>

void DesertBiome::generateLandmass(std::shared_ptr<ChunkColumn> chunkColumn, std::shared_ptr<ChunkManager> chunkManager)
{
	//for (std::shared_ptr<Chunk> chunk : chunkColumn->m_Chunks) SHOULD BE DONE ABOVE IN THE CALLSTACK
	//	chunk->setIsGenerated(false);

	std::vector<float> noiseOutput(ChunkSize * ChunkSize);

	generateJustHeightmap(chunkColumn, noiseOutput);


	int index = 0;
	for (int z = 0; z < ChunkSize; z++)
		for (int x = 0; x < ChunkSize; x++)
		{
			int height = noiseOutput[index++];
			for (int y = height - 1; y >= 0; y--)
				chunkColumn->setBlockInColumn({ x,y,z }, BlockName::Stone);
		}


	//for (std::shared_ptr<Chunk> chunk : chunkColumn->m_Chunks)
	//	chunk->setIsGenerated(true);
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
	FastNoise::SmartNode<> fnGenerator = FastNoise::NewFromEncodedNodeTree("FwAAAEDAAACAPwAAAAAAAIA/EwApXA8+GQATAMP1KD8NAAMAAADNzEw/CQAAPQpnQADXo3A/AQQAAAAAAAAAAACamZk+AAAAAAAAAAAAAAAAAACgwAAAAAA=");

	glm::ivec2 ColumnPos = chunkColumn->m_Position;

	fnGenerator->GenUniformGrid2D(Output.data(), ColumnPos.x * ChunkSize, ColumnPos.y * ChunkSize,
		ChunkSize, ChunkSize, 0.2f, 1337);

	for (auto& val : Output)
	{
		val *= Variation;
		val += BaseGround;
	}
}

void DesertBiome::getHeightAtWorldCoords(glm::vec2 WorldPos, float* Output)
{
	FastNoise::SmartNode<> fnGenerator = FastNoise::NewFromEncodedNodeTree("FwAAAEDAAACAPwAAAAAAAIA/EwApXA8+GQATAMP1KD8NAAMAAADNzEw/CQAAPQpnQADXo3A/AQQAAAAAAAAAAACamZk+AAAAAAAAAAAAAAAAAACgwAAAAAA=");

	float temp[MinFastNoiseDim * MinFastNoiseDim];
	fnGenerator->GenUniformGrid2D(Output, WorldPos.x, WorldPos.y,
		MinFastNoiseDim, MinFastNoiseDim, 0.2f, 1337);
	temp[0] *= Variation;
	temp[0] += BaseGround;
	*Output = temp[0];
}
