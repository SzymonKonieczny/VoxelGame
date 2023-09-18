#include "World.h"
#include "Util.h"
BlockInfo World::GetBlockOnPosition(glm::vec3 Pos)
{
	auto chunk =chunkManager.ChunkMap.at(glm::ivec2(Pos.x / ChunkSize, Pos.z / ChunkSize)).getChunk(Pos.y/ChunkSize);
	
	unsigned int ID = chunk->blocks[Util::Vec3ToIndex({ (int)Pos.x % ChunkSize,(int)Pos.y % ChunkSize,(int)Pos.z % ChunkSize })];
		return BlockTable[ID];
}

void World::SetBlockOnPosition(glm::vec3 Pos, int ID)
{
	auto chunk = chunkManager.ChunkMap.at(glm::ivec2(Pos.x / ChunkSize, Pos.z / ChunkSize)).getChunk(Pos.y / ChunkSize);
	chunk->blocks[Util::Vec3ToIndex({ (int)Pos.x % ChunkSize,(int)Pos.y % ChunkSize,(int)Pos.z % ChunkSize })] = ID;
	chunk->setIsDirty(true);
}

void World::TickWorld(double deltaTime)
{
	player.Update(deltaTime);
	chunkManager.UpdateLoadedChunkMap({ player.getPositon().x / ChunkSize, player.getPositon().z / ChunkSize });

}
