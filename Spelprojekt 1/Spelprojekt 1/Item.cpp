#include "Item.h"

Item::Item(ResourceHandler &handler, sf::Vector2f &position, std::string id) :
mPosition(position),
mId(id),
mIsActive(false),
mIsLookable(false),
mIsInteractable(false),
mIsPickupable(false),
mIsLookedAt(false),
mInteracted(false),
isOnPosition(true),
mSpeed(100.0f),
mCraftIndex(-1),
mCurrentFrame(0),
mFrameYOffset(0),
mFrameXOffset(0),
mCurrentTime(0),
mFrameTime(0.03f)
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
		mCraftIndex = 0;
		mName = "Fiskesp�";
		mDescription = "";
		mSprite.setPosition(mPosition);
		mSprite.setScale(sf::Vector2f(0.4f, 0.4f));
		mSprite.setTexture(*handler.getTexture("FishingRod.png")); //Add correct texture
	}

	if (id == "Magnet")
	{
		mIndex = 4;
		mCraftIndex = 0;
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

	//Last Level

	if (id == "Magic Clam")
	{
		mIndex = 8;
		mName = "Magisk Mussla";
		mDescription = "";
		mSprite.setPosition(mPosition);
		mSprite.setScale(sf::Vector2f(0.8f, 0.8f));
		mSprite.setTexture(*handler.getTexture("LastLevel_ItemTest1.png")); //Add correct texture

	}

	if (id == "Needle")
	{
		mIndex = 9;
		mName = "N�l";
		mDescription = "";
		mSprite.setPosition(mPosition);
		mSprite.setScale(sf::Vector2f(0.6f, 0.5f));
		mSprite.setTexture(*handler.getTexture("transparent.png")); //Add correct texture
	}

	if (id == "Earth")
	{
		mIndex = 10;
		mName = "Jordglob";
		mDescription = "";
		mSprite.setPosition(mPosition);
		mSprite.setScale(sf::Vector2f(0.22f, 0.22f));
		mSprite.setTexture(*handler.getTexture("Jordglob.png")); 
	}

	if (id == "Fish")
	{
		mIndex = 11;
		mName = "Fisk";
		mDescription = "";
		mSprite.setPosition(mPosition);
		mSprite.setScale(sf::Vector2f(0.28f, 0.28f));
		mSprite.setTexture(*handler.getTexture("Fisk2.png")); //Add correct texture
	}

	if (id == "Gramophone")
	{
		mIndex = 12;
		mName = "Grammofon";
		mDescription = "";
		mSprite.setPosition(mPosition);
		mSprite.setScale(sf::Vector2f(0.75f, 1.0f)); 
		mSprite.setTexture(*handler.getTexture("transparent.png"));
	}

	if (id == "Hoola Hoop")
	{
		mIndex = 13;
		mCraftIndex = 0;
		mName = "Rockring";
		mDescription = "";
		mSprite.setPosition(mPosition);
		mSprite.setScale(sf::Vector2f(0.3f, 0.3f));
		mSprite.setTexture(*handler.getTexture("LastLevel_ItemTest1.png")); //Add correct texture
	}

	if (id == "Beige Ball")
	{
		mIndex = 14;
		mCraftIndex = 0;
		mName = "Beige Boll";
		mDescription = "";
		mSprite.setPosition(mPosition);
		mSprite.setScale(sf::Vector2f(0.3f, 0.3f));
		mSprite.setTexture(*handler.getTexture("LastLevel_ItemTest1.png")); //Add correct texture
	}

	if (id == "Red Apple")
	{
		mIndex = 15;
		mName = "R�tt �pple";
		mDescription = "";
		mSprite.setPosition(mPosition);
		mSprite.setScale(sf::Vector2f(0.3f, 0.3f));
		mSprite.setTexture(*handler.getTexture("Apelsin.png")); 
	}

	if (id == "Fruitbowl")
	{
		mIndex = 16;
		mName = "Fruktsk�l";
		mDescription = "";
		mSprite.setPosition(mPosition);
		mSprite.setScale(sf::Vector2f(0.5f, 0.5f)); //Fixa
		mSprite.setTexture(*handler.getTexture("transparent.png")); 
	}

	if (id == "Cat")
	{
		mIndex = 17;
		mName = "Katt";
		mDescription = "";
		mSprite.setPosition(mPosition);
		mSprite.setScale(sf::Vector2f(0.01f, 0.01f)); //Fixa
		mSprite.setTexture(*handler.getTexture("Katten.png")); //Add correct texture
	}

	if (id == "Foodbowl")
	{
		mIndex = 18;
		mName = "Matsk�l";
		mDescription = "";
		mSprite.setPosition(mPosition);
		mSprite.setScale(sf::Vector2f(0.3f, 0.3f)); //Fixa
		mSprite.setTexture(*handler.getTexture("transparent.png")); //Add correct texture
	}

	if (id == "Putte")
	{
		mIndex = 19;
		mName = "Putte";
		mDescription = "";
		mSprite.setPosition(mPosition);
		mSprite.setScale(sf::Vector2f(0.01f, 0.01f)); //Fixa
		mSprite.setTexture(*handler.getTexture("PutteSad.png")); //Add correct texture
	}

	if (id == "Dollhouse")
	{
		mIndex = 20;
		mName = "Dockhus";
		mDescription = "";
		mSprite.setPosition(mPosition);
		mSprite.setScale(sf::Vector2f(1.2f, 1.25f)); 
		mSprite.setTexture(*handler.getTexture("transparent.png")); 
	}

	if (id == "Kids")
	{
		mIndex = 21;
		mName = "Barn";
		mDescription = "";
		mSprite.setPosition(mPosition);
		mSprite.setScale(sf::Vector2f(0.03f, 0.03f));
		mSprite.setTexture(*handler.getTexture("Lisa.png"));
	}

	if (id == "FishingRodMagnet")
	{
		mIndex = 22;
		mName = "Fiskesp� med magnet";
		mDescription = "";
		mSprite.setPosition(mPosition);
		mSprite.setScale(sf::Vector2f(0.3f, 0.3f));
		mSprite.setTexture(*handler.getTexture("FishingRodMagnet.png")); //Add correct texture
	}

	if (id == "Hole")
	{
		mIndex = 23;
		mName = "H�l";
		mDescription = "";
		mSprite.setPosition(mPosition);
		mSprite.setScale(sf::Vector2f(0.5f, 0.3f));
		mSprite.setTexture(*handler.getTexture("transparent.png")); //Add correct texture
	}

	if (id == "Pearl")
	{
		mIndex = 24;
		mName = "P�rla";
		mDescription = "";
		mSprite.setPosition(mPosition);
		mSprite.setScale(sf::Vector2f(1.0f, 1.0f));
		mSprite.setTexture(*handler.getTexture("Pluto.png")); //Add correct texture
	}

	if (id == "Saturn")
	{
		mIndex = 25;
		mName = "Saturnus";
		mDescription = "";
		mSprite.setPosition(mPosition);
		mSprite.setScale(sf::Vector2f(0.3f, 0.3f));
		mSprite.setTexture(*handler.getTexture("Saturnus.png")); //Add correct texture
	}

	//Level 3

	if (id == "Trimmer")
	{
		mIndex = 26;
		mName = "H�cksax";
		mDescription = "";
		mSprite.setPosition(mPosition);
		mSprite.setScale(sf::Vector2f(0.6f, 0.6f));
		mSprite.setTexture(*handler.getTexture("Trimmer.png")); //Add correct texture
	}

	if (id == "Stick")
	{
		mIndex = 27;
		mName = "Pinne";
		mDescription = "";
		mSprite.setPosition(mPosition);
		mSprite.setScale(sf::Vector2f(0.9f, 0.9f));
		mSprite.setTexture(*handler.getTexture("Stick.png")); //Add correct texture
	}

	if (id == "Flowers")
	{
		mIndex = 28;
		mName = "Blommor";
		mDescription = "";
		mSprite.setPosition(mPosition);
		mSprite.setScale(sf::Vector2f(5.8f, 1.0f));
		mSprite.setTexture(*handler.getTexture("transparent.png")); //Add correct texture
	}

	if (id == "Leash")
	{
		mIndex = 29;
		mName = "Koppel";
		mDescription = "";
		mSprite.setPosition(mPosition);
		mSprite.setScale(sf::Vector2f(0.3f, 1.0f));
		mSprite.setTexture(*handler.getTexture("LastLevel_ItemTest1.png")); //Add correct texture
	}

	if (id == "Dog")
	{
		mIndex = 30;
		mName = "Hund";
		mDescription = "";
		mSprite.setPosition(mPosition);
		mSprite.setScale(sf::Vector2f(-0.15f, 0.15f));
		mSprite.setOrigin(sf::Vector2f(500, 900));
		mSprite.setTexture(*handler.getTexture("DogRunning.png")); 
		mSprite.setTextureRect(sf::IntRect(0, 0, 1000, 1000));
	}

	if (id == "Flagpole")
	{
		mIndex = 31;
		mName = "Flagst�ng";
		mDescription = "";
		mSprite.setPosition(mPosition);
		mSprite.setScale(sf::Vector2f(0.2f, 1.5f));
		mSprite.setTexture(*handler.getTexture("transparent.png")); //Add correct texture
	}

	if (id == "Singleflower")
	{
		mIndex = 32;
		mName = "Blomma";
		mDescription = "";
		mSprite.setPosition(mPosition);
		mSprite.setScale(sf::Vector2f(0.3f, 0.3f));
		mSprite.setTexture(*handler.getTexture("LastLevel_ItemTest2.png")); //Add correct texture
	}

	//Animations
	mDog = *handler.getTexture("DogRunning.png");
	mGardenLady = *handler.getTexture("GardenLady.png");
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


void Item::toggleInteracted()
{
	//Toggle between true and false
	mInteracted = !mInteracted;
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


bool Item::isInteracted()
{
	return mInteracted;
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
	return mSprite.getGlobalBounds();
}


sf::Vector2f Item::getPosition()
{
	return mSprite.getPosition();
}


void Item::setPosition(float x, float y)
{
	mSprite.setPosition(sf::Vector2f(x, y));
	mDirection = sf::Vector2f(0, 0);
}


void Item::moveToPosition(float x, float y)
{
	//Creates a unit-direction vector that the player follows
	moveTo = sf::Vector2f(x, y);

	float deltaX = (moveTo.x - mSprite.getPosition().x);
	float deltaY = (moveTo.y - mSprite.getPosition().y);

	mDirection = sf::Vector2f(deltaX, deltaY);

	float squareX = (deltaX * deltaX);
	float squareY = (deltaY * deltaY);

	float added = (squareX + squareY);
	float root = sqrt(added);

	sf::Vector2f unit(mDirection.x / root, mDirection.y / root);
	mDirection = unit;
}


void Item::move(float deltaTime)
{
	mMoveToRect = sf::FloatRect(moveTo.x, moveTo.y, 2, 2);

	if (mSprite.getGlobalBounds().intersects(mMoveToRect))
	{
		isOnPosition = true;
	}
	else
	{
		isOnPosition = false;
	}


	if (isOnPosition == false)
	{
		mSprite.setPosition(mSprite.getPosition() + mDirection * mSpeed * deltaTime);
	}

}


bool Item::getIsOnPosition()
{
	return isOnPosition;
}


void Item::setScale(float x, float y)
{
	mSprite.setScale(sf::Vector2f(x, y));
}


sf::Sprite Item::getSprite()
{
	return mSprite;
}


void Item::update(float deltaTime)
{
	move(deltaTime);
	mCurrentTime += deltaTime;

	//Push Animation
	if (mActiveAnimation == "Dog")
	{
		if (mCurrentTime >= mFrameTime)
		{
			mSprite.setTextureRect(sf::IntRect(mFrameXOffset * 1000, mFrameYOffset * 1000, 1000, 1000));
			if (mCurrentFrame < 25)
			{
				mFrameXOffset += 1;
				if (mFrameXOffset % 8 == 7)
				{
					mFrameYOffset++;
				}
				if (mFrameXOffset >= 7)
				{
					mFrameXOffset = 0;
				}
				mCurrentFrame += 1;
			}
			else
			{
				mCurrentFrame = 0;
				mFrameXOffset = 0;
				mFrameYOffset = 0;
			}
			mCurrentTime = 0;
		}
	}

}


float Item::getSpeed()
{
	return mSpeed;
}


void Item::setSpeed(float speed)
{
	mSpeed = speed;
}


void Item::changeTexture(ResourceHandler &handler, std::string filename)
{
	mSprite.setTexture(*handler.getTexture(filename));
}
int Item::getCraftIndex()
{
	return mCraftIndex;
}

void Item::setActiveAnimation(std::string animation)
{
	if (animation == "Dog")
	{
		//Avoid starting animation over if already walking
		if (mActiveAnimation != "Dog")
		{
			mCurrentFrame = 0;
			mFrameXOffset = 0;
			mFrameYOffset = 0;
			mSprite.setTexture(mDog);
		}
		
	}
	else if (animation == "GardenLady")
	{
		if (mActiveAnimation != "GardenLady")
		{
			mCurrentFrame = 0;
			mFrameXOffset = 0;
			mFrameYOffset = 0;
			mSprite.setTexture(mGardenLady);
		}
	}

	mActiveAnimation = animation;
}

std::string Item::getActiveAnimation()
{
	return mActiveAnimation;
}