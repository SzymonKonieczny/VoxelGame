#include "Util.h"
std::mt19937 Util::gen;

int Util::random(int min, int max)
{
	std::uniform_int_distribution<> dist(min, max);

	return dist(gen);
}
