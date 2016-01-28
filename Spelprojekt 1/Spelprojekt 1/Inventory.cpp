#include "Inventory.h"

Inventory::Inventory():
mItemVector()
{

}

Inventory::~Inventory()
{

}

void Inventory::addItem(Item *item)
{
	mItemVector.push_back(item);
}

void Inventory::removeItem(Item *item)
{
	if (mItemVector.size() > 1)
	{
		for (ItemVector::size_type i = 0; i < mItemVector.size(); i++)
		{
			if (item->getId() == mItemVector[i]->getId())
			{
				std::swap(mItemVector[i], mItemVector.back());
				mItemVector.pop_back();
				break;
			}
		}
	}
}

std::string Inventory::getItemId(int index)
{
	return mItemVector[index]->getId();
}

void Inventory::drawInventory(sf::RenderWindow &window)
{

}