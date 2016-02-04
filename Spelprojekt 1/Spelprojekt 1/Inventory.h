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

	typedef std::vector<Item*> ItemVector;

	//Add and remove functions
	void addItem(Item *item);
	void removeItem(Item *item);

	//Get ItemVector
	ItemVector getItems();

	//Get index function
	std::string getItemId(int index);

	//Function to draw the inventory
	void drawInventory(sf::RenderWindow &window);

	//Sorting function
	void sort();

private:
	//Vector for items
	ItemVector mItemVector;
};

#endif