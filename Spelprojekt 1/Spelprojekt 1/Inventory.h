#ifndef INVENTORY
#define INVENTORY

#include <vector>

//Temporal Include
#include "Item.h"

class Inventory
{
public:
	Inventory();
	~Inventory();

	void addItem();
	void removeItem();

	//Function to draw the inventory
	void drawInventory(sf::RenderWindow &window);

private:
	typedef std::vector<Item*> InventoryVector;
};

#endif