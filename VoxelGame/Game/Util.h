#pragma once
#include <random>
#include <glm/glm.hpp>
class Util {
	std::random_device rd;
	static std::mt19937 gen;
public:
	static int  random(int min, int max);
	static glm::vec3 IndexToVec3(int i);
	static int Vec3ToIndex(glm::vec3 pos);
};
