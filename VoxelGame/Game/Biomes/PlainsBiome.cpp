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
	if (Util::random(1, 15) > 3) return;
	glm::vec3 WorldPos = {0,0,0}; 

	glm::vec2 LocCoords = { 2,2 };

	for (int y = (chunkColumn->m_Chunks.size() * ChunkSize) - 1; y >= 0; y--)
	{
		if (chunkColumn->getBlockInColumn({ LocCoords.x,y,LocCoords.y }) != BlockName::Air)
		{
			float localY = Util::WorldPosToLocalPos({ 0.f, (float)y, 0.f }).y;
			WorldPos = Util::LocPosAndChunkPosToWorldPos({ LocCoords.x,localY,LocCoords.y }, chunkColumn->m_Chunks[y/ChunkSize]->m_ChunkPos);
			break;
		}

	}
	for (int i = 0; i < 5; i++)
		chunkManager->SetBlockAtPosition(WorldPos + glm::vec3(0, i, 0), BlockName::Wood);
	for (int i = 0; i < 5; i++)
	{
		chunkManager->SetBlockAtPosition(WorldPos + glm::vec3(i, 4, 0), BlockName::Ore);
		chunkManager->SetBlockAtPosition(WorldPos + glm::vec3(-i, 4, 0), BlockName::Ore);
		chunkManager->SetBlockAtPosition(WorldPos + glm::vec3(0, 4, i), BlockName::Ore);
		chunkManager->SetBlockAtPosition(WorldPos + glm::vec3(0, 4, -i), BlockName::Ore);


	}
}

void PlainsBiome::generateJustHeightmap(std::shared_ptr<ChunkColumn> chunkColumn, std::vector<float>& Output)
{
	FastNoise::SmartNode<> fnGenerator = FastNoise::NewFromEncodedNodeTree("FwAAAEDAAACAPwAAAAAAAIA/EwApXA8+EAAAAABAGQATAMP1KD8NAAIAAADNzJxACQAAUriePgBmZqY/AQQAAAAAAAAAAACamZk+AAAAAAAAAAAAAAAAAACgwAAAAAAAzcxMPg==");

	glm::ivec2 ColumnPos = chunkColumn->m_Position;

	fnGenerator->GenUniformGrid2D(Output.data(), ColumnPos.x * ChunkSize, ColumnPos.y * ChunkSize,
		ChunkSize, ChunkSize, 0.2f, 1337);

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
		if (chunkColumn->getBlockInColumn({ LocCoords.x,y,LocCoords.y }) != BlockName::Air)
		{
			if(Util::random(1,15) ==1)
			chunkColumn->setBlockInColumn({ LocCoords.x,y+1,LocCoords.y }, BlockName::BlueRose);
			 break;
		}
	}
}

void PlainsBiome::getHeightAtWorldCoords(glm::vec2 WorldPos, float* Output)
{
	FastNoise::SmartNode<> fnGenerator = FastNoise::NewFromEncodedNodeTree("FwAAAEDAAACAPwAAAAAAAIA/EwApXA8+GQATAMP1KD8NAAMAAADNzEw/CQAAPQpnQADXo3A/AQQAAAAAAAAAAACamZk+AAAAAAAAAAAAAAAAAACgwAAAAAA=");
	float temp[MinFastNoiseDim * MinFastNoiseDim];

	fnGenerator->GenUniformGrid2D(temp, WorldPos.x, WorldPos.y,
		MinFastNoiseDim, MinFastNoiseDim, 0.2f, 1337);
	int index = 0;//MinFastNoiseDim * MinFastNoiseDim - 1;

	temp[index] *= Variation;
	temp[index] += BaseGround;
	*Output = temp[index];
}
