#pragma once
#include <vector>
struct ItemStack {
	short amount;
	int ID;
	bool stackable = true;

};

 class  IInventory {
 public:
	 std::vector<ItemStack> ItemStacks;

	  std::vector<ItemStack>& GetItemStacks()
	 {
		 return ItemStacks;
	 }

};