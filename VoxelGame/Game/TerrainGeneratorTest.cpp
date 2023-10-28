#include "TerrainGeneratorTest.h"
#include "Util.h"
#include <FastNoise/FastNoise.h>
void TerrainGeneratorTest::generateTerrain(std::shared_ptr<ChunkColumn> chunkColumn)
{
	FastNoise::SmartNode<> fnGenerator = FastNoise::NewFromEncodedNodeTree("DQAFAAAAAAAAQAgAAAAAAD8AAAAAAA==");
	
	std::vector<float> noiseOutput(16 * 16 * 16);

	// Generate a 16 x 16 x 16 area of noise
	fnGenerator->GenUniformGrid3D(noiseOutput.data(), 0, 0, 0, 16, 16, 16, 0.2f, 1337);

	for (std::shared_ptr<Chunk> chunk : chunkColumn->m_Chunks)
	{
		chunk->blockMutex.lock();
		chunk->setIsGenerated(false);

		int index = 0;
		if (chunk->m_ChunkPos.y > 0/* != 0*/) {

		}
		else
		{
			for (int y = 0; y < Util::random(5, 6); y++)
			{
				for (int z = 0; z < ChunkSize; z++)
					for (int x = 0; x < ChunkSize; x++)
					{
						chunk->blocks[index] = (Util::random(1, 4));
						index++;
					}
			}
		}
		chunk->setIsGenerated(true);
		chunk->blockMutex.unlock();

	}
	
}
