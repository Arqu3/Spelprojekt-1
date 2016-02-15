#include "Inventory.h"

using namespace std;

Inventory::Inventory():
mRow(0),
mCol(-1),
mColNum(3),
mInitialXOffset(100),
mInitialYOffset(100),
mXIncrease(80),
mYIncrease(80),
mItems(),
mCraftableItems(),
mEvent(),
mSelectedItem1(-1),
mSelectedItem2(-1),
mCraftSelect1(-1),
mCraftSelect2(-1),
mIsCraftable(false),
mHasCraft1(false),
mHasCraft2(false)
{
	//Size check
	cout << mItems.size() << endl;

	//Sets initial grid position
	setInitialGrid();

	//Rows and columns
	cout << "Number of columns: " << mCol + 1 << endl;
	cout << "Number of rows: " << mRow + 1 << endl;

	//Crafting rectangles
	mItem1Rect.setSize(sf::Vector2f(70, 70));
	mItem1Rect.setPosition(sf::Vector2f(500, 100));
	mItem1Rect.setFillColor(sf::Color::Cyan);

	mItem2Rect.setSize(sf::Vector2f(70, 70));
	mItem2Rect.setPosition(sf::Vector2f(620, 100));
	mItem2Rect.setFillColor(sf::Color::Cyan);

	//Result rectangle
	mResultRect.setSize(sf::Vector2f(80, 80));
	mResultRect.setPosition(sf::Vector2f(560, 275));

	//Craft button
	mCraftButton.setSize(sf::Vector2f(60, 40));
	mCraftButton.setPosition(sf::Vector2f(560, 200));
	mCraftButton.setFillColor(sf::Color::Yellow);

	//Mouse rectangle
	mRectShape.setSize(sf::Vector2f(10, 10));
	mRectShape.setFillColor(sf::Color::Red);

	//Select rectangle
	mSelectRect.setSize(sf::Vector2f(70, 70));
	mSelectRect.setFillColor(sf::Color::Yellow);
}

Inventory::~Inventory()
{
	mItems.clear();
	mCraftableItems.clear();
}

void Inventory::update(sf::RenderWindow &window)
{
	//Map mouse position to local window
	mPixelPos = sf::Mouse::getPosition(window);
	mWorldPos = window.mapPixelToCoords(mPixelPos);

	//Set mouse rectangle position
	mRectShape.setPosition(sf::Vector2f(mWorldPos));

	//Set select rectangle position
	if (mSelectedItem1 != -1)
	{
		mSelectRect.setPosition(sf::Vector2f(mItems[mSelectedItem1]->getPosition().x - 3, mItems[mSelectedItem1]->getPosition().y - 3));
	}

	//Swap selected items
	if (mSelectedItem1 != -1 && mSelectedItem2 != -1)
	{
		swapItems(mItems, mSelectedItem1, mSelectedItem2);
		deSelect();
	}
}

void Inventory::draw(sf::RenderWindow &window)
{
	if (mSelectedItem1 != -1)
	{
		window.draw(mSelectRect);
	}
	for (ItemVector::size_type i = 0; i < mItems.size(); i++)
	{
		//THIS DOESN'T WORK, NEEDS FIX
		//Set opacity to 50% if item is selected
		//if (mCraftSelect1 != -1)
		//{
		//	mItems[mCraftSelect1]->getSprite().setColor(sf::Color(255, 0, 255, 177));
		//}
		//if (mCraftSelect2 != -1)
		//{
		//	mItems[mCraftSelect2]->getSprite().setColor(sf::Color(255, 0, 255, 177));
		//}

		window.draw(mItems[i]->getSprite());
	}

	window.draw(mItem1Rect);
	window.draw(mItem2Rect);
	window.draw(mCraftButton);
	window.draw(mResultRect);

	//Draw selected items
	if (mHasCraft1)
	{
		window.draw(mItem1->getSprite());
	}
	if (mHasCraft2)
	{
		window.draw(mItem2->getSprite());
	}

	//Draw result
	if (mHasCraft1 && mHasCraft2 && (mItem1->getCraftIndex() != -1 || mItem2->getCraftIndex() != -1))
	{
		int temp = mItems[mCraftSelect1]->getCraftIndex();
		mResultItem = mCraftableItems[temp];
		mResultItem->setPosition(mResultRect.getPosition().x, mResultRect.getPosition().y);
		window.draw(mResultItem->getSprite());
	}

	window.draw(mRectShape);
}

void Inventory::addItem(Item* item)
{
	mItems.push_back(item);
	setDynamicGrid();
}

Inventory::ItemVector Inventory::getItems()
{
	return mItems;
}

//Function to get the id of an item in the ItemVector
string Inventory::getItemId(int index)
{
	if (index >= 0 && (unsigned)index < mItems.size())
	{
		return mItems[index]->getId();
	}
	return "ERROR, INDEX OUT OF RANGE";
}

void Inventory::setInitialGrid()
{
	//Set initial grid with for-loop
	for (ItemVector::size_type i = 0; i < mItems.size(); i++)
	{
		//Adds columns and rows depending on ItemVector size
		mCol++;
		if (mCol >= mColNum)
		{
			mRow++;
			mCol = 0;
		}

		mPosX = mInitialXOffset + (mCol * mXIncrease);
		mPosY = mInitialYOffset + (mRow * mYIncrease);

		mItems[i]->setPosition(mPosX, mPosY);
	}
}

void Inventory::setDynamicGrid()
{
	//Sets dynamic grid without affecting current grid position
	mCol++;
	if (mCol >= mColNum)
	{
		mRow++;
		mCol = 0;
	}

	mPosX = mInitialXOffset + (mCol * mXIncrease);
	mPosY = mInitialYOffset + (mRow * mYIncrease);

	mItems[mItems.size() - 1]->setPosition(mPosX, mPosY);
	cout << mPosX << endl;
	cout << mPosY << endl;
}


//Removes item at specific index
void Inventory::removeItem(int index)
{
	//Reverse additem functionality
	//If index is not last
	if (mItems.size() > 1)
	{
		if ((unsigned)index != mItems.size() - 1)
		{
			swap(mItems[index], mItems.back());
			swapPos(*mItems[index], *mItems.back());
			mItems.pop_back();

			//Sorts index and position
			for (index; (unsigned)index < mItems.size(); index++)
			{
				if ((unsigned)index + 1 != mItems.size())
				{
					swapPos(*mItems[index], *mItems[index + 1]);
					swap(mItems[index], mItems[index + 1]);
				}
			}
		}
		//If index is last
		else
		{
			mItems.pop_back();
		}
	}

	mCol--;
	if (mCol <= -1)
	{
		mRow--;
		mCol = 2;
	}
}

//Checks collision between any element in a vector and a sf::vector point
//If the collision check is true, it returns the specified element it collided with
void Inventory::checkCollision(ItemVector items, sf::Vector2f point)
{
	for (ItemVector::size_type i = 0; i < mItems.size(); i++)
	{
		if (mItems[i]->getRectangle().contains(point))
		{
			//Select first item if no first item is selected
			if (mSelectedItem1 == -1)
			{
				mSelectedItem1 = i;
				cout << "First selected item is: " << mSelectedItem1 << endl;
			}

			//Select second item if has selected first item and no second is selected, also avoid selecting same item twice
			if (mSelectedItem1 != -1 && mSelectedItem2 == -1 && mSelectedItem1 != i)
			{
				mSelectedItem2 = i;
				cout << "Second selected item is: " << mSelectedItem2 << endl;
			}
			return;
		}
	}
	deSelect();
}

void Inventory::setCraftPos(int index)
{
	//Offset position
	sf::Vector2f pos1(mItem1Rect.getPosition().x + 3, mItem1Rect.getPosition().y + 3);
	sf::Vector2f pos2(mItem2Rect.getPosition().x + 3, mItem2Rect.getPosition().y + 3);

	if (mSelectedItem1 != -1)
	{
		//If has selected item and clicks first position
		if (mItem1Rect.getGlobalBounds().contains(mWorldPos))
		{
			mCraftSelect1 = index;
			if (mCraftSelect1 != mCraftSelect2)
			{
				//If pointer is null, place item
				if (!mHasCraft1)
				{
					mHasCraft1 = true;
					mItem1 = new Item(*mItems[index]);
					mItem1->setPosition(pos1.x, pos1.y);
				}
			}
			mSelectedItem1 = -1;
		}

		//If has selected item and clicks position 2
		else if (mItem2Rect.getGlobalBounds().contains(mWorldPos))
		{
			mCraftSelect2 = index;
			if (mCraftSelect2 != mCraftSelect1)
			{
				//If pointer is null, place item
				if (!mHasCraft2)
				{
					mHasCraft2 = true;
					mItem2 = new Item(*mItems[index]);
					mItem2->setPosition(pos2.x, pos2.y);
				}
			}
			mSelectedItem1 = -1;
		}
		return;
	}
	deSelect();
}

void Inventory::craftItem(int index1, int index2)
{
	mCraftSelect1 = -1;
	mCraftSelect2 = -1;

	//Set crafts to false
	mHasCraft1 = false;
	mHasCraft2 = false;

	//More security checks
	//Checks if items aren't the same (should never happen anyway)
	if (mItems[index1]->getIndex() != mItems[index2]->getIndex())
	{
		//Check if items are craftable and have the same crafting index
		if ((mItems[index1]->getCraftIndex() != -1 && mItems[index2]->getCraftIndex() != -1) && mItems[index1]->getCraftIndex() == mItems[index2]->getCraftIndex())
		{
			int temp = mItems[index1]->getCraftIndex();
			addItem(mCraftableItems[temp]);
		}
	}

	//Remove highest index first to prevent index mismatch
	if (index1 > index2)
	{
		removeItem(index1);
		removeItem(index2);
	}
	else if (index2 > index1)
	{
		removeItem(index2);
		removeItem(index1);
	}
	mIsCraftable = false;
}

//Swaps elements in given vector, passed by referens to avoid copy
//Inputindex and swapindex decides what elements are swapped
void Inventory::swapItems(ItemVector &inputVector, int inputIndex, int swapIndex)
{
	//Safety checks
	if (inputVector.size() > 1 && inputIndex != swapIndex && inputIndex >= 0)
	{
		//Swap index
		std::swap(inputVector[inputIndex], inputVector[swapIndex]);

		swapPos(*inputVector[inputIndex], *inputVector[swapIndex]);

		cout << "Swapped" << endl;
	}
}

void Inventory::swapPos(Item &item1, Item &item2)
{
	sf::Vector2f tempPos(item1.getPosition());
	item1.setPosition(item2.getPosition().x, item2.getPosition().y);
	item2.setPosition(tempPos.x, tempPos.y);
}

void Inventory::deSelect()
{
	for (ItemVector::size_type i = 0; i < mItems.size(); i++)
	{
		//Deselect if you click on nothing interactable
		if (!mItems[i]->getRectangle().contains(mWorldPos) && !mItem1Rect.getGlobalBounds().contains(mWorldPos) && !mItem2Rect.getGlobalBounds().contains(mWorldPos) && !mCraftButton.getGlobalBounds().contains(mWorldPos))
		{
			mSelectedItem1 = -1;
			mSelectedItem2 = -1;
			mHasCraft1 = false;
			mHasCraft2 = false;
			mCraftSelect1 = -1;
			mCraftSelect2 = -1;
		}
	}
}

bool Inventory::craftCheck()
{
	if (mCraftButton.getGlobalBounds().contains(mWorldPos))
	{
		//TODO - Add real craftcheck
		if (mCraftSelect1 != -1 && mCraftSelect2 != -1 && mCraftSelect1 != mCraftSelect2)
		{
			if (mItems[mCraftSelect1]->getCraftIndex() != -1 && mItems[mCraftSelect2]->getCraftIndex() != -1)
			{
				if (mItems[mCraftSelect1]->getCraftIndex() == mItems[mCraftSelect2]->getCraftIndex())
				{
					mIsCraftable = true;
				}
			}
		}
		else
		{
			mIsCraftable = false;
		}

		return mIsCraftable;
	}

	return false;
}

//Loads craftable items depending on level
void Inventory::setCraftableItems(ResourceHandler &handler, int index)
{
	if (index == 0)
	{
		if (mCraftableItems.size() > 0)
		{
			mCraftableItems.clear();
		}
		//MAKE SURE CRAFTING INDEX IN ITEM CLASS IS IN CORRECT ORDER!
		mCraftableItems.push_back(new Item(handler, sf::Vector2f(0, 0), "FishingRodMagnet"));
	}
}

int Inventory::getSelectedItem()
{
	return mSelectedItem1;
}

int Inventory::getCraftSelect1()
{
	return mCraftSelect1;
}

int Inventory::getCraftSelect2()
{
	return mCraftSelect2;
}

Item* Inventory::selectedItem()
{
	if (mSelectedItem1 != -1)
	{
		return mItems[mSelectedItem1];
	}
	else
	{
		return NULL;
	}
}