#pragma once
#include "ChunkManager.h"
#include "Action.h"
#include "BlockInfo.h"
#include "Player.h"
#include "Ray.h"

class World {
public:
	ChunkManager chunkManager;
	BlockInfo GetBlockOnPosition(glm::vec3 Pos);
	void SetBlockOnPosition(glm::vec3 Pos, BlockName name);
	void TickWorld(double deltaTime);
	void HandleActionQueue(int amount);
	Player player; 
};
