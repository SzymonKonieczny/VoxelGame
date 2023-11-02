#include "EarthyTerrainGenerator.h"
#include <FastNoise/FastNoise.h>

void EarthyTerrainGenerator::generateTerrain(std::shared_ptr<ChunkColumn> chunkColumn)
{
	Plains.generateLandmass(chunkColumn, this->chunkManager);

	//EADsUbg/EwDsUbg+DAABAAAAzczMPQkAAOF6lD8ACtejPg==

	//Plains.addIcing(chunkColumn, this->chunkManager);

	std::vector<float> BiomeDecisionNoise(16 * 16 );

	FastNoise::SmartNode<> fnGenerator = FastNoise::NewFromEncodedNodeTree("EABmZoZAEwAK1yM8DAABAAAAzczMPQkAAOF6lD8AuB6FPw==");

	glm::ivec2 ColumnPos = chunkColumn->m_Position;

	fnGenerator->GenUniformGrid2D(BiomeDecisionNoise.data(), ColumnPos.x * ChunkSize, ColumnPos.y * ChunkSize,
		ChunkSize, ChunkSize, 0.2f, 1337);
	int index = 0;
	for (int z = 0; z < ChunkSize; z++)
		for (int x = 0; x < ChunkSize; x++)
		{
			float height = BiomeDecisionNoise[index++];
			if (height < 0.0f)
				Plains.addIcingRow(chunkColumn, chunkManager, glm::vec2(x, z));
			else
				Desert.addIcingRow(chunkColumn, chunkManager, glm::vec2(x, z));
		}

	generateCaves(chunkColumn);



}

void EarthyTerrainGenerator::generateCaves(std::shared_ptr<ChunkColumn>& chunkColumn)
{
	for (int nr = 0; nr < ChunksInColumn; nr++)
	{
		auto chunk = chunkColumn->m_Chunks[nr];

		chunk->blockMutex.lock();

		FastNoise::SmartNode<> fnGenerator = FastNoise::NewFromEncodedNodeTree("FwAAAEDAAABAQAAAgL8AAIA/EwCPwvU9GgABEQACAAAAAADgQBAAAACIQR8AFgABAAAACwADAAAAAgAAAAMAAAAEAAAAAAAAAD8BFAD//wAAAAAAAD8AAAAAPwAAAAA/AAAAAD8BFwAAAIC/AACAPz0KF0BSuB5AEwAAAKBABgAAj8J1PACamZk+AAAAAAABFwAAAIC/AACAPwAAAL8AAAA///8CAA==");

		std::vector<float> noiseOutput(16 * 16 * 16);
		glm::ivec3 ChunkPos = chunk->m_ChunkPos;

		fnGenerator->GenUniformGrid3D(noiseOutput.data(), ChunkPos.x * ChunkSize, ChunkPos.z * ChunkSize, ChunkPos.y * ChunkSize,
			ChunkSize, ChunkSize, ChunkSize, 0.2f, 1337);

		int index = 0;

		for (int i = 0; i < chunk->blocks.size(); i++)
		{
			if (noiseOutput[index++] < 0.0f)
				chunk->blocks[i] = (int)BlockName::Air;
		}
		chunk->blockMutex.unlock();

	}
}
