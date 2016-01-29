#ifndef CRAFTING
#define CRAFTING

#include "Inventory.h"

class Crafting
{
public:
	Crafting();
	~Crafting();

	void combineItems(Item *item, Item *item2);
private:
	Inventory *mInventory;
};

#endif