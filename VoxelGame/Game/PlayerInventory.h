#pragma once
#include "IInventory.h"
class PlayerInventory : public IInventory { //Unused, not enough time to implement survival-like inventory
	float Unit = 0.05; //Percent of screen resolution per unit of screen-space defined UI

	 std::vector<ItemStack> GetItemStacks();
	void UpdateInventoryGUI();

};