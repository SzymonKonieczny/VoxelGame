#include "HeavenTerrainGenerator.h"
#include <queue>
void HeavenTerrainGenerator::generateTerrain(std::shared_ptr<ChunkColumn> chunkColumn) 
//Wyjatkowo ten generator sam generuje 
// Landmass, i potem tylko naklada dodadki od Plains Biome
{

	// Far lands type EwApXA8+GgABDQAEAAAAexQOQAkAAHsUrj4BEACPwvW/EwCPwvU9//8AAADNzCxAAQMA16NwPw==

	//cool dziurawy Amplified EwDNzEw9IQANAAQAAAB7FA5ACQAAexSuPgEQAI/C9b8TAI/C9T3//wAAAM3MLEAEAI/CdT0AAAAAcT26wHsUrj8AAAAACtejvAAAAAAAAAAAAArXIzw=
	
	// With actual bottom. Good base !:
	// EwDFILC9GQANAAQAAAB7FA5ACQAAexSuPgAAAAAAAQQAAAAAAAAAAAAAAIA/AAAAAAAAAAAAAAAAAACAPwAAAAA=
	//EwCuR2G+DQAPAAAAhetRQCAADQAEAAAAexQOQAkAAHsUrj4AAAAAAAEEAAAAAAAAAAAACtcDQAAAAAAAAAAAAAAAAAAAgD8AAAAAAM3MzD0APQrXvgAAACBA
	
	
	for (int nr = 0; nr<ChunksInColumn-1;nr++)
	{
		auto chunk = chunkColumn->m_Chunks[nr];
		
		FastNoise::SmartNode<> fnGenerator = FastNoise::NewFromEncodedNodeTree("GQAJAAEEAAAAAAAAAAAAzcxMvQAAAAAAAAAAAAAAAAAAoEEAAAAA");

		std::vector<float> noiseOutput(16 * 16 * 16);
		glm::ivec3 ChunkPos =chunk->m_ChunkPos;

		fnGenerator->GenUniformGrid3D(noiseOutput.data(), ChunkPos.x*ChunkSize, ChunkPos.z * ChunkSize, ChunkPos.y * ChunkSize, 
			ChunkSize, ChunkSize, ChunkSize, 0.2f, 1337);

		chunk->blockMutex.lock();
		
		int index = 0;
		for (int i = 0; i < chunk->blocks.size(); i++)
		{
			chunk->blocks[i] = noiseOutput[index++] < 0.0f ? (int)BlockName::Stone : (int)BlockName::Air;
		}
		chunk->blockMutex.unlock();

	}


}
