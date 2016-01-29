#include "Item.h"

Item::Item(ResourceHandler &handler, sf::Vector2f &position, sf::FloatRect &rectangle, std::string id) :
mPosition(position),
mRectangle(rectangle),
mId(id),
mIsActive(false),
mIsLookable(false),
mIsInteractable(false),
mIsPickupable(false)
{
	//Create items here
	if (id == "Skruvmakapär")
	{
		mIndex = 0;
		mName = "Skruvmakapär";
		mSprite.setTexture(*handler.getTexture("Test_2.png")); //Add correct texture
	}

	if (id == "Stjärna")
	{
		mIndex = 1;
		mName = "Stjärna";
		mSprite.setTexture(*handler.getTexture("Test_2.png")); //Add correct texture
	}

	if (id == "Kloss")
	{
		mIndex = 2;
		mName = "Kloss";
		mSprite.setTexture(*handler.getTexture("Test_2.png")); //Add correct texture
	}

	if (id == "Tråd")
	{
		mIndex = 3;
		mName = "Tråd";
		mSprite.setTexture(*handler.getTexture("Test_2.png")); //Add correct texture
	}

	if (id == "Magnet")
	{
		mIndex = 4;
		mName = "Magnet";
		mSprite.setTexture(*handler.getTexture("Test_2.png")); //Add correct texture
	}

	if (id == "Astronaut")
	{
		mIndex = 5;
		mName = "Astronaut";
		mSprite.setTexture(*handler.getTexture("Test_2.png")); //Add correct texture
	}
}

Item::~Item()
{

}

//Toggle functions for flags
void Item::toggleActive()
{
	//Short if-statement. Toggles between true and false
	mIsActive ? !mIsActive : mIsActive;
}

void Item::toggleLookable()
{
	//Short if-statement. Toggles between true and false
	mIsLookable ? !mIsLookable : mIsLookable;
}

void Item::toggleInteractable()
{
	//Short if-statement. Toggles between true and false
	mIsInteractable ? !mIsInteractable : mIsInteractable;
}

void Item::togglePickupable()
{
	//Short if-statement. Toggles between true and false
	mIsPickupable ? !mIsPickupable : mIsPickupable;
}

std::string Item::getId()
{
	return mId;
}

int Item::getIndex()
{
	return mIndex;
}

void Item::setIndex(int value)
{
	mIndex = value;
}

//Get functions of flags (bools)
bool Item::getActive()
{
	return mIsActive;
}

bool Item::getLookable()
{
	return mIsLookable;
}

bool Item::getInteractable()
{
	return mIsInteractable;
}

bool Item::getPickupable()
{
	return mIsPickupable;
}

//Get name
std::string Item::getName()
{
	return mName;
}

//Get bounding boxes
sf::FloatRect Item::getRectangle()
{
	return mRectangle;
}

sf::Vector2f Item::getPosition()
{
	return mPosition;
}