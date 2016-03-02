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
		mName = "Skruvmakapär";
		mDescription = "En fantastisk Skruvmackapär!";
		mSprite.setPosition(mPosition);
		mSprite.setTexture(*handler.getTexture("thomasbowl.png")); //Add correct texture
		mINVSprite.setTexture(*handler.getTexture("ScrewDeviceINV.png"));
	}

	if (id == "Star")
	{
		mIndex = 1;
		mName = "Stjärna";
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
		mName = "Fiskespö";
		mDescription = "Ett Leksaksfiskespö";
		mSprite.setPosition(mPosition);
		mSprite.setTexture(*handler.getTexture("FishingRod.png")); //Add correct texture
		mINVSprite.setTexture(*handler.getTexture("FishingRodINV.png"));
	}

	if (id == "Magnet")
	{
		mIndex = 4;
		mCraftIndex = 0;
		mName = "Magnet";
		mDescription = "En Magnet";
		mSprite.setPosition(mPosition);
		mSprite.setScale(sf::Vector2f(0.3f, 0.3f));
		mSprite.setTexture(*handler.getTexture("thomasmagnet.png")); //Add correct texture
		mINVSprite.setTexture(*handler.getTexture("MagnetINV.png"));
	}

	if (id == "Astronaut")
	{
		mIndex = 5;
		mName = "Astronaut";
		mDescription = "En Astronaut";
		mSprite.setPosition(mPosition);
		mSprite.setScale(sf::Vector2f(0.4f, 0.4f));
		mSprite.setTexture(*handler.getTexture("thomasastronaut.png")); //Add correct texture
		mINVSprite.setTexture(*handler.getTexture("AstronautINV.png"));
	}

	if (id == "Bowl")
	{
		mIndex = 6;
		mName = "Skål";
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
		mINVSprite.setTexture(*handler.getTexture("ScrewDeviceINV.png")); //Add correct texture

	}

	if (id == "Needle")
	{
		mIndex = 9;
		mName = "Nål";
		mDescription = "";
		mSprite.setPosition(mPosition);
		mSprite.setScale(sf::Vector2f(0.6f, 0.5f));
		mSprite.setTexture(*handler.getTexture("transparent.png")); //Add correct texture
		mINVSprite.setTexture(*handler.getTexture("needleINV.png"));
	}

	if (id == "Earth")
	{
		mIndex = 10;
		mName = "Jordglob";
		mDescription = "";
		mSprite.setPosition(mPosition);
		mSprite.setScale(sf::Vector2f(0.22f, 0.22f));
		mSprite.setTexture(*handler.getTexture("Jordglob.png")); 
		mINVSprite.setTexture(*handler.getTexture("earthINV.png"));
	}

	if (id == "Fish")
	{
		mIndex = 11;
		mName = "Fisk";
		mDescription = "";
		mSprite.setPosition(mPosition);
		mSprite.setScale(sf::Vector2f(0.28f, 0.28f));
		mSprite.setTexture(*handler.getTexture("Fisk2.png")); //Add correct texture
		mINVSprite.setTexture(*handler.getTexture("fishINV.png"));
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
		mINVSprite.setTexture(*handler.getTexture("saturnusringINV.png"));
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
		mINVSprite.setTexture(*handler.getTexture("beigeballINV.png"));
	}

	if (id == "Red Apple")
	{
		mIndex = 15;
		mName = "Rött Äpple";
		mDescription = "";
		mSprite.setPosition(mPosition);
		mSprite.setScale(sf::Vector2f(0.3f, 0.3f));
		mSprite.setTexture(*handler.getTexture("Apelsin.png")); 
		mINVSprite.setTexture(*handler.getTexture("marsINV.png"));
	}

	if (id == "Fruitbowl")
	{
		mIndex = 16;
		mName = "Fruktskål";
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
		mSprite.setScale(sf::Vector2f(0.17f, 0.17f)); //Fixa
		
		mCatWalking = *handler.getTexture("CatWalking.png");
		mCatEating = *handler.getTexture("CatEating.png");

		mSprite.setTexture(mCatWalking); 
		mSprite.setTextureRect(sf::IntRect(0, 0, 1000, 1000));

	
	}

	if (id == "Foodbowl")
	{
		mIndex = 18;
		mName = "Matskål";
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
		mName = "Fiskespö med magnet";
		mSprite.setPosition(mPosition);
		mSprite.setScale(sf::Vector2f(0.3f, 0.3f));
		mSprite.setTexture(*handler.getTexture("FishingRodMagnet.png")); 
		mDescription = "Fiskespö med Magnet";
		mINVSprite.setPosition(mPosition);
		mINVSprite.setTexture(*handler.getTexture("FishingRodMagnet.png")); //Add correct texture

	}

	if (id == "Hole")
	{
		mIndex = 23;
		mName = "Hål";
		mDescription = "";
		mSprite.setPosition(mPosition);
		mSprite.setScale(sf::Vector2f(0.5f, 0.3f));
		mSprite.setTexture(*handler.getTexture("transparent.png")); 
	}

	if (id == "Pearl")
	{
		mIndex = 24;
		mName = "Pärla";
		mDescription = "";
		mSprite.setPosition(mPosition);
		mSprite.setScale(sf::Vector2f(1.0f, 1.0f));
		mSprite.setTexture(*handler.getTexture("Pluto.png")); 
		mINVSprite.setTexture(*handler.getTexture("plutoINV.png")); 
	}

	if (id == "Saturn")
	{
		mIndex = 25;
		mName = "Saturnus";
		mDescription = "";
		mSprite.setPosition(mPosition);
		mSprite.setScale(sf::Vector2f(0.3f, 0.3f));
		mSprite.setTexture(*handler.getTexture("Saturnus.png")); 
		mINVSprite.setTexture(*handler.getTexture("Saturnus.png")); //TODO - Use correct saturnus INV texture
	}

	if (id == "Venus")
	{
		mIndex = 26;
		mName = "Venus";
		mDescription = "";
		mSprite.setPosition(mPosition);
		mSprite.setScale(sf::Vector2f(0.3f, 0.3f));
		mSprite.setTexture(*handler.getTexture("LastLevel_ItemTest1.png")); //Add correct texture
		mINVSprite.setTexture(*handler.getTexture("pocketwatchINV.png"));
	}

	if (id == "WallStar")
	{
		mIndex = 27;
		mName = "Väggstjärna";
		mDescription = "";
		mSprite.setPosition(mPosition);
		mSprite.setScale(sf::Vector2f(0.6f, 0.6f));
		mSprite.setTexture(*handler.getTexture("thomaswallstar.png")); //Add correct texture
	}

	if (id == "Roger")
	{
		mIndex = 28;
		mName = "Fisken Roger";
		mDescription = "";
		mSprite.setPosition(mPosition);
		mSprite.setScale(sf::Vector2f(0.07f, 0.07f));
		mRogerSwim = *handler.getTexture("RogerSwim.png");
		mSprite.setTexture(mRogerSwim);
		mSprite.setOrigin(350, 0);
		mSprite.setTextureRect(sf::IntRect(0, 0, 700, 700));
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

void Item::drawINV(sf::RenderWindow &window)
{
	window.draw(mINVSprite);
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

sf::FloatRect Item::getINVRectangle()
{
	return mINVSprite.getGlobalBounds();
}

sf::Vector2f Item::getPosition()
{
	return mSprite.getPosition();
}

sf::Vector2f Item::getINVPosition()
{
	return mINVSprite.getPosition();
}

void Item::setPosition(float x, float y)
{
	mSprite.setPosition(sf::Vector2f(x, y));
	mDirection = sf::Vector2f(0, 0);
}

void Item::setINVPosition(float x, float y)
{
	mINVSprite.setPosition(sf::Vector2f(x, y));
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

sf::Sprite Item::getINVSprite()
{
	return mINVSprite;
}

void Item::update(float deltaTime)
{
	mCurrentTime += deltaTime;


	//Cat Walk
	if (mActiveAnimation == "CatWalking")
	{
		if (mCurrentTime >= mFrameTime)
		{
			mSprite.setTextureRect(sf::IntRect(mFrameXOffset * 1000, mFrameYOffset * 1000, 1000, 1000));

			if (mCurrentFrame < 27)
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


	if (mActiveAnimation == "RogerSwim")
		{
     	    if (mCurrentTime >= mFrameTime)
			{
		     	mSprite.setTextureRect(sf::IntRect(mFrameXOffset * 700, mFrameYOffset * 700, 700, 700));
					
				if (mCurrentFrame < 32)
				{
					mFrameXOffset += 1;
				
					
					if (mFrameXOffset % 7 == 6)
					{
						mFrameYOffset++;
					}
					if (mFrameXOffset >= 6)

					{
						mFrameXOffset = 0;
					}

					mCurrentFrame += 1;
				}
			}
			else
			{
				mCurrentFrame = 0;
				mFrameXOffset = 0;
				mFrameYOffset = 0;
			}
		mCurrentTime = 0;
	}
	
		//Cat Eating
	if (mActiveAnimation == "CatEating")
	{
		if (mCurrentTime >= mFrameTime)
		{
			mSprite.setTextureRect(sf::IntRect(mFrameXOffset * 1000, mFrameYOffset * 1000, 1000, 1000));
			if (mCurrentFrame < 27)
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


	move(deltaTime);
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


void Item :: setActiveAnimation(std::string name)
{
	if (name == "CatWalking")
	{
		mCurrentFrame = 0;
		mFrameXOffset = 0;
		mFrameYOffset = 0;

		mSprite.setTexture(mCatWalking);
	}

	else if (name == "CatEating")
	{
		mCurrentFrame = 0;
		mFrameXOffset = 0;
		mFrameYOffset = 0;

		mSprite.setTexture(mCatEating);
	}
	else if (name == "RogerSwim")
	{
		mSprite.setTexture(mRogerSwim);
	}

	mActiveAnimation = name;

	
} 
