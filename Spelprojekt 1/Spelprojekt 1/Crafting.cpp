#include "Crafting.h"

Crafting::Crafting()
{

}

Crafting::~Crafting()
{

}

void Crafting::combineItems(Item *item, Item *item2)
{
	if (item->getIndex() == 0 && item2->getIndex() == 1 || item->getIndex() == 1 && item2->getIndex() == 0)
	{
		//Doesn't work
		//mInventory->removeItem(item->getIndex() == 0);
		//mInventory->removeItem(item->getIndex() == 1);
		//mInventory->addItem(item->getIndex() == 2);
	}
}