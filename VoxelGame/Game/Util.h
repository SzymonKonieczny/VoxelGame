#pragma once
#include <random>
#include <glm/glm.hpp>
#include <string>
#include <sstream>
enum class CommandType {
	None,
	Teleport,
	GeneratorSwap


};
class Util {
	std::random_device rd;
	static std::mt19937 gen;
public:
	static int  random(int min, int max);
	static glm::vec3 IndexToVec3(int i);
	static int Vec3ToIndex(glm::vec3 pos);

	static glm::vec3 WorldPosToChunkPos(glm::vec3 WorldPos);
	static glm::vec3 LocPosAndChunkPosToWorldPos(glm::vec3 LocPos, glm::vec3 ChunkPos);
	static glm::vec3 WorldPosToLocalPos(glm::vec3 WorldPos);
	static CommandType ParseCommand(std::string command, std::vector<float>& args);

};
