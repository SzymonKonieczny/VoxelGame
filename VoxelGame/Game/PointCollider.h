#pragma once
#include <glm/glm.hpp>
#include "ChunkManager.h"
#include "BlockInfo.h"
class PointCollider{
public:
	static bool isBlockAtCollidable(glm::vec3 Pos, ChunkManager* World)
	{
		auto chunk = World->ChunkMap.at(glm::ivec2(Pos.x / ChunkSize, Pos.z / ChunkSize)).getChunk(Pos.y / ChunkSize);
		return BlockTable[chunk->blocks[Util::Vec3ToIndex({ (int)Pos.x % ChunkSize,(int)Pos.y % ChunkSize,(int)Pos.z % ChunkSize })]].isSold;

	}
};