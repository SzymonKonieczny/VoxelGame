#pragma once
#include <vector>
#include <glm/glm.hpp>

enum class ItemName {
	Air,TestSword
};
struct ItemInfo {
	glm::vec2 UV;
	int CorrespondingBlock;

	ItemInfo(glm::vec2 uv ) : UV(uv), CorrespondingBlock(0){};
	ItemInfo(glm::vec2 uv, int correspondingBlock) : UV(uv), CorrespondingBlock(correspondingBlock) {};

};
extern std::vector<ItemInfo> ItemTable;

