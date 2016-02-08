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
	typedef std::vector<sf::Texture> TextureVector;
	typedef std::vector<sf::Sprite> SpriteVector;
	typedef std::vector<Item*> ItemVector;

	void update(sf::RenderWindow &window);
	void draw(sf::RenderWindow &window);

	void addItem(Item* item);
	ItemVector getItems();
	std::string getItemId(int index);
	void setDynamicGrid();
	void removeItem();
	void checkCollision(ItemVector items, sf::Vector2f point);
	void swapItems(ItemVector &inputVector, int inputIndex, int swapIndex);
	void invertSelect();

private:
	void setInitialGrid();

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

	//Item specific - grid
	bool mHasSelected;
	sf::RectangleShape mSelectRect;
	sf::Vector2f mSelecPos;
	int mSelectedItem1;
	int mSelectedItem2;

	//Mouse
	sf::RectangleShape mRectShape;
	sf::Vector2i mPixelPos;
	sf::Vector2f mWorldPos;

	//Event
	sf::Event mEvent;
};

#endif