#pragma once
#include <glm/glm.hpp>
#include "ChunkManager.h"
#include "BlockInfo.h"
class PointCollider{
public:
	static bool isBlockAtCollidable(glm::vec3 Pos, ChunkManager& World)
	{

		glm::vec3 ChunkPos = Util::WorldPosToChunkPos(Pos);
		if (ChunkPos.y < 0 || ChunkPos.y >= ChunksInColumn) return false;
		glm::ivec2 ColumnPos = { ChunkPos.x,ChunkPos.z };
		if (World.ChunkMap.contains(ColumnPos))
		{
			glm::vec3 LocalPos = Util::WorldPosToLocalPos(Pos);
			auto& column = World.ChunkMap.at(ColumnPos);
			auto& chunk = column->getChunk(ChunkPos.y);
			int index = Util::Vec3ToIndex(LocalPos);
			if (index < 0) return false;
			return BlockTable[chunk->getBlock(index)].isRayCollidable;
		}
		return false; //chunk doesnt exist, so neither does the block, hence its not solid or collidable
	}
};