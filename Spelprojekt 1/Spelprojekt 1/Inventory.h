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

	void addItem(Item *item);
	void removeItem(Item *item);

	std::string getItemId(int index);

	//Function to draw the inventory
	void drawInventory(sf::RenderWindow &window);

private:
	typedef std::vector<Item*> ItemVector;
	ItemVector mItemVector;
};

#endif