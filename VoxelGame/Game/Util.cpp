#include "Util.h"
#include "Global.h"
std::mt19937 Util::gen;

int Util::random(int min, int max)
{
	

	std::uniform_int_distribution<int> distribution(min, max);

	return distribution(gen);

	

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

	if (pos.x < 0 || pos.y < 0 || pos.z < 0)
	{	
		//if (pos.x < 0) pos.x++;
		//if (pos.y < 0) pos.y++;
		//if (pos.z < 0) pos.z++;

		return glm::abs(ChunkSize * ChunkSize * pos.y + ChunkSize * pos.z + pos.x);
	}



	return ChunkSize * ChunkSize * pos.y + ChunkSize *pos.z + pos.x;

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
float Util::BilinearInterpolation(float q11, float q12, float q21, float q22, glm::vec2 p1, glm::vec2 p2, glm::vec2 p)
{
	//p1 and p2 are the corners that defince the rectangle, most cases for terrain gen 0,0 and 15,15 (-1,-1 and 16,16 when "peeking")
	//p is the point you want to get the interpolated value for
	float r1 = ((p2.x - p.x) / (p2.x - p1.x)) * q11 + ((p.x - p1.x) / (p2.x - p1.x)) * q21;
	float r2 = ((p2.x - p.x) / (p2.x - p1.x)) * q12 + ((p.x - p1.x) / (p2.x - p1.x)) * q22;
	return ((p2.y - p.y) / (p2.y - p1.y)) * r1 + ((p.y - p1.y) / (p2.y - p1.y)) * r2;
}
glm::vec3 Util::WorldPosToLocalPos(glm::vec3 WorldPos)
{	

	int x = static_cast<int>(WorldPos.x) %ChunkSize;
	int y = static_cast<int>(WorldPos.y) %ChunkSize;
	int z = static_cast<int>(WorldPos.z) %ChunkSize;

	if (WorldPos.x < 0) x--;
	if (WorldPos.y < 0) y--;
	if (WorldPos.z < 0) z--; 
	// 0 coordinate is in the positives, so negatives start at -1, chence chunkPos X =-1 are blocks -1 to -16, not 0 to 15
	
	return glm::vec3(x, y, z);
	//return glm::vec3((ChunkSize + (x % ChunkSize)) % ChunkSize, (ChunkSize + (y % ChunkSize)) % ChunkSize, (ChunkSize + (z % ChunkSize)) % ChunkSize);

}

CommandType Util::ParseCommand(std::string command, std::vector<float>& args)
{
	std::stringstream ss;
	std::string commandType;
	CommandType ret = CommandType::None;
	ss << command;
	ss >> commandType;
	int temp;

	if (commandType == "tp") ret = CommandType::Teleport;
	if (commandType == "genswap") ret = CommandType::GeneratorSwap;
	if (commandType == "seed") ret = CommandType::PrintSeed;
	if (commandType == "pos") ret = CommandType::PrintPosition;




	while (ss >> temp)
	{
		args.push_back(temp);
	}
	return ret;
}
