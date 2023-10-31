#include "World.h"
#include "Util.h"
BlockInfo World::GetBlockOnPosition(glm::vec3 Pos)
{
	return BlockTable[0];
}

void World::SetBlockOnPosition(glm::vec3 Pos, BlockName name)
{
	chunkManager.SetBlockAtPosition(Pos, name);
}

void World::TickWorld(double deltaTime)
{
	HandleActionQueue();
	int* a = &screenWidth;
	player.Update(deltaTime);

	chunkManager.UpdateLoadedChunkMap({ player.getPositon().x / ChunkSize, player.getPositon().z / ChunkSize });

}

void World::HandleActionQueue()
{
	Action action = player.GetAction();
	switch (action.type) {
		case ActionType::Break:
		{
			RayInfo info = Ray::Cast(action.Coordinates, action.Direction, chunkManager, action.Range, RayType::BLOCK_RAY);
			if (!info.Miss)
			{

				SetBlockOnPosition(info.HitPos, BlockName::Air);

			}
		}
		break;
		case ActionType::Place:
		{
			RayInfo info = Ray::Cast(action.Coordinates, action.Direction, chunkManager, action.Range, RayType::BLOCK_RAY);
			if (!info.Miss)
			{

				SetBlockOnPosition(info.HitFromPos, action.blockName);

			}
		}
		break;
	}
}
