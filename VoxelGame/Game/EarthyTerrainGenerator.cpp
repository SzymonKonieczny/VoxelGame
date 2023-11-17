#include "EarthyTerrainGenerator.h"
#include <FastNoise/FastNoise.h>

void EarthyTerrainGenerator::generateTerrain(std::shared_ptr<ChunkColumn> chunkColumn)
{



	FastNoise::SmartNode<> fnGenerator = FastNoise::NewFromEncodedNodeTree(BiomeDecisionTreeNode.c_str());

	glm::ivec2 ColumnPos = chunkColumn->m_Position;

	fnGenerator->GenUniformGrid2D(BiomeDecisionNoise.data(), ColumnPos.x * ChunkSize, ColumnPos.y * ChunkSize,
		ChunkSize, ChunkSize, 0.2f, 1337);

	bool isMultiBiomeChunk = CheckForMultiBiomeChunk(*chunkColumn); 
		if(isMultiBiomeChunk)	FillHeightMapMultiBiome(chunkColumn);
		else {
			switch (DecideBiomeFromNoiseOutput(BiomeDecisionNoise[0]))
			{
			case EarthBiomes::Desert:
				Desert.generateLandmass(chunkColumn, chunkManager);
				Desert.addDecoration(chunkColumn, chunkManager);

				break;
			case EarthBiomes::Plains:
				Plains.generateLandmass(chunkColumn, chunkManager);
				Plains.addDecoration(chunkColumn, chunkManager);
				break;
			default:
				break;
			}


		}
	generateLandMass(chunkColumn);

	addIcing(chunkColumn);


	

	//EADsUbg/EwDsUbg+DAABAAAAzczMPQkAAOF6lD8ACtejPg==

	//Plains.addIcing(chunkColumn, this->chunkManager);



	generateCaves(chunkColumn);
}

void EarthyTerrainGenerator::generateCaves(std::shared_ptr<ChunkColumn>& chunkColumn)
{
	for (int nr = 0; nr < ChunksInColumn; nr++)
	{
		auto chunk = chunkColumn->m_Chunks[nr];

		chunk->blockMutex.lock();

		FastNoise::SmartNode<> fnGenerator = FastNoise::NewFromEncodedNodeTree(CaveCarvingTreeNode.c_str());

		std::vector<float> noiseOutput(16 * 16 * 16);
		glm::ivec3 ChunkPos = chunk->m_ChunkPos;

		fnGenerator->GenUniformGrid3D(noiseOutput.data(), ChunkPos.x * ChunkSize, ChunkPos.z * ChunkSize, ChunkPos.y * ChunkSize,
			ChunkSize, ChunkSize, ChunkSize, 0.2f, 1337);

		int index = 0;

		for (int i = 0; i < chunk->getBlockVectorSize(); i++)
		{
			if (noiseOutput[index++] < 0.0f)
				chunk->setBlock(BlockName::Air, i);
		}
		chunk->blockMutex.unlock();

	}
}

void EarthyTerrainGenerator::FillHeightMapMultiBiome(std::shared_ptr<ChunkColumn>& chunkColumn)
{
	std::fill(HeightDecisionNoise.begin(), HeightDecisionNoise.end(), 0);

	



}

EarthBiomes EarthyTerrainGenerator::DecideBiomeFromNoiseOutput(float noise)
{
	if (noise < 0.0f) return EarthBiomes::Plains;
	else return EarthBiomes::Desert;

}

bool  EarthyTerrainGenerator::CheckForMultiBiomeChunk(ChunkColumn& chunkColumn)
{
	EarthBiomes last = DecideBiomeFromNoiseOutput(BiomeDecisionNoise[0]);
	bool multiBiomeChunk = false;

	for (float val : BiomeDecisionNoise)
	{
		int temp = (int)DecideBiomeFromNoiseOutput(val);
		if ((int)last != temp)
		{
			 multiBiomeChunk = true;
			 break;
		}
	}
	return multiBiomeChunk;
}



void EarthyTerrainGenerator::generateLandMass(std::shared_ptr<ChunkColumn>& chunkColumn)
{

	int index = 0;
	for (int z = 0; z < ChunkSize; z++)
		for (int x = 0; x < ChunkSize; x++)
		{
			int height = HeightDecisionNoise[index++];
			for (int y = height - 1; y >= 0; y--)
				chunkColumn->setBlockInColumn({ x,y,z }, BlockName::Stone);
		}


}

void EarthyTerrainGenerator::addIcing(std::shared_ptr<ChunkColumn>& chunkColumn)
{
	int index = 0;
	for (int z = 0; z < ChunkSize; z++)
		for (int x = 0; x < ChunkSize; x++)
		{
		
			switch (DecideBiomeFromNoiseOutput(BiomeDecisionNoise[index++]))
			{
			case EarthBiomes::Plains:
				Plains.addIcingRow(chunkColumn, chunkManager, glm::vec2(x, z));
				Plains.addDecorationRow(chunkColumn, chunkManager, glm::vec2(x, z));
				break;
			case EarthBiomes::Desert:
				Desert.addIcingRow(chunkColumn, chunkManager, glm::vec2(x, z));
				break;
			default:
				std::cout << "INVALID CHUNK FOR ICING\n";
				break;


			}
			
			
		}
}
