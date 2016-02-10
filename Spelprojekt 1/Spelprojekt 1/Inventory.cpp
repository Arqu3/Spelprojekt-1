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
mHasSelected(false),
mItems(),
mEvent(),
mSelectedItem1(-1),
mSelectedItem2(-1)
{
	//Size check
	cout << mItems.size() << endl;

	//Sets initial grid position
	setInitialGrid();

	//Rows and columns
	cout << "Number of columns: " << mCol + 1 << endl;
	cout << "Number of rows: " << mRow + 1 << endl;

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
		mSelectedItem1 = -1;
		mSelectedItem2 = -1;
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
		window.draw(mItems[i]->getSprite());
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
std::string Inventory::getItemId(int index)
{
	return mItems[index]->getId();
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
}


void Inventory::removeItem(Item* item)
{
	//Reverse additem functionality 
	//mItems.pop_back();

	if (mItems.size() > 1)
	{
		for (ItemVector::size_type i = 0; i < mItems.size(); i++)
		{
			if (item->getId() == mItems[i]->getId())
			{
				/*Swaps the chosen element and the last element in the vector
				and removes the new last element*/
				std::swap(mItems[i], mItems.back());
				mItems.pop_back();
				break;
			}
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
			cout << i << endl;
		}
	}
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

		//Swap position
		sf::Vector2f tempPos(inputVector[inputIndex]->getPosition());
		inputVector[inputIndex]->setPosition(inputVector[swapIndex]->getPosition().x, inputVector[swapIndex]->getPosition().y);
		inputVector[swapIndex]->setPosition(tempPos.x, tempPos.y);

		cout << "Swapped" << endl;
	}
}

void Inventory::invertSelect()
{
	mHasSelected = !mHasSelected;
}