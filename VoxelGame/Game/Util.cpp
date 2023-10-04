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

glm::vec3 Util::WorldPosToChunkPos(glm::vec3 WorldPos)
{
	return glm::vec3(
		static_cast<int>(WorldPos.x < 0 ? ((WorldPos.x - ChunkSize) / ChunkSize) : (WorldPos.x / ChunkSize)),
		static_cast<int>(WorldPos.y < 0 ? ((WorldPos.y - ChunkSize) / ChunkSize) : (WorldPos.y / ChunkSize)),
		static_cast<int>(WorldPos.z < 0 ? ((WorldPos.z - ChunkSize) / ChunkSize) : (WorldPos.z / ChunkSize))
	);
}

glm::vec3 Util::LocPosAndChunkPosToWorldPos(glm::vec3 LocPos, glm::vec3 ChunkPos)
{

	return glm::vec3(LocPos.x + ChunkPos.x * ChunkSize, LocPos.y + ChunkPos.y * ChunkSize, LocPos.z + ChunkPos.z  * ChunkSize);


}

glm::vec3 Util::WorldPosToLocalPos(glm::vec3 WorldPos)
{
	int x = static_cast<int>(WorldPos.x);
	int y = static_cast<int>(WorldPos.y);
	int z = static_cast<int>(WorldPos.z);

	//if (x < 0) x--;
	//if (z < 0) z--; // 0 coordinate is in the positives, so negatives start at -1, chence chunkPos X =-1 are blocks -1 to -16, not 0 to 15
	return glm::vec3((ChunkSize + (x % ChunkSize)) % ChunkSize, (ChunkSize + (y % ChunkSize)) % ChunkSize, (ChunkSize + (z % ChunkSize)) % ChunkSize);

}
