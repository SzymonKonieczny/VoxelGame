#pragma once
#include <vector>
#include <glm/glm.hpp>
enum class BlockName {
	Air, Grass, Ore, Stone, Dirt, Wood, BlueRose, Sand, Leaves, RedGrass, RedLeaves, GlowWood, Aliceline,
	Cobblestone, Planks
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
	bool isCollidable = true;
	int LightEmission;
	BlockInfo(glm::vec2 UVCoord, BlockModelType blockModelType, bool transparent, bool solid, bool collidable, int lightEmission = 0) :
		UVtop(UVCoord), UVside(UVCoord), UVbottom(UVCoord), //UVs
		 isTransparent(transparent), isSold(solid), ModelType(blockModelType), isCollidable(collidable),  //misc
		LightEmission(lightEmission) //light
	{};
	BlockInfo(glm::vec2 UVCoordTop, glm::vec2 UVCoordSide, glm::vec2 UVCoordBottom, 
		BlockModelType blockModelType, bool transparent, bool solid) :
		UVtop(UVCoordTop), UVside(UVCoordSide), UVbottom(UVCoordBottom), //UVs
		isTransparent(transparent), isSold(solid), ModelType(blockModelType),    //misc
		LightEmission(0)	//light
	{};

};
 extern std::vector<BlockInfo> BlockTable;
