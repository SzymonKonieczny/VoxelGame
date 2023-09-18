#pragma once
#include "ChunkManager.h"
#include "Action.h"
#include "BlockInfo.h"
#include "Player.h"
class World {
public:
	ChunkManager chunkManager;
	BlockInfo GetBlockOnPosition(glm::vec3 Pos);
	void SetBlockOnPosition(glm::vec3 Pos, int ID);
	void TickWorld(double deltaTime);
	Player player; //put into World
};
