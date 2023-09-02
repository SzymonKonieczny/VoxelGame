#pragma once
#include <vector>
#include <glm/glm.hpp>
enum class BlockName {
	Air, Grass, Stone, Wood
};
struct BlockInfo {
	glm::vec2 UV;
	bool isTransparent=false;
	bool isSold=true;
	BlockInfo(glm::vec2 UVCoord, bool transparent, bool solid) : UV(UVCoord), isTransparent(transparent), isSold(solid) {};
};
 extern std::vector<BlockInfo> BlockTable;
