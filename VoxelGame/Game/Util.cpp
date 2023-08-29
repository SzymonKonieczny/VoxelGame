#include "Util.h"

int Util::random(int min, int max)
{
	std::uniform_int_distribution<> dist(min, max);
	std::mt19937 gen;

	return dist(gen);
}
