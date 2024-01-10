#include "Ray.h"


RayInfo Ray::Cast(glm::vec3 Start, glm::vec3 Direction, ChunkManager& chunkManager, float distance, RayType Type)
{

	Direction = glm::normalize(Direction);
	RayInfo info;
	info.Miss = true;
	info.HitFromPos = Start;//glm::floor(Start);
	info.HitPos = Start;//;glm::floor(Start);

	for (float i = 0; i < distance; i += 0.1f)
	{
		info.HitFromPos = info.HitPos;
		//info.HitPos = info.HitFromPos + (Direction * 0.1f);
		if ((int)Type & (int)RayType::BLOCK_RAY)
		{
			info.HitPos = info.HitFromPos;
			bool hit = false;
			info.HitPos.x += (Direction.x * 0.1f);
			if (PointCollider::isBlockAtCollidable(info.HitPos, chunkManager)) hit = true;
			else {
				info.HitPos.z += (Direction.z * 0.1f);
				if (PointCollider::isBlockAtCollidable(info.HitPos, chunkManager)) hit = true;
				else
				{
					info.HitPos.y += (Direction.y * 0.1f);
							if (PointCollider::isBlockAtCollidable(info.HitPos, chunkManager)) hit = true;
		
				}
			}


		
			if (hit)
			{
				info.HitPos = glm::floor(info.HitPos);
				info.HitFromPos = glm::floor(info.HitFromPos);
				info.Miss = false;
				return info;
			}

		}

	}

	return info;
	return RayInfo();
}