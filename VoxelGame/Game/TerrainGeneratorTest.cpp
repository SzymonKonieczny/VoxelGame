#include "TerrainGeneratorTest.h"
#include "Util.h"
void TerrainGeneratorTest::generateTerrain(Chunk& chunk)
{
	for (int y = 0; y < Util::random(2, 4);y++)
	{
		for (int z = 0; z < ChunkSize; z++)
			for (int x = 0; x < ChunkSize; x++)
			{

				chunk.blocks.push_back(1);
			}
	}
}
