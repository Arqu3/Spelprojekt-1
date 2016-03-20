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
mFrameTime(0.05f),
mWalkable(true)
{
	//Create items here
	if (id == "Screwdevice")
	{
		mIndex = 0;
		mName = "Skruvmakap�r";
		mDescription = "En fantastisk Skruvmackap�r!";
		mSprite.setPosition(mPosition);
		mSprite.setTexture(*handler.getTexture("thomasbowl.png")); //Add correct texture
		mINVSprite.setTexture(*handler.getTexture("ScrewDeviceINV.png"));
	}

	if (id == "Star")
	{
		mIndex = 1;
		mName = "Stj�rna";
		mDescription = "Stj�rna";
		mSprite.setPosition(mPosition);
		mSprite.setScale(sf::Vector2f(0.4f, 0.4f));
		mSprite.setTexture(*handler.getTexture("thomasstar.png"));
	}

	if (id == "Block")
	{
		mIndex = 2;
		mName = "Kloss";
		mDescription = "Kloss";
		mSprite.setPosition(mPosition);
		mSprite.setScale(sf::Vector2f(0.3f, 0.3f));
		mSprite.setTexture(*handler.getTexture("thomasblock.png"));
	}

	if (id == "String")
	{
		mIndex = 3;
		mCraftIndex = 0;
		mName = "Fiskesp�";
		mDescription = "Leksaksfiskesp�";
		mSprite.setPosition(mPosition);
		mSprite.setTexture(*handler.getTexture("FishingRod.png"));
		mINVSprite.setTexture(*handler.getTexture("FishingRodINV.png"));
	}

	if (id == "Magnet")
	{
		mIndex = 4;
		mCraftIndex = 0;
		mName = "Magnet";
		mDescription = "Magnet";
		mSprite.setPosition(mPosition);
		mSprite.setScale(sf::Vector2f(0.3f, 0.3f));
		mSprite.setTexture(*handler.getTexture("thomasmagnet.png"));
		mINVSprite.setTexture(*handler.getTexture("MagnetINV.png"));
	}

	if (id == "Astronaut")
	{
		mIndex = 5;
		mName = "Astronaut";
		mDescription = "Astronaut";
		mSprite.setPosition(mPosition);
		mSprite.setScale(sf::Vector2f(0.4f, 0.4f));
		mSprite.setTexture(*handler.getTexture("thomasastronaut.png"));
		mINVSprite.setTexture(*handler.getTexture("AstronautINV.png"));
	}

	if (id == "Bowl")
	{
		mIndex = 6;
		mName = "Sk�l";
		mDescription = "Sk�l";
		mSprite.setPosition(mPosition);
		mSprite.setScale(sf::Vector2f(0.3f, 0.3f));
		mSprite.setTexture(*handler.getTexture("thomasbowl.png"));
	}

	if (id == "Cube")
	{
		mIndex = 7;
		mName = "Kub";
		mDescription = "Rubiks kub";
		mSprite.setPosition(mPosition);
		mSprite.setScale(sf::Vector2f(0.3f, 0.3f));
		mSprite.setTexture(*handler.getTexture("thomascube.png"));
	}

	//Last Level

	if (id == "Magic Clam")
	{
		mIndex = 8;
		mName = "Magisk Mussla";
		mDescription = "Mussla";
		mSprite.setPosition(mPosition);
		mSprite.setScale(sf::Vector2f(0.8f, 0.8f));
		mSprite.setTexture(*handler.getTexture("LastLevel_ItemTest1.png")); //Add correct texture
		mINVSprite.setTexture(*handler.getTexture("clamINV.png"));
	}

	if (id == "Needle")
	{
		mIndex = 9;
		mName = "N�l";
		mDescription = "N�l";
		mSprite.setPosition(mPosition);
		mSprite.setScale(sf::Vector2f(0.6f, 0.5f));
		mSprite.setTexture(*handler.getTexture("transparent.png"));
		mINVSprite.setTexture(*handler.getTexture("needleINV.png"));
	}

	if (id == "Earth")
	{
		mIndex = 10;
		mName = "Jordglob";
		mDescription = "Jordglob";
		mSprite.setPosition(mPosition);
		mSprite.setScale(sf::Vector2f(0.22f, 0.22f));
		mSprite.setTexture(*handler.getTexture("Jordglob.png")); 
		mINVSprite.setTexture(*handler.getTexture("earthINV.png"));
	}

	if (id == "Fish")
	{
		mIndex = 11;
		mName = "Fisk";
		mDescription = "Fisk";
		mSprite.setPosition(mPosition);
		mSprite.setScale(sf::Vector2f(0.28f, 0.28f));
		mSprite.setTexture(*handler.getTexture("Fisk2.png")); //Add correct texture
		mINVSprite.setTexture(*handler.getTexture("fishINV.png"));
	}

	if (id == "Gramophone")
	{
		mIndex = 12;
		mName = "Grammofon";
		mDescription = "Grammofon";
		mSprite.setPosition(mPosition);
		mSprite.setScale(sf::Vector2f(0.75f, 1.3f)); 
		mSprite.setTexture(*handler.getTexture("transparent.png"));
	}

	if (id == "Hoola Hoop")
	{
		mIndex = 13;
		mCraftIndex = 0;
		mName = "Rockring";
		mDescription = "Rockring";
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
		mDescription = "Beige boll";
		mSprite.setPosition(mPosition);
		mSprite.setScale(sf::Vector2f(0.3f, 0.3f));
		mSprite.setTexture(*handler.getTexture("LastLevel_ItemTest1.png")); //Add correct texture
		mINVSprite.setTexture(*handler.getTexture("beigeballINV.png"));
	}

	if (id == "Red Apple")
	{
		mIndex = 15;
		mName = "R�tt �pple";
		mDescription = "Apelsin";
		mSprite.setPosition(mPosition);
		mSprite.setScale(sf::Vector2f(0.3f, 0.3f));
		mSprite.setTexture(*handler.getTexture("Apelsin.png")); 
		mINVSprite.setTexture(*handler.getTexture("marsINV.png"));
	}

	if (id == "Fruitbowl")
	{
		mIndex = 16;
		mName = "Fruktsk�l";
		mDescription = "Fruktsk�l";
		mSprite.setPosition(mPosition);
		mSprite.setScale(sf::Vector2f(0.6f, 0.5f));
		mSprite.setTexture(*handler.getTexture("transparent.png")); 
	}

	if (id == "Cat")
	{
		mIndex = 17;
		mName = "Katt";
		mDescription = "Katt";
		mSprite.setPosition(mPosition);
		mSprite.setScale(sf::Vector2f(0.17f, 0.17f)); //Fixa
		/*mCatWalking = *handler.getTexture("CatWalking.png");
		mCatEating = *handler.getTexture("CatEating.png");*/
		mCatWalking.loadFromFile("Resources/Textures/CatWalking.png");
		mCatEating.loadFromFile("Resources/Textures/CatEating.png");
		mSprite.setTexture(mCatWalking); 
		mSprite.setTextureRect(sf::IntRect(0, 0, 1000, 1000));
	}

	if (id == "Foodbowl")
	{
		mIndex = 18;
		mName = "Matsk�l";
		mDescription = "Matsk�l";
		mSprite.setPosition(mPosition);
		mSprite.setScale(sf::Vector2f(0.5f, 0.4f));
		mSprite.setTexture(*handler.getTexture("transparent.png")); //Add correct texture
	}

	if (id == "Putte")
	{
		mIndex = 19;
		mName = "Putte";
		mDescription = "Putte";
		mSprite.setPosition(mPosition);
		mSprite.setScale(sf::Vector2f(0.01f, 0.01f)); //Fixa
		mSprite.setTexture(*handler.getTexture("PutteSad.png")); //Add correct texture
	}

	if (id == "Dollhouse")
	{
		mIndex = 20;
		mName = "Dockhus";
		mDescription = "Dockhus";
		mSprite.setPosition(mPosition);
		mSprite.setScale(sf::Vector2f(1.2f, 1.25f)); 
		mSprite.setTexture(*handler.getTexture("transparent.png")); 
	}

	if (id == "Kids")
	{
		mIndex = 21;
		mName = "Barn";
		mDescription = "Lisa och Totte";
		mSprite.setPosition(mPosition);
		mSprite.setScale(sf::Vector2f(0.03f, 0.03f));
		mSprite.setTexture(*handler.getTexture("LisaTotte.png"));
	}

	if (id == "FishingRodMagnet")
	{
		mIndex = 22;
		mName = "Fiskesp� med magnet";
		mSprite.setPosition(mPosition);
		mSprite.setScale(sf::Vector2f(0.3f, 0.3f));
		mSprite.setTexture(*handler.getTexture("FishingRodMagnet.png")); 
		mDescription = "Fiskesp� med Magnet";
		mINVSprite.setPosition(mPosition);
		mINVSprite.setTexture(*handler.getTexture("FishingRodMagnet.png")); //Add correct texture

	}

	if (id == "Hole")
	{
		mIndex = 23;
		mName = "H�l";
		mDescription = "H�l";
		mSprite.setPosition(mPosition);
		mSprite.setScale(sf::Vector2f(0.5f, 0.3f));
		mSprite.setTexture(*handler.getTexture("transparent.png")); 
	}

	if (id == "Pearl")
	{
		mIndex = 24;
		mName = "P�rla";
		mDescription = "P�rla";
		mSprite.setPosition(mPosition);
		mSprite.setScale(sf::Vector2f(1.0f, 1.0f));
		mSprite.setTexture(*handler.getTexture("Pluto.png")); 
		mINVSprite.setTexture(*handler.getTexture("plutoINV.png"));
	}

	if (id == "Saturn")
	{
		mIndex = 25;
		mCraftIndex = 0;
		mName = "Saturnus";
		mDescription = "Saturnus";
		mSprite.setPosition(mPosition);
		mSprite.setScale(sf::Vector2f(0.3f, 0.3f));
		mSprite.setTexture(*handler.getTexture("Saturnus.png")); 
		mINVSprite.setTexture(*handler.getTexture("saturnusINV.png")); //TODO - Use correct (unpumped) saturnus INV texture
	}

	if (id == "Venus")
	{
		mIndex = 26;
		mName = "Venus";
		mDescription = "Venus";
		mSprite.setPosition(mPosition);
		mSprite.setScale(sf::Vector2f(0.3f, 0.3f));
		mSprite.setTexture(*handler.getTexture("Venus.png"));
		mINVSprite.setTexture(*handler.getTexture("pocketwatchINV.png"));
	}

	if (id == "WallStar")
	{

		mIndex = 27;
		mName = "V�ggstj�rna";
		mDescription = "Stj�rna p� v�ggen";
		mSprite.setPosition(mPosition);
		mSprite.setScale(sf::Vector2f(0.6f, 0.6f));
		mSprite.setTexture(*handler.getTexture("thomaswallstar.png"));
	}

	if (id == "Roger")
	{
		mIndex = 28;
		mName = "Fisken Roger";
		mDescription = "G�tfisken Roger";
		mSprite.setPosition(mPosition);
		mSprite.setScale(sf::Vector2f(0.07f, 0.07f));
		mRogerSwim = *handler.getTexture("RogerSwim.png");
		mSprite.setTexture(mRogerSwim);
		mSprite.setOrigin(350, 0);
		mSprite.setTextureRect(sf::IntRect(0, 0, 700, 700));
	}

	//Level 3

	if (id == "Trimmer")
	{
		mIndex = 31;
		mName = "H�cksax";
		mDescription = "H�cksax";
		mSprite.setPosition(mPosition);
		mSprite.setScale(sf::Vector2f(0.6f, 0.6f));
		mSprite.setTexture(*handler.getTexture("Trimmer.png")); //Add correct texture
		mINVSprite.setTexture(*handler.getTexture("TrimmerIcon.png"));
	}

	if (id == "Stick")
	{
		mIndex = 32;
		mName = "Pinne";
		mDescription = "Pinne";
		mSprite.setPosition(mPosition);
		mSprite.setScale(sf::Vector2f(0.9f, 0.9f));
		mSprite.setTexture(*handler.getTexture("Stick.png")); //Add correct texture
		mINVSprite.setTexture(*handler.getTexture("StickIcon.png"));
	}

	if (id == "Flowers")
	{
		mIndex = 33;
		mName = "Blommor";
		mDescription = "Blommor";
		mSprite.setPosition(mPosition);
		mSprite.setScale(sf::Vector2f(5.8f, 1.0f));
		mSprite.setTexture(*handler.getTexture("transparent.png")); //Add correct texture
		mINVSprite.setTexture(*handler.getTexture("LastLevel_ItemTest2.png"));
	}

	if (id == "Leash")
	{
		mIndex = 34;
		mName = "Koppel";
		mDescription = "Koppel";
		mSprite.setPosition(mPosition);
		mSprite.setScale(sf::Vector2f(0.3f, 1.0f));
		mSprite.setTexture(*handler.getTexture("LastLevel_ItemTest1.png")); //Add correct texture
	}

	if (id == "Dog")
	{
		mIndex = 35;
		mName = "Hund";
		mDescription = "Hund";
		mSprite.setPosition(mPosition);
		mSprite.setScale(sf::Vector2f(-0.15f, 0.15f));
		mSprite.setOrigin(sf::Vector2f(500, 900));
		/*mDog = *handler.getTexture("DogRunning.png");*/
		mDog.loadFromFile("Resources/Textures/DogRunning.png");
		mSprite.setTexture(mDog); 
		mSprite.setTextureRect(sf::IntRect(0, 0, 1000, 1000));
	}

	if (id == "Flagpole")
	{
		mIndex = 36;
		mName = "Flagst�ng";
		mDescription = "Flaggst�ng";
		mSprite.setPosition(mPosition);
		mSprite.setScale(sf::Vector2f(0.2f, 1.5f));
		mSprite.setTexture(*handler.getTexture("transparent.png")); //Add correct texture
	}

	if (id == "Singleflower")
	{
		mIndex = 37;
		mName = "Blomma";
		mDescription = "Blomma";
		mSprite.setPosition(mPosition);
		mSprite.setScale(sf::Vector2f(0.3f, 0.3f));
		mSprite.setTexture(*handler.getTexture("LastLevel_ItemTest2.png")); //Add correct texture
	}

	if (id == "Cable")
	{
		mIndex = 38;
		mCraftIndex = 0;
		mName = "Kabel";
		mDescription = "Kabel";
		mSprite.setPosition(mPosition);
		mSprite.setScale(sf::Vector2f(0.3f, 0.3f));
		mSprite.setTexture(*handler.getTexture("LastLevel_ItemTest1.png")); //Add correct texture
		mINVSprite.setTexture(*handler.getTexture("LastLevel_ItemTest2.png")); //Add correct texture
	}

	if (id == "Airbag")
	{
		mIndex = 39;
		mCraftIndex = 0;
		mName = "Airbag";
		mDescription = "Airbag";
		mSprite.setPosition(mPosition);
		mSprite.setScale(sf::Vector2f(0.3f, 0.3f));
		mSprite.setTexture(*handler.getTexture("LastLevel_ItemTest1.png")); //Add correct texture
		mINVSprite.setTexture(*handler.getTexture("LastLevel_ItemTest2.png")); //Add correct texture
	}

	if (id == "FilledBalloon")
	{
		mIndex = 40;
		mName = "�ngfylld ballong";
		mDescription = "�ngfylld ballong";
		mSprite.setPosition(mPosition);
		mSprite.setScale(sf::Vector2f(0.3f, 0.3f));
		mSprite.setTexture(*handler.getTexture("LastLevel_ItemTest1.png")); //Add correct texture
		mINVSprite.setTexture(*handler.getTexture("LastLevel_ItemTest2.png")); //Add correct texture
	}

	if (id == "Juice")
	{
		mIndex = 41;
		mName = "Saft";
		mDescription = "Saft";
		mSprite.setPosition(mPosition);
		mSprite.setScale(sf::Vector2f(0.3f, 0.3f));
		mSprite.setTexture(*handler.getTexture("LastLevel_ItemTest1.png")); //Add correct texture
		mINVSprite.setTexture(*handler.getTexture("LastLevel_ItemTest2.png")); //Add correct texture
	}

	if (id == "Glove")
	{
		mIndex = 42;
		mCraftIndex = 1;
		mName = "Handske";
		mDescription = "Handske";
		mSprite.setPosition(mPosition);
		mSprite.setScale(sf::Vector2f(0.3f, 0.3f));
		mSprite.setTexture(*handler.getTexture("LastLevel_ItemTest1.png")); //Add correct texture
		mINVSprite.setTexture(*handler.getTexture("LastLevel_ItemTest2.png")); //Add correct texture
	}

	if (id == "Key")
	{
		mIndex = 43;
		mName = "Nyckel";
		mDescription = "Nyckel";
		mSprite.setPosition(mPosition);
		mSprite.setScale(sf::Vector2f(0.3f, 0.3f));
		mSprite.setTexture(*handler.getTexture("LastLevel_ItemTest1.png")); //Add correct texture
		mINVSprite.setTexture(*handler.getTexture("LastLevel_ItemTest2.png")); //Add correct texture
	}

	if (id == "WorkshopStick")
	{
		mIndex = 44;
		mCraftIndex = 1;
		mName = "Pinne";
		mDescription = "Pinne";
		mSprite.setPosition(mPosition);
		mSprite.setScale(sf::Vector2f(0.3f, 0.3f));
		mSprite.setTexture(*handler.getTexture("LastLevel_ItemTest1.png")); //Add correct texture
		mINVSprite.setTexture(*handler.getTexture("LastLevel_ItemTest2.png")); //Add correct texture
	}

	if (id == "Cloth")
	{
		mIndex = 45;
		mName = "Trasa";
		mDescription = "Trasa";
		mSprite.setPosition(mPosition);
		mSprite.setScale(sf::Vector2f(0.3f, 0.3f));
		mSprite.setTexture(*handler.getTexture("LastLevel_ItemTest1.png")); //Add correct texture
		mINVSprite.setTexture(*handler.getTexture("LastLevel_ItemTest2.png")); //Add correct texture
	}

	if (id == "Can")
	{
		mIndex = 46;
		mName = "Burk";
		mDescription = "Burk";
		mSprite.setPosition(mPosition);
		mSprite.setScale(sf::Vector2f(0.3f, 0.3f));
		mSprite.setTexture(*handler.getTexture("LastLevel_ItemTest1.png")); //Add correct texture
		mINVSprite.setTexture(*handler.getTexture("LastLevel_ItemTest2.png")); //Add correct texture
	}

	if (id == "Arnold")
	{
		mIndex = 47;
		mName = "Arnold";
		mDescription = "Arnold";
		mSprite.setPosition(mPosition);
		mSprite.setScale(sf::Vector2f(0.3f, 0.3f));
		mSprite.setTexture(*handler.getTexture("LastLevel_ItemTest1.png")); //Add correct texture
		mINVSprite.setTexture(*handler.getTexture("LastLevel_ItemTest2.png")); //Add correct texture
	}

	if (id == "Balloon")
	{
		mIndex = 48;
		mCraftIndex = 0;
		mName = "Ballong";
		mDescription = "Ballong";
		mSprite.setPosition(mPosition);
		mSprite.setScale(sf::Vector2f(0.3f, 0.3f));
		mSprite.setTexture(*handler.getTexture("LastLevel_ItemTest1.png")); //Add correct texture
		mINVSprite.setTexture(*handler.getTexture("LastLevel_ItemTest2.png")); //Add correct texture
	}

	if (id == "SteamMachine")
	{
		mIndex = 49;
		mName = "�ngmaskin";
		mDescription = "�ngmaskin";
		mSprite.setPosition(mPosition);
		mSprite.setScale(sf::Vector2f(0.3f, 0.3f));
		mSprite.setTexture(*handler.getTexture("LastLevel_ItemTest1.png")); //Add correct texture
		mINVSprite.setTexture(*handler.getTexture("LastLevel_ItemTest2.png")); //Add correct texture
	}

	if (id == "Vise")
	{
		mIndex = 50;
		mName = "Skruvst�d";
		mDescription = "Skruvst�d";
		mSprite.setPosition(mPosition);
		mSprite.setScale(sf::Vector2f(0.3f, 0.3f));
		mSprite.setTexture(*handler.getTexture("LastLevel_ItemTest1.png")); //Add correct texture
		mINVSprite.setTexture(*handler.getTexture("LastLevel_ItemTest2.png")); //Add correct texture
	}

	if (id == "Drawer")
	{
		mIndex = 51;
		mName = "L�da";
		mDescription = "L�da";
		mSprite.setPosition(mPosition);
		mSprite.setScale(sf::Vector2f(0.3f, 0.3f));
		mSprite.setTexture(*handler.getTexture("LastLevel_ItemTest1.png")); //Add correct texture
		mINVSprite.setTexture(*handler.getTexture("LastLevel_ItemTest2.png")); //Add correct texture
	}

	if (id == "ExtensionArm")
	{
		mIndex = 52;
		mCraftIndex = 1;
		mName = "F�rl�ngningsarm";
		mDescription = "F�rl�ngningsarm";
		mSprite.setPosition(mPosition);
		mSprite.setScale(sf::Vector2f(0.3f, 0.3f));
		mSprite.setTexture(*handler.getTexture("LastLevel_ItemTest1.png")); //Add correct texture
		mINVSprite.setTexture(*handler.getTexture("LastLevel_ItemTest2.png")); //Add correct texture
	}

	//Animations

	/*mGardenLady = *handler.getTexture("GardenLady.png");*/
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
			else
			{
				mCurrentFrame = 0;
				mFrameXOffset = 0;
				mFrameYOffset = 0;
			}
			mCurrentTime = 0;
		}
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

	else if (animation == "RogerSwim")
	{
		mSprite.setTexture(mRogerSwim);
	}


	else if (animation== "CatWalking")
	{
		mCurrentFrame = 0;
		mFrameXOffset = 0;
		mFrameYOffset = 0;

		mSprite.setTexture(mCatWalking);
	}

	else if (animation == "CatEating")
	{
		mCurrentFrame = 0;
		mFrameXOffset = 0;
		mFrameYOffset = 0;

		mSprite.setTexture(mCatEating);
	}

	else if (animation == "RogerSwim")
	{
		mCurrentFrame = 0;
		mFrameXOffset = 0;
		mFrameYOffset = 0;

		mSprite.setTexture(mRogerSwim);
	}
	
	mActiveAnimation = animation;
}

std::string Item::getActiveAnimation()
{
	return mActiveAnimation;
}

void Item::setCraftIndex(int craftIndex)
{
	mCraftIndex = craftIndex;
}

bool Item::getWalkable()
{
	return mWalkable;
}

void Item::toggleWalkable()
{
	mWalkable = !mWalkable;
}

