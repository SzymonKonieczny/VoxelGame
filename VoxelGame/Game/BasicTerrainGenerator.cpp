#include "BasicTerrainGenerator.h"
#include <FastNoise/FastNoise.h>
void BasicTerrainGenerator::generateTerrain(std::shared_ptr<ChunkColumn> chunkColumn)
{


	//for (auto& chunk : chunkColumn->m_Chunks)
	for (int nr = 0; nr<3;nr++)
	{
		auto chunk = chunkColumn->m_Chunks[nr];
		FastNoise::SmartNode<> fnGenerator = FastNoise::NewFromEncodedNodeTree("EwDNzIxACAA=");

		std::vector<float> noiseOutput(16 * 16 * 16);
		glm::vec3 ChunkPos =chunk->m_ChunkPos;
		// Generate a 16 x 16 x 16 area of noise
		fnGenerator->GenUniformGrid3D(noiseOutput.data(), ChunkPos.x*ChunkSize, ChunkPos.y * ChunkSize, ChunkPos.z * ChunkSize, 
			ChunkSize, ChunkSize, ChunkSize, 0.2f, 1337);
		//fnGenerator->GenUniformGrid3D(noiseOutput.data(), 0, 0, 0, 16, 16, 16, 0.2f, 1337);
		int index = 0;
		for (int i = 0; i < chunk->blocks.size(); i++)
		{
			chunk->blocks[i] = noiseOutput[index++] > 0.3f ? (int)BlockName::Stone : (int)BlockName::Air;
		}

	}

}
