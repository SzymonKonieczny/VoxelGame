#pragma once
#include <random>
#include <glm/glm.hpp>
#include <string>
#include <sstream>
enum class CommandType {
	None,
	Teleport,
	GeneratorSwap,
	PrintSeed,
	PrintPosition


};
class Util {
public:
	static std::mt19937 gen;
	static int  random(int min, int max);
	static glm::vec3 IndexToVec3(int i);
	static int Vec3ToIndex(glm::vec3 pos);
	static float BilinearInterpolation(float q11, float q12, float q21, float q22, glm::vec2 p1, glm::vec2 p2, glm::vec2 p);
	static glm::vec3 WorldPosToChunkPos(glm::vec3 WorldPos);
	static glm::vec3 LocPosAndChunkPosToWorldPos(glm::vec3 LocPos, glm::vec3 ChunkPos);
	static glm::vec3 WorldPosToLocalPos(glm::vec3 WorldPos);
	static CommandType ParseCommand(std::string command, std::vector<float>& args);

};
