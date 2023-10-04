#pragma once
#include "PointCollider.h"
enum class RayType
{
	BLOCK_RAY = 1, //0x100
	ENTITY_RAY = 2,//0x010
	OTHER_RAYS = 4 //0x001  in case i need more raytypes, each next is anotehr bit 
};
struct RayInfo
{
	glm::vec3 HitPos;
	glm::vec3 HitFromPos;
	bool Miss;

};
class Ray {
public:
	static RayInfo Cast(glm::vec3 Start, glm::vec3 Direction, ChunkManager& chunkManager, float distance,
		RayType Type = RayType::BLOCK_RAY);

};
