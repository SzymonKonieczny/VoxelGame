#pragma once
#include "../Renderer/Mesh.h"
class Item {

};
class BlockItem : public Item {

};
struct ItemStack {
	short amount;
	bool stackable;
	int ID;

};

 class  IInventory {

	 virtual std::vector<ItemStack> GetItemStacks() = 0;

};