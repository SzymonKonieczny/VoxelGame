#include "TerrainGeneratorTest.h"
#include "Util.h"
void TerrainGeneratorTest::generateTerrain(Chunk& chunk)
{
	chunk.setIsGenerated(false);

	int index = 0;
	if (chunk.m_ChunkPos.y != 0) {
		for(int i =0;i<ChunkSize;i++)
		chunk.blocks[Util::Vec3ToIndex({7.f,i,7.f})] = (Util::random(1, 4));
		
	}
	else
	{
		for (int y = 0; y < Util::random(2, 4);y++)
		{
			for (int z = 0; z < ChunkSize; z++)
				for (int x = 0; x < ChunkSize; x++)
				{
					chunk.blocks[index] = (Util::random(1, 4));
					index++;
				}
		}
	}
	chunk.setIsGenerated(true);

}
