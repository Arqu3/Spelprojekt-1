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

void DialogueSystem::getSpiderText(float posX, float posY, float offsetX, float offsetY)
{

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

	//Spider
	if (indexName == "spider" && mHasClicked == false)
	{
		mSpider = true;
		mHasClicked = true;
	}

	//Advanced Dialogue
	//if (indexName == "level1Start" && mHasClicked == false)
	//{
	//	mLevel1Start = true;
	//	mHasClicked = true;
	//}

	if (indexName == "missingRocket" && mHasClicked == false)
	{
		mLevel2MissingRocket = true;
		mHasClicked = true;
	}
	if (indexName == "putte" && mHasClicked == false)
	{
		mLevel2Putte = true;
		mHasClicked = true;
	}
	if (indexName == "steamMachine" && mHasClicked == false)
	{
		mLevel2SteamMachine = true;
		mHasClicked = true;
	}
	if (indexName == "arnold" && mHasClicked == false)
	{
		mLevel2Arnold = true;
		mHasClicked = true;
	}
	if (indexName == "arnoldMemories" && mHasClicked == false)
	{
		mLevel2ArnoldMemories = true;
		mHasClicked = true;
	}
	if (indexName == "putteRescue" && mHasClicked == false)
	{
		mLevel2PutteRescue = true;
		mHasClicked = true;
	}
	if (indexName == "openBox" && mHasClicked == false)
	{
		mLevel2OpenBox = true;
		mHasClicked = true;
	}
	if (indexName == "magpieSteals" && mHasClicked == false)
	{
		mLevel2MapieSteals = true;
		mHasClicked = true;
	}
	if (indexName == "grandmasCloth" && mHasClicked == false)
	{
		mLevel2GrandmasCloth = true;
		mHasClicked = true;
	}

	//Thomas' Room
	if (indexName == "ScrewDevice" && mHasClicked == false)
	{
		mLevel1End = true;
		mHasClicked = true;
	}
	if (indexName == "books" && mHasClicked == false)
	{
		mBooks = true;
		mHasClicked = true;
	}
	if (indexName == "lamp" && mHasClicked == false)
	{
		mLamp = true;
		mHasClicked = true;
	}
	if (indexName == "rubicCube" && mHasClicked == false)
	{
		mRubicCube = true;
		mHasClicked = true;
	}
	if (indexName == "poster" && mHasClicked == false)
	{
		mPoster = true;
		mHasClicked = true;
	}
	if (indexName == "backpack" && mHasClicked == false)
	{
		mBackpack = true;
		mHasClicked = true;
	}
	if (indexName == "bowl" && mHasClicked == false)
	{
		mBowl = true;
		mHasClicked = true;
	}
	if (indexName == "radio" && mHasClicked == false)
	{
		mRadio = true;
		mHasClicked = true;
	}
	if (indexName == "mat" && mHasClicked == false)
	{
		mMat = true;
		mHasClicked = true;
	}
	if (indexName == "star" && mHasClicked == false)
	{
		mStar = true;
		mHasClicked = true;
	}
	if (indexName == "aquarium" && mHasClicked == false)
	{
		mAquarium = true;
		mHasClicked = true;
	}
	if (indexName == "block" && mHasClicked == false)
	{
		mBlock = true;
		mHasClicked = true;
	}
	if (indexName == "astronaut" && mHasClicked == false)
	{
		mAstronaut = true;
		mHasClicked = true;
	}
	if (indexName == "magnet" && mHasClicked == false)
	{
		mMagnet = true;
		mHasClicked = true;
	}
	if (indexName == "string" && mHasClicked == false)
	{
		mString = true;
		mHasClicked = true;
	}

	//Grandma's Livingroom
	if (indexName == "books2" && mHasClicked == false)
	{
		mBooks2 = true;
		mHasClicked = true;
	}
	if (indexName == "jewelryCase" && mHasClicked == false)
	{
		mJewelryCase = true;
		mHasClicked = true;
	}
	if (indexName == "mask" && mHasClicked == false)
	{
		mMask = true;
		mHasClicked = true;
	}
	if (indexName == "textileCart" && mHasClicked == false)
	{
		mTextileCart = true;
		mHasClicked = true;
	}
	if (indexName == "earthGlobe" && mHasClicked == false)
	{
		mEarthGlobe = true;
		mHasClicked = true;
	}
	if (indexName == "gramophne" && mHasClicked == false)
	{
		mGramophone = true;
		mHasClicked = true;
	}
	if (indexName == "fishTrophy" && mHasClicked == false)
	{
		mFishTrophy = true;
		mHasClicked = true;
	}
	if (indexName == "plant" && mHasClicked == false)
	{
		mPlant = true;
		mHasClicked = true;
	}
	if (indexName == "armchair" && mHasClicked == false)
	{
		mArmchair = true;
		mHasClicked = true;
	}
	if (indexName == "glassesAndNuts" && mHasClicked == false)
	{
		mGlassesAndNuts = true;
		mHasClicked = true;
	}

	//Grandma's Kitchen
	if (indexName == "refridgerator" && mHasClicked == false)
	{
		mRefridgerator = true;
		mHasClicked = true;
	}
	if (indexName == "cat" && mHasClicked == false)
	{
		mCat = true;
		mHasClicked = true;
	}
	if (indexName == "catFoodBowl" && mHasClicked == false)
	{
		mCatFoodBowl = true;
		mHasClicked = true;
	}
	if (indexName == "mouseDwelling" && mHasClicked == false)
	{
		mMouseDwelling = true;
		mHasClicked = true;
	}
	if (indexName == "waterTap" && mHasClicked == false)
	{
		mWaterTap = true;
		mHasClicked = true;
	}
	if (indexName == "fruitBowl" && mHasClicked == false)
	{
		mFruitBowl = true;
		mHasClicked = true;
	}
	if (indexName == "flowers" && mHasClicked == false)
	{
		mFlowers = true;
		mHasClicked = true;
	}
	if (indexName == "rocketDrawings" && mHasClicked == false)
	{
		mRocketDrawings = true;
		mHasClicked = true;
	}
	if (indexName == "tools" && mHasClicked == false)
	{
		mTools = true;
		mHasClicked = true;
	}

	//Grandma's Room
	if (indexName == "planets" && mHasClicked == false)
	{
		mPlanets = true;
		mHasClicked = true;
	}
	if (indexName == "mercury" && mHasClicked == false)
	{
		mMercury = true;
		mHasClicked = true;
	}
	if (indexName == "venus" && mHasClicked == false)
	{
		mVenus = true;
		mHasClicked = true;
	}
	if (indexName == "emptyEarth" && mHasClicked == false)
	{
		mEmptyEarth = true;
		mHasClicked = true;
	}
	if (indexName == "emptyMars" && mHasClicked == false)
	{
		mEmptyMars = true;
		mHasClicked = true;
	}
	if (indexName == "jupiter" && mHasClicked == false)
	{
		mJupiter = true;
		mHasClicked = true;
	}
	if (indexName == "emptySaturn" && mHasClicked == false)
	{
		mEmptySaturn = true;
		mHasClicked = true;
	}
	if (indexName == "uranus" && mHasClicked == false)
	{
		mUranus = true;
		mHasClicked = true;
	}
	if (indexName == "neptune" && mHasClicked == false)
	{
		mNeptune = true;
		mHasClicked = true;
	}
	if (indexName == "emptyPluto" && mHasClicked == false)
	{
		mEmptyPluto = true;
		mHasClicked = true;
	}
	if (indexName == "mars" && mHasClicked == false)
	{
		mMars = true;
		mHasClicked = true;
	}
	if (indexName == "earth" && mHasClicked == false)
	{
		mEarth = true;
		mHasClicked = true;
	}
	if (indexName == "saturn" && mHasClicked == false)
	{
		mSaturn = true;
		mHasClicked = true;
	}
	if (indexName == "pluto" && mHasClicked == false)
	{
		mPluto = true;
		mHasClicked = true;
	}
	if (indexName == "swords" && mHasClicked == false)
	{
		mSwords = true;
		mHasClicked = true;
	}
	if (indexName == "drawings" && mHasClicked == false)
	{
		mDrawings = true;
		mHasClicked = true;
	}
	if (indexName == "balconyDoor" && mHasClicked == false)
	{
		mBalconyDoor = true;
		mHasClicked = true;
	}
	if (indexName == "dollHouse" && mHasClicked == false)
	{
		mDollHouse = true;
		mHasClicked = true;
	}
	if (indexName == "putte" && mHasClicked == false)
	{
		mPutte = true;
		mHasClicked = true;
	}
	if (indexName == "putteFamily" && mHasClicked == false)
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

//Update function
void DialogueSystem::update(float time)
{
	//Spider Dialogue
	if (mSpider == true)
	{
		displaySpiderDialogue();
	}

	//Advanced Dialogue
	if (mLevel1Start == true)
	{
		displayLevel1StartAdvancedDialogue();
	}
	if (mLevel1End == true)
	{
		displayLevel1EndAdvancedDialogue();
	}
	if (mLevel2Start == true)
	{
		displayLevel2StartAdvancedDialogue();
	}
	if (mLevel2End == true)
	{
		displayLevel2EndAdvancedDialogue();
	}
	if (mLevel2MissingRocket == true)
	{
		displayLevel2MissingRocketAdvancedDialogue();
	}
	if (mLevel2Putte == true)
	{
		displayLevel2PutteAdvancedDialogue();
	}
	if (mLevel2SteamMachine == true)
	{
		displayLevel2SteamMachineAdvancedDialogue();
	}
	if (mLevel2Arnold == true)
	{
		displayLevel2ArnoldAdvancedDialogue();
	}
	if (mLevel2ArnoldMemories == true)
	{
		displayLevel2ArnoldMemoriesAdvancedDialogue();
	}
	if (mLevel2PutteRescue == true)
	{
		displayLevel2PutteRescueAdvancedDialogue();
	}
	if (mLevel2OpenBox == true)
	{
		displayLevel2OpenBoxAdvancedDialogue();
	}
	if (mLevel2MapieSteals == true)
	{
		displayLevel2MagpieStealsAdvancedDialogue();
	}
	if (mLevel2GrandmasCloth == true)
	{
		displayLevel2GrandmasClothAdvancedDialogue();
	}

	//Thomas' Room
	if (mBooks == true)
	{
		displayBooksDialogue();
	}
	if (mLamp == true)
	{
		displayLampDialogue();
	}
	if (mRubicCube == true)
	{
		displayRubicCubeDialogue();
	}
	if (mPoster == true)
	{
		displayPosterDialogue();
	}
	if (mBackpack == true)
	{
		displayBackpackDialogue();
	}
	if (mBowl == true)
	{
		displayBowlDialogue();
	}
	if (mRadio == true)
	{
		displayRadioDialogue();
	}
	if (mMat == true)
	{
		displayMatDialogue();
	}
	if (mStar == true)
	{
		displayStarDialogue();
	}
	if (mAquarium == true)
	{
		displayAquariumDialogue();
	}
	if (mBlock == true)
	{
		displayBlockDialogue();
	}
	if (mAstronaut == true)
	{
		displayAstronautDialogue();
	}
	if (mMagnet == true)
	{
		displayMagnetDialogue();
	}
	if (mString == true)
	{
		displayStringDialogue();
	}

	//Grandma's Livingroom
	if (mBooks2 == true)
	{
		displayBooks2Dialogue();
	}
	if (mJewelryCase == true)
	{
		displayJewelryCaseDialogue();
	}
	if (mMask == true)
	{
		displayMaskDialogue();
	}
	if (mTextileCart == true)
	{
		displayTextileCartDialogue();
	}
	if (mEarthGlobe == true)
	{
		displayEarthGlobeDialogue();
	}
	if (mGramophone == true)
	{
		displayGramophoneDialogue();
	}
	if (mFishTrophy == true)
	{
		displayFishTrophyDialogue();
	}
	if (mPlant == true)
	{
		displayPlantDialogue();
	}
	if (mArmchair == true)
	{
		displayArmchairDialogue();
	}
	if (mGlassesAndNuts == true)
	{
		displayGlassesAndNutsDialogue();
	}

	//Grandma's Kitchen
	if (mRefridgerator == true)
	{
		displayRefridgeratorDialogue();
	}
	if (mCat == true)
	{
		displayCatDialogue();
	}
	if (mCatFoodBowl == true)
	{
		displayCatFoodBowlDialogue();
	}
	if (mMouseDwelling == true)
	{
		displayMouseDwellingDialogue();
	}
	if (mWaterTap == true)
	{
		displayWaterTapDialogue();
	}
	if (mFruitBowl == true)
	{
		displayFruitBowlDialogue();
	}
	if (mFlowers == true)
	{
		displayFlowersDialogue();
	}
	if (mRocketDrawings == true)
	{
		displayRocketDrawingsDialogue();
	}
	if (mTools == true)
	{
		displayToolsDialogue();
	}
	
	//Grandma's Room
	if (mPlanets == true)
	{
		displayPlanetsDialogue();
	}
	if (mMercury == true)
	{
		displayMercuryDialogue();
	}
	if (mVenus == true)
	{
		displayVenusDialogue();
	}
	if (mEmptyEarth == true)
	{
		displayEarthDialogue();
	}
	if (mEmptyMars == true)
	{
		displayEmptyMarsDialogue();
	}
	if (mJupiter == true)
	{
		displayJupiterDialogue();
	}
	if (mEmptySaturn == true)
	{
		displayEmptySaturnDialogue();
	}
	if (mUranus == true)
	{
		displayUranusDialogue();
	}
	if (mNeptune == true)
	{
		displayNeptuneDialogue();
	}
	if (mEmptyPluto == true)
	{
		displayEmptyPlutoDialogue();
	}
	if (mMars == true)
	{
		displayMarsDialogue();
	}
	if (mEarth == true)
	{
		displayEarthDialogue();
	}
	if (mSaturn == true)
	{
		displaySaturnDialogue();
	}
	if (mPluto == true)
	{
		displayPlutoDialogue();
	}
	if (mSwords == true)
	{
		displaySwordsDialogue();
	}
	if (mDrawings == true)
	{
		displayDrawingsDialogue();
	}
	if (mBalconyDoor == true)
	{
		displayBalconyDoorDialogue();
	}
	if (mDollHouse == true)
	{
		displayDollHouseDialogue();
	}
	if (mPutte == true)
	{
		displayPutteDialogue();
	}
	if (mPutteFamily == true)
	{
		displayPutteFamilyDialogue();
	}
}

void DialogueSystem::setState()
{
	mState++;
}

void DialogueSystem::setStateManual(int state)
{
	mState = state;
}

bool DialogueSystem::isDialogueFinished()
{
	return mFinishedDialogue;
}

//Spider Dialogue
void DialogueSystem::displaySpiderDialogue()
{
	if (mState >= 25)
	{
		mText.setString("");
		mActorText.setString("");
		mHasClicked = false;
		mLevel1Start = false;
		mAdvancedIsActive = false;
		mFinishedDialogue = true;
	}

	else if (mState >= 0 && mState <= 24)
	{
		mAdvancedIsActive = true;
		getSpiderText(100.f, 420.f, 1.f, 1.f);
		drawFirstCharacter(mHandler, 300.f, 30.f, 1.f, 1.f, -0.2f, 0.2f, "");
		createTextBox(-1.f, 280.f, 1.f, 1.f, 0.267f, 0.45f);
		actorText("", 480.f, 307.f, 1.f, 1.f);
	}
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

	if (mState >= 25)
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
	std::string level2PutteTeller = "På hyllan satt en liten, liten varelse. Den påminde väldigt mycket om Hilma i utseendet. Det måste vara en till hittare! Den såg mycket bekymrad ut... När Thomas var påväg att fråga hittaren hur det stod till, hindrade Hilma honom hastigt.";
	std::string level2PutteHilma = "Men kolla här borta! Det ser jätteintressant ut, vi borde kolla-";
	std::string level2PutteTeller2 = "Men innan hon hann säga mycket mer hade Thomas redan frågat hittaren. Hilma slog sig irriterat för ansiktet.";
	std::string level2PuttePutte = "En människa! Oh nej, jag måste gömma mig innan-";
	std::string level2PutteTeller3 = "Då fick hittaren syn på Hilma och fick ett leende på läpparna. Hilma log dock inte tillbaka. Hon försökte istället undvika hittarens blick.";
	std::string level2PuttePutte2 = "Men Hilma! Åh, vad bra att du är här! Vem är människan du är med? Inte visste jag att du hade människovän-";
	std::string level2PutteHilma2 = "För det första, det angår inte dig! För det andra, så är vi lite upptagna. Om du ursäktar oss-";
	std::string level2PutteThomas = "Jag heter Thomas! Trevligt att träffas!";
	std::string level2PutteTeller4 = "Hilma blängde surt på Thomas och ryckte i hans ärm för att gå vidare.";
	std::string level2PuttePutte3 = "Snälla gå inte! Jag behöver din hjälp! J-jag kanske kan hjälpa dig i utbyte!";
	std::string level2PutteHilma3 = "Igen!? Hur många gånger måste jag hjälpa dig? Och hur ska jag kunna få hjälp av dig som inte ens kan sköta sitt jobb som hittare? Jag har inte någon nytta av dig, tapparen Putte!";
	std::string level2PuttePutte4 = "Snälla! Jag ber dig! Jag har inte tappat något den här gången. Jag behöver nyckeln på den översta hyllan. Men jag når inte upp! Och... Jag kan inte komma ned...";
	std::string level2PutteHilma4 = "Du har alltså tappat bort din nyckel OCH dina egna tankar?";
	std::string level2PutteHilma5 = "Inte konstigt att du är fast däruppe. Ledsen men vi har inte tid med det här.";
	std::string level2PutteThomas2 = "Men... Men Hilma. Ska vi inte hjälpa honom? Han behöver ju hjälp.";
	std::string level2PuttePutte5 = "Nej! Jag har inte tappat bort nyckeln! Den blev stulen från mig av skatan!";
	std::string level2PutteHilma6 = "Skata säger du... Och vad ska du med nyckeln till? Vad ger du mig i utbyte OM jag skulle hjälpa dig?";
	std::string level2PuttePutte6 = "Jag behöver några saker i den låsta lådan, jag kan ge dig något från den lådan i utbyte!";
	std::string level2PutteThomas3 = "Det kanske finns något därinne som vi behöver? Det är ju... mormors låda!";
	std::string level2PutteHilma7 = "Okej, för den här gången. Men! Om det är något därinne som inte är värdig som utbyte, lämnar jag dig åt skatan!";
	std::string level2PuttePutte7 = "Tack så mycket Hilma!";
	std::string level2PutteThomas4 = "Du... tänker väl inte ge honom till skatan?";
	std::string level2PutteHilma8 = "Skator har ett öga för saker som glittrar. Putte är så långt från glitter man kan komma.";

	if (mState >= 24)
	{
		mText.setString("");
		mActorText.setString("");
		mHasClicked = false;
		mLevel2Putte = false;
		mAdvancedIsActive = false;
		mFinishedDialogue = true;
	}
	if (mState == 0)
	{
		mAdvancedIsActive = true;
		advancedText(level2PutteTeller, 100.f, 420.f, 1.f, 1.f);
		drawFirstCharacter(mHandler, 300.f, 30.f, 1.f, 1.f, -0.2f, 0.2f, "expressionHilmaNervous.png");
		drawSecondCharacter(mHandler, 700.f, 30.f, 1.f, 1.f, 0.2f, 0.2f, "expressionThomasHappy.png");
		createTextBox(-1.f, 280.f, 1.f, 1.f, 0.267f, 0.45f);
		actorText("Berättare", 462.f, 307.f, 1.f, 1.f);
	}
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