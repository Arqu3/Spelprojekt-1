#include "Inventory.h"

using namespace std;

Inventory::Inventory(ResourceHandler &handler):
mRow(0),
mCol(-1),
mColNum(3),
mInitialXOffset(350),
mInitialYOffset(150),
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
	mItem1Rect.setSize(sf::Vector2f(60, 65));
	mItem1Rect.setPosition(sf::Vector2f(640, 100));
	mItem1Rect.setFillColor(sf::Color::Cyan);

	mItem2Rect.setSize(sf::Vector2f(60, 65));
	mItem2Rect.setPosition(sf::Vector2f(745, 100));
	mItem2Rect.setFillColor(sf::Color::Cyan);

	//Result rectangle
	mResultRect.setSize(sf::Vector2f(60, 60));
	mResultRect.setPosition(sf::Vector2f(695, 208));

	//Craft button
	mCraftButton.setSize(sf::Vector2f(60, 60));
	mCraftButton.setPosition(sf::Vector2f(695, 208));
	mCraftButton.setFillColor(sf::Color::Yellow);

	//Mouse rectangle
	mRectShape.setSize(sf::Vector2f(10, 10));
	mRectShape.setFillColor(sf::Color::Red);

	//Select rectangle
	mSelectRect.setSize(sf::Vector2f(70, 70));
	mSelectRect.setFillColor(sf::Color::Yellow);

	//UI Rects
	mInventoryRect = sf::FloatRect(sf::Vector2f(30, 305), sf::Vector2f(80, 85));
	mCluesRect = sf::FloatRect(sf::Vector2f(155, 365), sf::Vector2f(75, 80));
	mMemoriesRect = sf::FloatRect(sf::Vector2f(195, 475), sf::Vector2f(75, 80));

	//Sounds
	mCraftingSound.setBuffer(*handler.getSound("Crafting.ogg"));
	mMenuMainUISound.setBuffer(*handler.getSound("Menu_MainUI.ogg"));
	mMenuHatSound.setBuffer(*handler.getSound("Menu_Hat.ogg"));
	mInventoryMoveSound.setBuffer(*handler.getSound("Inventory_Move.ogg"));

	mCraftingSound.setVolume(50);

	//Font / Text
	mFont.loadFromFile("Resources/Fonts/ShadowsIntoLight.ttf");
	mDescription.setFont(mFont);
	mDescription.setCharacterSize(18);
	mDescription.setStyle(sf::Text::Bold);
	mDescription.setColor(sf::Color::Black);
	mDescription.setPosition(400, 420);
	mCraftable.setFont(mFont);
	mCraftable.setCharacterSize(14);
	mCraftable.setStyle(sf::Text::Bold);
	mCraftable.setStyle(sf::Text::Italic);
	mCraftable.setColor(sf::Color::Black);
	mCraftable.setPosition(430, 450);
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
		mSelectRect.setPosition(sf::Vector2f(mItems[mSelectedItem1]->getINVPosition().x - 3, mItems[mSelectedItem1]->getINVPosition().y - 3));
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
		//TODO - THIS DOESN'T WORK, NEEDS FIX
		//Set opacity to 50% if item is selected
		//if (mCraftSelect1 != -1)
		//{
		//	mItems[mCraftSelect1]->getSprite().setColor(sf::Color(255, 0, 255, 177));
		//}
		//if (mCraftSelect2 != -1)
		//{
		//	mItems[mCraftSelect2]->getSprite().setColor(sf::Color(255, 0, 255, 177));
		//}

		window.draw(mItems[i]->getINVSprite());
	}

	//window.draw(mItem1Rect);
	//window.draw(mItem2Rect);
	//window.draw(mCraftButton);
	//window.draw(mResultRect);

	//Draw selected items
	if (mHasCraft1)
	{
		window.draw(mItem1->getINVSprite());
	}
	if (mHasCraft2)
	{
		window.draw(mItem2->getINVSprite());
	}

	//Draw result
	if (mHasCraft1 && mHasCraft2 && (mItem1->getCraftIndex() != -1 || mItem2->getCraftIndex() != -1) && mItem1->getCraftIndex() == mItem2->getCraftIndex())
	{
		int temp = mItems[mCraftSelect1]->getCraftIndex();
		mResultItem = mCraftableItems[temp];
		mResultItem->setINVPosition(mResultRect.getPosition().x, mResultRect.getPosition().y);
		window.draw(mResultItem->getINVSprite());
	}

	//Draw Item Description
	window.draw(mDescription);
	window.draw(mCraftable);
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

		mItems[i]->setINVPosition(mPosX, mPosY);
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

	mItems[mItems.size() - 1]->setINVPosition(mPosX, mPosY);
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

		else
		{
			mItems.pop_back();
		}

		mCraftable.setString("");
	}
	
	//If index is last
	else
	{
		mItems.pop_back();
	}

	mCol--;
	if (mCol <= -1)
	{
		mRow--;
		mCol = 2;
	}

	mSelectedItem1 = -1;
}

//Checks collision between any element in a vector and a sf::vector point
//If the collision check is true, it returns the specified element it collided with
void Inventory::checkCollision(ItemVector items, sf::Vector2f point, UI &ui)
{
	for (ItemVector::size_type i = 0; i < mItems.size(); i++)
	{
		if (mItems[i]->getINVRectangle().contains(point))
		{
			//Select first item if no first item is selected
			if (mSelectedItem1 == -1)
			{
				mSelectedItem1 = i;
				cout << "First selected item is: " << mSelectedItem1 << endl;
				mDescription.setString(mItems[mSelectedItem1]->getDescription());
				if (mItems[mSelectedItem1]->getCraftIndex() != -1)
				{
					mCraftable.setString("Kan Kombineras");
				}
				else
				{
					mCraftable.setString("Kan Ej Kombineras");
				}
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

	if (ui.getHatIconRect().contains(point))
	{
		ui.setState(UI::HAT);
		mMenuHatSound.play();
	}
	else if (ui.getMenuIconRect().contains(point))
	{
		ui.setState(UI::MAINUI);
		mMenuMainUISound.play();
	}
	else if (mInventoryRect.contains(point))
	{
		ui.setState(UI::HAT);
	}
	else if (mCluesRect.contains(point))
	{
		ui.setState(UI::CLUES);
	}
	else if (mMemoriesRect.contains(point))
	{
		ui.setState(UI::MEMORIES);
	}
	else
	{
		deSelect();
	}
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
					mItem1->setINVPosition(pos1.x, pos1.y);
					mInventoryMoveSound.play();
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
					mItem2->setINVPosition(pos2.x, pos2.y);
					mInventoryMoveSound.play();
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
	mCraftingSound.play();
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
		mInventoryMoveSound.play();
	}
}

void Inventory::swapPos(Item &item1, Item &item2)
{
	sf::Vector2f tempPos(item1.getINVPosition());
	item1.setINVPosition(item2.getINVPosition().x, item2.getINVPosition().y);
	item2.setINVPosition(tempPos.x, tempPos.y);
}

void Inventory::deSelect()
{
	for (ItemVector::size_type i = 0; i < mItems.size(); i++)
	{
		//Deselect if you click on nothing interactable
		if (!mItems[i]->getINVRectangle().contains(mWorldPos) && !mItem1Rect.getGlobalBounds().contains(mWorldPos) && !mItem2Rect.getGlobalBounds().contains(mWorldPos) && !mCraftButton.getGlobalBounds().contains(mWorldPos))
		{
			mSelectedItem1 = -1;
			mSelectedItem2 = -1;
			mHasCraft1 = false;
			mHasCraft2 = false;
			mCraftSelect1 = -1;
			mCraftSelect2 = -1;
		}
	}

	mDescription.setString("");
	mCraftable.setString("");
}

bool Inventory::craftCheck()
{
	if (mCraftButton.getGlobalBounds().contains(mWorldPos))
	{
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
	if (mCraftableItems.size() > 0)
	{
		mCraftableItems.clear();
	}

	if (index == 0)
	{
		
		//MAKE SURE CRAFTING INDEX IN ITEM CLASS IS IN CORRECT ORDER!
		mCraftableItems.push_back(new Item(handler, sf::Vector2f(0, 0), "FishingRodMagnet"));
	}
	else if (index == 1)
	{
		mCraftableItems.push_back(new Item(handler, sf::Vector2f(0, 0), "Saturn"));
		mCraftableItems.push_back(new Item(handler, sf::Vector2f(0, 0), "PumpedSaturn"));
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

void Inventory::setGridPosition(sf::Vector2f viewCenter)
{
	//Item Icons
	mInitialXOffset = viewCenter.x - 162;
	for (ItemVector::size_type i = 0; i < mItems.size(); i++)
	{
		mPosX = mInitialXOffset + (i % 3) * (mXIncrease);

		mItems[i]->setINVPosition(mPosX, mItems[i]->getINVPosition().y);
	}

	if (mItem1 != NULL)
	{
		mItem1->setINVPosition(viewCenter.x + 131, 103);
	}
	if (mItem2 != NULL)
	{
		mItem2->setINVPosition(viewCenter.x + 236, 103);
	}

	//Craft Rects
	mItem1Rect.setPosition(sf::Vector2f(viewCenter.x + 128, 100));
	mItem2Rect.setPosition(sf::Vector2f(viewCenter.x + 233, 100));
	mResultRect.setPosition(sf::Vector2f(viewCenter.x + 183, 208));
	mCraftButton.setPosition(sf::Vector2f(viewCenter.x + 183, 208));

	//Item Descriptions
	if (mSelectedItem1 != -1)
	{
		mDescription.setPosition((viewCenter.x - 112) - (float)mItems[mSelectedItem1]->getDescription().length(), 420); // TODO - Make more dynamic, centered etc.
		mCraftable.setPosition((viewCenter.x - 80), 450);
	}
}