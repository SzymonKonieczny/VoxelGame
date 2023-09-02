#include "Util.h"
#include "Global.h"
std::mt19937 Util::gen;

int Util::random(int min, int max)
{
	std::uniform_int_distribution<> dist(min, max);

	return dist(gen);
}

glm::vec3 Util::IndexToVec3(int i)
{
	//order is as follows
	/*
	^
	|
  z	|
	|ChunkSize+1,ChunkSize+2 ...
	|0,1,2,3,4,5, ... ChunkSize
	---------------->
		x

	*/
	int remainder = 0;
	int y = i / (ChunkSize * ChunkSize);
	remainder = i % (ChunkSize * ChunkSize);
	int z = remainder / (ChunkSize);
	remainder = remainder % (ChunkSize);

	int x = remainder;

	return glm::vec3(x, y, z);
}

int Util::Vec3ToIndex(glm::vec3 pos)
{
	return ChunkSize * ChunkSize * pos.y + ChunkSize * pos.z + pos.x;

}
