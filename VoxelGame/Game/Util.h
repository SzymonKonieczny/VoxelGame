#pragma once
#include <random>

class Util {
	std::random_device rd;
	static std::mt19937 gen;
public:
	static int  random(int min, int max);

};
