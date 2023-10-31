#include "EarthyTerrainGenerator.h"

void EarthyTerrainGenerator::generateTerrain(std::shared_ptr<ChunkColumn> chunkColumn)
{
	Plains.generateLandmass(chunkColumn, this->chunkManager);
	Plains.addIcing(chunkColumn, this->chunkManager);

}