#include "DialogueSystem.h"
#include <iostream>
#include "SFML\System.hpp"

DialogueSystem::DialogueSystem(ResourceHandler &handler) :
mHasClicked(false),
mTime(0),
mText(),
mActorText(),
mFont(),
mIsActive(false),
mAdvancedIsActive(false),
mFinishedDialogue(false),
mHandler(handler),
mFirstCharacter(),
mSecondCharacter(),
mState(0),
mLevel1Start(true),
mLevel1End(false),
mLevel2Start(false),
mLevel2End(false)
{
	mFont.loadFromFile("Resources/Fonts/Lora-Regular.ttf");
	mBubble.setTexture(*handler.getTexture("textbubble.png"));
	mTextBox.setTexture(*handler.getTexture("textbox.png"));
	mSepia.setSize(sf::Vector2f(1024, 576));
	mSepia.setTexture(handler.getTexture("sepia.png"));
}

DialogueSystem::~DialogueSystem()
{

}

//Function for all text in dialogues
void DialogueSystem::text(std::string text, sf::Vector2f &position, float x, float y)
{
	mText.setFont(mFont);
	mText.setCharacterSize(18);
	//mText.setStyle(sf::Text::Bold);
	mText.setColor(sf::Color::Black);
	mText.setPosition(position);

	std::string::size_type tempChar = 0;

	if (text.length() > 20)
	{
		std::string::size_type spacePos = text.rfind(' ', 20);
		if (spacePos == std::string::npos)
		{
			spacePos = text.find(' ', 20);
		}
		if (spacePos != std::string::npos)
		{
			text[spacePos] = '\n';
			tempChar = spacePos;
		}
	}
	if (text.length() > tempChar + 20)
	{
		std::string::size_type spacePos = text.rfind(' ', tempChar + 20);
		if (spacePos == std::string::npos)
		{
			spacePos = text.find(' ', tempChar + 20);
		}
		if (spacePos != std::string::npos)
		{
			text[spacePos] = '\n';
			y = y - 15;
			tempChar = spacePos;
		}
	}
	if (text.length() > tempChar + 20)
	{
		std::string::size_type spacePos = text.rfind(' ', tempChar + 20);
		if (spacePos == std::string::npos)
		{
			spacePos = text.find(' ', tempChar + 20);
		}
		if (spacePos != std::string::npos)
		{
			text[spacePos] = '\n';
			y = y - 15;
			tempChar = spacePos;
		}
	}
	if (text.length() > tempChar + 20)
	{
		std::string::size_type spacePos = text.rfind(' ', tempChar + 20);
		if (spacePos == std::string::npos)
		{
			spacePos = text.find(' ', tempChar + 20);
		}
		if (spacePos != std::string::npos)
		{
			text[spacePos] = '\n';
			y = y - 15;
			tempChar = spacePos;
		}
	}
	else
		tempChar = 0;

	mText.move(x, y);
	mText.setString(text);
}

void DialogueSystem::advancedText(std::string advancedText, float posX, float posY, float offsetX, float offsetY)
{
	mText.setFont(mFont);
	mText.setCharacterSize(22);
	mText.setStyle(sf::Text::Bold);
	mText.setColor(sf::Color::Black);
	mText.move(offsetX, offsetY);

	std::string::size_type tempChar = 0;

	if (advancedText.length() > 70)
	{
		std::string::size_type spacePos = advancedText.rfind(' ', 70);
		if (spacePos == std::string::npos)
		{
			spacePos = advancedText.find(' ', 70);
		}
		if (spacePos != std::string::npos)
		{
			advancedText[spacePos] = '\n';
			tempChar = spacePos;
		}
	}

	if (advancedText.length() > tempChar + 70)
	{
		std::string::size_type spacePos = advancedText.rfind(' ', tempChar + 70);
		if (spacePos == std::string::npos)
		{
			spacePos = advancedText.find(' ', tempChar + 70);
		}
		if (spacePos != std::string::npos)
		{
			advancedText[spacePos] = '\n';
			posY = posY - 15;
			tempChar = spacePos;
		}
	}

	if (advancedText.length() > tempChar + 70)
	{
		std::string::size_type spacePos = advancedText.rfind(' ', tempChar + 70);
		if (spacePos == std::string::npos)
		{
			spacePos = advancedText.find(' ', tempChar + 70);
		}
		if (spacePos != std::string::npos)
		{
			advancedText[spacePos] = '\n';
			posY = posY - 15;
			tempChar = spacePos;
		}
	}

	if (advancedText.length() > tempChar + 70)
	{
		std::string::size_type spacePos = advancedText.rfind(' ', tempChar + 70);
		if (spacePos == std::string::npos)
		{
			spacePos = advancedText.find(' ', tempChar + 70);
		}
		if (spacePos != std::string::npos)
		{
			advancedText[spacePos] = '\n';
			posY = posY - 15;
			tempChar = spacePos;
		}
	}
	else
		tempChar = 0;

	mText.setPosition(posX, posY);
	mText.setString(advancedText);
}

void DialogueSystem::actorText(std::string actorText, float posX, float posY, float offsetX, float offsetY)
{
	mActorText.setFont(mFont);
	mActorText.setCharacterSize(20);
	mActorText.setStyle(sf::Text::Bold);
	mActorText.setColor(sf::Color::Yellow);
	mActorText.move(offsetX, offsetY);
	mActorText.setPosition(posX, posY);
	mActorText.setString(actorText);
}

//Draw function for game to use
void DialogueSystem::drawDialogue(sf::RenderWindow &window)
{
	if (mIsActive)
	{
		window.draw(mBubble);
		window.draw(mText);
	}
	if (mAdvancedIsActive)
	{
		window.draw(mSepia);
		window.draw(mFirstCharacter);
		window.draw(mSecondCharacter);
		window.draw(mTextBox);
		window.draw(mActorText);
		window.draw(mText);
	}
}

void DialogueSystem::createTalkBubble(sf::Vector2f &position, float offsetX, float offsetY, float scaleX, float scaleY)
{
	mBubble.setPosition(position);
	mBubble.setScale(sf::Vector2f(scaleX, scaleY));
	mBubble.move(offsetX, offsetY);
}

void DialogueSystem::createTextBox(float x, float y, float offsetX, float offsetY, float scaleX, float scaleY)
{
	mTextBox.setPosition(x, y);
	mTextBox.setScale(scaleX, scaleY);
	mTextBox.move(offsetX, offsetY);
}

void DialogueSystem::drawFirstCharacter(ResourceHandler &handler, float x, float y, float offsetX, float offsetY, float scaleX, float scaleY, std::string character)
{
	mFirstCharacter.setPosition(x, y);
	mFirstCharacter.setScale(scaleX, scaleY);
	mFirstCharacter.move(offsetX, offsetY);
	mFirstCharacter.setTexture(*handler.getTexture(character));
}

void DialogueSystem::drawSecondCharacter(ResourceHandler &handler, float x, float y, float offsetX, float offsetY, float scaleX, float scaleY, std::string character)
{
	mSecondCharacter.setPosition(x, y);
	mSecondCharacter.setScale(scaleX, scaleY);
	mSecondCharacter.move(offsetX, offsetY);
	mSecondCharacter.setTexture(*handler.getTexture(character));
}

//Function to check if the player has clicked on an object
void DialogueSystem::hasClicked(std::string indexName, Player *player)
{
	mPlayer = player;

	//Advanced Dialogue

	//Level 1

	//if (indexName == "level1Start" && mHasClicked == false)
	//{
	//	mLevel1Start = true;
	//	mHasClicked = true;
	//}

	//Level 2

	if (indexName == "missingRocket" && mHasClicked == false)
	{
		mLevel2MissingRocket = true;
		mHasClicked = true;
	}
	else if (indexName == "putte" && mHasClicked == false)
	{
		mLevel2Putte = true;
		mHasClicked = true;
	}
	else if (indexName == "steamMachine" && mHasClicked == false)
	{
		mLevel2SteamMachine = true;
		mHasClicked = true;
	}
	else if (indexName == "arnold" && mHasClicked == false)
	{
		mLevel2Arnold = true;
		mHasClicked = true;
	}
	else if (indexName == "arnoldMemories" && mHasClicked == false)
	{
		mLevel2ArnoldMemories = true;
		mHasClicked = true;
	}
	else if (indexName == "putteRescue" && mHasClicked == false)
	{
		mLevel2PutteRescue = true;
		mHasClicked = true;
	}
	else if (indexName == "openBox" && mHasClicked == false)
	{
		mLevel2OpenBox = true;
		mHasClicked = true;
	}
	else if (indexName == "magpieSteals" && mHasClicked == false)
	{
		mLevel2MapieSteals = true;
		mHasClicked = true;
	}
	else if (indexName == "grandmasCloth" && mHasClicked == false)
	{
		mLevel2GrandmasCloth = true;
		mHasClicked = true;
	}

	//Level 3

	else if (indexName == "level3Start" && mHasClicked == false)
	{
		mLevel3Start = true;
		mHasClicked = true;
	}

	else if (indexName == "shed" && mHasClicked == false)
	{
		mLevel3Shed = true;
		mHasClicked = true;
	}

	//Level 5
	else if (indexName == "balconyDoor" && mHasClicked == false)
	{
		mLevel5BalconyDoor = true;
		mHasClicked = true;
	}

	else if (indexName == "putte2" && mHasClicked == false)
	{
		mLevel5Putte2 = true;
		mHasClicked = true;
	}

	else if (indexName == "solarSystem" && mHasClicked == false)
	{
		mLevel5SolarSystem = true;
		mHasClicked = true;
	}

	else if (indexName == "mouseHole" && mHasClicked == false)
	{
		mLevel5MouseHole = true;
		mHasClicked = true;
	}

	else if (indexName == "together" && mHasClicked == false)
	{
		mLevel5Together = true;
		mHasClicked = true;
	}

	//Thomas' Room
	else if (indexName == "ScrewDevice" && mHasClicked == false)
	{
		mLevel1End = true;
		mHasClicked = true;
	}
	else if (indexName == "books" && mHasClicked == false)
	{
		mBooks = true;
		mHasClicked = true;
	}
	else if (indexName == "lamp" && mHasClicked == false)
	{
		mLamp = true;
		mHasClicked = true;
	}
	else if (indexName == "rubicCube" && mHasClicked == false)
	{
		mRubicCube = true;
		mHasClicked = true;
	}
	else if (indexName == "poster" && mHasClicked == false)
	{
		mPoster = true;
		mHasClicked = true;
	}
	else if (indexName == "backpack" && mHasClicked == false)
	{
		mBackpack = true;
		mHasClicked = true;
	}
	else if (indexName == "bowl" && mHasClicked == false)
	{
		mBowl = true;
		mHasClicked = true;
	}
	else if (indexName == "radio" && mHasClicked == false)
	{
		mRadio = true;
		mHasClicked = true;
	}
	else if (indexName == "mat" && mHasClicked == false)
	{
		mMat = true;
		mHasClicked = true;
	}
	else if (indexName == "star" && mHasClicked == false)
	{
		mStar = true;
		mHasClicked = true;
	}
	else if (indexName == "aquarium" && mHasClicked == false)
	{
		mAquarium = true;
		mHasClicked = true;
	}
	else if (indexName == "block" && mHasClicked == false)
	{
		mBlock = true;
		mHasClicked = true;
	}
	else if (indexName == "astronaut" && mHasClicked == false)
	{
		mAstronaut = true;
		mHasClicked = true;
	}
	else if (indexName == "magnet" && mHasClicked == false)
	{
		mMagnet = true;
		mHasClicked = true;
	}
	else if (indexName == "string" && mHasClicked == false)
	{
		mString = true;
		mHasClicked = true;
	}

	//Grandma's Livingroom
	else if (indexName == "books2" && mHasClicked == false)
	{
		mBooks2 = true;
		mHasClicked = true;
	}
	else if (indexName == "jewelryCase" && mHasClicked == false)
	{
		mJewelryCase = true;
		mHasClicked = true;
	}
	else if (indexName == "mask" && mHasClicked == false)
	{
		mMask = true;
		mHasClicked = true;
	}
	else if (indexName == "textileCart" && mHasClicked == false)
	{
		mTextileCart = true;
		mHasClicked = true;
	}
	else if (indexName == "earthGlobe" && mHasClicked == false)
	{
		mEarthGlobe = true;
		mHasClicked = true;
	}
	else if (indexName == "gramophne" && mHasClicked == false)
	{
		mGramophone = true;
		mHasClicked = true;
	}
	else if (indexName == "fishTrophy" && mHasClicked == false)
	{
		mFishTrophy = true;
		mHasClicked = true;
	}
	else if (indexName == "plant" && mHasClicked == false)
	{
		mPlant = true;
		mHasClicked = true;
	}
	else if (indexName == "armchair" && mHasClicked == false)
	{
		mArmchair = true;
		mHasClicked = true;
	}
	else if (indexName == "glassesAndNuts" && mHasClicked == false)
	{
		mGlassesAndNuts = true;
		mHasClicked = true;
	}

	//Grandma's Kitchen
	else if (indexName == "refridgerator" && mHasClicked == false)
	{
		mRefridgerator = true;
		mHasClicked = true;
	}
	else if (indexName == "cat" && mHasClicked == false)
	{
		mCat = true;
		mHasClicked = true;
	}
	else if (indexName == "catFoodBowl" && mHasClicked == false)
	{
		mCatFoodBowl = true;
		mHasClicked = true;
	}
	else if (indexName == "mouseDwelling" && mHasClicked == false)
	{
		mMouseDwelling = true;
		mHasClicked = true;
	}
	else if (indexName == "waterTap" && mHasClicked == false)
	{
		mWaterTap = true;
		mHasClicked = true;
	}
	else if (indexName == "fruitBowl" && mHasClicked == false)
	{
		mFruitBowl = true;
		mHasClicked = true;
	}
	else if (indexName == "flowers" && mHasClicked == false)
	{
		mFlowers = true;
		mHasClicked = true;
	}
	else if (indexName == "rocketDrawings" && mHasClicked == false)
	{
		mRocketDrawings = true;
		mHasClicked = true;
	}
	else if (indexName == "tools" && mHasClicked == false)
	{
		mTools = true;
		mHasClicked = true;
	}

	//Grandma's Room
	else if (indexName == "planets" && mHasClicked == false)
	{
		mPlanets = true;
		mHasClicked = true;
	}
	else if (indexName == "mercury" && mHasClicked == false)
	{
		mMercury = true;
		mHasClicked = true;
	}
	else if (indexName == "venus" && mHasClicked == false)
	{
		mVenus = true;
		mHasClicked = true;
	}
	else if (indexName == "emptyEarth" && mHasClicked == false)
	{
		mEmptyEarth = true;
		mHasClicked = true;
	}
	else if (indexName == "emptyMars" && mHasClicked == false)
	{
		mEmptyMars = true;
		mHasClicked = true;
	}
	else if (indexName == "jupiter" && mHasClicked == false)
	{
		mJupiter = true;
		mHasClicked = true;
	}
	else if (indexName == "emptySaturn" && mHasClicked == false)
	{
		mEmptySaturn = true;
		mHasClicked = true;
	}
	else if (indexName == "uranus" && mHasClicked == false)
	{
		mUranus = true;
		mHasClicked = true;
	}
	else if (indexName == "neptune" && mHasClicked == false)
	{
		mNeptune = true;
		mHasClicked = true;
	}
	else if (indexName == "emptyPluto" && mHasClicked == false)
	{
		mEmptyPluto = true;
		mHasClicked = true;
	}
	else if (indexName == "mars" && mHasClicked == false)
	{
		mMars = true;
		mHasClicked = true;
	}
	else if (indexName == "earth" && mHasClicked == false)
	{
		mEarth = true;
		mHasClicked = true;
	}
	else if (indexName == "saturn" && mHasClicked == false)
	{
		mSaturn = true;
		mHasClicked = true;
	}
	else if (indexName == "pluto" && mHasClicked == false)
	{
		mPluto = true;
		mHasClicked = true;
	}
	else if (indexName == "swords" && mHasClicked == false)
	{
		mSwords = true;
		mHasClicked = true;
	}
	else if (indexName == "drawings" && mHasClicked == false)
	{
		mDrawings = true;
		mHasClicked = true;
	}
	else if (indexName == "balconyDoor" && mHasClicked == false)
	{
		mBalconyDoor = true;
		mHasClicked = true;
	}
	else if (indexName == "dollHouse" && mHasClicked == false)
	{
		mDollHouse = true;
		mHasClicked = true;
	}
	else if (indexName == "putte" && mHasClicked == false)
	{
		mPutte = true;
		mHasClicked = true;
	}
	else if (indexName == "putteFamily" && mHasClicked == false)
	{
		mPutteFamily = true;
		mHasClicked = true;
	}

	else
		mHasClicked = false;
}

//Resets all variables
void DialogueSystem::reset()
{
	mFinishedDialogue = false;
	mHasClicked = false;
	mState = 0;

	mText.setString("");
}

//Setters and getters
void DialogueSystem::setLevel1End()
{
	mLevel1End = true;
}

bool DialogueSystem::getLevel1End()
{
	return mLevel1End;
}

void DialogueSystem::setLevel1Start()
{
	mLevel1Start = true;
	mAdvancedIsActive = true;
}

bool DialogueSystem::getLevel1Start()
{
	return mLevel1Start;
}

void DialogueSystem::setLevel2End()
{
	mLevel2End = true;
}

bool DialogueSystem::getLevel2End()
{
	return mLevel2End;
}

void DialogueSystem::setLevel2Start()
{
	mLevel2Start = true;
}

bool DialogueSystem::getLevel2Start()
{
	return mLevel2Start;
}

void DialogueSystem::setLevel3Start()
{
	mLevel3Start = true;
}

bool DialogueSystem::getLevel3Start()
{
	return mLevel3Start;
}

void DialogueSystem::setLevel3End()
{
	mLevel3End = true;
}

bool DialogueSystem::getLevel3End()
{
	return mLevel3End;
}

void DialogueSystem::setLevel5Start()
{
	mLevel5Start = true;
}

bool DialogueSystem::getLevel5Start()
{
	return mLevel5Start;
}

void DialogueSystem::setLevel5End()
{
	mLevel5End = true;
}

bool DialogueSystem::getLevel5End()
{
	return mLevel5End;
}

//Update function
void DialogueSystem::update(float time)
{
	//Advanced Dialogue

	//Level 1
	if (mLevel1Start == true)
	{
		displayLevel1StartAdvancedDialogue();
	}
	else if (mLevel1End == true)
	{
		displayLevel1EndAdvancedDialogue();
	}

	//Level 2
	else if (mLevel2Start == true)
	{
		displayLevel2StartAdvancedDialogue();
	}
	else if (mLevel2End == true)
	{
		displayLevel2EndAdvancedDialogue();
	}
	else if (mLevel2MissingRocket == true)
	{
		displayLevel2MissingRocketAdvancedDialogue();
	}
	else if (mLevel2Putte == true)
	{
		displayLevel2PutteAdvancedDialogue();
	}
	else if (mLevel2SteamMachine == true)
	{
		displayLevel2SteamMachineAdvancedDialogue();
	}
	else if (mLevel2Arnold == true)
	{
		displayLevel2ArnoldAdvancedDialogue();
	}
	else if (mLevel2ArnoldMemories == true)
	{
		displayLevel2ArnoldMemoriesAdvancedDialogue();
	}
	else if (mLevel2PutteRescue == true)
	{
		displayLevel2PutteRescueAdvancedDialogue();
	}
	else if (mLevel2OpenBox == true)
	{
		displayLevel2OpenBoxAdvancedDialogue();
	}
	else if (mLevel2MapieSteals == true)
	{
		displayLevel2MagpieStealsAdvancedDialogue();
	}
	else if (mLevel2GrandmasCloth == true)
	{
		displayLevel2GrandmasClothAdvancedDialogue();
	}

	//Level 3

	else if (mLevel3Start == true)
	{
		displayLevel3StartAdvancedDialogue();
	}

	else if (mLevel3Shed == true)
	{
		displayLevel3ShedAdvancedDialogue();
	}

	//Level 5
	else if (mLevel5Start == true)
	{
		displayLevel5StartAdvancedDialogue();
	}

	else if (mLevel5BalconyDoor == true)
	{
		displayLevel5BalconyDoorAdvancedDialogue();
	}

	else if (mLevel5Putte2 == true)
	{
		displayLevel5Putte2AdvancedDialogue();
	}

	else if (mLevel5SolarSystem == true)
	{
		displayLevel5SolarSystemAdvancedDialogue();
	}

	else if (mLevel5MouseHole == true)
	{
		displayLevel5MouseHoleAdvancedDialogue();
	}

	else if (mLevel5Victory == true)
	{
		displayLevel5VictoryAdvancedDialogue();
	}

	else if (mLevel5Together == true)
	{
		displayLevel5TogetherAdvancedDialogue();
	}

	//Thomas' Room
	else if (mBooks == true)
	{
		displayBooksDialogue();
	}
	else if (mLamp == true)
	{
		displayLampDialogue();
	}
	else if (mRubicCube == true)
	{
		displayRubicCubeDialogue();
	}
	else if (mPoster == true)
	{
		displayPosterDialogue();
	}
	else if (mBackpack == true)
	{
		displayBackpackDialogue();
	}
	else if (mBowl == true)
	{
		displayBowlDialogue();
	}
	else if (mRadio == true)
	{
		displayRadioDialogue();
	}
	else if (mMat == true)
	{
		displayMatDialogue();
	}
	else if (mStar == true)
	{
		displayStarDialogue();
	}
	else if (mAquarium == true)
	{
		displayAquariumDialogue();
	}
	else if (mBlock == true)
	{
		displayBlockDialogue();
	}
	else if (mAstronaut == true)
	{
		displayAstronautDialogue();
	}
	else if (mMagnet == true)
	{
		displayMagnetDialogue();
	}
	else if (mString == true)
	{
		displayStringDialogue();
	}

	//Grandma's Livingroom
	else if (mBooks2 == true)
	{
		displayBooks2Dialogue();
	}
	else if (mJewelryCase == true)
	{
		displayJewelryCaseDialogue();
	}
	else if (mMask == true)
	{
		displayMaskDialogue();
	}
	else if (mTextileCart == true)
	{
		displayTextileCartDialogue();
	}
	else if (mEarthGlobe == true)
	{
		displayEarthGlobeDialogue();
	}
	else if (mGramophone == true)
	{
		displayGramophoneDialogue();
	}
	else if (mFishTrophy == true)
	{
		displayFishTrophyDialogue();
	}
	else if (mPlant == true)
	{
		displayPlantDialogue();
	}
	else if (mArmchair == true)
	{
		displayArmchairDialogue();
	}
	else if (mGlassesAndNuts == true)
	{
		displayGlassesAndNutsDialogue();
	}

	//Grandma's Kitchen
	else if (mRefridgerator == true)
	{
		displayRefridgeratorDialogue();
	}
	else if (mCat == true)
	{
		displayCatDialogue();
	}
	else if (mCatFoodBowl == true)
	{
		displayCatFoodBowlDialogue();
	}
	else if (mMouseDwelling == true)
	{
		displayMouseDwellingDialogue();
	}
	else if (mWaterTap == true)
	{
		displayWaterTapDialogue();
	}
	else if (mFruitBowl == true)
	{
		displayFruitBowlDialogue();
	}
	else if (mFlowers == true)
	{
		displayFlowersDialogue();
	}
	else if (mRocketDrawings == true)
	{
		displayRocketDrawingsDialogue();
	}
	else if (mTools == true)
	{
		displayToolsDialogue();
	}
	
	//Grandma's Room
	else if (mPlanets == true)
	{
		displayPlanetsDialogue();
	}
	else if (mMercury == true)
	{
		displayMercuryDialogue();
	}
	else if (mVenus == true)
	{
		displayVenusDialogue();
	}
	else if (mEmptyEarth == true)
	{
		displayEarthDialogue();
	}
	else if (mEmptyMars == true)
	{
		displayEmptyMarsDialogue();
	}
	else if (mJupiter == true)
	{
		displayJupiterDialogue();
	}
	else if (mEmptySaturn == true)
	{
		displayEmptySaturnDialogue();
	}
	else if (mUranus == true)
	{
		displayUranusDialogue();
	}
	else if (mNeptune == true)
	{
		displayNeptuneDialogue();
	}
	else if (mEmptyPluto == true)
	{
		displayEmptyPlutoDialogue();
	}
	else if (mMars == true)
	{
		displayMarsDialogue();
	}
	else if (mEarth == true)
	{
		displayEarthDialogue();
	}
	else if (mSaturn == true)
	{
		displaySaturnDialogue();
	}
	else if (mPluto == true)
	{
		displayPlutoDialogue();
	}
	else if (mSwords == true)
	{
		displaySwordsDialogue();
	}
	else if (mDrawings == true)
	{
		displayDrawingsDialogue();
	}
	else if (mBalconyDoor == true)
	{
		displayBalconyDoorDialogue();
	}
	else if (mDollHouse == true)
	{
		displayDollHouseDialogue();
	}
	else if (mPutte == true)
	{
		displayPutteDialogue();
	}
	else if (mPutteFamily == true)
	{
		displayPutteFamilyDialogue();
	}
}

void DialogueSystem::setState()
{
	mState++;
}

bool DialogueSystem::isDialogueFinished()
{
	return mFinishedDialogue;
}

//Advanced Dialogues
//Level 1
void DialogueSystem::displayLevel1StartAdvancedDialogue()
{
	std::string level1StartHilma = "Men för bövelingen! Min flygfarkost alldeles förstörd! Förbaskade flygfän som alltid ska vara så livliga... Nä detta måste lagas!";
	std::string level1StartTeller = "Den vresiga lilla hittaren tog av sin mössa och började leta i den. Hon letade och letade, längre och längre ner i mössan. Hela hon försvann ner i den! Det enda man kunde se av henne var hennes små, små fötter. Sedan hoppade hon ut ur den. Men då var hon helröd i ansiktet!";
	std::string level1StartHilma2 = "Men vad sjutton är det här!? Är den borta!? ALLT ÄR BORTA! DET HÄR KAN INTE VARA SANT!";
	std::string level1StartHilma3 = "Det var det bästa utbytet jag hittills har fått! Jag som hade hittat så bra...";
	std::string level1StartThomas = "V-vad har du tappat?";
	std::string level1StartHilma4 = "För det första, jag har inte tappat bort något. För det andra, är det en mycket ovärderlig sak som tog väldigt lång tid att få. Det var en fantastisk skruvmackapär. Med den skulle jag bygga en mycket finare flygfarkost än denna skrothög. Men nu har jag INGENTING jag kan laga skrothögen med.";
	std::string level1StartTeller2 = "Pojken tyckte synd om den lilla varelsen och undrade om han kunde hjälpa till. Då kom han på en idé.";
	std::string level1StartThomas2 = "J-jag kanske... har en skruvmackapär-";
	std::string level1StartHilma5 = "Jamen då så! Var har du den?";
	std::string level1StartThomas3 = "Eh... jag vet inte...";
	std::string level1StartHilma6 = "Men oj då, det var verkligen till stor hjälp! Kan det vara så att du har tappat bort den?";
	std::string level1StartHilma7 = "Du får väl tacka vinden för att den var så bångstyrig idag. För du fick turen att träffa på mig! Det råkar vara så att jag är en hittare!";
	std::string level1StartTeller3 = "En hittare? Vad kunde det vara? Pojken hade aldrig hört talas om dem innan.";
	std::string level1StartHilma8 = "Vi Hittare har funnits länge och hållit reda på er slarviga människor. Tappar ni bort något så hittar vi det åt er. Jag och min egna hittarbyrå kan hitta vad som helst, var som helst!";
	std::string level1StartThomas4 = "O-om du verkligen är en h-hittare. Kan du... Kan du hitta tre saker åt mig-";
	std::string level1StartHilma9 = "För att bevisa för dig att jag är en hittare? Utmaning godtagen! Vad är det du vill att jag ska hitta? Kom igen nu, vela inte så mycket!";
	std::string level1StartThomas5 = "En självlysande stjärna... den föll från väggen, min favoritastronaut och... skruvmackapären...";
	std::string level1StartHilma10 = "Och vad får jag i utbyte?";
	std::string level1StartThomas6 = "Hur mycket kostar det?";
	std::string level1StartHilma11 = "Inte pengar! Ge mig något användbart!";
	std::string level1StartHilma12 = "Ge mig skruvmackapären sen när jag har hittat den.";
	std::string level1StartHilma13 = "Just ja! Hilma heter jag; vad är ditt namn?";
	std::string level1StartThomas7 = "... Thomas";
	std::string level1StartHilma14 = "Då så, Thomas. Då ska jag hitta en stjärna, en astronaut och en skruvmackapär åt dig!";
	std::string level1StartInterlude = "*Thomas nickar tveksamt*";

	if (mState == 25)
	{
		mText.setString("");
		mActorText.setString("");
		mHasClicked = false;
		mLevel1Start = false;
		mAdvancedIsActive = false;
		mFinishedDialogue = true;
	}

	if (mState == 0)
	{
		mAdvancedIsActive = true;
		advancedText(level1StartHilma, 100.f, 420.f, 1.f, 1.f);
		drawFirstCharacter(mHandler, 300.f, 30.f, 1.f, 1.f, -0.2f, 0.2f, "expressionHilmaGrumpy.png");
		createTextBox(-1.f, 280.f, 1.f, 1.f, 0.267f, 0.45f);
		actorText("Hilma", 480.f, 307.f, 1.f, 1.f);
	}
	if (mState == 1)
	{
		advancedText(level1StartTeller, 100.f, 420.f, 1.f, 1.f);
		actorText("Berättare", 462.f, 307.f, 1.f, 1.f);
	}
	if (mState == 2)
	{
		advancedText(level1StartHilma2, 100.f, 420.f, 1.f, 1.f);
		drawFirstCharacter(mHandler, 300.f, 30.f, 1.f, 1.f, -0.2f, 0.2f, "expressionHilmaAngry.png");
		actorText("Hilma", 480.f, 307.f, 1.f, 1.f);
	}
	if (mState == 3)
	{
		advancedText(level1StartHilma3, 100.f, 420.f, 1.f, 1.f);
		drawFirstCharacter(mHandler, 300.f, 30.f, 1.f, 1.f, -0.2f, 0.2f, "expressionHilmaAbject.png");
	}
	if (mState == 4)
	{
		advancedText(level1StartThomas, 100.f, 420.f, 1.f, 1.f);
		drawSecondCharacter(mHandler, 700.f, 30.f, 1.f, 1.f, 0.2f, 0.2f, "expressionThomasThoughtful.png");
		actorText("Thomas", 472.f, 307.f, 1.f, 1.f);
	}
	if (mState == 5)
	{
		advancedText(level1StartHilma4, 100.f, 420.f, 1.f, 1.f);
		drawFirstCharacter(mHandler, 300.f, 30.f, 1.f, 1.f, -0.2f, 0.2f, "expressionHilmaGrumpy.png");
		actorText("Hilma", 480.f, 307.f, 1.f, 1.f);
	}
	if (mState == 6)
	{
		advancedText(level1StartTeller2, 100.f, 420.f, 1.f, 1.f);
		actorText("Berättare", 462.f, 307.f, 1.f, 1.f);
	}
	if (mState == 7)
	{
		advancedText(level1StartThomas2, 100.f, 420.f, 1.f, 1.f);
		drawSecondCharacter(mHandler, 700.f, 30.f, 1.f, 1.f, 0.2f, 0.2f, "expressionThomasThoughtful.png");
		actorText("Thomas", 472.f, 307.f, 1.f, 1.f);
	}
	if (mState == 8)
	{
		advancedText(level1StartHilma5, 100.f, 420.f, 1.f, 1.f);
		drawFirstCharacter(mHandler, 300.f, 30.f, 1.f, 1.f, -0.2f, 0.2f, "expressionHilmaHappy.png");
		actorText("Hilma", 480.f, 307.f, 1.f, 1.f);
	}
	if (mState == 9)
	{
		advancedText(level1StartThomas3, 100.f, 420.f, 1.f, 1.f);
		drawSecondCharacter(mHandler, 700.f, 30.f, 1.f, 1.f, 0.2f, 0.2f, "expressionThomasSurprised.png");
		actorText("Thomas", 472.f, 307.f, 1.f, 1.f);
	}
	if (mState == 10)
	{
		advancedText(level1StartHilma6, 100.f, 420.f, 1.f, 1.f);
		drawFirstCharacter(mHandler, 300.f, 30.f, 1.f, 1.f, -0.2f, 0.2f, "expressionHilmaGrumpy.png");
		actorText("Hilma", 480.f, 307.f, 1.f, 1.f);
	}
	if (mState == 11)
	{
		advancedText(level1StartHilma7, 100.f, 420.f, 1.f, 1.f);
		drawFirstCharacter(mHandler, 300.f, 30.f, 1.f, 1.f, -0.2f, 0.2f, "expressionHilmaConfident.png");
	}
	if (mState == 12)
	{
		advancedText(level1StartTeller3, 100.f, 420.f, 1.f, 1.f);
		actorText("Berättare", 462.f, 307.f, 1.f, 1.f);
	}
	if (mState == 13)
	{
		advancedText(level1StartHilma8, 100.f, 420.f, 1.f, 1.f);
		actorText("Hilma", 480.f, 307.f, 1.f, 1.f);
	}
	if (mState == 14)
	{
		advancedText(level1StartThomas4, 100.f, 420.f, 1.f, 1.f);
		drawSecondCharacter(mHandler, 700.f, 30.f, 1.f, 1.f, 0.2f, 0.2f, "expressionThomasWorried.png");
		actorText("Thomas", 472.f, 307.f, 1.f, 1.f);
	}
	if (mState == 15)
	{
		advancedText(level1StartHilma9, 100.f, 420.f, 1.f, 1.f);
		drawFirstCharacter(mHandler, 300.f, 30.f, 1.f, 1.f, -0.2f, 0.2f, "expressionHilmaConfident.png");
		actorText("Hilma", 480.f, 307.f, 1.f, 1.f);
	}
	if (mState == 16)
	{
		advancedText(level1StartThomas5, 100.f, 420.f, 1.f, 1.f);
		drawSecondCharacter(mHandler, 700.f, 30.f, 1.f, 1.f, 0.2f, 0.2f, "expressionThomasThoughtful.png");
		actorText("Thomas", 472.f, 307.f, 1.f, 1.f);
	}
	if (mState == 17)
	{
		advancedText(level1StartHilma10, 100.f, 420.f, 1.f, 1.f);
		drawFirstCharacter(mHandler, 300.f, 30.f, 1.f, 1.f, -0.2f, 0.2f, "expressionHilmaDetermined.png");
		actorText("Hilma", 480.f, 307.f, 1.f, 1.f);
	}
	if (mState == 18)
	{
		advancedText(level1StartThomas6, 100.f, 420.f, 1.f, 1.f);
		drawSecondCharacter(mHandler, 700.f, 30.f, 1.f, 1.f, 0.2f, 0.2f, "expressionThomasWorried.png");
		actorText("Thomas", 472.f, 307.f, 1.f, 1.f);
	}
	if (mState == 19)
	{
		advancedText(level1StartHilma11, 100.f, 420.f, 1.f, 1.f);
		actorText("Hilma", 480.f, 307.f, 1.f, 1.f);
	}
	if (mState == 20)
	{
		advancedText(level1StartHilma12, 100.f, 420.f, 1.f, 1.f);
		drawFirstCharacter(mHandler, 300.f, 30.f, 1.f, 1.f, -0.2f, 0.2f, "expressionHilmaSigh.png");
		actorText("Hilma", 480.f, 307.f, 1.f, 1.f);
	}
	if (mState == 21)
	{
		advancedText(level1StartInterlude, 100.f, 420.f, 1.f, 1.f);
		drawSecondCharacter(mHandler, 700.f, 30.f, 1.f, 1.f, 0.2f, 0.2f, "expressionThomasSigh.png");
		actorText("Thomas", 472.f, 307.f, 1.f, 1.f);
	}
	if (mState == 22)
	{
		advancedText(level1StartHilma13, 100.f, 420.f, 1.f, 1.f);
		drawFirstCharacter(mHandler, 300.f, 30.f, 1.f, 1.f, -0.2f, 0.2f, "expressionHilmaHappy.png");
		actorText("Hilma", 480.f, 307.f, 1.f, 1.f);
	}
	if (mState == 23)
	{
		advancedText(level1StartThomas7, 100.f, 420.f, 1.f, 1.f);
		drawSecondCharacter(mHandler, 700.f, 30.f, 1.f, 1.f, 0.2f, 0.2f, "expressionThomasBlush.png");
		actorText("Thomas", 472.f, 307.f, 1.f, 1.f);
	}
	if (mState == 24)
	{
		advancedText(level1StartHilma14, 100.f, 420.f, 1.f, 1.f);
		drawFirstCharacter(mHandler, 300.f, 30.f, 1.f, 1.f, -0.2f, 0.2f, "expressionHilmaConfident.png");
		actorText("Hilma", 480.f, 307.f, 1.f, 1.f);
	}
}

void DialogueSystem::displayLevel1EndAdvancedDialogue()
{
	std::string level1EndHilma = "Här är alla! Precis vad du bad om. Har jag övertygat dig tillräckligt?";
	std::string level1EndTeller = "När Thomas fick syn på alla föremål kunde han inte tro sina ögon. Han som hade letat så mycket själv! Hans mamma hade sagt att när något försvann i hans stökiga rum, var det försvunnet för alltid. Tydligen inte för en hittare.";
	std::string level1EndHilma2 = "Jag sa ju det! Jag hittar vad som helst, var som helst!";
	std::string level1EndTeller2 = "Då fick han ett litet, litet leende på läpparna och tackade så mycket för Hilmas hjälp. Men leendet försvann snabbt när han såg på skruvmackapären.";
	std::string level1EndTeller3 = "Han blev alldeles tyst och stirrade på den. Plötsligt kunde han inte bara ge den till den hjälpsamma hittaren. Han höll hårdare i skruvmackapären. Nu började Hilma bli otålig.";
	std::string level1EndHilma3 = "Hallå? Thomas? Jorden anropar!";
	std::string level1EndThomas = "F-förlåt jag... jag... Det är bara det att det inte är min skruvmackapär jag ger dig.";
	std::string level1EndHilma4 = "Jaha ja, vems är det då om man får fråga? Har du stulit den?";
	std::string level1EndThomas2 = "N-nej! Absolut inte! Det... Jag lånade den av min... mormor.";
	std::string level1EndHilma5 = "Din mormor? Vem är denna tankspridda mormor som låter en slarvgosse som du ta hand om en sådan fantastisk skruvmackapär?";
	std::string level1EndThomas3 = "Säg inte så om henne! Hon är den bästa mekanikern som har någonsin funnits!";
	std::string level1EndHilma6 = "Jaha jaså ja... Vad kan den här mormor bygga då?";
	std::string level1EndThomas4 = "Hon kan bygga allt och laga allt! Hon lagar bilar, cykelpunkor, och bygger de bästa lådbilarna, flygplanen... Och-och, just nu bygger vi en rymdraket som ska ta oss till månen! Där ska vi bo och jobba som rymdcowboys...";
	std::string level1EndThomas5 = "Det var det hon sa att vi skulle göra i alla fall...";
	std::string level1EndHilma7 = "Jaså vad då då, törs hon inte eller?";
	std::string level1EndThomas6 = "Så klart hon törs! Det är inte det... Hon bara... hon... hon är borta...";
	std::string level1EndThomas7 = "Hon har försvunnit och ingen kan hitta henne!";
	std::string level1EndTeller4 = "Stackars pojke! Skulle de flesta ha sagt. Men det råkar vara så att Hilma inte är särskilt förtjust i gråtande barn. Men det pojken sade gav henne en idé.";
	std::string level1EndHilma8 = "Din mormor är borttappad eller hur? Och vad är mitt jobb?";
	std::string level1EndThomas8 = "Att hitta bortappade saker?";
	std::string level1EndHilma9 = "Ja men se där ja! Du är ju inte helt bakom flötet! Och kan jag hitta saker, kan jag hitta..?";
	std::string level1EndThomas9 = "Mormor?";
	std::string level1EndHilma10 = "Exakt.";
	std::string level1EndTeller5 = "Nu slutade tårarna rinna på Thomas. Kunde verkligen Hilma hitta mormor? Thomas sken upp i lycka.";
	std::string level1EndThomas10 = "Verkligen? Kan du verkligen hitta henne?";
	std::string level1EndHilma11 = "Ja självklart! Men! På ett villkor!";
	std::string level1EndThomas11 = "Vad vill du ha i utbyte?";
	std::string level1EndHilma12 = "Rymdskeppet som du och mormor byggde på. Om hon verkligen kan bygga sådana fantastiska flygfarkoster lär den vara bra mycket bättre än mitt pappersflygplan. Så vad väntar vi på? Nu går vi och hittar Mormor!";
	std::string level1EndTeller6 = "Thomas nickade och hans leende kröp sakta tillbaka. Ett nytt hopp hade grott inom honom.";
	std::string level1EndThomas12 = "Ja! Vi går!";

	if (mState == 30)
	{
		mText.setString("");
		mActorText.setString("");
		mHasClicked = false;
		mLevel1End = false;
		mAdvancedIsActive = false;
		mFinishedDialogue = true;
	}

	if (mState == 0)
	{
		mAdvancedIsActive = true;
		advancedText(level1EndHilma, 100.f, 420.f, 1.f, 1.f);
		drawFirstCharacter(mHandler, 300.f, 30.f, 1.f, 1.f, -0.2f, 0.2f, "expressionHilmaConfident.png");
		drawSecondCharacter(mHandler, 700.f, 30.f, 1.f, 1.f, 0.2f, 0.2f, "expressionThomasSurprised.png");
		createTextBox(-1.f, 280.f, 1.f, 1.f, 0.267f, 0.45f);
		actorText("Hilma", 480.f, 307.f, 1.f, 1.f);
	}
	if (mState == 1)
	{
		advancedText(level1EndTeller, 100.f, 420.f, 1.f, 1.f);
		actorText("Berättare", 462.f, 307.f, 1.f, 1.f);
	}
	if (mState == 2)
	{
		advancedText(level1EndHilma2, 100.f, 420.f, 1.f, 1.f);
		drawSecondCharacter(mHandler, 700.f, 30.f, 1.f, 1.f, 0.2f, 0.2f, "expressionThomasHappy.png");
		actorText("Hilma", 480.f, 307.f, 1.f, 1.f);
	}
	if (mState == 3)
	{
		advancedText(level1EndTeller2, 100.f, 420.f, 1.f, 1.f);
		drawSecondCharacter(mHandler, 700.f, 30.f, 1.f, 1.f, 0.2f, 0.2f, "expressionThomasSad.png");
		actorText("Berättare", 462.f, 307.f, 1.f, 1.f);
	}
	if (mState == 4)
	{
		advancedText(level1EndTeller3, 100.f, 420.f, 1.f, 1.f);
	}
	if (mState == 5)
	{
		advancedText(level1EndHilma3, 100.f, 420.f, 1.f, 1.f);
		drawFirstCharacter(mHandler, 300.f, 30.f, 1.f, 1.f, -0.2f, 0.2f, "expressionHilmaGrumpy.png");
		actorText("Hilma", 480.f, 307.f, 1.f, 1.f);
	}
	if (mState == 6)
	{
		advancedText(level1EndThomas, 100.f, 420.f, 1.f, 1.f);
		actorText("Thomas", 472.f, 307.f, 1.f, 1.f);
	}
	if (mState == 7)
	{
		advancedText(level1EndHilma4, 100.f, 420.f, 1.f, 1.f);
		actorText("Hilma", 480.f, 307.f, 1.f, 1.f);
	}
	if (mState == 8)
	{
		advancedText(level1EndThomas2, 100.f, 420.f, 1.f, 1.f);
		drawSecondCharacter(mHandler, 700.f, 30.f, 1.f, 1.f, 0.2f, 0.2f, "expressionThomasWorried.png");
		actorText("Thomas", 472.f, 307.f, 1.f, 1.f);
	}
	if (mState == 9)
	{
		advancedText(level1EndHilma5, 100.f, 420.f, 1.f, 1.f);
		actorText("Hilma", 480.f, 307.f, 1.f, 1.f);
	}
	if (mState == 10)
	{
		advancedText(level1EndThomas3, 100.f, 420.f, 1.f, 1.f);
		drawSecondCharacter(mHandler, 700.f, 30.f, 1.f, 1.f, 0.2f, 0.2f, "expressionThomasDetermined.png");
		actorText("Thomas", 472.f, 307.f, 1.f, 1.f);
	}
	if (mState == 11)
	{
		advancedText(level1EndHilma6, 100.f, 420.f, 1.f, 1.f);
		drawFirstCharacter(mHandler, 300.f, 30.f, 1.f, 1.f, -0.2f, 0.2f, "expressionHilmaThoughtful.png");
		actorText("Hilma", 480.f, 307.f, 1.f, 1.f);
	}
	if (mState == 12)
	{
		advancedText(level1EndThomas4, 100.f, 420.f, 1.f, 1.f);
		drawSecondCharacter(mHandler, 700.f, 30.f, 1.f, 1.f, 0.2f, 0.2f, "expressionThomasHappy.png");
		actorText("Thomas", 472.f, 307.f, 1.f, 1.f);
	}
	if (mState == 13)
	{
		advancedText(level1EndThomas5, 100.f, 420.f, 1.f, 1.f);
		drawSecondCharacter(mHandler, 700.f, 30.f, 1.f, 1.f, 0.2f, 0.2f, "expressionThomasSad.png");
	}
	if (mState == 14)
	{
		advancedText(level1EndHilma7, 100.f, 420.f, 1.f, 1.f);
		actorText("Hilma", 480.f, 307.f, 1.f, 1.f);
	}
	if (mState == 15)
	{
		advancedText(level1EndThomas6, 100.f, 420.f, 1.f, 1.f);
		drawSecondCharacter(mHandler, 700.f, 30.f, 1.f, 1.f, 0.2f, 0.2f, "expressionThomasDetermined.png");
		actorText("Thomas", 472.f, 307.f, 1.f, 1.f);
	}
	if (mState == 16)
	{
		advancedText(level1EndThomas7, 100.f, 420.f, 1.f, 1.f);
		drawSecondCharacter(mHandler, 700.f, 30.f, 1.f, 1.f, 0.2f, 0.2f, "expressionThomasCry.png");
	}
	if (mState == 17)
	{
		advancedText(level1EndTeller4, 100.f, 420.f, 1.f, 1.f);
		drawFirstCharacter(mHandler, 300.f, 30.f, 1.f, 1.f, -0.2f, 0.2f, "expressionHilmaSigh.png");
		actorText("Berättare", 462.f, 307.f, 1.f, 1.f);
	}
	if (mState == 18)
	{
		advancedText(level1EndHilma8, 100.f, 420.f, 1.f, 1.f);
		drawFirstCharacter(mHandler, 300.f, 30.f, 1.f, 1.f, -0.2f, 0.2f, "expressionHilmaThoughtful.png");
		actorText("Hilma", 480.f, 307.f, 1.f, 1.f);
	}
	if (mState == 19)
	{
		advancedText(level1EndThomas8, 100.f, 420.f, 1.f, 1.f);
		drawSecondCharacter(mHandler, 700.f, 30.f, 1.f, 1.f, 0.2f, 0.2f, "expressionThomasSad.png");
		actorText("Thomas", 472.f, 307.f, 1.f, 1.f);
	}
	if (mState == 20)
	{
		advancedText(level1EndHilma9, 100.f, 420.f, 1.f, 1.f);
		drawFirstCharacter(mHandler, 300.f, 30.f, 1.f, 1.f, -0.2f, 0.2f, "expressionHilmaHappy.png");
		actorText("Hilma", 480.f, 307.f, 1.f, 1.f);
	}
	if (mState == 21)
	{
		advancedText(level1EndThomas9, 100.f, 420.f, 1.f, 1.f);
		drawSecondCharacter(mHandler, 700.f, 30.f, 1.f, 1.f, 0.2f, 0.2f, "expressionThomasWorried.png");
		actorText("Thomas", 472.f, 307.f, 1.f, 1.f);
	}
	if (mState == 22)
	{
		advancedText(level1EndHilma10, 100.f, 420.f, 1.f, 1.f);
		drawFirstCharacter(mHandler, 300.f, 30.f, 1.f, 1.f, -0.2f, 0.2f, "expressionHilmaConfident.png");
		actorText("Hilma", 480.f, 307.f, 1.f, 1.f);
	}
	if (mState == 23)
	{
		advancedText(level1EndTeller5, 100.f, 420.f, 1.f, 1.f);
		actorText("Berättare", 462.f, 307.f, 1.f, 1.f);
	}
	if (mState == 24)
	{
		advancedText(level1EndThomas10, 100.f, 420.f, 1.f, 1.f);
		drawSecondCharacter(mHandler, 700.f, 30.f, 1.f, 1.f, 0.2f, 0.2f, "expressionThomasSurprised.png");
		actorText("Thomas", 472.f, 307.f, 1.f, 1.f);
	}
	if (mState == 25)
	{
		advancedText(level1EndHilma11, 100.f, 420.f, 1.f, 1.f);
		drawFirstCharacter(mHandler, 300.f, 30.f, 1.f, 1.f, -0.2f, 0.2f, "expressionHilmaDetermined.png");
		actorText("Hilma", 480.f, 307.f, 1.f, 1.f);
	}
	if (mState == 26)
	{
		advancedText(level1EndThomas11, 100.f, 420.f, 1.f, 1.f);
		drawSecondCharacter(mHandler, 700.f, 30.f, 1.f, 1.f, 0.2f, 0.2f, "expressionThomasWorried.png");
		actorText("Thomas", 472.f, 307.f, 1.f, 1.f);
	}
	if (mState == 27)
	{
		advancedText(level1EndHilma12, 100.f, 420.f, 1.f, 1.f);
		drawFirstCharacter(mHandler, 300.f, 30.f, 1.f, 1.f, -0.2f, 0.2f, "expressionHilmaConfident.png");
		actorText("Hilma", 480.f, 307.f, 1.f, 1.f);
	}
	if (mState == 28)
	{
		advancedText(level1EndTeller6, 100.f, 420.f, 1.f, 1.f);
		actorText("Berättare", 462.f, 307.f, 1.f, 1.f);
		drawSecondCharacter(mHandler, 700.f, 30.f, 1.f, 1.f, 0.2f, 0.2f, "expressionThomasHappy.png");
	}
	if (mState == 29)
	{
		advancedText(level1EndThomas12, 100.f, 420.f, 1.f, 1.f);
		actorText("Thomas", 472.f, 307.f, 1.f, 1.f);
	}
}

//Level 2
void DialogueSystem::displayLevel2StartAdvancedDialogue()
{
	std::string level2StartHilma = "Så det var här du såg mormor senast?";
	std::string level2StartThomas = "Ja... Det är mormors verkstad.";
	std::string level2StartHilma2 = "Jaså verkstad säger du? Då måste väl rymdfarkosten vara här?";
	std::string level2StartThomas2 = "Mhm… den står längst in i verkstaden.";
	std::string level2StartHilma3 = "Jaha ja! Låt mig få inspektera denna ‘Rymdfarkost.";
	std::string level2StartThomas3 = "Ja visst! Åh nej! Cykeln fick punka... Och... styret verkar löst...";
	std::string level2StartHilma4 = "Då får vi väl hitta på något sätt att laga den!";
	std::string level2StartThomas4 = "Man brukar använda cykelpump för att fixa däcket... och en skruvmakapär för styret.";

	if (mState == 8)
	{
		mText.setString("");
		mActorText.setString("");
		mHasClicked = false;
		mLevel2Start = false;
		mAdvancedIsActive = false;
		mFinishedDialogue = true;
	}
	if (mState == 0)
	{
		mAdvancedIsActive = true;
		advancedText(level2StartHilma, 100.f, 420.f, 1.f, 1.f);
		drawFirstCharacter(mHandler, 300.f, 30.f, 1.f, 1.f, -0.2f, 0.2f, "expressionHilmaThoughtful.png");
		createTextBox(-1.f, 280.f, 1.f, 1.f, 0.267f, 0.45f);
		actorText("Hilma", 480.f, 307.f, 1.f, 1.f);
	}
	if (mState == 1)
	{
		advancedText(level2StartThomas, 100.f, 420.f, 1.f, 1.f);
		drawSecondCharacter(mHandler, 700.f, 30.f, 1.f, 1.f, 0.2f, 0.2f, "expressionThomasNeutral.png");
		actorText("Thomas", 472.f, 307.f, 1.f, 1.f);
	}
	if (mState == 2)
	{
		advancedText(level2StartHilma2, 100.f, 420.f, 1.f, 1.f);
		drawFirstCharacter(mHandler, 300.f, 30.f, 1.f, 1.f, -0.2f, 0.2f, "expressionHilmaConfident.png");
		actorText("Hilma", 480.f, 307.f, 1.f, 1.f);
	}
	if (mState == 3)
	{
		advancedText(level2StartThomas2, 100.f, 420.f, 1.f, 1.f);
		drawSecondCharacter(mHandler, 700.f, 30.f, 1.f, 1.f, 0.2f, 0.2f, "expressionThomasThoughtful.png");
		actorText("Thomas", 472.f, 307.f, 1.f, 1.f);
	}
	if (mState == 4)
	{
		advancedText(level2StartHilma3, 100.f, 420.f, 1.f, 1.f);
		actorText("Hilma", 480.f, 307.f, 1.f, 1.f);
	}
	if (mState == 5)
	{
		advancedText(level2StartThomas3, 100.f, 420.f, 1.f, 1.f);
		drawSecondCharacter(mHandler, 700.f, 30.f, 1.f, 1.f, 0.2f, 0.2f, "expressionThomas.png");
		actorText("Thomas", 472.f, 307.f, 1.f, 1.f);
	}
	if (mState == 6)
	{
		advancedText(level2StartHilma4, 100.f, 420.f, 1.f, 1.f);
		actorText("Hilma", 480.f, 307.f, 1.f, 1.f);
	}
	if (mState == 7)
	{
		advancedText(level2StartThomas2, 100.f, 420.f, 1.f, 1.f);
		drawSecondCharacter(mHandler, 700.f, 30.f, 1.f, 1.f, 0.2f, 0.2f, "expressionThomasThoughtful.png");
		actorText("Thomas", 472.f, 307.f, 1.f, 1.f);
	}
}

void DialogueSystem::displayLevel2EndAdvancedDialogue()
{
	std::string level2End = "";
}

void DialogueSystem::displayLevel2MissingRocketAdvancedDialogue()
{
	std::string level2MissingRocketTeller = "Men där rymdraketen skulle stå var det alldeles tomt. Nu var det inte bara mormor som hade försvunnit utan även rymdraketen! Vad kunde allt det här betyda?";
	std::string level2MissingRocketHilma = "Jaha ja, jag kan inte se en rymdraket här. Ljög du om det här? För om det är något jag inte gillar så är det folk som ljuger!";
	std::string level2MissingRocketThomas = "N-n-nej! Men-men varför är den borta?T-tänk om någon har snott den?";
	std::string level2MissingRocketHilma2 = "Tja, det är ju inte helt fel. Det är inte som att det inte finns tjuvar här i staden-";
	std::string level2MissingRocketTeller2 = "Thomas ögon blev blanka när Hilma sade så. Han höll på att gråta igen! Det här var inte bra, tänkte Hilma.";
	std::string level2MissingRocketHilma3 = "Jag menar, den kanske har blivit borttappad? Det kan inte vara så svårt att hitta en stor rymdraket!";
	std::string level2MissingRocketPutte = "Oh nej! Oh nej! Hur hamnade den där!?";
	std::string level2MissingRocketTeller3 = "Vem kunde det vara som lät så eländig?";

	if (mState == 8)
	{
		mText.setString("");
		mActorText.setString("");
		mHasClicked = false;
		mLevel2MissingRocket = false;
		mAdvancedIsActive = false;
		mFinishedDialogue = true;
	}
	if (mState == 0)
	{
		mAdvancedIsActive = true;
		advancedText(level2MissingRocketTeller, 100.f, 420.f, 1.f, 1.f);
		drawFirstCharacter(mHandler, 300.f, 30.f, 1.f, 1.f, -0.2f, 0.2f, "expressionHilmaGrumpy.png");
		drawSecondCharacter(mHandler, 700.f, 30.f, 1.f, 1.f, 0.2f, 0.2f, "expressionThomasWorried.png");
		createTextBox(-1.f, 280.f, 1.f, 1.f, 0.267f, 0.45f);
		actorText("Berättare", 462.f, 307.f, 1.f, 1.f);
	}
	if (mState == 1)
	{
		advancedText(level2MissingRocketHilma, 100.f, 420.f, 1.f, 1.f);
		actorText("Hilma", 480.f, 307.f, 1.f, 1.f);
	}
	if (mState == 2)
	{
		advancedText(level2MissingRocketThomas, 100.f, 420.f, 1.f, 1.f);
		actorText("Thomas", 472.f, 307.f, 1.f, 1.f);
	}
	if (mState == 3)
	{
		advancedText(level2MissingRocketHilma2, 100.f, 420.f, 1.f, 1.f);
		drawFirstCharacter(mHandler, 300.f, 30.f, 1.f, 1.f, -0.2f, 0.2f, "expressionHilmaThoughtful.png");
		actorText("Hilma", 480.f, 307.f, 1.f, 1.f);
	}
	if (mState == 4)
	{
		advancedText(level2MissingRocketTeller2, 100.f, 420.f, 1.f, 1.f);
		actorText("Berättare", 462.f, 307.f, 1.f, 1.f);
	}
	if (mState == 5)
	{
		advancedText(level2MissingRocketHilma3, 100.f, 420.f, 1.f, 1.f);
		drawFirstCharacter(mHandler, 300.f, 30.f, 1.f, 1.f, -0.2f, 0.2f, "expressionHilmaNervous.png");
		actorText("Hilma", 480.f, 307.f, 1.f, 1.f);
	}
	if (mState == 6)
	{
		advancedText(level2MissingRocketPutte, 100.f, 420.f, 1.f, 1.f);
		drawFirstCharacter(mHandler, 300.f, 30.f, 1.f, 1.f, -0.2f, 0.2f, "expressionHilmaSurprised.png");
		drawSecondCharacter(mHandler, 700.f, 30.f, 1.f, 1.f, 0.2f, 0.2f, "expressionThomasSurprised.png");
		actorText("Putte", 480.f, 307.f, 1.f, 1.f);
	}
	if (mState == 7)
	{
		advancedText(level2MissingRocketTeller3, 100.f, 420.f, 1.f, 1.f);
		actorText("Berättare", 462.f, 307.f, 1.f, 1.f);
	}
}

void DialogueSystem::displayLevel2PutteAdvancedDialogue()
{

}

void DialogueSystem::displayLevel2SteamMachineAdvancedDialogue()
{

}

void DialogueSystem::displayLevel2ArnoldAdvancedDialogue()
{

}

void DialogueSystem::displayLevel2ArnoldMemoriesAdvancedDialogue()
{

}

void DialogueSystem::displayLevel2PutteRescueAdvancedDialogue()
{

}

void DialogueSystem::displayLevel2OpenBoxAdvancedDialogue()
{

}

void DialogueSystem::displayLevel2MagpieStealsAdvancedDialogue()
{

}

void DialogueSystem::displayLevel2GrandmasClothAdvancedDialogue()
{

}

//Level3

void DialogueSystem::displayLevel3StartAdvancedDialogue()
{
	std::string level3StartHilma = "Där! Skatan flög in i skjulet! Thomas, skynda på, vi måste följa efter den!";
	std::string level3StartThomas = "Vänta Hilma, du kan inte bara springa in. Det här är Surtantens trädgård!";
	std::string level3StartHilma2 = "Surtanten?";
	std::string level3StartThomas2 = "Det är vad alla kallar henne. Hon är alltid här i hennes trädgård och planterar och pysslar. Hon HATAR när ungar leker i den.";
	std::string level3StartThomas3 = "En gång skjöt jag och mormor upp en modellraket som flög jättehögt!";
	std::string level3StartThomas4 = "Men så exploderade den och förstörde Surtantens trädgård. Sedan dess är vi bannlysta härifrån...";
	std::string level3StartHilma3 = "Låter som hon hade en bra anledning.";
	std::string level3StartThomas5 = "Vi bad om ursäkt jättemånga gånger! Mormor bakade henne till och med en kaka men den...";
	std::string level3StartHilma4 = "Vänta! Tyst! Hör du det där Thomas?";
	std::string level3StartSurtanten = "Muttranden";
	std::string level3StartThomas6 = "Åh nej! Hon är här!";
	std::string level3StartHilma5 = "Ser ut som att vi får smyga förbi henne då, borde vara lätt för någon i min storlek!";
	std::string level3StartThomas7 = "Kanske det, så länge hennes hund inte märker dig…";
	std::string level3StartHilma6 = "Hund? Det sa du inget om! Jag har inget till övers för såna stora bestar!";
	std::string level3StartThomas8 = "Vi kanske kan hitta ett sätt att få bort den... Åh just det, det bor också bin i trädgården.";
	std::string level3StartHilma7 = "Låt mig gissa, bina bor utanför skjulet?";
	std::string level3StartThomas9 = "Jag... jag har för mig det.";
	std::string level3StartHilma8 = "Typiskt, just där ingången är...";
	std::string level3StartHilma9 = "Vi har inget val, vi måste få tag i det där fickuret! Kom Thomas, nu gör vi det här.";

	if (mState >= 19)
	{
		mText.setString("");
		mActorText.setString("");
		mHasClicked = false;
		mLevel3Start = false;
		mAdvancedIsActive = false;
		mFinishedDialogue = true;
	}

	else if (mState == 0)
	{
		mAdvancedIsActive = true;
		advancedText(level3StartHilma, 100.f, 420.f, 1.f, 1.f);
		drawFirstCharacter(mHandler, 300.f, 30.f, 1.f, 1.f, -0.2f, 0.2f, "expressionHilmaDetermined.png");
		drawSecondCharacter(mHandler, 700.f, 30.f, 1.f, 1.f, 0.2f, 0.2f, "expressionThomasNeutral.png");
		createTextBox(-1.f, 280.f, 1.f, 1.f, 0.267f, 0.45f);
		actorText("Hilma", 480.f, 307.f, 1.f, 1.f);
	}

	else if (mState == 1)
	{
		advancedText(level3StartThomas, 100.f, 420.f, 1.f, 1.f);
		drawSecondCharacter(mHandler, 700.f, 30.f, 1.f, 1.f, 0.2f, 0.2f, "expressionThomasWorried.png");
		actorText("Thomas", 472.f, 307.f, 1.f, 1.f);
	}

	else if (mState == 2)
	{
		advancedText(level3StartHilma2, 100.f, 420.f, 1.f, 1.f);
		drawFirstCharacter(mHandler, 300.f, 30.f, 1.f, 1.f, -0.2f, 0.2f, "expressionHilmaThoughtful.png");
		actorText("Hilma", 480.f, 307.f, 1.f, 1.f);
	}

	else if (mState == 3)
	{
		advancedText(level3StartThomas2, 100.f, 420.f, 1.f, 1.f);
		actorText("Thomas", 472.f, 307.f, 1.f, 1.f);
	}

	else if (mState == 4)
	{
		advancedText(level3StartThomas3, 100.f, 420.f, 1.f, 1.f);
		drawSecondCharacter(mHandler, 700.f, 30.f, 1.f, 1.f, 0.2f, 0.2f, "expressionThomasHappy.png");
		actorText("Thomas", 472.f, 307.f, 1.f, 1.f);
	}

	else if (mState == 5)
	{
		advancedText(level3StartThomas4, 100.f, 420.f, 1.f, 1.f);
		drawSecondCharacter(mHandler, 700.f, 30.f, 1.f, 1.f, 0.2f, 0.2f, "expressionThomasWorried.png");
		actorText("Thomas", 472.f, 307.f, 1.f, 1.f);
	}

	else if (mState == 6)
	{
		advancedText(level3StartHilma3, 100.f, 420.f, 1.f, 1.f);
		drawFirstCharacter(mHandler, 300.f, 30.f, 1.f, 1.f, -0.2f, 0.2f, "expressionHilmaAbject.png");
		actorText("Hilma", 480.f, 307.f, 1.f, 1.f);
	}

	else if (mState == 7)
	{
		advancedText(level3StartThomas5, 100.f, 420.f, 1.f, 1.f);
		actorText("Thomas", 472.f, 307.f, 1.f, 1.f);
	}

	else if (mState == 8)
	{
		advancedText(level3StartHilma4, 100.f, 420.f, 1.f, 1.f);
		drawFirstCharacter(mHandler, 300.f, 30.f, 1.f, 1.f, -0.2f, 0.2f, "expressionHilmaSurprised.png");
		actorText("Hilma", 480.f, 307.f, 1.f, 1.f);
	}

	else if (mState == 9)
	{
		advancedText(level3StartSurtanten, 100.f, 420.f, 1.f, 1.f);
		actorText("Surtanten", 462.f, 307.f, 1.f, 1.f);
	}

	else if (mState == 10)
	{
		advancedText(level3StartThomas6, 100.f, 420.f, 1.f, 1.f);
		drawSecondCharacter(mHandler, 700.f, 30.f, 1.f, 1.f, 0.2f, 0.2f, "expressionThomasChocked.png");
		actorText("Thomas", 472.f, 307.f, 1.f, 1.f);
	}

	else if (mState == 11)
	{
		advancedText(level3StartHilma5, 100.f, 420.f, 1.f, 1.f);
		drawFirstCharacter(mHandler, 300.f, 30.f, 1.f, 1.f, -0.2f, 0.2f, "expressionHilmaConfident.png");
		actorText("Hilma", 480.f, 307.f, 1.f, 1.f);
	}

	else if (mState == 12)
	{
		advancedText(level3StartThomas7, 100.f, 420.f, 1.f, 1.f);
		drawSecondCharacter(mHandler, 700.f, 30.f, 1.f, 1.f, 0.2f, 0.2f, "expressionThomasWorried.png");
		actorText("Thomas", 472.f, 307.f, 1.f, 1.f);
	}

	else if (mState == 13)
	{
		advancedText(level3StartHilma6, 100.f, 420.f, 1.f, 1.f);
		drawFirstCharacter(mHandler, 300.f, 30.f, 1.f, 1.f, -0.2f, 0.2f, "expressionHilmaSurprised.png");
		actorText("Hilma", 480.f, 307.f, 1.f, 1.f);
	}

	else if (mState == 14)
	{
		advancedText(level3StartThomas8, 100.f, 420.f, 1.f, 1.f);
		actorText("Thomas", 472.f, 307.f, 1.f, 1.f);
	}

	else if (mState == 15)
	{
		advancedText(level3StartHilma7, 100.f, 420.f, 1.f, 1.f);
		drawFirstCharacter(mHandler, 300.f, 30.f, 1.f, 1.f, -0.2f, 0.2f, "expressionHilmaGrumpy.png");
		actorText("Hilma", 480.f, 307.f, 1.f, 1.f);
	}

	else if (mState == 16)
	{
		advancedText(level3StartThomas9, 100.f, 420.f, 1.f, 1.f);
		drawSecondCharacter(mHandler, 700.f, 30.f, 1.f, 1.f, 0.2f, 0.2f, "expressionThomasThoughtful.png");
		actorText("Thomas", 472.f, 307.f, 1.f, 1.f);
	}

	else if (mState == 17)
	{
		advancedText(level3StartHilma8, 100.f, 420.f, 1.f, 1.f);
		drawFirstCharacter(mHandler, 300.f, 30.f, 1.f, 1.f, -0.2f, 0.2f, "expressionHilmaSigh.png");
		actorText("Hilma", 480.f, 307.f, 1.f, 1.f);
	}

	else if (mState == 18)
	{
		advancedText(level3StartHilma9, 100.f, 420.f, 1.f, 1.f);
		drawFirstCharacter(mHandler, 300.f, 30.f, 1.f, 1.f, -0.2f, 0.2f, "expressionHilmaDetermined.png");
		actorText("Hilma", 480.f, 307.f, 1.f, 1.f);
	}
}

void DialogueSystem::displayLevel3ShedAdvancedDialogue()
{
	std::string level3ShedThomas = "Wow! Jag trodde aldrig vi skulle ta oss förbi!";
	std::string level3ShedHilma = "Du borde lita mer på mig Thomas! Varken vidunder eller ilskna bin kan stå i min väg!";
	std::string level3ShedThomas2 = "Så hur tar vi oss till Hittarnas Värld?";
	std::string level3ShedHilma2 = "Tyvärr Thomas. Du är för stor för att få plats där nere. Härifrån måste jag fortsätta ensam.";
	std::string level3ShedThomas3 = "Men...";
	std::string level3ShedHilma3 = "Det är okej, jag är tillbaka på nolltid och med fickuret i hand! Dessutom behöver jag någon som kan stå vakt, så att inte hunden eller bina kommer tillbaka.";
	std::string level3ShedThomas4 = "Okej, men om du ser nåt häftigt kom ihåg att berätta det för mig sen!";
	std::string level3ShedHilma4 = "Jag lovar! Ses snart!";

	if (mState >= 8)
	{
		mText.setString("");
		mActorText.setString("");
		mHasClicked = false;
		mLevel3Shed = false;
		mAdvancedIsActive = false;
		mFinishedDialogue = true;
	}

	else if (mState == 0)
	{
		mAdvancedIsActive = true;
		advancedText(level3ShedThomas, 100.f, 420.f, 1.f, 1.f);
		drawFirstCharacter(mHandler, 300.f, 30.f, 1.f, 1.f, -0.2f, 0.2f, "expressionHilmaHappy.png");
		drawSecondCharacter(mHandler, 700.f, 30.f, 1.f, 1.f, 0.2f, 0.2f, "expressionThomasHappy.png");
		createTextBox(-1.f, 280.f, 1.f, 1.f, 0.267f, 0.45f);
		actorText("Thomas", 472.f, 307.f, 1.f, 1.f);
	}

	else if (mState == 1)
	{
		advancedText(level3ShedHilma, 100.f, 420.f, 1.f, 1.f);
		drawFirstCharacter(mHandler, 300.f, 30.f, 1.f, 1.f, -0.2f, 0.2f, "expressionHilmaConfident.png");
		actorText("Hilma", 480.f, 307.f, 1.f, 1.f);
	}

	else if (mState == 2)
	{
		advancedText(level3ShedThomas2, 100.f, 420.f, 1.f, 1.f);
		actorText("Thomas", 472.f, 307.f, 1.f, 1.f);
	}

	else if (mState == 3)
	{
		advancedText(level3ShedHilma2, 100.f, 420.f, 1.f, 1.f);
		drawFirstCharacter(mHandler, 300.f, 30.f, 1.f, 1.f, -0.2f, 0.2f, "expressionHilmaSigh.png");
		actorText("Hilma", 480.f, 307.f, 1.f, 1.f);
	}

	else if (mState == 4)
	{
		advancedText(level3ShedThomas3, 100.f, 420.f, 1.f, 1.f);
		drawSecondCharacter(mHandler, 700.f, 30.f, 1.f, 1.f, 0.2f, 0.2f, "expressionThomasWorried.png");
		actorText("Thomas", 472.f, 307.f, 1.f, 1.f);
	}

	else if (mState == 5)
	{
		advancedText(level3ShedHilma3, 100.f, 420.f, 1.f, 1.f);
		drawFirstCharacter(mHandler, 300.f, 30.f, 1.f, 1.f, -0.2f, 0.2f, "expressionHilmaHappy.png");
		actorText("Hilma", 480.f, 307.f, 1.f, 1.f);
	}

	else if (mState == 6)
	{
		advancedText(level3ShedThomas4, 100.f, 420.f, 1.f, 1.f);
		drawSecondCharacter(mHandler, 700.f, 30.f, 1.f, 1.f, 0.2f, 0.2f, "expressionThomasHappy.png");
		actorText("Thomas", 472.f, 307.f, 1.f, 1.f);
	}

	else if (mState == 7)
	{
		advancedText(level3ShedHilma4, 100.f, 420.f, 1.f, 1.f);
		actorText("Hilma", 480.f, 307.f, 1.f, 1.f);
	}
}

void DialogueSystem::displayLevel3Skatmaran1AdvancedDialogue()
{
	std::string level3Skatmaran1Hilma = "Hörru du din tjuv! Ge tillbaka det du stulit!";
	std::string level3Skatmaran1Skatmaran = "Vem är det som skriker här? Och vem anklagar mig för att vara en tjuv?";
	std::string level3Skatmaran1Skatmaran2 = "Hilma? Är det du som står här och gormar?";
	std::string level3Skatmaran1Hilma2 = "Klart det är jag din hönshjärna! Någon måste komma och säga till när dina skator är ute och stjäl från hederligt folk!";
	std::string level3Skatmaran1Skatmaran3 = "Vad är det här för hemska anklagelser? Hur vågar du påsta att jag, Skatmaran, den främsta bland hittare, är en tjuv?";
	std::string level3Skatmaran1Hilma3 = "Din dumma skata tog ett fickur från människan jag hjälper. Vi följde den hela vägen hit och alla vet att det skatorna stjäl häromkring hamnar i dina händer.";
	std::string level3Skatmaran1Skatmaran4 = "Det stämmer väl och det stämmer att en av mina skator nyss dök upp med ett vackert fickur. Men mina skator är tränade att aldrig stjäla, det du påstår är omöjligt.";
	std::string level3Skatmaran1Hilma4 = "Omöjligt? Jag såg det ju hända med mina egna ögon! En människa och Tapparen Putte såg det med!";
	std::string level3Skatmaran1Skatmaran5 = "Den där tapparen kan ha sett vad som helst, hans ord är lika goda som den människans. Och du vet att vi inte lyssnar på människor.";
	std::string level3Skatmaran1Hilma5 = "";
	std::string level3Skatmaran1Skatmaran6 = "Det HAR hänt att mina skator tagit saker från någon som inte tillhört dem. Var det människans fickur?";
	std::string level3Skatmaran1Hilma6 = "Nej... det var hans mormors.";
	std::string level3Skatmaran1Skatmaran7 = "Aha! Då är det ju knappast stulet! Och den här mormorn, letar hon efter sitt fickur?";
	std::string level3Skatmaran1Hilma7 = "Nej hon är försvunnen och det där fickuret är en ledtråd som kan hjälpa mig hitta henne!";
	std::string level3Skatmaran1Skatmaran8 = "Reglerna säger att jag bara måste ge bort föremål till personen som äger det. Om den här mormor nu är försvunnen spelar det ju ingen roll om fickuret är borttappat eller i mina händer!";
	std::string level3Skatmaran1Hilma8 = "Lyssna här din fjäderskalle, jag måste ha det där fickuret och du kommer att ge det till mig.";
	std::string level3Skatmaran1Skatmaran9 = "Inte då! Det är en av de finaste skatterna jag någonsin hittat! Dessutom hjälper den mig att hålla koll på tiden för min bokföring.";
	std::string level3Skatmaran1Skatmaran10 = "Enda anledningen till att jag skulle ge den till dig är om du ger mig något annat jag vill ha mer.";
	std::string level3Skatmaran1Hilma9 = "Jaha? Vad då för nåt?";
	std::string level3Skatmaran1Skatmaran11 = "Jag vet till exempel att hon där borta har en mycket fin brosch jag länge haft ögonen på.";
	std::string level3Skatmaran1Hilma10 = "Va? Vill du att jag går och stjäl åt dig nu för att få tillbaka något du stulit?";
	std::string level3Skatmaran1Skatmaran12 = "Jag har inte sagt någonting om att stjäla. Hur du får tag i den är din ensak.";
	std::string level3Skatmaran1Hilma11 = "Okej då, jag går och frågar om det finns någonting jag kan göra för att få den. Men det är bäst för dig att du håller ditt löfte.";
	std::string level3Skatmaran1Skatmaran13 = "Har jag någonsin ljugit för dig?";
	std::string level3Skatmaran1Hilma12 = "Flera gånger.";
	std::string level3Skatmaran1Skatmaran14 = "Hohoho.";

	if (mState >= 26)
	{
		mText.setString("");
		mActorText.setString("");
		mHasClicked = false;
		mLevel3Skatmaran1 = false;
		mAdvancedIsActive = false;
		mFinishedDialogue = true;
	}

	else if (mState == 0)
	{
		mAdvancedIsActive = true;
		advancedText(level3Skatmaran1Hilma, 100.f, 420.f, 1.f, 1.f);
		drawFirstCharacter(mHandler, 300.f, 30.f, 1.f, 1.f, -0.2f, 0.2f, "expressionHilmaAngry.png");
		drawSecondCharacter(mHandler, 700.f, 30.f, 1.f, 1.f, 0.2f, 0.2f, "expressionThomasHappy.png");
		createTextBox(-1.f, 280.f, 1.f, 1.f, 0.267f, 0.45f);
		actorText("Hilma", 480.f, 307.f, 1.f, 1.f);
	}

	else if (mState == 1)
	{
		advancedText(level3Skatmaran1Skatmaran, 100.f, 420.f, 1.f, 1.f);
		actorText("Skatmaran", 470.f, 307.f, 1.f, 1.f);
	}

	else if (mState == 2)
	{
		advancedText(level3Skatmaran1Skatmaran2, 100.f, 420.f, 1.f, 1.f);
		actorText("Skatmaran", 470.f, 307.f, 1.f, 1.f);
	}

	else if (mState == 3)
	{
		advancedText(level3Skatmaran1Hilma2, 100.f, 420.f, 1.f, 1.f);
		drawFirstCharacter(mHandler, 300.f, 30.f, 1.f, 1.f, -0.2f, 0.2f, "expressionHilmaGrumpy.png");
		actorText("Hilma", 480.f, 307.f, 1.f, 1.f);
	}

	else if (mState == 5)
	{
		advancedText(level3Skatmaran1Hilma3, 100.f, 420.f, 1.f, 1.f);
		drawFirstCharacter(mHandler, 300.f, 30.f, 1.f, 1.f, -0.2f, 0.2f, "expressionHilmaAngry.png");
		actorText("Hilma", 480.f, 307.f, 1.f, 1.f);
	}

	else if (mState == 7)
	{
		advancedText(level3Skatmaran1Hilma4, 100.f, 420.f, 1.f, 1.f);
		drawFirstCharacter(mHandler, 300.f, 30.f, 1.f, 1.f, -0.2f, 0.2f, "expressionHilmaGrumpy.png");
		actorText("Hilma", 480.f, 307.f, 1.f, 1.f);
	}

	else if (mState == 9)
	{
		advancedText(level3Skatmaran1Hilma5, 100.f, 420.f, 1.f, 1.f);
		drawFirstCharacter(mHandler, 300.f, 30.f, 1.f, 1.f, -0.2f, 0.2f, "expressionHilmaAngry.png");
		actorText("Hilma", 480.f, 307.f, 1.f, 1.f);
	}

	else if (mState == 11)
	{
		advancedText(level3Skatmaran1Hilma6, 100.f, 420.f, 1.f, 1.f);
		drawFirstCharacter(mHandler, 300.f, 30.f, 1.f, 1.f, -0.2f, 0.2f, "expressionHilmaSigh.png");
		actorText("Hilma", 480.f, 307.f, 1.f, 1.f);
	}

	else if (mState == 13)
	{
		advancedText(level3Skatmaran1Hilma7, 100.f, 420.f, 1.f, 1.f);
		drawFirstCharacter(mHandler, 300.f, 30.f, 1.f, 1.f, -0.2f, 0.2f, "expressionHilmaGrumpy.png");
		actorText("Hilma", 480.f, 307.f, 1.f, 1.f);
	}

	else if (mState == 15)
	{
		advancedText(level3Skatmaran1Hilma8, 100.f, 420.f, 1.f, 1.f);
		drawFirstCharacter(mHandler, 300.f, 30.f, 1.f, 1.f, -0.2f, 0.2f, "expressionHilmaAngry.png");
		actorText("Hilma", 480.f, 307.f, 1.f, 1.f);
	}

	else if (mState == 18)
	{
		advancedText(level3Skatmaran1Hilma9, 100.f, 420.f, 1.f, 1.f);
		drawFirstCharacter(mHandler, 300.f, 30.f, 1.f, 1.f, -0.2f, 0.2f, "expressionHilmaGrumpy.png");
		actorText("Hilma", 480.f, 307.f, 1.f, 1.f);
	}

	else if (mState == 20)
	{
		advancedText(level3Skatmaran1Hilma10, 100.f, 420.f, 1.f, 1.f);
		actorText("Hilma", 480.f, 307.f, 1.f, 1.f);
	}

	else if (mState == 22)
	{
		advancedText(level3Skatmaran1Hilma11, 100.f, 420.f, 1.f, 1.f);
		actorText("Hilma", 480.f, 307.f, 1.f, 1.f);
	}

	else if (mState == 24)
	{
		advancedText(level3Skatmaran1Hilma12, 100.f, 420.f, 1.f, 1.f);
		actorText("Hilma", 480.f, 307.f, 1.f, 1.f);
	}
}

//Level 5
void DialogueSystem::displayLevel5StartAdvancedDialogue()
{
	std::string level5StartTeller = "Efter att ha cyklat i full fart kom de till slut fram till skogens hjärta. Där stod ett stort, gammalt hus. Tomten var alldeles igenvuxen med vildblomster och huset såg övergivet ut. Kunde mormor verkligen vara här?";
	std::string level5StartHilma = "Det ser ju städat ut här inne.";
	std::string level5StartThomas = "Tror du kanske att...";
	std::string level5StartHilma2 = "Ja, hon måste vara här, Thomas.";
	std::string level5StartTeller2 = "Det klappade till i Thomas hjärta. Hon var här, det var han säker på. Thomas kunde knappt hålla inne sin lycka.";
	std::string level5StartThomas2 = "Vad väntar vi på! Kom så hittar vi henne! Hon skrev i brevet att hon skulle se kometen idag; hon borde vara på övervåningen!";
	std::string level5StartHilma3 = "Jag tror jag såg en balkong förut, hon kanske är där?";

	if (mState >= 7)
	{
		mText.setString("");
		mActorText.setString("");
		mHasClicked = false;
		mLevel5Start = false;
		mAdvancedIsActive = false;
		mFinishedDialogue = true;
	}

	else if (mState == 0)
	{
		mAdvancedIsActive = true;
		advancedText(level5StartTeller, 100.f, 420.f, 1.f, 1.f);
		drawFirstCharacter(mHandler, 300.f, 30.f, 1.f, 1.f, -0.2f, 0.2f, "expressionHilmaSurprised.png");
		drawSecondCharacter(mHandler, 700.f, 30.f, 1.f, 1.f, 0.2f, 0.2f, "expressionThomasHappy.png");
		createTextBox(-1.f, 280.f, 1.f, 1.f, 0.267f, 0.45f);
		actorText("Berättare", 462.f, 307.f, 1.f, 1.f);
	}

	else if (mState == 1)
	{
		advancedText(level5StartHilma, 100.f, 420.f, 1.f, 1.f);
		actorText("Hilma", 480.f, 307.f, 1.f, 1.f);
	}

	else if (mState == 2)
	{
		advancedText(level5StartThomas, 100.f, 420.f, 1.f, 1.f);
		actorText("Thomas", 472.f, 307.f, 1.f, 1.f);
	}

	else if (mState == 3)
	{
		advancedText(level5StartHilma2, 100.f, 420.f, 1.f, 1.f);
		drawFirstCharacter(mHandler, 300.f, 30.f, 1.f, 1.f, -0.2f, 0.2f, "expressionHilmaHappy.png");
		actorText("Hilma", 480.f, 307.f, 1.f, 1.f);
	}

	else if (mState == 4)
	{
		advancedText(level5StartTeller2, 100.f, 420.f, 1.f, 1.f);
		actorText("Berättare", 462.f, 307.f, 1.f, 1.f);
	}

	else if (mState == 5)
	{
		advancedText(level5StartThomas2, 100.f, 420.f, 1.f, 1.f);
		actorText("Thomas", 472.f, 307.f, 1.f, 1.f);
	}

	else if (mState == 6)
	{
		advancedText(level5StartHilma3, 100.f, 420.f, 1.f, 1.f);
		drawFirstCharacter(mHandler, 300.f, 30.f, 1.f, 1.f, -0.2f, 0.2f, "expressionHilmaThoughtful.png");
		actorText("Hilma", 480.f, 307.f, 1.f, 1.f);
	}
}

void DialogueSystem::displayLevel5BalconyDoorAdvancedDialogue()
{
	std::string level5ClosedTeller = "Gång på gång knackade Thomas på dörren i hopp om att mormor skulle höra. Men de fick inget svar.";
	std::string level5ClosedHilma = "Hm… Detta var väldigt märkligt. Låst? Varför är det låst om hon vill träffa oss? Det här går verkligen inte ihop!";
	std::string level5ClosedThomas = "Mormor kanske stängde av hörapparaten? Hon brukade i alla fall göra det när hon inte ville bli störd eller om surtanten kom och knackade på.";
	std::string level5ClosedHilma2 = "Hmph! gamla människor… Men det förklarar fortfarande inte varför dörren är låst!";
	std::string level5ClosedThomas2 = "Jag vet inte,  ibland brukar dörrar låsas av sig själva när man stänger dem. Hon låste säkert ut sig själv och har inte märkt det. Och nu hör hon oss inte för att hörapparaten är avstängd.";
	std::string level5ClosedThomas3 = "Vi måste hitta ett sätt att låsa upp dörren!";
	std::string level5ClosedHilma3 = "Jag har fått nog av låsta dörrar för idag...";
	std::string level5ClosedTeller2 = "Hilma och Thomas försökte tänka ut hur de skulle kunna låsa upp dörren. De hade ingen nyckel och hon såg inget kryphål eller annat sätt att ta sig förbi den. Men då hörde de plötsligt en röst. Det var någon de kände igen.";

	if (mState >= 8)
	{
		mText.setString("");
		mActorText.setString("");
		mHasClicked = false;
		mLevel5BalconyDoor = false;
		mAdvancedIsActive = false;
		mFinishedDialogue = true;
	}

	else if (mState == 0)
	{
		mAdvancedIsActive = true;
		advancedText(level5ClosedTeller, 100.f, 420.f, 1.f, 1.f);
		drawFirstCharacter(mHandler, 300.f, 30.f, 1.f, 1.f, -0.2f, 0.2f, "expressionHilmaThoughtful.png");
		drawSecondCharacter(mHandler, 700.f, 30.f, 1.f, 1.f, 0.2f, 0.2f, "expressionThomasThoughtful.png");
		createTextBox(-1.f, 280.f, 1.f, 1.f, 0.267f, 0.45f);
		actorText("Berättare", 462.f, 307.f, 1.f, 1.f);
	}

	else if (mState == 1)
	{
		advancedText(level5ClosedHilma, 100.f, 420.f, 1.f, 1.f);
		actorText("Hilma", 480.f, 307.f, 1.f, 1.f);
	}

	else if (mState == 2)
	{
		advancedText(level5ClosedThomas, 100.f, 420.f, 1.f, 1.f);
		actorText("Thomas", 472.f, 307.f, 1.f, 1.f);
	}

	else if (mState == 3)
	{
		advancedText(level5ClosedHilma2, 100.f, 420.f, 1.f, 1.f);
		drawFirstCharacter(mHandler, 300.f, 30.f, 1.f, 1.f, -0.2f, 0.2f, "expressionHilmaGrumpy.png");
		actorText("Hilma", 480.f, 307.f, 1.f, 1.f);
	}

	else if (mState == 4)
	{
		advancedText(level5ClosedThomas2, 100.f, 420.f, 1.f, 1.f);
		actorText("Thomas", 472.f, 307.f, 1.f, 1.f);
	}

	else if (mState == 5)
	{
		advancedText(level5ClosedThomas3, 100.f, 420.f, 1.f, 1.f);
		actorText("Thomas", 472.f, 307.f, 1.f, 1.f);
	}

	else if (mState == 6)
	{
		advancedText(level5ClosedHilma3, 100.f, 420.f, 1.f, 1.f);
		drawFirstCharacter(mHandler, 300.f, 30.f, 1.f, 1.f, -0.2f, 0.2f, "expressionHilmaSigh.png");
		actorText("Hilma", 480.f, 307.f, 1.f, 1.f);
	}

	else if (mState == 7)
	{
		advancedText(level5ClosedTeller2, 100.f, 420.f, 1.f, 1.f);
		actorText("Berättare", 462.f, 307.f, 1.f, 1.f);
	}
}
//Saknar Putte, fel expressions
void DialogueSystem::displayLevel5Putte2AdvancedDialogue()
{
	std::string level5ReunionPutte = "Lisa! Totte! Var är ni? Åh vart har ni tagit vägen? Det här kan inte vara sant...";
	std::string level5ReunionHilma = "Vad är det nu då Putte? Hur kommer det sig att du alltid är där vi är? Följer du efter oss eller?";
	std::string level5ReunionThomas = "Vad har hänt Putte?";
	std::string level5ReunionPutte2 = "Jag är så värdelös...Jag är Tapparen Putte… som inte ens kan hålla reda på sina egna barn.";
	std::string level5ReunionThomas2 = "Har du barn?";
	std::string level5ReunionHilma2 = "Åh nej, två Putte till...";
	std::string level5ReunionPutte3 = "Ja… Lisa och Totte heter dem. Jag vet inte hur många gånger jag har sagt åt dem att ta det försiktigt... Och nu... nu är de borta...";
	std::string level5ReunionTeller = "Bakom Putte kom en annan hittare fram och la en tröstande hand på hans axel. Denna hittare hade en sjal istället för en mössa och var klädd i solens färger.";
	std::string level5ReunionLillemor = "Såja, Puttinutten, var inte orolig! De är säkert någonstans på nedervåningen och leker. Kanske har de hittat ett nytt gömställe? Du vet ju vilka duktiga hittare de är!";
	std::string level5ReunionHilma3 = "Puttinutten?";
	std::string level5ReunionPutte4 = "Men tänk om katten har tagit dem! Eller om de har fastnat i råttfällan? Eller blivit tagna av fåglarna? Ack! Jag kan inte ens hålla reda på mina barn…";
	std::string level5ReunionPutte5 = "Jag är den sämsta hittaren någonsin...";
	std::string level5ReunionLillemor2 = "Men älskade vän. Nog kan du vara slarvig, men inte den sämsta! De kommer säkert tillbaka snart. Du måste låta dem breda ut sina vingar!";
	std::string level5ReunionPutte6 = "";
	std::string level5ReunionThomas3 = "Du Hilma, jag tror vi borde hjälpa honom att hitta sina barn.";
	std::string level5ReunionHilma4 = "Borde och borde? Vi måste väl om han ska sluta gråta någon gång det här århundradet! Hörrudu Putte!";
	std::string level5ReunionHilma5 = "Vi hjälper dig, men det här är sista gången!";
	std::string level5ReunionPutte7 = "Verkligen?";
	std::string level5ReunionTeller2 = "Putte blev överlycklig och kramade om Hilma så hårt att hon nästan höll på att kvävas. Hon slet sig ifrån hans famn och ramlade baklänges ner i Thomas hand.";
	std::string level5ReunionLillemor3 = "Tack att ni hjälper min eländiga make! Han brukar bli väldigt orolig för våra barn. Jag har sagt åt honom flera gånger att de måste få leka själva och lära sig om livet. Men vad jag än säger kan han inte sluta oroa sig över dem. ";
	std::string level5ReunionLillemor4 = "Lillemor heter jag förresten! Och ni gissar jag är Hilma och Thomas? Putte har pratat så mycket om er två sedan han träffade er.";
	std::string level5ReunionThomas4 = "Vi ska hitta dem, Lillemor! Det lovar vi!";
	std::string level5ReunionHilma6 = "Var brukar Lisa och Totte leka?";
	std::string level5ReunionLillemor5 = "De brukar ofta leka på nedervåningen. Kolla i vardagsrummet eller köket: de brukar hålla till där!";
	std::string level5ReunionHilma7 = "Då så! Då börjar vi leta där. Ah! just ja! Vet ni hur man öppnar balkongdörren?";
	std::string level5ReunionLillemor6 = "Jag vet inte riktigt i detalj, men ibland har jag sett en äldre kvinna klättra upp för en stege och sätta upp konstiga bollar i taket för att öppna balkongdörren.";

	if (mState >= 26)
	{
		mText.setString("");
		mActorText.setString("");
		mHasClicked = false;
		mLevel5Putte2 = false;
		mAdvancedIsActive = false;
		mFinishedDialogue = true;
	}

	else if (mState == 0)
	{
		mAdvancedIsActive = true;
		advancedText(level5ReunionPutte, 100.f, 420.f, 1.f, 1.f);
		drawFirstCharacter(mHandler, 300.f, 30.f, 1.f, 1.f, -0.2f, 0.2f, "expressionHilmaAngry.png");
		drawSecondCharacter(mHandler, 700.f, 30.f, 1.f, 1.f, 0.2f, 0.2f, "expressionThomasThoughtful.png");
		createTextBox(-1.f, 280.f, 1.f, 1.f, 0.267f, 0.45f);
		actorText("Putte", 480.f, 307.f, 1.f, 1.f);
	}

	else if (mState == 1)
	{
		advancedText(level5ReunionHilma, 100.f, 420.f, 1.f, 1.f);
		actorText("Hilma", 480.f, 307.f, 1.f, 1.f);
	}

	else if (mState == 2)
	{
		advancedText(level5ReunionThomas, 100.f, 420.f, 1.f, 1.f);
		drawSecondCharacter(mHandler, 700.f, 30.f, 1.f, 1.f, 0.2f, 0.2f, "expressionThomasHappy.png");
		actorText("Thomas", 472.f, 307.f, 1.f, 1.f);
	}

	else if (mState == 3)
	{
		advancedText(level5ReunionPutte2, 100.f, 420.f, 1.f, 1.f);
		drawFirstCharacter(mHandler, 300.f, 30.f, 1.f, 1.f, -0.2f, 0.2f, "expressionHilmaSurprised.png");
		drawSecondCharacter(mHandler, 700.f, 30.f, 1.f, 1.f, 0.2f, 0.2f, "expressionThomasSurprised.png");
		actorText("Putte", 480.f, 307.f, 1.f, 1.f);
	}

	else if (mState == 4)
	{
		advancedText(level5ReunionThomas2, 100.f, 420.f, 1.f, 1.f);
		actorText("Thomas", 472.f, 307.f, 1.f, 1.f);
	}

	else if (mState == 5)
	{
		advancedText(level5ReunionHilma2, 100.f, 420.f, 1.f, 1.f);
		actorText("Hilma", 480.f, 307.f, 1.f, 1.f);
	}

	else if (mState == 6)
	{
		advancedText(level5ReunionPutte3, 100.f, 420.f, 1.f, 1.f);
		drawFirstCharacter(mHandler, 300.f, 30.f, 1.f, 1.f, -0.2f, 0.2f, "expressionHilmaGrumpy.png");
		actorText("Putte", 480.f, 307.f, 1.f, 1.f);
	}
	
	else if (mState == 7)
	{
		advancedText(level5ReunionTeller, 100.f, 420.f, 1.f, 1.f);
		actorText("Berättare", 462.f, 307.f, 1.f, 1.f);
	}

	else if (mState == 8)
	{
		advancedText(level5ReunionLillemor, 100.f, 420.f, 1.f, 1.f);
		actorText("Lillemor", 470.f, 307.f, 1.f, 1.f);
	}

	else if (mState == 9)
	{
		advancedText(level5ReunionHilma3, 100.f, 420.f, 1.f, 1.f);
		drawFirstCharacter(mHandler, 300.f, 30.f, 1.f, 1.f, -0.2f, 0.2f, "expressionHilmaThoughful.png");
		actorText("Hilma", 480.f, 307.f, 1.f, 1.f);
	}

	else if (mState == 10)
	{
		advancedText(level5ReunionPutte4, 100.f, 420.f, 1.f, 1.f);
		drawFirstCharacter(mHandler, 300.f, 30.f, 1.f, 1.f, -0.2f, 0.2f, "expressionHilmaGrumpy.png");
		actorText("Putte", 480.f, 307.f, 1.f, 1.f);
	}

	else if (mState == 11)
	{
		advancedText(level5ReunionPutte5, 100.f, 420.f, 1.f, 1.f);
		drawFirstCharacter(mHandler, 300.f, 30.f, 1.f, 1.f, -0.2f, 0.2f, "expressionHilmaGrumpy.png");
		actorText("Putte", 480.f, 307.f, 1.f, 1.f);
	}

	else if (mState == 12)
	{
		advancedText(level5ReunionLillemor2, 100.f, 420.f, 1.f, 1.f);
		actorText("Lillemor", 470.f, 307.f, 1.f, 1.f);
	}

	else if (mState == 13)
	{
		advancedText(level5ReunionPutte6, 100.f, 420.f, 1.f, 1.f);
		drawFirstCharacter(mHandler, 300.f, 30.f, 1.f, 1.f, -0.2f, 0.2f, "expressionHilmaGrumpy.png");
		actorText("Putte", 480.f, 307.f, 1.f, 1.f);
	}

	else if (mState == 14)
	{
		advancedText(level5ReunionThomas3, 100.f, 420.f, 1.f, 1.f);
		drawSecondCharacter(mHandler, 700.f, 30.f, 1.f, 1.f, 0.2f, 0.2f, "expressionThomasWorried.png");
		actorText("Thomas", 472.f, 307.f, 1.f, 1.f);
	}

	else if (mState == 15)
	{
		advancedText(level5ReunionHilma4, 100.f, 420.f, 1.f, 1.f);
		actorText("Hilma", 480.f, 307.f, 1.f, 1.f);
	}

	else if (mState == 16)
	{
		advancedText(level5ReunionHilma5, 100.f, 420.f, 1.f, 1.f);
		actorText("Hilma", 480.f, 307.f, 1.f, 1.f);
	}

	else if (mState == 17)
	{
		advancedText(level5ReunionPutte7, 100.f, 420.f, 1.f, 1.f);
		drawFirstCharacter(mHandler, 300.f, 30.f, 1.f, 1.f, -0.2f, 0.2f, "expressionHilmaGrumpy.png");
		actorText("Putte", 480.f, 307.f, 1.f, 1.f);
	}

	else if (mState == 18)
	{
		advancedText(level5ReunionTeller2, 100.f, 420.f, 1.f, 1.f);
		actorText("Berättare", 462.f, 307.f, 1.f, 1.f);
	}

	else if (mState == 19)
	{
		advancedText(level5ReunionLillemor3, 100.f, 420.f, 1.f, 1.f);
		actorText("Lillemor", 470.f, 307.f, 1.f, 1.f);
	}

	else if (mState == 20)
	{
		advancedText(level5ReunionLillemor4, 100.f, 420.f, 1.f, 1.f);
		actorText("Lillemor", 470.f, 307.f, 1.f, 1.f);
	}

	else if (mState == 21)
	{
		advancedText(level5ReunionThomas4, 100.f, 420.f, 1.f, 1.f);
		actorText("Thomas", 472.f, 307.f, 1.f, 1.f);
	}

	else if (mState == 22)
	{
		advancedText(level5ReunionHilma6, 100.f, 420.f, 1.f, 1.f);
		actorText("Hilma", 480.f, 307.f, 1.f, 1.f);
	}

	else if (mState == 23)
	{
		advancedText(level5ReunionLillemor5, 100.f, 420.f, 1.f, 1.f);
		actorText("Lillemor", 470.f, 307.f, 1.f, 1.f);
	}

	else if (mState == 24)
	{
		advancedText(level5ReunionHilma7, 100.f, 420.f, 1.f, 1.f);
		actorText("Hilma", 480.f, 307.f, 1.f, 1.f);
	}

	else if (mState == 25)
	{
		advancedText(level5ReunionLillemor6, 100.f, 420.f, 1.f, 1.f);
		actorText("Lillemor", 470.f, 307.f, 1.f, 1.f);
	}
}

void DialogueSystem::displayLevel5SolarSystemAdvancedDialogue()

{
	std::string level5SolarSystemHilma = "Varför hänger det en massa bollar i taket?";
	std::string level5SolarSystemThomas = "Det är planeterna i vårt solsystem!";
	std::string level5SolarSystemHilma2 = "Planeter? Solsystem? Vad pratar du om?";
	std::string level5SolarSystemThomas2 = "Mormor berättade en gång, att rymden är JÄTTESTOR. Och i rymden finns det massa stjärnor, planeter och galaxer. Vissa har man hittat, men det finns fortfarande en massa som ingen har hittat ännu!";
	std::string level5SolarSystemHilma3 = "Inte hittade? Heh, de skulle behöva en hittare i rymden!";
	std::string level5SolarSystemThomas3 = "När jag blir astronaut kan du få följa med och hjälpa mig! Jag vet! Du kan också bli astronaut!";
	std::string level5SolarSystemHilma4 = "En hittare som astronaut?";
	std::string level5SolarSystemHilma5 = "Ja du, det låter inte dumt. Men jag förstår fortfarande inte det där med planeterna. Jag förstår att man vill hitta dem för att de inte är hittade, men vad mer? Vill man samla på planeter? Vad får man i utbyte?";
	std::string level5SolarSystemThomas4 = "Hm… Mormor sa att planeter är som olika hem. Vårt hem är planeten jorden och är den enda planeten i vårt solsystem där man kan bo. Men det är lite ensamt så vi vill hitta andra planeter som också har liv!";
	std::string level5SolarSystemHilma6 = "Jasså jaha ja, vilken planet är jorden då?";
	std::string level5SolarSystemThomas5 = "Där...";
	std::string level5SolarSystemThomas6 = "Jorden är inte med? Inte Mars,Venus, Pluto, och Saturnus heller! Det här är jättekonstigt. Mormor skulle aldrig ha ett ofärdigt solsystem. Hon kan namnet på alla planeter och till och med månarna!";
	std::string level5SolarSystemHilma7 = "Ja du, Thomas, De kanske gick sönder? Eller… har försvunnit?";
	std::string level5SolarSystemThomas7 = "Jag vet! Vi försöker hitta dem och sätta dem på rätt plats. Då blir mormor jätteglad!";
	std::string level5SolarSystemHilma8 = "Se där Thomas! Det är rätta tankar! Du är en riktig snilleblixt du!";

	if (mState >= 15)
	{
		mText.setString("");
		mActorText.setString("");
		mHasClicked = false;
		mLevel5SolarSystem = false;
		mAdvancedIsActive = false;
		mFinishedDialogue = true;
	}

	else if (mState == 0)
	{
		mAdvancedIsActive = true;
		advancedText(level5SolarSystemHilma, 100.f, 420.f, 1.f, 1.f);
		drawFirstCharacter(mHandler, 300.f, 30.f, 1.f, 1.f, -0.2f, 0.2f, "expressionHilmaThoughtful.png");
		drawSecondCharacter(mHandler, 700.f, 30.f, 1.f, 1.f, 0.2f, 0.2f, "expressionThomasHappy.png");
		createTextBox(-1.f, 280.f, 1.f, 1.f, 0.267f, 0.45f);
		actorText("Hilma", 480.f, 307.f, 1.f, 1.f);
	}

	else if (mState == 1)
	{
		advancedText(level5SolarSystemThomas, 100.f, 420.f, 1.f, 1.f);
		actorText("Thomas", 472.f, 307.f, 1.f, 1.f);
	}

	else if (mState == 2)
	{
		advancedText(level5SolarSystemHilma2, 100.f, 420.f, 1.f, 1.f);
		actorText("Hilma", 480.f, 307.f, 1.f, 1.f);
	}

	else if (mState == 3)
	{
		advancedText(level5SolarSystemThomas2, 100.f, 420.f, 1.f, 1.f);
		drawSecondCharacter(mHandler, 700.f, 30.f, 1.f, 1.f, 0.2f, 0.2f, "expressionThomasSmile.png");
		actorText("Thomas", 472.f, 307.f, 1.f, 1.f);
	}

	else if (mState == 4)
	{
		advancedText(level5SolarSystemHilma3, 100.f, 420.f, 1.f, 1.f);
		drawFirstCharacter(mHandler, 300.f, 30.f, 1.f, 1.f, -0.2f, 0.2f, "expressionHilmaConfident.png");
		actorText("Hilma", 480.f, 307.f, 1.f, 1.f);
	}

	else if (mState == 5)
	{
		advancedText(level5SolarSystemThomas3, 100.f, 420.f, 1.f, 1.f);
		actorText("Thomas", 472.f, 307.f, 1.f, 1.f);
	}

	else if (mState == 6)
	{
		advancedText(level5SolarSystemHilma4, 100.f, 420.f, 1.f, 1.f);
		actorText("Hilma", 480.f, 307.f, 1.f, 1.f);
	}

	else if (mState == 7)
	{
		advancedText(level5SolarSystemHilma5, 100.f, 420.f, 1.f, 1.f);
		drawFirstCharacter(mHandler, 300.f, 30.f, 1.f, 1.f, -0.2f, 0.2f, "expressionHilmaHappy.png");
		actorText("Hilma", 480.f, 307.f, 1.f, 1.f);
	}

	else if (mState == 8)
	{
		advancedText(level5SolarSystemThomas4, 100.f, 420.f, 1.f, 1.f);
		drawSecondCharacter(mHandler, 700.f, 30.f, 1.f, 1.f, 0.2f, 0.2f, "expressionThomasThoughtful.png");
		actorText("Thomas", 472.f, 307.f, 1.f, 1.f);
	}

	else if (mState == 9)
	{
		advancedText(level5SolarSystemHilma6, 100.f, 420.f, 1.f, 1.f);
		drawFirstCharacter(mHandler, 300.f, 30.f, 1.f, 1.f, -0.2f, 0.2f, "expressionHilmaThoughtful.png");
		actorText("Hilma", 480.f, 307.f, 1.f, 1.f);
	}

	else if (mState == 10)
	{
		advancedText(level5SolarSystemThomas5, 100.f, 420.f, 1.f, 1.f);
		drawSecondCharacter(mHandler, 700.f, 30.f, 1.f, 1.f, 0.2f, 0.2f, "expressionThomasHappy.png");
		actorText("Thomas", 472.f, 307.f, 1.f, 1.f);
	}

	else if (mState == 11)
	{
		advancedText(level5SolarSystemThomas6, 100.f, 420.f, 1.f, 1.f);
		drawSecondCharacter(mHandler, 700.f, 30.f, 1.f, 1.f, 0.2f, 0.2f, "expressionThomasChocked.png");
		actorText("Thomas", 472.f, 307.f, 1.f, 1.f);
	}

	else if (mState == 12)
	{
		advancedText(level5SolarSystemHilma7, 100.f, 420.f, 1.f, 1.f);
		actorText("Hilma", 480.f, 307.f, 1.f, 1.f);
	}

	else if (mState == 13)
	{
		advancedText(level5SolarSystemThomas7, 100.f, 420.f, 1.f, 1.f);
		drawSecondCharacter(mHandler, 700.f, 30.f, 1.f, 1.f, 0.2f, 0.2f, "expressionThomasHappy.png");
		actorText("Thomas", 472.f, 307.f, 1.f, 1.f);
	}

	else if (mState == 14)
	{
		advancedText(level5SolarSystemHilma8, 100.f, 420.f, 1.f, 1.f);
		drawFirstCharacter(mHandler, 300.f, 30.f, 1.f, 1.f, -0.2f, 0.2f, "expressionHilmaHappy.png");
		actorText("Hilma", 480.f, 307.f, 1.f, 1.f);
	}
}

void DialogueSystem::displayLevel5MouseHoleAdvancedDialogue()
{
	std::string level5MouseHoleVoices = "Någon skriker på hjälp.";
	std::string level5MouseHoleThomas = "Kan det där vara Lisa och Totte?";
	std::string level5MouseHoleHilma = "Definitivt! Och kattskrället har jagat in dem i mushålet! Vi måste locka bort den på något vis.";

	if (mState >= 3)
	{
		mText.setString("");
		mActorText.setString("");
		mHasClicked = false;
		mLevel5MouseHole = false;
		mAdvancedIsActive = false;
		mFinishedDialogue = true;
	}

	else if (mState == 0)
	{
		mAdvancedIsActive = true;
		advancedText(level5MouseHoleVoices, 100.f, 420.f, 1.f, 1.f);
		drawFirstCharacter(mHandler, 300.f, 30.f, 1.f, 1.f, -0.2f, 0.2f, "expressionHilmaSurprised.png");
		drawSecondCharacter(mHandler, 700.f, 30.f, 1.f, 1.f, 0.2f, 0.2f, "expressionThomasSurprised.png");
		createTextBox(-1.f, 280.f, 1.f, 1.f, 0.267f, 0.45f);
		actorText("Röster", 480.f, 307.f, 1.f, 1.f);
	}

	else if (mState == 1)
	{
		advancedText(level5MouseHoleThomas, 100.f, 420.f, 1.f, 1.f);
		actorText("Thomas", 472.f, 307.f, 1.f, 1.f);
	}

	else if (mState == 2)
	{
		advancedText(level5MouseHoleHilma, 100.f, 420.f, 1.f, 1.f);
		drawFirstCharacter(mHandler, 300.f, 30.f, 1.f, 1.f, -0.2f, 0.2f, "expressionHilmaConfident.png");
		actorText("Hilma", 480.f, 307.f, 1.f, 1.f);
	}
}

void DialogueSystem::displayLevel5VictoryAdvancedDialogue()
{
	std::string level5VictoryHilma = "Så det är ni som är Lisa och Totte? Varför jagade katten efter er?";
	std::string level5VictoryLisa = "Vi lekte med tusse! Och, och, och sen, så öppnade den sin STORA MUN!! Den hade JÄTTESTORA TÄNDER och försökte äta upp oss!";
	std::string level5VictoryTotte = "Tusse brukar annars vara snäll. Den var säkert hungrig, för matskålen är tom.";
	std::string level5VictoryHilma2 = "Nåja, eran pappa har varit jätteorolig för er. Gå upp nu så han slutar att böla!";
	std::string level5VictoryLisa2 = "Ja ja tjatmaja! Vi lekte ju bara.";
	std::string level5VictoryTotte2 = "Tack för att ni hjälpte oss. Här, ni kan få låna våra leksaker!";

	if (mState >= 6)
	{
		mText.setString("");
		mActorText.setString("");
		mHasClicked = false;
		mLevel5Victory = false;
		mAdvancedIsActive = false;
		mFinishedDialogue = true;
	}

	else if (mState == 0)
	{
		mAdvancedIsActive = true;
		advancedText(level5VictoryHilma, 100.f, 420.f, 1.f, 1.f);
		drawFirstCharacter(mHandler, 300.f, 30.f, 1.f, 1.f, -0.2f, 0.2f, "expressionHilmaGrumpy.png");
		drawSecondCharacter(mHandler, 700.f, 30.f, 1.f, 1.f, 0.2f, 0.2f, "expressionThomasChocked.png");
		createTextBox(-1.f, 280.f, 1.f, 1.f, 0.267f, 0.45f);
		actorText("Hilma", 480.f, 307.f, 1.f, 1.f);
	}

	else if (mState == 1)
	{
		advancedText(level5VictoryLisa, 100.f, 420.f, 1.f, 1.f);
		actorText("Lisa", 488.f, 307.f, 1.f, 1.f);
	}

	else if (mState == 2)
	{
		advancedText(level5VictoryTotte, 100.f, 420.f, 1.f, 1.f);
		actorText("Totte", 480.f, 307.f, 1.f, 1.f);
	}

	else if (mState == 3)
	{
		advancedText(level5VictoryHilma2, 100.f, 420.f, 1.f, 1.f);
		drawFirstCharacter(mHandler, 300.f, 30.f, 1.f, 1.f, -0.2f, 0.2f, "expressionHilmaConfident.png");
		actorText("Hilma", 480.f, 307.f, 1.f, 1.f);
	}

	else if (mState == 4)
	{
		advancedText(level5VictoryLisa2, 100.f, 420.f, 1.f, 1.f);
		actorText("Lisa", 488.f, 307.f, 1.f, 1.f);
	}

	else if (mState == 5)
	{
		advancedText(level5VictoryTotte2, 100.f, 420.f, 1.f, 1.f);
		actorText("Totte", 480.f, 307.f, 1.f, 1.f);
	}
}

void DialogueSystem::displayLevel5EndAdvancedDialogue()
{
	//LIEK IDK
}

//Expressions saknas
void DialogueSystem::displayLevel5TogetherAdvancedDialogue()
{
	std::string level5TogetherTeller = "Nu var Puttes familj tillsammans igen. Puttes kinder var alldeles våta av lyckotårar. Han kramade om sina barn, nästan hårdare än vad han kramade Hilma, och lovade att han aldrig skulle tappa bort dem igen.";
	std::string level5TogetherTotte = "Vi var aldrig borttappade pappa.";
	std::string level5TogetherLisa = "Pappa, pappa, pappa! Du skulle ha sett hur Hilma manövrade den stora BESTEN!";
	std::string level5TogetherLillemor = "Tack för att ni hjälpt Putte så många gånger.";
	std::string level5TogetherHilma = "Äsch, det var inget. Jag förstår mig bara inte på honom. Hur kan en hittare vara så slarvig?";
	std::string level5TogetherThomas = "Men Hilma, han hittade faktiskt mormors guldklocka!";
	std::string level5TogetherLillemor2 = "Han må vara klumpig och tappar bort saker. Men han kämpar varje dag för att vara en bra hittare, en bra far, och en god man. Det han lyckas behålla bevarar han väldigt kärt.";
	std::string level5TogetherLillemor3 = "Här! Ni får denna mussla jag hittade i medelhavet för flera år sedan. Det går inte att öppna denna skatt som en vanlig skattkista. Bara där den känner sig som hemma öppnar den upp sig.";
	std::string level5TogetherThomas2 = "Tack så mycket, Lillemor!";
	std::string level5TogetherHilma2 = "Tja... tack.";
	std::string level5TogetherLillemor4 = "Inget att tacka för! Lycka till att hitta det ni söker!";

	if (mState >= 11)
	{
		mText.setString("");
		mActorText.setString("");
		mHasClicked = false;
		mLevel5Together = false;
		mAdvancedIsActive = false;
		mFinishedDialogue = true;
	}

	else if (mState == 0)
	{
		mAdvancedIsActive = true;
		advancedText(level5TogetherTeller, 100.f, 420.f, 1.f, 1.f);
		drawFirstCharacter(mHandler, 300.f, 30.f, 1.f, 1.f, -0.2f, 0.2f, "expressionHilmaGrumpy.png");
		drawSecondCharacter(mHandler, 700.f, 30.f, 1.f, 1.f, 0.2f, 0.2f, "expressionThomasChocked.png");
		createTextBox(-1.f, 280.f, 1.f, 1.f, 0.267f, 0.45f);
		actorText("Berättare", 462.f, 307.f, 1.f, 1.f);
	}

	else if (mState == 1)
	{
		advancedText(level5TogetherTotte, 100.f, 420.f, 1.f, 1.f);
		actorText("Totte", 480.f, 307.f, 1.f, 1.f);
	}

	else if (mState == 2)
	{
		advancedText(level5TogetherLisa, 100.f, 420.f, 1.f, 1.f);
		actorText("Lisa", 488.f, 307.f, 1.f, 1.f);
	}

	else if (mState == 3)
	{
		advancedText(level5TogetherLillemor, 100.f, 420.f, 1.f, 1.f);
		actorText("Lillemor", 470.f, 307.f, 1.f, 1.f);
	}

	else if (mState == 4)
	{
		advancedText(level5TogetherHilma, 100.f, 420.f, 1.f, 1.f);
		actorText("Hilma", 480.f, 307.f, 1.f, 1.f);
	}

	else if (mState == 5)
	{
		advancedText(level5TogetherThomas, 100.f, 420.f, 1.f, 1.f);
		actorText("Thomas", 472.f, 307.f, 1.f, 1.f);
	}

	else if (mState == 6)
	{
		advancedText(level5TogetherLillemor2, 100.f, 420.f, 1.f, 1.f);
		actorText("Lillemor", 470.f, 307.f, 1.f, 1.f);
	}

	else if (mState == 7)
	{
		advancedText(level5TogetherLillemor3, 100.f, 420.f, 1.f, 1.f);
		actorText("Lillemor", 470.f, 307.f, 1.f, 1.f);
	}

	else if (mState == 8)
	{
		advancedText(level5TogetherThomas2, 100.f, 420.f, 1.f, 1.f);
		actorText("Thomas", 472.f, 307.f, 1.f, 1.f);
	}

	else if (mState == 9)
	{
		advancedText(level5TogetherHilma2, 100.f, 420.f, 1.f, 1.f);
		actorText("Hilma", 480.f, 307.f, 1.f, 1.f);
	}

	else if (mState == 10)
	{
		advancedText(level5TogetherLillemor4, 100.f, 420.f, 1.f, 1.f);
		actorText("Lillemor", 470.f, 307.f, 1.f, 1.f);
	}
}

void DialogueSystem::displayLevel5SolutionAdvancedDialogue()
{
	std::string level5SolutionTeller = "När alla planeterna var på plats hördes ett märkligt ljud. Det kom från balkongsdörren...";
	std::string level5SolutionThomas = "Hilma! Jag tror balkongdörren öppnades nu!";
	std::string level5SolutionTeller2 = "Sannerligen var det öppet! De gick fram till balkongdörren. Thomas höll i handtaget och tog ett djupt andetag.";
	std::string level5SolutionHilma = "Redo?";
	std::string level5SolutionThomas2 = "“Redo!";
	std::string level5SolutionTeller3 = "De öppnade balkongdörrarna...";

	if (mState >= 11)
	{
		mText.setString("");
		mActorText.setString("");
		mHasClicked = false;
		mLevel5Together = false;
		mAdvancedIsActive = false;
		mFinishedDialogue = true;
	}

	else if (mState == 0)
	{
		mAdvancedIsActive = true;
		advancedText(level5SolutionTeller, 100.f, 420.f, 1.f, 1.f);
		drawFirstCharacter(mHandler, 300.f, 30.f, 1.f, 1.f, -0.2f, 0.2f, "expressionHilmaHappy.png");
		drawSecondCharacter(mHandler, 700.f, 30.f, 1.f, 1.f, 0.2f, 0.2f, "expressionThomasHappy.png");
		createTextBox(-1.f, 280.f, 1.f, 1.f, 0.267f, 0.45f);
		actorText("Berättare", 462.f, 307.f, 1.f, 1.f);
	}

	else if (mState == 1)
	{
		advancedText(level5SolutionThomas, 100.f, 420.f, 1.f, 1.f);
		drawSecondCharacter(mHandler, 700.f, 30.f, 1.f, 1.f, 0.2f, 0.2f, "expressionThomasSmile.png");
		actorText("Thomas", 472.f, 307.f, 1.f, 1.f);
	}

	else if (mState == 2)
	{
		advancedText(level5SolutionTeller2, 100.f, 420.f, 1.f, 1.f);
		actorText("Berättare", 462.f, 307.f, 1.f, 1.f);
	}

	else if (mState == 3)
	{
		advancedText(level5SolutionHilma, 100.f, 420.f, 1.f, 1.f);
		actorText("Hilma", 480.f, 307.f, 1.f, 1.f);
	}

	else if (mState == 4)
	{
		advancedText(level5SolutionThomas2, 100.f, 420.f, 1.f, 1.f);
		actorText("Thomas", 472.f, 307.f, 1.f, 1.f);
	}

	else if (mState == 5)
	{
		advancedText(level5SolutionTeller3, 100.f, 420.f, 1.f, 1.f);
		actorText("Berättare", 462.f, 307.f, 1.f, 1.f);
	}
}

void DialogueSystem::displayLevel5PaintingAdvancedDialogue()
{
	std::string level5PaintingThomas = "Wow... vilken vacker tavla.";
	std::string level5PaintingHilma = "Har mormor målat den?";
	std::string level5PaintingThomas2 = "Nej... mormor målar inte så fint. Mormor har berättat att man kan se i hörnet på tavlor vem som har målat. Det står… E-e-ez... Ez-i-o… Sen kan jag inte läsa mer. Det var ett jätte långt och krångligt efternamn.";
	std::string level5PaintingHilma2 = "Suck… Människor krånglar alltid till sina namn...";

	if (mState >= 4)
	{
		mText.setString("");
		mActorText.setString("");
		mHasClicked = false;
		mLevel5Painting = false;
		mAdvancedIsActive = false;
		mFinishedDialogue = true;
	}

	else if (mState == 0)
	{
		mAdvancedIsActive = true;
		advancedText(level5PaintingThomas, 100.f, 420.f, 1.f, 1.f);
		drawFirstCharacter(mHandler, 300.f, 30.f, 1.f, 1.f, -0.2f, 0.2f, "expressionHilmaNeutral.png");
		drawSecondCharacter(mHandler, 700.f, 30.f, 1.f, 1.f, 0.2f, 0.2f, "expressionThomasSurprised.png");
		createTextBox(-1.f, 280.f, 1.f, 1.f, 0.267f, 0.45f);
		actorText("Thomas", 472.f, 307.f, 1.f, 1.f);
	}

	else if (mState == 1)
	{
		advancedText(level5PaintingHilma, 100.f, 420.f, 1.f, 1.f);
		drawFirstCharacter(mHandler, 300.f, 30.f, 1.f, 1.f, -0.2f, 0.2f, "expressionHilmaThoughtful.png");
		actorText("Hilma", 480.f, 307.f, 1.f, 1.f);
	}

	else if (mState == 2)
	{
		advancedText(level5PaintingThomas2, 100.f, 420.f, 1.f, 1.f);
		drawSecondCharacter(mHandler, 700.f, 30.f, 1.f, 1.f, 0.2f, 0.2f, "expressionThomasSceptic.png");
		actorText("Thomas", 472.f, 307.f, 1.f, 1.f);
	}

	else if (mState == 3)
	{
		advancedText(level5PaintingHilma2, 100.f, 420.f, 1.f, 1.f);
		drawFirstCharacter(mHandler, 300.f, 30.f, 1.f, 1.f, -0.2f, 0.2f, "expressionHilmaSigh.png");
		actorText("Hilma", 480.f, 307.f, 1.f, 1.f);
	}
}

void DialogueSystem::displayLevel5RecordsAdvancedDialogue()
{
	std::string level5RecordsHilma = "Vad vacker hon är på bilden! Vad är det för skiva?";
	std::string level5RecordsThomas = "Det är en sådan där jättegammal skiva med musik som min mormor brukade lyssna på när hon var ung. Det finns jättemånga såna här skivor i bokhyllan.";
	std::string level5RecordsHilma2 = "Vad för musik?";
	std::string level5RecordsThomas2 = "J.-j-ag vet inte. Det står på ett väldigt lustigt språk...";

	if (mState >= 4)
	{
		mText.setString("");
		mActorText.setString("");
		mHasClicked = false;
		mLevel5Records = false;
		mAdvancedIsActive = false;
		mFinishedDialogue = true;
	}

	else if (mState == 0)
	{
		mAdvancedIsActive = true;
		advancedText(level5RecordsHilma2, 100.f, 420.f, 1.f, 1.f);
		drawFirstCharacter(mHandler, 300.f, 30.f, 1.f, 1.f, -0.2f, 0.2f, "expressionHilmaSurprised.png");
		drawSecondCharacter(mHandler, 700.f, 30.f, 1.f, 1.f, 0.2f, 0.2f, "expressionThomasNeutral.png");
		createTextBox(-1.f, 280.f, 1.f, 1.f, 0.267f, 0.45f);
		actorText("Hilma", 480.f, 307.f, 1.f, 1.f);
	}

	else if (mState == 1)
	{
		advancedText(level5RecordsThomas, 100.f, 420.f, 1.f, 1.f);
		drawSecondCharacter(mHandler, 700.f, 30.f, 1.f, 1.f, 0.2f, 0.2f, "expressionThomasThoughtful.png");
		actorText("Thomas", 472.f, 307.f, 1.f, 1.f);
	}

	else if (mState == 2)
	{
		advancedText(level5RecordsHilma2, 100.f, 420.f, 1.f, 1.f);
		drawFirstCharacter(mHandler, 300.f, 30.f, 1.f, 1.f, -0.2f, 0.2f, "expressionHilmaThoughtful.png");
		actorText("Hilma", 480.f, 307.f, 1.f, 1.f);
	}

	else if (mState == 3)
	{
		advancedText(level5RecordsThomas2, 100.f, 420.f, 1.f, 1.f);
		actorText("Thomas", 472.f, 307.f, 1.f, 1.f);
	}
}

void DialogueSystem::displayLevel5DrawingsAdvancedDialogue()
{
	std::string level5DrawingsHilma = "Är det dina teckningar? Det ser i alla fall ut som barnteckningar.";
	std::string level5DrawingsThomas = "Nej... jag har aldrig sett de här teckningarna förut...";
	std::string level5DrawingsHilma2 = "Hm... kan det vara din mormors?";

	if (mState >= 3)
	{
		mText.setString("");
		mActorText.setString("");
		mHasClicked = false;
		mLevel5Records = false;
		mAdvancedIsActive = false;
		mFinishedDialogue = true;
	}

	else if (mState == 0)
	{
		mAdvancedIsActive = true;
		advancedText(level5DrawingsHilma, 100.f, 420.f, 1.f, 1.f);
		drawFirstCharacter(mHandler, 300.f, 30.f, 1.f, 1.f, -0.2f, 0.2f, "expressionHilmaSurprised.png");
		drawSecondCharacter(mHandler, 700.f, 30.f, 1.f, 1.f, 0.2f, 0.2f, "expressionThomasThoughtful.png");
		createTextBox(-1.f, 280.f, 1.f, 1.f, 0.267f, 0.45f);
		actorText("Hilma", 480.f, 307.f, 1.f, 1.f);
	}

	else if (mState == 1)
	{
		advancedText(level5DrawingsThomas, 100.f, 420.f, 1.f, 1.f);
		drawSecondCharacter(mHandler, 700.f, 30.f, 1.f, 1.f, 0.2f, 0.2f, "expressionThomasSceptic.png");
		actorText("Thomas", 472.f, 307.f, 1.f, 1.f);
	}

	else if (mState == 2)
	{
		advancedText(level5DrawingsHilma2, 100.f, 420.f, 1.f, 1.f);
		drawFirstCharacter(mHandler, 300.f, 30.f, 1.f, 1.f, -0.2f, 0.2f, "expressionHilmaThoughtful.png");
		actorText("Hilma", 480.f, 307.f, 1.f, 1.f);
	}
}

//Dialogue functions down below
//Thomas' Room
void DialogueSystem::displayBooksDialogue()
{
	std::string booksHilma = "Hur många böcker  har du egentligen?";
	std::string booksThomas = "Senast jag räknade var det tjugofyra, men... det var ju ett tag sen...";

	if (mState == 2)
	{
		mText.setString("");
		mHasClicked = false;
		mBooks = false;
		mIsActive = false;
		mFinishedDialogue = true;
	}
	if (mState == 0)
	{
		mIsActive = true;
		if (mPlayer->isFacingLeft() == true)
		{
			text(booksHilma, mPlayer->getPosition(), -250, -200);
			createTalkBubble(mPlayer->getPosition(), -265, -210, 0.25f, 0.15f);
		}
		if (mPlayer->isFacingLeft() == false)
		{
			text(booksHilma, mPlayer->getPosition(), 60, -200);
			createTalkBubble(mPlayer->getPosition(), 45, -210, 0.25f, 0.15f);
		}
	}
	if (mState == 1)
	{
		if (mPlayer->isFacingLeft() == true)
		{
			text(booksThomas, mPlayer->getPosition(), 60, -250);
			createTalkBubble(mPlayer->getPosition(), 45, -290, 0.23f, 0.25f);
		}
		if (mPlayer->isFacingLeft() == false)
		{
			text(booksThomas, mPlayer->getPosition(), -250, -250);
			createTalkBubble(mPlayer->getPosition(), -265, -290, 0.23f, 0.25f);
		}
	}
}

void DialogueSystem::displayLampDialogue()
{
	std::string lampHilma = "Vad för oansvarig människa placerar en lampa vid sitt fönster? Jag flög nästan in i den!";
	std::string lampThomas = "Jag visste inte att det var farligt med lampor...";
	std::string lampHilma2 = "Ni människor är så vårdslösa.";
	std::string lampThomas2 = "Det var ju faktiskt du som krashade i mitt rum. Det tycker jag låter vårdslöst.";
	std::string lampHilma3 = "Hmpf.";

	if (mState == 5)
	{
		mText.setString("");
		mHasClicked = false;
		mLamp = false;
		mIsActive = false;
		mFinishedDialogue = true;
	}

	if (mState == 0)
	{
		mIsActive = true;
		if (mPlayer->isFacingLeft() == true)
		{
			text(lampHilma, mPlayer->getPosition(), -240, -220);
			createTalkBubble(mPlayer->getPosition(), -255, -275, 0.23f, 0.3f);
		}
		if (mPlayer->isFacingLeft() == false)
		{
			text(lampHilma, mPlayer->getPosition(), 60, -220);
			createTalkBubble(mPlayer->getPosition(), 45, -275, 0.23f, 0.3f);
		}
	}

	if (mState == 1)
	{
		if (mPlayer->isFacingLeft() == true)
		{
			text(lampThomas, mPlayer->getPosition(), 60, -250);
			createTalkBubble(mPlayer->getPosition(), 45, -275, 0.23f, 0.2f);
		}
		if (mPlayer->isFacingLeft() == false)
		{
			text(lampThomas, mPlayer->getPosition(), -250, -250);
			createTalkBubble(mPlayer->getPosition(), -265, -275, 0.23f, 0.2f);
		}
	}

	if (mState == 2)
	{
		if (mPlayer->isFacingLeft() == true)
		{
			text(lampHilma2, mPlayer->getPosition(), -230, -200);
			createTalkBubble(mPlayer->getPosition(), -245, -210, 0.23f, 0.15f);
		}
		if (mPlayer->isFacingLeft() == false)
		{
			text(lampHilma2, mPlayer->getPosition(), 60, -200);
			createTalkBubble(mPlayer->getPosition(), 45, -210, 0.23f, 0.15f);
		}
	}

	if (mState == 3)
	{
		if (mPlayer->isFacingLeft() == true)
		{
			text(lampThomas2, mPlayer->getPosition(), 60, -250);
			createTalkBubble(mPlayer->getPosition(), 45, -305, 0.23f, 0.3f);
		}
		if (mPlayer->isFacingLeft() == false)
		{
			text(lampThomas2, mPlayer->getPosition(), -250, -250);
			createTalkBubble(mPlayer->getPosition(), -265, -305, 0.23f, 0.3f);
		}
	}
	if (mState == 4)
	{
		if (mPlayer->isFacingLeft() == true)
		{
			text(lampHilma3, mPlayer->getPosition(), -110, -180);
			createTalkBubble(mPlayer->getPosition(), -120, -190, 0.085f, 0.1f);
		}
		if (mPlayer->isFacingLeft() == false)
		{
			text(lampHilma3, mPlayer->getPosition(), 60, -180);
			createTalkBubble(mPlayer->getPosition(), 50, -190, 0.085f, 0.1f);
		}
	}
}

void DialogueSystem::displayRubicCubeDialogue()
{
	std::string rubicHilma = "Vad är det här?";
	std::string rubicThomas = "En Rubiks kub, man ska få alla färger på varsin sida.";
	std::string rubicHilma2 = "Men vad är det för utmaning? Låter ju jättelätt!";

	if (mState == 3)
	{
		mText.setString("");
		mHasClicked = false;
		mRubicCube = false;
		mIsActive = false;
		mFinishedDialogue = true;
	}

	if (mState == 0)
	{
		mIsActive = true;
		if (mPlayer->isFacingLeft() == true)
		{
			text(rubicHilma, mPlayer->getPosition(), -200, -180);
			createTalkBubble(mPlayer->getPosition(), -210, -190, 0.185f, 0.1f);
		}
		if (mPlayer->isFacingLeft() == false)
		{
			text(rubicHilma, mPlayer->getPosition(), 60, -180);
			createTalkBubble(mPlayer->getPosition(), 50, -190, 0.185f, 0.1f);
		}
	}
	if (mState == 1)
	{
		if (mPlayer->isFacingLeft() == true)
		{
			text(rubicThomas, mPlayer->getPosition(), 60, -250);
			createTalkBubble(mPlayer->getPosition(), 45, -275, 0.24f, 0.2f);
		}
		if (mPlayer->isFacingLeft() == false)
		{
			text(rubicThomas, mPlayer->getPosition(), -250, -250);
			createTalkBubble(mPlayer->getPosition(), -265, -275, 0.24f, 0.2f);
		}
	}
	if (mState == 2)
	{
		if (mPlayer->isFacingLeft() == true)
		{
			text(rubicHilma2, mPlayer->getPosition(), -230, -200);
			createTalkBubble(mPlayer->getPosition(), -245, -225, 0.23f, 0.2f);
		}
		if (mPlayer->isFacingLeft() == false)
		{
			text(rubicHilma2, mPlayer->getPosition(), 60, -200);
			createTalkBubble(mPlayer->getPosition(), 45, -225, 0.23f, 0.2f);
		}
	}
}

void DialogueSystem::displayPosterDialogue()
{
	std::string posterHilma = "Varför är det bara rymdbilder?";
	std::string posterThomas = "Jag gillar rymden och planeter och sånt. Min mormor gav mig de flesta av dem.";

	if (mState == 2)
	{
		mText.setString("");
		mHasClicked = false;
		mPoster = false;
		mIsActive = false;
		mFinishedDialogue = true;
	}

	if (mState == 0)
	{
		mIsActive = true;
		if (mPlayer->isFacingLeft() == true)
		{
			text(posterHilma, mPlayer->getPosition(), -230, -200);
			createTalkBubble(mPlayer->getPosition(), -245, -210, 0.23f, 0.15f);
		}
		if (mPlayer->isFacingLeft() == false)
		{
			text(posterHilma, mPlayer->getPosition(), 60, -200);
			createTalkBubble(mPlayer->getPosition(), 45, -210, 0.23f, 0.15f);
		}
	}

	if (mState == 1)
	{
		if (mPlayer->isFacingLeft() == true)
		{
			text(posterThomas, mPlayer->getPosition(), 60, -250);
			createTalkBubble(mPlayer->getPosition(), 45, -305, 0.23f, 0.3f);
		}
		if (mPlayer->isFacingLeft() == false)
		{
			text(posterThomas, mPlayer->getPosition(), -250, -250);
			createTalkBubble(mPlayer->getPosition(), -265, -305, 0.23f, 0.3f);
		}
	}
}

void DialogueSystem::displayBackpackDialogue()
{
	std::string backpackHilma = "Vad är det för en massa papper i väskan?";
	std::string backpackThomas = "Läxor... de var roliga ett tag men sen fick jag bara fler och fler!";

	if (mState == 2)
	{
		mText.setString("");
		mHasClicked = false;
		mBackpack = false;
		mIsActive = false;
		mFinishedDialogue = true;
	}

	if (mState == 0)
	{
		mIsActive = true;
		if (mPlayer->isFacingLeft() == true)
		{
			text(backpackHilma, mPlayer->getPosition(), -230, -200);
			createTalkBubble(mPlayer->getPosition(), -245, -225, 0.22f, 0.2f);
		}
		if (mPlayer->isFacingLeft() == false)
		{
			text(backpackHilma, mPlayer->getPosition(), 60, -200);
			createTalkBubble(mPlayer->getPosition(), 45, -225, 0.22f, 0.2f);
		}
	}

	if (mState == 1)
	{
		if (mPlayer->isFacingLeft() == true)
		{
			text(backpackThomas, mPlayer->getPosition(), 60, -250);
			createTalkBubble(mPlayer->getPosition(), 45, -290, 0.23f, 0.25f);
		}
		if (mPlayer->isFacingLeft() == false)
		{
			text(backpackThomas, mPlayer->getPosition(), -250, -250);
			createTalkBubble(mPlayer->getPosition(), -265, -290, 0.23f, 0.25f);
		}
	}
}

void DialogueSystem::displayBowlDialogue()
{
	std::string bowlHilma = "Använde du den här när du klippte dig eller?";
	std::string bowlThomas = "Vad menar du?";
	std::string bowlHilma2 = "Äh, glöm det...";

	if (mState == 3)
	{
		mText.setString("");
		mHasClicked = false;
		mBowl = false;
		mIsActive = false;
		mFinishedDialogue = true;
	}

	if (mState == 0)
	{
		mIsActive = true;
		if (mPlayer->isFacingLeft() == true)
		{
			text(bowlHilma, mPlayer->getPosition(), -230, -200);
			createTalkBubble(mPlayer->getPosition(), -245, -225, 0.24f, 0.2f);
		}
		if (mPlayer->isFacingLeft() == false)
		{
			text(bowlHilma, mPlayer->getPosition(), 60, -200);
			createTalkBubble(mPlayer->getPosition(), 45, -225, 0.24f, 0.2f);
		}
	}

	if (mState == 1)
	{
		if (mPlayer->isFacingLeft() == true)
		{
			text(bowlThomas, mPlayer->getPosition(), 60, -220);
			createTalkBubble(mPlayer->getPosition(), 50, -230, 0.18f, 0.1f);
		}
		if (mPlayer->isFacingLeft() == false)
		{
			text(bowlThomas, mPlayer->getPosition(), -200, -220);
			createTalkBubble(mPlayer->getPosition(), -210, -230, 0.18f, 0.1f);
		}
	}

	if (mState == 2)
	{
		if (mPlayer->isFacingLeft() == true)
		{
			text(bowlHilma2, mPlayer->getPosition(), -190, -180);
			createTalkBubble(mPlayer->getPosition(), -200, -190, 0.17f, 0.1f);
		}
		if (mPlayer->isFacingLeft() == false)
		{
			text(bowlHilma2, mPlayer->getPosition(), 60, -180);
			createTalkBubble(mPlayer->getPosition(), 50, -190, 0.17f, 0.1f);
		}
	}
}

void DialogueSystem::displayRadioDialogue()
{
	std::string radioHilma = "En radio! De brukar vara fulla av användbara delar!";
	std::string radioThomas = "Snälla förstör inte min radio.";
	std::string radioHilma2 = "Okej då...";

	if (mState == 3)
	{
		mText.setString("");
		mHasClicked = false;
		mRadio = false;
		mIsActive = false;
		mFinishedDialogue = true;
	}

	if (mState == 0)
	{
		mIsActive = true;
		if (mPlayer->isFacingLeft() == true)
		{
			text(radioHilma, mPlayer->getPosition(), -230, -200);
			createTalkBubble(mPlayer->getPosition(), -245, -225, 0.24f, 0.2f);
		}
		if (mPlayer->isFacingLeft() == false)
		{
			text(radioHilma, mPlayer->getPosition(), 60, -200);
			createTalkBubble(mPlayer->getPosition(), 45, -225, 0.24f, 0.2f);
		}
	}

	if (mState == 1)
	{
		if (mPlayer->isFacingLeft() == true)
		{
			text(radioThomas, mPlayer->getPosition(), 60, -250);
			createTalkBubble(mPlayer->getPosition(), 45, -260, 0.23f, 0.15f);
		}
		if (mPlayer->isFacingLeft() == false)
		{
			text(radioThomas, mPlayer->getPosition(), -250, -250);
			createTalkBubble(mPlayer->getPosition(), -265, -260, 0.23f, 0.15f);
		}
	}

	if (mState == 2)
	{
		if (mPlayer->isFacingLeft() == true)
		{
			text(radioHilma2, mPlayer->getPosition(), -140, -180);
			createTalkBubble(mPlayer->getPosition(), -150, -190, 0.12f, 0.1f);
		}
		if (mPlayer->isFacingLeft() == false)
		{
			text(radioHilma2, mPlayer->getPosition(), 60, -180);
			createTalkBubble(mPlayer->getPosition(), 50, -190, 0.12f, 0.1f);
		}
	}
}

void DialogueSystem::displayMatDialogue()
{
	std::string matHilma = "Magneten dras mot knölen i mattan.";

	if (mState == 1)
	{
		mText.setString("");
		mHasClicked = false;
		mMat = false;
		mIsActive = false;
		mFinishedDialogue = true;
	}

	if (mState == 0)
	{
		mIsActive = true;
		if (mPlayer->isFacingLeft() == true)
		{
			text(matHilma, mPlayer->getPosition(), -230, -200);
			createTalkBubble(mPlayer->getPosition(), -245, -210, 0.24f, 0.15f);
		}
		if (mPlayer->isFacingLeft() == false)
		{
			text(matHilma, mPlayer->getPosition(), 60, -200);
			createTalkBubble(mPlayer->getPosition(), 45, -210, 0.24f, 0.15f);
		}
	}
}

void DialogueSystem::displayStarDialogue()
{
	std::string starHilma = "Den här stjärnan  ser inte ut som de andra, tror du..?";

	if (mState == 1)
	{
		mText.setString("");
		mHasClicked = false;
		mStar = false;
		mIsActive = false;
		mFinishedDialogue = true;
	}

	if (mState == 0)
	{
		mIsActive = true;
		if (mPlayer->isFacingLeft() == true)
		{
			text(starHilma, mPlayer->getPosition(), -240, -200);
			createTalkBubble(mPlayer->getPosition(), -255, -225, 0.23f, 0.2f);
		}
		if (mPlayer->isFacingLeft() == false)
		{
			text(starHilma, mPlayer->getPosition(), 60, -200);
			createTalkBubble(mPlayer->getPosition(), 45, -225, 0.23f, 0.2f);
		}
	}
}

void DialogueSystem::displayAquariumDialogue()
{
	std::string aquariumHilma = "Varför har du en fisk inne på rummet? Dem ska ju vara i sjöar!";
	std::string aquariumThomas = "Men det är mitt husdjur, han heter Roger.";
	std::string aquariumHilma2 = "Kan Roger ha ätit upp astronauten?";
	std::string aquariumThomas2 = "Nä, inte Roger, han är snäll.";

	if (mState == 4)
	{
		mText.setString("");
		mHasClicked = false;
		mAquarium = false;
		mIsActive = false;
		mFinishedDialogue = true;
	}

	if (mState == 0)
	{
		mIsActive = true;
		if (mPlayer->isFacingLeft() == true)
		{
			text(aquariumHilma, mPlayer->getPosition(), -250, -220);
			createTalkBubble(mPlayer->getPosition(), -265, -260, 0.25f, 0.25f);
		}
		if (mPlayer->isFacingLeft() == false)
		{
			text(aquariumHilma, mPlayer->getPosition(), 60, -220);
			createTalkBubble(mPlayer->getPosition(), 45, -260, 0.25f, 0.25f);
		}
	}

	if (mState == 1)
	{
		if (mPlayer->isFacingLeft() == true)
		{
			text(aquariumThomas, mPlayer->getPosition(), 60, -250);
			createTalkBubble(mPlayer->getPosition(), 45, -275, 0.23f, 0.2f);
		}
		if (mPlayer->isFacingLeft() == false)
		{
			text(aquariumThomas, mPlayer->getPosition(), -250, -250);
			createTalkBubble(mPlayer->getPosition(), -265, -275, 0.23f, 0.2f);
		}
	}

	if (mState == 2)
	{
		if (mPlayer->isFacingLeft() == true)
		{
			text(aquariumHilma2, mPlayer->getPosition(), -230, -200);
			createTalkBubble(mPlayer->getPosition(), -245, -210, 0.23f, 0.15f);
		}
		if (mPlayer->isFacingLeft() == false)
		{
			text(aquariumHilma2, mPlayer->getPosition(), 60, -200);
			createTalkBubble(mPlayer->getPosition(), 45, -210, 0.23f, 0.15f);
		}
	}

	if (mState == 3)
	{
		if (mPlayer->isFacingLeft() == true)
		{
			text(aquariumThomas2, mPlayer->getPosition(), 60, -250);
			createTalkBubble(mPlayer->getPosition(), 45, -260, 0.24f, 0.15f);
		}
		if (mPlayer->isFacingLeft() == false)
		{
			text(aquariumThomas2, mPlayer->getPosition(), -250, -250);
			createTalkBubble(mPlayer->getPosition(), -265, -260, 0.24f, 0.15f);
		}
	}
}

void DialogueSystem::displayBlockDialogue()
{
	std::string blockHilma = "En helt omärkvärdig kloss.";

	if (mState == 1)
	{
		mText.setString("");
		mHasClicked = false;
		mBlock = false;
		mIsActive = false;
		mFinishedDialogue = true;
	}

	if (mState == 0)
	{
		mIsActive = true;
		if (mPlayer->isFacingLeft() == true)
		{
			text(blockHilma, mPlayer->getPosition(), -250, -200);
			createTalkBubble(mPlayer->getPosition(), -265, -210, 0.25f, 0.15f);
		}
		if (mPlayer->isFacingLeft() == false)
		{
			text(blockHilma, mPlayer->getPosition(), 60, -200);
			createTalkBubble(mPlayer->getPosition(), 45, -210, 0.25f, 0.15f);
		}
	}
}

void DialogueSystem::displayAstronautDialogue()
{
	std::string astronautHilma = "Där är astronauten! Titta Thomas! Jag hittade den!";
	std::string astronautThomas = "Ja... men den är ju i akvariet. Jag vill ha den i handen!";
	std::string astronautHilma2 = "Okej då, jag får väl hitta ett sätt att fiska upp den.";

	if (mState == 3)
	{
		mText.setString("");
		mHasClicked = false;
		mAstronaut = false;
		mIsActive = false;
		mFinishedDialogue = true;
	}

	if (mState == 0)
	{
		mIsActive = true;
		if (mPlayer->isFacingLeft() == true)
		{
			text(astronautHilma, mPlayer->getPosition(), -250, -200);
			createTalkBubble(mPlayer->getPosition(), -265, -225, 0.25f, 0.2f);
		}
		if (mPlayer->isFacingLeft() == false)
		{
			text(astronautHilma, mPlayer->getPosition(), 60, -200);
			createTalkBubble(mPlayer->getPosition(), 45, -225, 0.25f, 0.2f);
		}
	}

	if (mState == 1)
	{
		if (mPlayer->isFacingLeft() == true)
		{
			text(astronautThomas, mPlayer->getPosition(), 60, -250);
			createTalkBubble(mPlayer->getPosition(), 45, -290, 0.23f, 0.25f);
		}
		if (mPlayer->isFacingLeft() == false)
		{
			text(astronautThomas, mPlayer->getPosition(), -250, -250);
			createTalkBubble(mPlayer->getPosition(), -265, -290, 0.23f, 0.25f);
		}
	}

	if (mState == 2)
	{
		if (mPlayer->isFacingLeft() == true)
		{
			text(astronautHilma2, mPlayer->getPosition(), -250, -200);
			createTalkBubble(mPlayer->getPosition(), -265, -225, 0.24f, 0.2f);
		}
		if (mPlayer->isFacingLeft() == false)
		{
			text(astronautHilma2, mPlayer->getPosition(), 60, -200);
			createTalkBubble(mPlayer->getPosition(), 45, -225, 0.24f, 0.2f);
		}
	}
}

void DialogueSystem::displayMagnetDialogue()
{
	std::string magnetHilma = "En magnet... hmm den kan vara användbar.";

	if (mState == 1)
	{
		mText.setString("");
		mHasClicked = false;
		mMagnet = false;
		mIsActive = false;
		mFinishedDialogue = true;
	}

	if (mState == 0)
	{
		mIsActive = true;
		if (mPlayer->isFacingLeft() == true)
		{
			text(magnetHilma, mPlayer->getPosition(), -270, -200);
			createTalkBubble(mPlayer->getPosition(), -285, -210, 0.27f, 0.15f);
		}
		if (mPlayer->isFacingLeft() == false)
		{
			text(magnetHilma, mPlayer->getPosition(), 60, -200);
			createTalkBubble(mPlayer->getPosition(), 45, -210, 0.27f, 0.15f);
		}
	}
}

void DialogueSystem::displayStringDialogue()
{
	std::string stringHilma = "Ett fiskespö.";

	if (mState == 1)
	{
		mText.setString("");
		mHasClicked = false;
		mString = false;
		mIsActive = false;
		mFinishedDialogue = true;
	}

	if (mState == 0)
	{
		mIsActive = true;
		if (mPlayer->isFacingLeft() == true)
		{
			text(stringHilma, mPlayer->getPosition(), -170, -180);
			createTalkBubble(mPlayer->getPosition(), -180, -190, 0.16f, 0.1f);
		}
		if (mPlayer->isFacingLeft() == false)
		{
			text(stringHilma, mPlayer->getPosition(), 60, -180);
			createTalkBubble(mPlayer->getPosition(), 50, -190, 0.16f, 0.1f);
		}
	}
}

//Grandma's Livingroom
void DialogueSystem::displayBooks2Dialogue()
{
	std::string books2Thomas = "Rymdböcker... precis som mina där hemma.";

	if (mState == 1)
	{
		mText.setString("");
		mHasClicked = false;
		mBooks2 = false;
		mIsActive = false;
		mFinishedDialogue = true;
	}

	if (mState == 0)
	{
		mIsActive = true;
		text(books2Thomas, mPlayer->getPosition(), 60, -250);
		createTalkBubble(mPlayer->getPosition(), 45, -260, 0.23f, 0.15f);
	}
}

void DialogueSystem::displayJewelryCaseDialogue()
{
	std::string jewelryCaseThomas = "Ett smyckesskrin.";
	std::string jewelryCaseHilma = "Vi öppnar och kollar vad som finns i den!";
	std::string jewelryCaseHilma2 = "Den är bara full av muttrar!";

	if (mState == 3)
	{
		mText.setString("");
		mHasClicked = false;
		mJewelryCase = false;
		mIsActive = false;
		mFinishedDialogue = true;
	}

	if (mState == 0)
	{
		mIsActive = true;
		text(jewelryCaseThomas, mPlayer->getPosition(), 60, -250);
		createTalkBubble(mPlayer->getPosition(), 60, -250, 2.5f, 1.f);
	}

	if (mState == 1)
	{
		text(jewelryCaseHilma, mPlayer->getPosition(), -180, -180);
		createTalkBubble(mPlayer->getPosition(), -180, -200, 2.1f, 1.f);
	}

	if (mState == 2)
	{
		text(jewelryCaseHilma2, mPlayer->getPosition(), -180, -180);
		createTalkBubble(mPlayer->getPosition(), -180, -200, 2.1f, 1.f);
	}
}

void DialogueSystem::displayMaskDialogue()
{
	std::string maskHilma = "Vilka lustiga masker! Var kommer de ifrån?";
	std::string maskThomas = "Någonstans i Afrika tror jag. Mormor reste mycket när hon var ung.";

	if (mState == 2)
	{
		mText.setString("");
		mHasClicked = false;
		mMask = false;
		mIsActive = false;
		mFinishedDialogue = true;
	}

	if (mState == 0)
	{
		mIsActive = true;
		text(maskHilma, mPlayer->getPosition(), -180, -180);
		createTalkBubble(mPlayer->getPosition(), -180, -200, 2.1f, 1.f);
	}

	if (mState == 1)
	{
		text(maskThomas, mPlayer->getPosition(), 60, -250);
		createTalkBubble(mPlayer->getPosition(), 60, -250, 2.5f, 1.f);
	}
}

void DialogueSystem::displayTextileCartDialogue()
{
	std::string textileCartHilma = "Garnnystan och nålar. Kan vara användbart!";

	if (mState == 1)
	{
		mText.setString("");
		mHasClicked = false;
		mTextileCart = false;
		mIsActive = false;
		mFinishedDialogue = true;
	}

	if (mState == 0)
	{
		mIsActive = true;
		text(textileCartHilma, mPlayer->getPosition(), -180, -180);
		createTalkBubble(mPlayer->getPosition(), -180, -200, 2.1f, 1.f);
	}
}

void DialogueSystem::displayEarthGlobeDialogue()
{
	std::string earthGlobeThomas = "En jordglob. Jag har alltid velat ha en sån…";
	std::string earthGlobeHilma = "Vet du vad Thomas, vi kanske kan ha användning för den…";

	if (mState == 2)
	{
		mText.setString("");
		mHasClicked = false;
		mEarthGlobe = false;
		mIsActive = false;
		mFinishedDialogue = true;
	}

	if (mState == 0)
	{
		mIsActive = true;
		text(earthGlobeThomas, mPlayer->getPosition(), 60, -250);
		createTalkBubble(mPlayer->getPosition(), 60, -250, 2.5f, 1.f);
	}

	if (mState == 1)
	{
		text(earthGlobeHilma, mPlayer->getPosition(), -180, -180);
		createTalkBubble(mPlayer->getPosition(), -180, -200, 2.1f, 1.f);
	}
}

void DialogueSystem::displayGramophoneDialogue()
{
	std::string gramophoneHilma = "Vad är det här för något?";
	std::string gramophoneThomas = "Jag vet inte riktigt, men jag har sett sånna på TV. Folk brukade spela musik med dem här. Men det verkar som nålen till den saknas.";

	if (mState == 2)
	{
		mText.setString("");
		mHasClicked = false;
		mGramophone = false;
		mIsActive = false;
		mFinishedDialogue = true;
	}

	if (mState == 0)
	{
		mIsActive = true;
		text(gramophoneHilma, mPlayer->getPosition(), -180, -180);
		createTalkBubble(mPlayer->getPosition(), -180, -200, 2.1f, 1.f);
	}

	if (mState == 1)
	{
		text(gramophoneThomas, mPlayer->getPosition(), 60, -250);
		createTalkBubble(mPlayer->getPosition(), 60, -250, 2.5f, 1.f);
	}
}

void DialogueSystem::displayFishTrophyDialogue()
{
	std::string fishTrophyHilma = "En fisk! Vad är det med din familj och att ha fiskar inomhus egentligen?";

	if (mState == 1)
	{
		mText.setString("");
		mHasClicked = false;
		mFishTrophy = false;
		mIsActive = false;
		mFinishedDialogue = true;
	}

	if (mState == 0)
	{
		mIsActive = true;
		text(fishTrophyHilma, mPlayer->getPosition(), -180, -180);
		createTalkBubble(mPlayer->getPosition(), -180, -200, 2.1f, 1.f);
	}
}

void DialogueSystem::displayPlantDialogue()
{
	std::string plantHilma = "Någon måste ta hand om den här plantan, säkert din mormor";

	if (mState == 1)
	{
		mText.setString("");
		mHasClicked = false;
		mPlant = false;
		mIsActive = false;
		mFinishedDialogue = true;
	}

	if (mState == 0)
	{
		mIsActive = true;
		text(plantHilma, mPlayer->getPosition(), -180, -180);
		createTalkBubble(mPlayer->getPosition(), -180, -200, 2.1f, 1.f);
	}
}

void DialogueSystem::displayArmchairDialogue()
{
	std::string armchairHilma = "En radio! De brukar vara fulla av användbara delar!";

	if (mState == 1)
	{
		mText.setString("");
		mHasClicked = false;
		mArmchair = false;
		mIsActive = false;
		mFinishedDialogue = true;
	}

	if (mState == 0)
	{
		mIsActive = true;
		text(armchairHilma, mPlayer->getPosition(), -180, -180);
		createTalkBubble(mPlayer->getPosition(), -180, -200, 2.1f, 1.f);
	}
}

void DialogueSystem::displayGlassesAndNutsDialogue()
{
	std::string glassesAndNutsHilma = "Det ser ut som att någon suttit här och läst.";
	std::string glassesAndNutsThomas = "Det måste vara mormor, hon använde alltid läsglasögon.";

	if (mState == 2)
	{
		mText.setString("");
		mHasClicked = false;
		mGlassesAndNuts = false;
		mIsActive = false;
		mFinishedDialogue = true;
	}

	if (mState == 0)
	{
		mIsActive = true;
		text(glassesAndNutsHilma, mPlayer->getPosition(), -180, -180);
		createTalkBubble(mPlayer->getPosition(), -180, -200, 2.1f, 1.f);
	}

	if (mState == 1)
	{
		text(glassesAndNutsThomas, mPlayer->getPosition(), 60, -250);
		createTalkBubble(mPlayer->getPosition(), 60, -250, 2.5f, 1.f);
	}
}

//Grandma's Kitchen
void DialogueSystem::displayRefridgeratorDialogue()
{
	std::string refridgeratorThomas = "Ett gammalt kylskåp.";

	if (mState == 1)
	{
		mText.setString("");
		mHasClicked = false;
		mRefridgerator = false;
		mIsActive = false;
		mFinishedDialogue = true;
	}

	if (mState == 0)
	{
		mIsActive = true;
		text(refridgeratorThomas, mPlayer->getPosition(), 60, -250);
		createTalkBubble(mPlayer->getPosition(), 60, -250, 2.5f, 1.f);
	}
}

void DialogueSystem::displayCatDialogue()
{
	std::string catHilma = "Åh nej! En katt! Jag hatar katter! Kom, vi går härifrån!";
	std::string catThomas = "Vänta Hilma, hör du inte det där?";
	std::string catHilma2 = "Vadå?";
	std::string catThomas2 = "Det låter som något litet som ropar på hjälp!";

	if (mState == 4)
	{
		mText.setString("");
		mHasClicked = false;
		mCat = false;
		mIsActive = false;
		mFinishedDialogue = true;
	}

	if (mState == 0)
	{
		mIsActive = true;
		text(catHilma, mPlayer->getPosition(), -180, -180);
		createTalkBubble(mPlayer->getPosition(), -180, -200, 2.1f, 1.f);
	}

	if (mState == 1)
	{
		text(catThomas, mPlayer->getPosition(), 60, -250);
		createTalkBubble(mPlayer->getPosition(), 60, -250, 2.5f, 1.f);
	}

	if (mState == 2)
	{
		text(catHilma2, mPlayer->getPosition(), -180, -180);
		createTalkBubble(mPlayer->getPosition(), -180, -200, 2.1f, 1.f);
	}

	if (mState == 3)
	{
		text(catThomas2, mPlayer->getPosition(), 60, -250);
		createTalkBubble(mPlayer->getPosition(), 60, -250, 2.5f, 1.f);
	}
}

void DialogueSystem::displayCatFoodBowlDialogue()
{
	std::string catFoodBowlThomas = "Måste vara kattens matskål. Och den är tom. Katten kanske är hungrig?";

	if (mState == 1)
	{
		mText.setString("");
		mHasClicked = false;
		mCatFoodBowl = false;
		mIsActive = false;
		mFinishedDialogue = true;
	}

	if (mState == 0)
	{
		mIsActive = true;
		text(catFoodBowlThomas, mPlayer->getPosition(), 60, -250);
		createTalkBubble(mPlayer->getPosition(), 60, -250, 2.5f, 1.f);
	}
}

void DialogueSystem::displayMouseDwellingDialogue()
{
	std::string mouseDwellingHilma = "Ett mushål. Och någon ropar på hjälp innifrån!";

	if (mState == 1)
	{
		mText.setString("");
		mHasClicked = false;
		mMouseDwelling = false;
		mIsActive = false;
		mFinishedDialogue = true;
	}

	if (mState == 0)
	{
		mIsActive = true;
		text(mouseDwellingHilma, mPlayer->getPosition(), -180, -180);
		createTalkBubble(mPlayer->getPosition(), -180, -200, 2.1f, 1.f);
	}
}

void DialogueSystem::displayWaterTapDialogue()
{
	std::string waterTapThomas = "Hmm den här vattenkranen funkar inte.";
	std::string waterTapHilma = "Med våra redskap ska vi nog kunna fixa den!";

	if (mState == 2)
	{
		mText.setString("");
		mHasClicked = false;
		mWaterTap = false;
		mIsActive = false;
		mFinishedDialogue = true;
	}

	if (mState == 0)
	{
		mIsActive = true;
		text(waterTapThomas, mPlayer->getPosition(), 60, -250);
		createTalkBubble(mPlayer->getPosition(), 60, -250, 2.5f, 1.f);
	}

	if (mState == 1)
	{
		text(waterTapHilma, mPlayer->getPosition(), -180, -180);
		createTalkBubble(mPlayer->getPosition(), -180, -200, 2.1f, 1.f);
	}
}

void DialogueSystem::displayFruitBowlDialogue()
{
	std::string fruitBowlThomas = "Den här frukten är ju fortfarande färsk! Mormor måste ha varit här!";

	if (mState == 1)
	{
		mText.setString("");
		mHasClicked = false;
		mFruitBowl = false;
		mIsActive = false;
		mFinishedDialogue = true;
	}

	if (mState == 0)
	{
		mIsActive = true;
		text(fruitBowlThomas, mPlayer->getPosition(), 60, -250);
		createTalkBubble(mPlayer->getPosition(), 60, -250, 2.5f, 1.f);
	}
}

void DialogueSystem::displayFlowersDialogue()
{
	std::string flowersThomas = "Blommorna är fräscha, mormor måste ta hand om dem.";

	if (mState == 1)
	{
		mText.setString("");
		mHasClicked = false;
		mFlowers = false;
		mIsActive = false;
		mFinishedDialogue = true;
	}

	if (mState == 0)
	{
		mIsActive = true;
		text(flowersThomas, mPlayer->getPosition(), 60, -250);
		createTalkBubble(mPlayer->getPosition(), 60, -250, 2.5f, 1.f);
	}
}

void DialogueSystem::displayRocketDrawingsDialogue()
{
	std::string rocketDrawingsThomas = "Dem här liknar ritningarna på raketen jag och mormor byggde, men dem här ser jättekomplicerade ut!";

	if (mState == 1)
	{
		mText.setString("");
		mHasClicked = false;
		mRocketDrawings = false;
		mIsActive = false;
		mFinishedDialogue = true;
	}

	if (mState == 0)
	{
		mIsActive = true;
		text(rocketDrawingsThomas, mPlayer->getPosition(), 60, -250);
		createTalkBubble(mPlayer->getPosition(), 60, -250, 2.5f, 1.f);
	}
}

void DialogueSystem::displayToolsDialogue()
{
	std::string toolsThomas = "Det här är ju mormors verkstyg. Vad har hon byggt här?";

	if (mState == 1)
	{
		mText.setString("");
		mHasClicked = false;
		mTools = false;
		mIsActive = false;
		mFinishedDialogue = true;
	}

	if (mState == 0)
	{
		mIsActive = true;
		text(toolsThomas, mPlayer->getPosition(), 60, -250);
		createTalkBubble(mPlayer->getPosition(), 60, -250, 2.5f, 1.f);
	}
}

//Grandma's Room
void DialogueSystem::displayPlanetsDialogue()
{
	std::string planetsThomas = "Wow… alla solsystemets planeter! Men… vissa av dem saknas!";

	if (mState == 1)
	{
		mText.setString("");
		mHasClicked = false;
		mPlanets = false;
		mIsActive = false;
		mFinishedDialogue = true;
	}

	if (mState == 0)
	{
		mIsActive = true;
		text(planetsThomas, mPlayer->getPosition(), 60, -250);
		createTalkBubble(mPlayer->getPosition(), 60, -250, 2.5f, 1.f);
	}
}

void DialogueSystem::displayMercuryDialogue()
{
	std::string mercuryThomas = "Merkurius, planeten närmast solen.";

	if (mState == 1)
	{
		mText.setString("");
		mHasClicked = false;
		mMercury = false;
		mIsActive = false;
		mFinishedDialogue = true;
	}

	if (mState == 0)
	{
		mIsActive = true;
		text(mercuryThomas, mPlayer->getPosition(), 60, -250);
		createTalkBubble(mPlayer->getPosition(), 60, -250, 2.5f, 1.f);
	}
}

void DialogueSystem::displayVenusDialogue()
{
	std::string venusThomas = "Venus liknar mycket jorden men har en jättegiftig atmosfär.";

	if (mState == 1)
	{
		mText.setString("");
		mHasClicked = false;
		mVenus = false;
		mIsActive = false;
		mFinishedDialogue = true;
	}

	if (mState == 0)
	{
		mIsActive = true;
		text(venusThomas, mPlayer->getPosition(), 60, -250);
		createTalkBubble(mPlayer->getPosition(), 60, -250, 2.5f, 1.f);
	}
}

void DialogueSystem::displayEmptyEarthDialogue()
{
	std::string emptyEarthThomas = "Men! jorden ska ju vara här!";

	if (mState == 1)
	{
		mText.setString("");
		mHasClicked = false;
		mEmptyEarth = false;
		mIsActive = false;
		mFinishedDialogue = true;
	}

	if (mState == 0)
	{
		mIsActive = true;
		text(emptyEarthThomas, mPlayer->getPosition(), 60, -250);
		createTalkBubble(mPlayer->getPosition(), 60, -250, 2.5f, 1.f);
	}
}

void DialogueSystem::displayEmptyMarsDialogue()
{
	std::string emptyMarsThomas = "Mars saknas också.";

	if (mState == 1)
	{
		mText.setString("");
		mHasClicked = false;
		mEmptyMars = false;
		mIsActive = false;
		mFinishedDialogue = true;
	}

	if (mState == 0)
	{
		mIsActive = true;
		text(emptyMarsThomas, mPlayer->getPosition(), 60, -250);
		createTalkBubble(mPlayer->getPosition(), 60, -250, 2.5f, 1.f);
	}
}

void DialogueSystem::displayJupiterDialogue()
{
	std::string jupiterThomas = "Jupiter är den största planeten i vårt solsystem men ändå bara en tusendel av solens storlek!";

	if (mState == 1)
	{
		mText.setString("");
		mHasClicked = false;
		mJupiter = false;
		mIsActive = false;
		mFinishedDialogue = true;
	}

	if (mState == 0)
	{
		mIsActive = true;
		text(jupiterThomas, mPlayer->getPosition(), 60, -250);
		createTalkBubble(mPlayer->getPosition(), 60, -250, 2.5f, 1.f);
	}
}

void DialogueSystem::displayEmptySaturnDialogue()
{
	std::string emptySaturnThomas = "Här ska ju Saturnus, planeten med ringar, vara!";

	if (mState == 1)
	{
		mText.setString("");
		mHasClicked = false;
		mEmptySaturn = false;
		mIsActive = false;
		mFinishedDialogue = true;
	}

	if (mState == 0)
	{
		mIsActive = true;
		text(emptySaturnThomas, mPlayer->getPosition(), 60, -250);
		createTalkBubble(mPlayer->getPosition(), 60, -250, 2.5f, 1.f);
	}
}

void DialogueSystem::displayUranusDialogue()
{
	std::string uranusThomas = "Uranus är en isplanet och den kallaste i vårt solsystem.";

	if (mState == 1)
	{
		mText.setString("");
		mHasClicked = false;
		mUranus = false;
		mIsActive = false;
		mFinishedDialogue = true;
	}

	if (mState == 0)
	{
		mIsActive = true;
		text(uranusThomas, mPlayer->getPosition(), 60, -250);
		createTalkBubble(mPlayer->getPosition(), 60, -250, 2.5f, 1.f);
	}
}

void DialogueSystem::displayNeptuneDialogue()
{
	std::string neptuneThomas = "Neptunus, en blå isplanet med starka vindar.";

	if (mState == 1)
	{
		mText.setString("");
		mHasClicked = false;
		mNeptune = false;
		mIsActive = false;
		mFinishedDialogue = true;
	}

	if (mState == 0)
	{
		mIsActive = true;
		text(neptuneThomas, mPlayer->getPosition(), 60, -250);
		createTalkBubble(mPlayer->getPosition(), 60, -250, 2.5f, 1.f);
	}
}

void DialogueSystem::displayEmptyPlutoDialogue()
{
	std::string emptyPlutoThomas = "Pluto, dvärgplaneten, är borta!";

	if (mState == 1)
	{
		mText.setString("");
		mHasClicked = false;
		mEmptyPluto = false;
		mIsActive = false;
		mFinishedDialogue = true;
	}

	if (mState == 0)
	{
		mIsActive = true;
		text(emptyPlutoThomas, mPlayer->getPosition(), 60, -250);
		createTalkBubble(mPlayer->getPosition(), 60, -250, 2.5f, 1.f);
	}
}

void DialogueSystem::displayMarsDialogue()
{
	std::string marsThomas = "Den här frukten liknar Mars, och den är ungefär lika stor!";

	if (mState == 1)
	{
		mText.setString("");
		mHasClicked = false;
		mMars = false;
		mIsActive = false;
		mFinishedDialogue = true;
	}

	if (mState == 0)
	{
		mIsActive = true;
		text(marsThomas, mPlayer->getPosition(), 60, -250);
		createTalkBubble(mPlayer->getPosition(), 60, -250, 2.5f, 1.f);
	}
}

void DialogueSystem::displayEarthDialogue()
{
	std::string earthHilma = "En jordglob fungerar lika bra som den riktiga!";

	if (mState == 1)
	{
		mText.setString("");
		mHasClicked = false;
		mEarth = false;
		mIsActive = false;
		mFinishedDialogue = true;
	}

	if (mState == 0)
	{
		mIsActive = true;
		text(earthHilma, mPlayer->getPosition(), 60, -250);
		createTalkBubble(mPlayer->getPosition(), -180, -200, 2.1f, 1.f);
	}
}

void DialogueSystem::displaySaturnDialogue()
{
	std::string saturnThomas = "Saturnus! Komplett med ringarna!";

	if (mState == 1)
	{
		mText.setString("");
		mHasClicked = false;
		mSaturn = false;
		mIsActive = false;
		mFinishedDialogue = true;
	}

	if (mState == 0)
	{
		mIsActive = true;
		text(saturnThomas, mPlayer->getPosition(), 60, -250);
		createTalkBubble(mPlayer->getPosition(), 60, -250, 2.5f, 1.f);
	}
}

void DialogueSystem::displayPlutoDialogue()
{
	std::string plutoThomas = "Den här pärlan är liten och grå, likt Pluto.";

	if (mState == 1)
	{
		mText.setString("");
		mHasClicked = false;
		mPluto = false;
		mIsActive = false;
		mFinishedDialogue = true;
	}

	if (mState == 0)
	{
		mIsActive = true;
		text(plutoThomas, mPlayer->getPosition(), 60, -250);
		createTalkBubble(mPlayer->getPosition(), 60, -250, 2.5f, 1.f);
	}
}

void DialogueSystem::displaySwordsDialogue()
{
	std::string swordsHilma = "Vilka häftiga svärd!";

	if (mState == 1)
	{
		mText.setString("");
		mHasClicked = false;
		mSwords = false;
		mIsActive = false;
		mFinishedDialogue = true;
	}

	if (mState == 0)
	{
		mIsActive = true;
		text(swordsHilma, mPlayer->getPosition(), 60, -250);
		createTalkBubble(mPlayer->getPosition(), -180, -200, 2.1f, 1.f);
	}
}

void DialogueSystem::displayDrawingsDialogue()
{
	std::string drawingsHilma = "Dem här ritningarna ser jättekomplicerade ut.";
	std::string drawingsThomas = "Dem är ritningar på en raket. Fast den här är större än den jag och mormor byggde!";

	if (mState == 2)
	{
		mText.setString("");
		mHasClicked = false;
		mDrawings = false;
		mIsActive = false;
		mFinishedDialogue = true;
	}

	if (mState == 0)
	{
		mIsActive = true;
		text(drawingsHilma, mPlayer->getPosition(), -180, -180);
		createTalkBubble(mPlayer->getPosition(), -180, -200, 2.1f, 1.f);
	}

	if (mState == 1)
	{
		text(drawingsThomas, mPlayer->getPosition(), 60, -250);
		createTalkBubble(mPlayer->getPosition(), 60, -250, 2.5f, 1.f);
	}
}

void DialogueSystem::displayBalconyDoorDialogue()
{
	std::string balconyDoorHilma = "Näpp! Där kommer vi inte igenom! Vi måste få upp den på något sätt…";

	if (mState == 1)
	{
		mText.setString("");
		mHasClicked = false;
		mBalconyDoor = false;
		mIsActive = false;
		mFinishedDialogue = true;
	}

	if (mState == 0)
	{
		mIsActive = true;
		text(balconyDoorHilma, mPlayer->getPosition(), 60, -250);
		createTalkBubble(mPlayer->getPosition(), -180, -200, 2.1f, 1.f);
	}
}

void DialogueSystem::displayDollHouseDialogue()
{
	std::string dollHouseHilma = "Vilket fint hus!";
	std::string dollHouseThomas = "Det ser ut som ett gammalt dockhus.";
	std::string dollHouseHilma2 = "Det kanske är ett dockhus för dig men för mig ser det ju ut som en herrgård!";

	if (mState == 3)
	{
		mText.setString("");
		mHasClicked = false;
		mDollHouse = false;
		mIsActive = false;
		mFinishedDialogue = true;
	}

	if (mState == 0)
	{
		mIsActive = true;
		text(dollHouseHilma, mPlayer->getPosition(), -180, -180);
		createTalkBubble(mPlayer->getPosition(), -180, -200, 2.1f, 1.f);
	}

	if (mState == 1)
	{
		text(dollHouseThomas, mPlayer->getPosition(), 60, -250);
		createTalkBubble(mPlayer->getPosition(), 60, -250, 2.5f, 1.f);
	}

	if (mState == 2)
	{
		text(dollHouseHilma2, mPlayer->getPosition(), -180, -180);
		createTalkBubble(mPlayer->getPosition(), -180, -200, 2.1f, 1.f);
	}
}

void DialogueSystem::displayPutteDialogue()
{
	std::string putteHilma = "Den där Putte igen.";

	if (mState == 1)
	{
		mText.setString("");
		mHasClicked = false;
		mPutte = false;
		mIsActive = false;
		mFinishedDialogue = true;
	}

	if (mState == 0)
	{
		mIsActive = true;
		text(putteHilma, mPlayer->getPosition(), 60, -250);
		createTalkBubble(mPlayer->getPosition(), -180, -200, 2.1f, 1.f);
	}
}

void DialogueSystem::displayPutteFamilyDialogue()
{
	std::string putteFamilyHilma = "Nu är hela familjen samlad!";

	if (mState == 1)
	{
		mText.setString("");
		mHasClicked = false;
		mPutteFamily = false;
		mIsActive = false;
		mFinishedDialogue = true;
	}

	if (mState == 0)
	{
		mIsActive = true;
		text(putteFamilyHilma, mPlayer->getPosition(), 60, -250);
		createTalkBubble(mPlayer->getPosition(), -180, -200, 2.1f, 1.f);
	}
}