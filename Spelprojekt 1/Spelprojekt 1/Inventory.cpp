#include "Inventory.h"

Inventory::Inventory():
mItemVector()
{

}

Inventory::~Inventory()
{
	mItemVector.clear();
}

//Adds an item to the inventory
void Inventory::addItem(Item *item)
{
	mItemVector.push_back(item);
}

//Removes an item from the inventory
void Inventory::removeItem(Item *item)
{
	if (mItemVector.size() > 1)
	{
		for (ItemVector::size_type i = 0; i < mItemVector.size(); i++)
		{
			if (item->getId() == mItemVector[i]->getId())
			{
				/*Swaps the chosen element and the last element in the vector
				and removes the new last element*/ 
				std::swap(mItemVector[i], mItemVector.back());
				mItemVector.pop_back();
				break;
			}
		}
	}
}

//Function to get the id of an item in the index list
std::string Inventory::getItemId(int index)
{
	return mItemVector[index]->getId();
}

//Function to draw the inventory
void Inventory::drawInventory(sf::RenderWindow &window)
{
	for (ItemVector::size_type i = 0; i < mItemVector.size(); i++)
	{
		mItemVector[i]->draw(window);
	}
}

//Sorting function, to sort items in the vector
void Inventory::sort()
{
	if (mItemVector.size() > 1)
	{
		int indexId = 0;
		for (ItemVector::size_type i = 0; i < mItemVector.size(); i++)
		{
			for (ItemVector::size_type j = 0; j < mItemVector.size(); j++)
			{
				if (mItemVector[j] < mItemVector[j + 1])
				{
					indexId = mItemVector[j]->getIndex();
					mItemVector[j] = mItemVector[j + 1];
					mItemVector[j + 1]->setIndex(indexId);
				}
			}
		}
	}
}

Inventory::ItemVector Inventory::getItems()
{
	return mItemVector;
}