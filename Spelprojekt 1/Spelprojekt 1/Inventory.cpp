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