#pragma once
#include <vector>
#include <glm/glm.hpp>
enum class BlockName {
	Air, Grass, Ore, Stone, Dirt, Wood, BlueRose, Sand
};
enum class BlockModelType {
	Cube, X
};
struct BlockInfo {
	glm::vec2 UVtop;
	glm::vec2 UVside;
	glm::vec2 UVbottom;

	BlockModelType ModelType;
	bool isTransparent=false;
	bool isSold=true;
	BlockInfo(glm::vec2 UVCoord, BlockModelType blockModelType, bool transparent, bool solid) :
		UVtop(UVCoord), UVside(UVCoord), UVbottom(UVCoord),
		 isTransparent(transparent), isSold(solid), ModelType(blockModelType)
	{};
	BlockInfo(glm::vec2 UVCoordTop, glm::vec2 UVCoordSide, glm::vec2 UVCoordBottom, 
		BlockModelType blockModelType, bool transparent, bool solid) :
		UVtop(UVCoordTop), UVside(UVCoordSide), UVbottom(UVCoordBottom), 
		isTransparent(transparent), isSold(solid), ModelType(blockModelType)
	{};
};
 extern std::vector<BlockInfo> BlockTable;
