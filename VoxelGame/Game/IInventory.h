#pragma once
#include <vector>
struct ItemStack {
	short amount;
	int ID;
	bool stackable = true;
	ItemStack( ) : amount(1), ID(0) {}

	ItemStack(int id) : amount(1), ID(id) {}
	ItemStack(int Amount, int id) : amount(Amount), ID(id) {}

};

 class  IInventory {
 public:
	 std::vector<ItemStack> ItemStacks;

	  std::vector<ItemStack>& GetItemStacks()
	 {
		 return ItemStacks;
	 }

};