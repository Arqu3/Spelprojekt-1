#ifndef INCLUDED_INVENTORY
#define INCLUDED_INVENTORY

#include <cstdlib>
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <string>

#include "SFML\Graphics.hpp"
#include "SFML\Window.hpp"
#include "SFML\System.hpp"

#include "Item.h"

class Inventory
{
public:
	Inventory();
	~Inventory();

	//Vectors
	typedef std::vector<Item*> ItemVector;

	void update(sf::RenderWindow &window);
	void draw(sf::RenderWindow &window);

	//Items
	void addItem(Item* item);
	ItemVector getItems();
	std::string getItemId(int index);
	void removeItem(int index);
	void craftItem(int index1, int index2);
	void swapItems(ItemVector &inputVector, int inputIndex, int swapIndex);

	//Grid
	void setDynamicGrid();
	void checkCollision(ItemVector items, sf::Vector2f point);
	void setCraftPos(int index);
	bool craftCheck();

	//Get values
	int getSelectedItem();
	int getCraftSelect1();
	int getCraftSelect2();

private:
	void setInitialGrid();
	void swapPos(Item &item1, Item &item2);
	void deSelect();

	//Grid specific
	float mRow;
	float mCol;
	float mPosX;
	float mPosY;
	int mColNum;

	//Grid specific - offset position variables
	float mInitialXOffset;
	float mInitialYOffset;
	float mXIncrease;
	float mYIncrease;

	//ItemVector
	ItemVector mItems;
	ItemVector mCraftableItems;

	//Item specific - grid
	sf::RectangleShape mSelectRect;
	sf::Vector2f mSelectPos;
	int mSelectedItem1;
	int mSelectedItem2;

	//Item specific - crafting
	sf::RectangleShape mItem1Rect;
	sf::RectangleShape mItem2Rect;
	sf::RectangleShape mResultRect;
	sf::RectangleShape mCraftButton;
	Item *mItem1;
	Item *mItem2;
	//Item mResultItem;
	int mCraftSelect1;
	int mCraftSelect2;
	bool mIsCraftable;
	bool mHasCraft1;
	bool mHasCraft2;

	//Mouse
	sf::RectangleShape mRectShape;
	sf::Vector2i mPixelPos;
	sf::Vector2f mWorldPos;

	//Event
	sf::Event mEvent;
};

#endif