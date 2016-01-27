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
	if (id == "")
	{
		mName = "";
		mSprite.setTexture(*handler.getTexture(0));
		mPosition.x = 0;
		mPosition.y = 0;
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

void Item::addToInventory()
{

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