#include "IBiome.h"
/*#include "IBiome.h"

void IBiome::getHeightAtWorldCoords(glm::vec2 WorldPos, float* Output)
{
	FastNoise::SmartNode<> fnGenerator = FastNoise::NewFromEncodedNodeTree(EncodedTree.c_str());

	float temp[MinFastNoiseDim * MinFastNoiseDim];
	fnGenerator->GenUniformGrid2D(temp, WorldPos.x, WorldPos.y,
		MinFastNoiseDim, MinFastNoiseDim, 0.2f, 1337);
	int index = 0;// MinFastNoiseDim * MinFastNoiseDim - 1;
	temp[index] *= Variation;
	temp[index] += BaseGround;
	*Output = temp[index];
}*/

void IBiome::addIcingRow(std::shared_ptr<ChunkColumn> chunkColumn, std::shared_ptr<ChunkManager> chunkManager, glm::vec2 LocCoords)
{

	std::queue<BlockName> topToBottomSpecialBlocksCopy(topToBottomSpecialBlocks);


	for (int y = (chunkColumn->m_Chunks.size() * ChunkSize) - 1; y >= 0; y--)
	{
		if (chunkColumn->getBlockInColumn({ LocCoords.x,y,LocCoords.y }) == BlockName::Stone)
		{
			chunkColumn->setBlockInColumn({ LocCoords.x,y,LocCoords.y }, topToBottomSpecialBlocksCopy.front());
			topToBottomSpecialBlocksCopy.pop();
			if (topToBottomSpecialBlocksCopy.empty()) break;
		}
	}

}


