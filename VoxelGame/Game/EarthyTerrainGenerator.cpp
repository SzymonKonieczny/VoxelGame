#include "EarthyTerrainGenerator.h"
#include <FastNoise/FastNoise.h>

void EarthyTerrainGenerator::generateTerrain(std::shared_ptr<ChunkColumn> chunkColumn)
{
	Plains.generateLandmass(chunkColumn, this->chunkManager);
	Plains.addIcing(chunkColumn, this->chunkManager);

	for (int nr = 0; nr < ChunksInColumn; nr++)
	{
		auto chunk = chunkColumn->m_Chunks[nr];

		chunk->blockMutex.lock();

		FastNoise::SmartNode<> fnGenerator = FastNoise::NewFromEncodedNodeTree("FwAAAIC/AACAPwAAQEAAAEDAEwAK1yM8GgABEQACAAAAAADgQBAAAACIQR8AFgABAAAACwADAAAAAgAAAAMAAAAEAAAAAAAAAD8BFAD//wAAAAAAAD8AAAAAPwAAAAA/AAAAAD8BFwAAAIC/AACAPz0KF0BSuB5AEwAAAKBABgAAj8J1PACamZk+AAAAAAAA4XoUPw==");

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