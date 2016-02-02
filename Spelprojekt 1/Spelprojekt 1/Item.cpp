#include "Item.h"

Item::Item(ResourceHandler &handler, sf::Vector2f &position, sf::FloatRect &rectangle, std::string id) :
mPosition(position),
mRectangle(rectangle),
mId(id),
mIsActive(false),
mIsLookable(false),
mIsInteractable(false),
mIsPickupable(false),
mIsLookedAt(false)
{
	//Create items here
	if (id == "Screwdevice")
	{
		mIndex = 0;
		mName = "Skruvmakap�r";
		mDescription = "Testar Description!";
		mSprite.setPosition(mPosition);
		mSprite.setTexture(*handler.getTexture("thomasbowl.png")); //Add correct texture
	}

	if (id == "Star")
	{
		mIndex = 1;
		mName = "Stj�rna";
		mDescription = "";
		mSprite.setPosition(mPosition);
		mSprite.setScale(sf::Vector2f(0.4f, 0.4f));
		mSprite.setTexture(*handler.getTexture("thomasstar.png")); //Add correct texture
	}

	if (id == "Block")
	{
		mIndex = 2;
		mName = "Kloss";
		mDescription = "";
		mSprite.setPosition(mPosition);
		mSprite.setScale(sf::Vector2f(0.3f, 0.3f));
		mSprite.setTexture(*handler.getTexture("thomasblock.png")); //Add correct texture
	}

	if (id == "String")
	{
		mIndex = 3;
		mName = "Tr�d";
		mDescription = "";
		mSprite.setPosition(mPosition);
		mSprite.setScale(sf::Vector2f(0.4f, 0.4f));
		mSprite.setTexture(*handler.getTexture("thomasstring.png")); //Add correct texture
	}

	if (id == "Magnet")
	{
		mIndex = 4;
		mName = "Magnet";
		mDescription = "";
		mSprite.setPosition(mPosition);
		mSprite.setScale(sf::Vector2f(0.3f, 0.3f));
		mSprite.setTexture(*handler.getTexture("thomasmagnet.png")); //Add correct texture
	}

	if (id == "Astronaut")
	{
		mIndex = 5;
		mName = "Astronaut";
		mDescription = "Skruvar p� saker";
		mSprite.setPosition(mPosition);
		mSprite.setScale(sf::Vector2f(0.4f, 0.4f));
		mSprite.setTexture(*handler.getTexture("thomasastronaut.png")); //Add correct texture
	}

	if (id == "Bowl")
	{
		mIndex = 6;
		mName = "Sk�l";
		mDescription = "";
		mSprite.setPosition(mPosition);
		mSprite.setScale(sf::Vector2f(0.3f, 0.3f));
		mSprite.setTexture(*handler.getTexture("thomasbowl.png")); //Add correct texture
	}

	if (id == "Cube")
	{
		mIndex = 7;
		mName = "Kub";
		mDescription = "";
		mSprite.setPosition(mPosition);
		mSprite.setScale(sf::Vector2f(0.3f, 0.3f));
		mSprite.setTexture(*handler.getTexture("thomascube.png")); //Add correct texture
	}
}

Item::~Item()
{

}

//Toggle functions for flags
void Item::toggleActive()
{
	//Toggles between true and false
	mIsActive = !mIsActive;
}

void Item::toggleLookable()
{
	//Toggles between true and false
	mIsLookable = !mIsLookable;
}

void Item::toggleInteractable()
{
	//Toggles between true and false
	mIsInteractable = !mIsInteractable;
}

void Item::togglePickupable()
{
	//Toggles between true and false
	mIsPickupable = !mIsPickupable;
}

void Item::toggleIsLookedAt()
{
	//Toggle between true and false
	mIsLookedAt = !mIsLookedAt;
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

void Item::draw(sf::RenderWindow &window)
{
	window.draw(mSprite);
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

bool Item::isLookedAt()
{
	return mIsLookedAt;
}

//Get name
std::string Item::getName()
{
	return mName;
}

//Get Description
std::string Item::getDescription()
{
	return mDescription;
}

//Get bounding boxes
sf::FloatRect Item::getRectangle()
{
	//return mRectangle;
	return mSprite.getGlobalBounds();
}

sf::Vector2f Item::getPosition()
{
	return mPosition;
}

void Item::setPosition(float x, float y)
{
	mSprite.setPosition(sf::Vector2f(x, y));
}

void Item::setScale(float x, float y)
{
	mSprite.setScale(sf::Vector2f(x, y));
}