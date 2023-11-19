#pragma once
#include "IInventory.h"
class PlayerInventory : public IInventory {
	float Unit = 0.05; //Percent of screen resolution per unit of screen-space defined UI

	 std::vector<ItemStack> GetItemStacks();
	void UpdateInventoryGUI();

};