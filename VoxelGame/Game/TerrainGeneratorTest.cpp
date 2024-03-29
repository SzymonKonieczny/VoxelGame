#include "TerrainGeneratorTest.h"
#include "Util.h"
#include <FastNoise/FastNoise.h>
void TerrainGeneratorTest::generateTerrain(std::shared_ptr<ChunkColumn> chunkColumn)
{


	for (std::shared_ptr<Chunk> chunk : chunkColumn->m_Chunks)
	{
		chunk->blockMutex.lock();
		chunk->setIsGenerated(false);

		int index = 0;
		if (chunk->m_ChunkPos.y > 0/* != 0*/) {

		}
		else
		{
			for (int y = 0; y < Util::random(2, 16); y++)
			{
				for (int z = 0; z < ChunkSize; z++)
					for (int x = 0; x < ChunkSize; x++)
					{
						BlockName block;
						if (chunkColumn->m_Position.x < 0 && chunkColumn->m_Position.y < 0)
							block = BlockName::Dirt;
						if (chunkColumn->m_Position.x >= 0 && chunkColumn->m_Position.y < 0)
							block = BlockName::Sand;
						if (chunkColumn->m_Position.x < 0 && chunkColumn->m_Position.y >= 0)
							block = BlockName::Stone;
						if (chunkColumn->m_Position.x >= 0 && chunkColumn->m_Position.y >= 0)
							block = BlockName::Grass;
						chunk->setBlock(block, index);
						index++;
					}
			}
		}
		chunk->setIsGenerated(true);
		chunk->blockMutex.unlock();

	}
	
}
