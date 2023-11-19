#include "EarthyTerrainGenerator.h"
#include <FastNoise/FastNoise.h>

EarthyTerrainGenerator::EarthyTerrainGenerator(std::shared_ptr<ChunkManager> ChunkManagerRef) : ITerrainGenerator(ChunkManagerRef)
{
	Biomes.push_back(std::make_unique<PlainsBiome>() );
	Biomes.push_back(std::make_unique<DesertBiome>());
}

void EarthyTerrainGenerator::generateTerrain(std::shared_ptr<ChunkColumn> chunkColumn)
{


	for (std::shared_ptr<Chunk> chunk : chunkColumn->m_Chunks)
		chunk->setIsGenerated(false);


	glm::ivec2 ColumnPos = chunkColumn->m_Position;
	FastNoise::SmartNode<> fnGenerator = FastNoise::NewFromEncodedNodeTree(BiomeDecisionTreeNode.c_str());
	fnGenerator->GenUniformGrid2D(BiomeDecisionNoise.data(), ColumnPos.x * ChunkSize, ColumnPos.y * ChunkSize,
		ChunkSize, ChunkSize, 0.2f, 1337);

	bool isMultiBiomeChunk = CheckForMultiBiomeChunk(*chunkColumn); 
	if (isMultiBiomeChunk)
	{

		 FillHeightMapMultiBiome(chunkColumn);
		 generateLandMass(chunkColumn);
	}
	else {
			int BiomeID = (int)DecideBiomeFromNoiseOutput(BiomeDecisionNoise[0]);
			Biomes[BiomeID]->generateLandmass(chunkColumn, chunkManager);
			Biomes[BiomeID]->addDecoration(chunkColumn, chunkManager);

		}


	addIcing(chunkColumn);

	generateCaves(chunkColumn);

	for (std::shared_ptr<Chunk> chunk : chunkColumn->m_Chunks)
		chunk->setIsGenerated(true);
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



	FastNoise::SmartNode<> fnGenerator = FastNoise::NewFromEncodedNodeTree(BiomeDecisionTreeNode.c_str());
	glm::ivec2 ColumnPos = chunkColumn->m_Position;
	glm::vec2 CornerCoords[4] = { glm::vec2((ColumnPos.x* ChunkSize) -1,  (ColumnPos.y  * ChunkSize)-1),// - - 
								 glm::vec2( (ColumnPos.x * ChunkSize)-1, (ColumnPos.y+1)  * ChunkSize), // - + 
								 glm::vec2((ColumnPos.x+1) * ChunkSize , (ColumnPos.y  * ChunkSize )-1), // + -
								 glm::vec2((ColumnPos.x + 1) * ChunkSize , (ColumnPos.y+1)  * ChunkSize)};// + + 

	/*	glm::vec2 CornerCoords[4] = { glm::vec2((ColumnPos.x)*ChunkSize-1, (ColumnPos.y) * ChunkSize-1),
								 glm::vec2((ColumnPos.x) * ChunkSize-1,(ColumnPos.y) * ChunkSize+1), 
								 glm::vec2((ColumnPos.x) * ChunkSize+1,(ColumnPos.y) * ChunkSize-1), 
								 glm::vec2((ColumnPos.x) * ChunkSize+1,(ColumnPos.y) * ChunkSize+1)};*/

	float corners[4] = {0,0,0,0};
	for (int i = 0; i < 4; i++)
	{
		float BiomeVal[MinFastNoiseDim * MinFastNoiseDim];
		fnGenerator->GenUniformGrid2D( BiomeVal, CornerCoords[i].x, CornerCoords[i].y,
			MinFastNoiseDim, MinFastNoiseDim, 0.2f, 1337);

		int BiomeID = (int)DecideBiomeFromNoiseOutput(BiomeVal[0]);
		Biomes[BiomeID]->getHeightAtWorldCoords(CornerCoords[i], &corners[i]);

	}

	float q11 = corners[0];
	float q12 = corners[2];
	float q21 = corners[1];
	float q22 = corners[3];


	int index = 0;
	for (int z = 0; z < ChunkSize; z++)
		for (int x = 0; x < ChunkSize; x++)
		{		
			int height = (Util::BilinearInterpolation(q11, q12, q21, q22, glm::vec2(0, 0), glm::vec2(17, 17), glm::vec2(x, z)));
			HeightDecisionNoise[index++] = height;
			
			

		}

}

float EarthyTerrainGenerator::getHeightAtBlock(glm::vec2 WorldPos)
{
	FastNoise::SmartNode<> fnGenerator = FastNoise::NewFromEncodedNodeTree(BiomeDecisionTreeNode.c_str());
	float BiomeVal;
	fnGenerator->GenUniformGrid2D(&BiomeVal, WorldPos.x , WorldPos.y,
		1, 1, 0.2f, 1337);

	float result=0;
	
	int BiomeID = (int)DecideBiomeFromNoiseOutput(BiomeVal);
	Biomes[BiomeID]->getHeightAtWorldCoords(WorldPos, &result);




	return result;
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

	for (std::shared_ptr<Chunk> chunk : chunkColumn->m_Chunks)
		chunk->setIsGenerated(false);

	int index = 0;
	for (int z = 0; z < ChunkSize; z++)
		for (int x = 0; x < ChunkSize; x++)
		{
			int height = HeightDecisionNoise[index++];
			for (int y = height - 1; y >= 0; y--)
				chunkColumn->setBlockInColumn({ x,y,z }, BlockName::Stone);
		}


	for (std::shared_ptr<Chunk> chunk : chunkColumn->m_Chunks)
		chunk->setIsGenerated(true);
}

void EarthyTerrainGenerator::addIcing(std::shared_ptr<ChunkColumn>& chunkColumn)
{
	int index = 0;
	for (int z = 0; z < ChunkSize; z++)
		for (int x = 0; x < ChunkSize; x++)
		{
			int BiomeID = (int)DecideBiomeFromNoiseOutput(BiomeDecisionNoise[index++]);
			Biomes[BiomeID]->addIcingRow(chunkColumn, chunkManager, glm::vec2(x, z));
			Biomes[BiomeID]->addDecorationRow(chunkColumn, chunkManager, glm::vec2(x, z));
	
			
			
		}
}
