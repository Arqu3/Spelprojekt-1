#ifndef INVENTORY
#define INVENTORY

#include <vector>
#include "Item.h"

class Inventory
{
public:
	Inventory();
	~Inventory();
private:
	typedef std::vector<Item*> InventoryVector;
};

#endif