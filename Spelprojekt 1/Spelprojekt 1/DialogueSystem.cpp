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
	std::string level1StartHilma = "Men f�r b�velingen! Min flygfarkost alldeles f�rst�rd! F�rbaskade flygf�n som alltid ska vara s� livliga... N� detta m�ste lagas!";
	std::string level1StartTeller = "Den vresiga lilla hittaren tog av sin m�ssa och b�rjade leta i den. Hon letade och letade, l�ngre och l�ngre ner i m�ssan. Hela hon f�rsvann ner i den! Det enda man kunde se av henne var hennes sm�, sm� f�tter. Sedan hoppade hon ut ur den. Men d� var hon helr�d i ansiktet!";
	std::string level1StartHilma2 = "Men vad sjutton �r det h�r!? �r den borta!? ALLT �R BORTA! DET H�R KAN INTE VARA SANT!";
	std::string level1StartHilma3 = "Det var det b�sta utbytet jag hittills har f�tt! Jag som hade hittat s� bra...";
	std::string level1StartThomas = "V-vad har du tappat?";
	std::string level1StartHilma4 = "F�r det f�rsta, jag har inte tappat bort n�got. F�r det andra, �r det en mycket ov�rderlig sak som tog v�ldigt l�ng tid att f�. Det var en fantastisk skruvmackap�r. Med den skulle jag bygga en mycket finare flygfarkost �n denna skroth�g. Men nu har jag INGENTING jag kan laga skroth�gen med.";
	std::string level1StartTeller2 = "Pojken tyckte synd om den lilla varelsen och undrade om han kunde hj�lpa till. D� kom han p� en id�.";
	std::string level1StartThomas2 = "J-jag kanske... har en skruvmackap�r-";
	std::string level1StartHilma5 = "Jamen d� s�! Var har du den?";
	std::string level1StartThomas3 = "Eh... jag vet inte...";
	std::string level1StartHilma6 = "Men oj d�, det var verkligen till stor hj�lp! Kan det vara s� att du har tappat bort den?";
	std::string level1StartHilma7 = "Du f�r v�l tacka vinden f�r att den var s� b�ngstyrig idag. F�r du fick turen att tr�ffa p� mig! Det r�kar vara s� att jag �r en hittare!";
	std::string level1StartTeller3 = "En hittare? Vad kunde det vara? Pojken hade aldrig h�rt talas om dem innan.";
	std::string level1StartHilma8 = "Vi Hittare har funnits l�nge och h�llit reda p� er slarviga m�nniskor. Tappar ni bort n�got s� hittar vi det �t er. Jag och min egna hittarbyr� kan hitta vad som helst, var som helst!";
	std::string level1StartThomas4 = "O-om du verkligen �r en h-hittare. Kan du... Kan du hitta tre saker �t mig-";
	std::string level1StartHilma9 = "F�r att bevisa f�r dig att jag �r en hittare? Utmaning godtagen! Vad �r det du vill att jag ska hitta? Kom igen nu, vela inte s� mycket!";
	std::string level1StartThomas5 = "En sj�lvlysande stj�rna... den f�ll fr�n v�ggen, min favoritastronaut och... skruvmackap�ren...";
	std::string level1StartHilma10 = "Och vad f�r jag i utbyte?";
	std::string level1StartThomas6 = "Hur mycket kostar det?";
	std::string level1StartHilma11 = "Inte pengar! Ge mig n�got anv�ndbart!";
	std::string level1StartHilma12 = "Ge mig skruvmackap�ren sen n�r jag har hittat den.";
	std::string level1StartHilma13 = "Just ja! Hilma heter jag; vad �r ditt namn?";
	std::string level1StartThomas7 = "... Thomas";
	std::string level1StartHilma14 = "D� s�, Thomas. D� ska jag hitta en stj�rna, en astronaut och en skruvmackap�r �t dig!";
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
		actorText("Ber�ttare", 462.f, 307.f, 1.f, 1.f);
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
		actorText("Ber�ttare", 462.f, 307.f, 1.f, 1.f);
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
		actorText("Ber�ttare", 462.f, 307.f, 1.f, 1.f);
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
	std::string level1EndHilma = "H�r �r alla! Precis vad du bad om. Har jag �vertygat dig tillr�ckligt?";
	std::string level1EndTeller = "N�r Thomas fick syn p� alla f�rem�l kunde han inte tro sina �gon. Han som hade letat s� mycket sj�lv! Hans mamma hade sagt att n�r n�got f�rsvann i hans st�kiga rum, var det f�rsvunnet f�r alltid. Tydligen inte f�r en hittare.";
	std::string level1EndHilma2 = "Jag sa ju det! Jag hittar vad som helst, var som helst!";
	std::string level1EndTeller2 = "D� fick han ett litet, litet leende p� l�pparna och tackade s� mycket f�r Hilmas hj�lp. Men leendet f�rsvann snabbt n�r han s�g p� skruvmackap�ren.";
	std::string level1EndTeller3 = "Han blev alldeles tyst och stirrade p� den. Pl�tsligt kunde han inte bara ge den till den hj�lpsamma hittaren. Han h�ll h�rdare i skruvmackap�ren. Nu b�rjade Hilma bli ot�lig.";
	std::string level1EndHilma3 = "Hall�? Thomas? Jorden anropar!";
	std::string level1EndThomas = "F-f�rl�t jag... jag... Det �r bara det att det inte �r min skruvmackap�r jag ger dig.";
	std::string level1EndHilma4 = "Jaha ja, vems �r det d� om man f�r fr�ga? Har du stulit den?";
	std::string level1EndThomas2 = "N-nej! Absolut inte! Det... Jag l�nade den av min... mormor.";
	std::string level1EndHilma5 = "Din mormor? Vem �r denna tankspridda mormor som l�ter en slarvgosse som du ta hand om en s�dan fantastisk skruvmackap�r?";
	std::string level1EndThomas3 = "S�g inte s� om henne! Hon �r den b�sta mekanikern som har n�gonsin funnits!";
	std::string level1EndHilma6 = "Jaha jas� ja... Vad kan den h�r mormor bygga d�?";
	std::string level1EndThomas4 = "Hon kan bygga allt och laga allt! Hon lagar bilar, cykelpunkor, och bygger de b�sta l�dbilarna, flygplanen... Och-och, just nu bygger vi en rymdraket som ska ta oss till m�nen! D�r ska vi bo och jobba som rymdcowboys...";
	std::string level1EndThomas5 = "Det var det hon sa att vi skulle g�ra i alla fall...";
	std::string level1EndHilma7 = "Jas� vad d� d�, t�rs hon inte eller?";
	std::string level1EndThomas6 = "S� klart hon t�rs! Det �r inte det... Hon bara... hon... hon �r borta...";
	std::string level1EndThomas7 = "Hon har f�rsvunnit och ingen kan hitta henne!";
	std::string level1EndTeller4 = "Stackars pojke! Skulle de flesta ha sagt. Men det r�kar vara s� att Hilma inte �r s�rskilt f�rtjust i gr�tande barn. Men det pojken sade gav henne en id�.";
	std::string level1EndHilma8 = "Din mormor �r borttappad eller hur? Och vad �r mitt jobb?";
	std::string level1EndThomas8 = "Att hitta bortappade saker?";
	std::string level1EndHilma9 = "Ja men se d�r ja! Du �r ju inte helt bakom fl�tet! Och kan jag hitta saker, kan jag hitta..?";
	std::string level1EndThomas9 = "Mormor?";
	std::string level1EndHilma10 = "Exakt.";
	std::string level1EndTeller5 = "Nu slutade t�rarna rinna p� Thomas. Kunde verkligen Hilma hitta mormor? Thomas sken upp i lycka.";
	std::string level1EndThomas10 = "Verkligen? Kan du verkligen hitta henne?";
	std::string level1EndHilma11 = "Ja sj�lvklart! Men! P� ett villkor!";
	std::string level1EndThomas11 = "Vad vill du ha i utbyte?";
	std::string level1EndHilma12 = "Rymdskeppet som du och mormor byggde p�. Om hon verkligen kan bygga s�dana fantastiska flygfarkoster l�r den vara bra mycket b�ttre �n mitt pappersflygplan. S� vad v�ntar vi p�? Nu g�r vi och hittar Mormor!";
	std::string level1EndTeller6 = "Thomas nickade och hans leende kr�p sakta tillbaka. Ett nytt hopp hade grott inom honom.";
	std::string level1EndThomas12 = "Ja! Vi g�r!";

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
		actorText("Ber�ttare", 462.f, 307.f, 1.f, 1.f);
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
		actorText("Ber�ttare", 462.f, 307.f, 1.f, 1.f);
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
		actorText("Ber�ttare", 462.f, 307.f, 1.f, 1.f);
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
		actorText("Ber�ttare", 462.f, 307.f, 1.f, 1.f);
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
		actorText("Ber�ttare", 462.f, 307.f, 1.f, 1.f);
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
	std::string level2StartHilma = "S� det var h�r du s�g mormor senast?";
	std::string level2StartThomas = "Ja... Det �r mormors verkstad.";
	std::string level2StartHilma2 = "Jas� verkstad s�ger du? D� m�ste v�l rymdfarkosten vara h�r?";
	std::string level2StartThomas2 = "Mhm� den st�r l�ngst in i verkstaden.";
	std::string level2StartHilma3 = "Jaha ja! L�t mig f� inspektera denna �Rymdfarkost.";
	std::string level2StartThomas3 = "Ja visst! �h nej! Cykeln fick punka... Och... styret verkar l�st...";
	std::string level2StartHilma4 = "D� f�r vi v�l hitta p� n�got s�tt att laga den!";
	std::string level2StartThomas4 = "Man brukar anv�nda cykelpump f�r att fixa d�cket... och en skruvmakap�r f�r styret.";

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
	std::string level2MissingRocketTeller = "Men d�r rymdraketen skulle st� var det alldeles tomt. Nu var det inte bara mormor som hade f�rsvunnit utan �ven rymdraketen! Vad kunde allt det h�r betyda?";
	std::string level2MissingRocketHilma = "Jaha ja, jag kan inte se en rymdraket h�r. Lj�g du om det h�r? F�r om det �r n�got jag inte gillar s� �r det folk som ljuger!";
	std::string level2MissingRocketThomas = "N-n-nej! Men-men varf�r �r den borta?T-t�nk om n�gon har snott den?";
	std::string level2MissingRocketHilma2 = "Tja, det �r ju inte helt fel. Det �r inte som att det inte finns tjuvar h�r i staden-";
	std::string level2MissingRocketTeller2 = "Thomas �gon blev blanka n�r Hilma sade s�. Han h�ll p� att gr�ta igen! Det h�r var inte bra, t�nkte Hilma.";
	std::string level2MissingRocketHilma3 = "Jag menar, den kanske har blivit borttappad? Det kan inte vara s� sv�rt att hitta en stor rymdraket!";
	std::string level2MissingRocketPutte = "Oh nej! Oh nej! Hur hamnade den d�r!?";
	std::string level2MissingRocketTeller3 = "Vem kunde det vara som l�t s� el�ndig?";

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
		actorText("Ber�ttare", 462.f, 307.f, 1.f, 1.f);
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
		actorText("Ber�ttare", 462.f, 307.f, 1.f, 1.f);
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
		actorText("Ber�ttare", 462.f, 307.f, 1.f, 1.f);
	}
}

void DialogueSystem::displayLevel2PutteAdvancedDialogue()
{
	std::string level2PutteTeller = "P� hyllan satt en liten, liten varelse. Den p�minde v�ldigt mycket om Hilma i utseendet. Det m�ste vara en till hittare! Den s�g mycket bekymrad ut... N�r Thomas var p�v�g att fr�ga hittaren hur det stod till, hindrade Hilma honom hastigt.";
	std::string level2PutteHilma = "Men kolla h�r borta! Det ser j�tteintressant ut, vi borde kolla-";
	std::string level2PutteTeller2 = "Men innan hon hann s�ga mycket mer hade Thomas redan fr�gat hittaren. Hilma slog sig irriterat f�r ansiktet.";
	std::string level2PuttePutte = "En m�nniska! Oh nej, jag m�ste g�mma mig innan-";
	std::string level2PutteTeller3 = "D� fick hittaren syn p� Hilma och fick ett leende p� l�pparna. Hilma log dock inte tillbaka. Hon f�rs�kte ist�llet undvika hittarens blick.";
	std::string level2PuttePutte2 = "Men Hilma! �h, vad bra att du �r h�r! Vem �r m�nniskan du �r med? Inte visste jag att du hade m�nniskov�n-";
	std::string level2PutteHilma2 = "F�r det f�rsta, det ang�r inte dig! F�r det andra, s� �r vi lite upptagna. Om du urs�ktar oss-";
	std::string level2PutteThomas = "Jag heter Thomas! Trevligt att tr�ffas!";
	std::string level2PutteTeller4 = "Hilma bl�ngde surt p� Thomas och ryckte i hans �rm f�r att g� vidare.";
	std::string level2PuttePutte3 = "Sn�lla g� inte! Jag beh�ver din hj�lp! J-jag kanske kan hj�lpa dig i utbyte!";
	std::string level2PutteHilma3 = "Igen!? Hur m�nga g�nger m�ste jag hj�lpa dig? Och hur ska jag kunna f� hj�lp av dig som inte ens kan sk�ta sitt jobb som hittare? Jag har inte n�gon nytta av dig, tapparen Putte!";
	std::string level2PuttePutte4 = "Sn�lla! Jag ber dig! Jag har inte tappat n�got den h�r g�ngen. Jag beh�ver nyckeln p� den �versta hyllan. Men jag n�r inte upp! Och... Jag kan inte komma ned...";
	std::string level2PutteHilma4 = "Du har allts� tappat bort din nyckel OCH dina egna tankar?";
	std::string level2PutteHilma5 = "Inte konstigt att du �r fast d�ruppe. Ledsen men vi har inte tid med det h�r.";
	std::string level2PutteThomas2 = "Men... Men Hilma. Ska vi inte hj�lpa honom? Han beh�ver ju hj�lp.";
	std::string level2PuttePutte5 = "Nej! Jag har inte tappat bort nyckeln! Den blev stulen fr�n mig av skatan!";
	std::string level2PutteHilma6 = "Skata s�ger du... Och vad ska du med nyckeln till? Vad ger du mig i utbyte OM jag skulle hj�lpa dig?";
	std::string level2PuttePutte6 = "Jag beh�ver n�gra saker i den l�sta l�dan, jag kan ge dig n�got fr�n den l�dan i utbyte!";
	std::string level2PutteThomas3 = "Det kanske finns n�got d�rinne som vi beh�ver? Det �r ju... mormors l�da!";
	std::string level2PutteHilma7 = "Okej, f�r den h�r g�ngen. Men! Om det �r n�got d�rinne som inte �r v�rdig som utbyte, l�mnar jag dig �t skatan!";
	std::string level2PuttePutte7 = "Tack s� mycket Hilma!";
	std::string level2PutteThomas4 = "Du... t�nker v�l inte ge honom till skatan?";
	std::string level2PutteHilma8 = "Skator har ett �ga f�r saker som glittrar. Putte �r s� l�ngt fr�n glitter man kan komma.";

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
		actorText("Ber�ttare", 462.f, 307.f, 1.f, 1.f);
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
	std::string booksHilma = "Hur m�nga b�cker  har du egentligen?";
	std::string booksThomas = "Senast jag r�knade var det tjugofyra, men... det var ju ett tag sen...";

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
	std::string lampHilma = "Vad f�r oansvarig m�nniska placerar en lampa vid sitt f�nster? Jag fl�g n�stan in i den!";
	std::string lampThomas = "Jag visste inte att det var farligt med lampor...";
	std::string lampHilma2 = "Ni m�nniskor �r s� v�rdsl�sa.";
	std::string lampThomas2 = "Det var ju faktiskt du som krashade i mitt rum. Det tycker jag l�ter v�rdsl�st.";
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
	std::string rubicHilma = "Vad �r det h�r?";
	std::string rubicThomas = "En Rubiks kub, man ska f� alla f�rger p� varsin sida.";
	std::string rubicHilma2 = "Men vad �r det f�r utmaning? L�ter ju j�ttel�tt!";

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
	std::string posterHilma = "Varf�r �r det bara rymdbilder?";
	std::string posterThomas = "Jag gillar rymden och planeter och s�nt. Min mormor gav mig de flesta av dem.";

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
	std::string backpackHilma = "Vad �r det f�r en massa papper i v�skan?";
	std::string backpackThomas = "L�xor... de var roliga ett tag men sen fick jag bara fler och fler!";

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
	std::string bowlHilma = "Anv�nde du den h�r n�r du klippte dig eller?";
	std::string bowlThomas = "Vad menar du?";
	std::string bowlHilma2 = "�h, gl�m det...";

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
	std::string radioHilma = "En radio! De brukar vara fulla av anv�ndbara delar!";
	std::string radioThomas = "Sn�lla f�rst�r inte min radio.";
	std::string radioHilma2 = "Okej d�...";

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
	std::string matHilma = "Magneten dras mot kn�len i mattan.";

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
	std::string starHilma = "Den h�r stj�rnan  ser inte ut som de andra, tror du..?";

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
	std::string aquariumHilma = "Varf�r har du en fisk inne p� rummet? Dem ska ju vara i sj�ar!";
	std::string aquariumThomas = "Men det �r mitt husdjur, han heter Roger.";
	std::string aquariumHilma2 = "Kan Roger ha �tit upp astronauten?";
	std::string aquariumThomas2 = "N�, inte Roger, han �r sn�ll.";

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
	std::string blockHilma = "En helt om�rkv�rdig kloss.";

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
	std::string astronautHilma = "D�r �r astronauten! Titta Thomas! Jag hittade den!";
	std::string astronautThomas = "Ja... men den �r ju i akvariet. Jag vill ha den i handen!";
	std::string astronautHilma2 = "Okej d�, jag f�r v�l hitta ett s�tt att fiska upp den.";

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
	std::string magnetHilma = "En magnet... hmm den kan vara anv�ndbar.";

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
	std::string stringHilma = "Ett fiskesp�.";

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
	std::string books2Thomas = "Rymdb�cker... precis som mina d�r hemma.";

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
	std::string jewelryCaseHilma = "Vi �ppnar och kollar vad som finns i den!";
	std::string jewelryCaseHilma2 = "Den �r bara full av muttrar!";

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
	std::string maskHilma = "Vilka lustiga masker! Var kommer de ifr�n?";
	std::string maskThomas = "N�gonstans i Afrika tror jag. Mormor reste mycket n�r hon var ung.";

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
	std::string textileCartHilma = "Garnnystan och n�lar. Kan vara anv�ndbart!";

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
	std::string earthGlobeThomas = "En jordglob. Jag har alltid velat ha en s�n�";
	std::string earthGlobeHilma = "Vet du vad Thomas, vi kanske kan ha anv�ndning f�r den�";

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
	std::string gramophoneHilma = "Vad �r det h�r f�r n�got?";
	std::string gramophoneThomas = "Jag vet inte riktigt, men jag har sett s�nna p� TV. Folk brukade spela musik med dem h�r. Men det verkar som n�len till den saknas.";

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
	std::string fishTrophyHilma = "En fisk! Vad �r det med din familj och att ha fiskar inomhus egentligen?";

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
	std::string plantHilma = "N�gon m�ste ta hand om den h�r plantan, s�kert din mormor";

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
	std::string armchairHilma = "En radio! De brukar vara fulla av anv�ndbara delar!";

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
	std::string glassesAndNutsHilma = "Det ser ut som att n�gon suttit h�r och l�st.";
	std::string glassesAndNutsThomas = "Det m�ste vara mormor, hon anv�nde alltid l�sglas�gon.";

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
	std::string refridgeratorThomas = "Ett gammalt kylsk�p.";

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
	std::string catHilma = "�h nej! En katt! Jag hatar katter! Kom, vi g�r h�rifr�n!";
	std::string catThomas = "V�nta Hilma, h�r du inte det d�r?";
	std::string catHilma2 = "Vad�?";
	std::string catThomas2 = "Det l�ter som n�got litet som ropar p� hj�lp!";

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
	std::string catFoodBowlThomas = "M�ste vara kattens matsk�l. Och den �r tom. Katten kanske �r hungrig?";

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
	std::string mouseDwellingHilma = "Ett mush�l. Och n�gon ropar p� hj�lp innifr�n!";

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
	std::string waterTapThomas = "Hmm den h�r vattenkranen funkar inte.";
	std::string waterTapHilma = "Med v�ra redskap ska vi nog kunna fixa den!";

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
	std::string fruitBowlThomas = "Den h�r frukten �r ju fortfarande f�rsk! Mormor m�ste ha varit h�r!";

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
	std::string flowersThomas = "Blommorna �r fr�scha, mormor m�ste ta hand om dem.";

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
	std::string rocketDrawingsThomas = "Dem h�r liknar ritningarna p� raketen jag och mormor byggde, men dem h�r ser j�ttekomplicerade ut!";

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
	std::string toolsThomas = "Det h�r �r ju mormors verkstyg. Vad har hon byggt h�r?";

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
	std::string planetsThomas = "Wow� alla solsystemets planeter! Men� vissa av dem saknas!";

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
	std::string mercuryThomas = "Merkurius, planeten n�rmast solen.";

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
	std::string venusThomas = "Venus liknar mycket jorden men har en j�ttegiftig atmosf�r.";

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
	std::string emptyEarthThomas = "Men! jorden ska ju vara h�r!";

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
	std::string emptyMarsThomas = "Mars saknas ocks�.";

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
	std::string jupiterThomas = "Jupiter �r den st�rsta planeten i v�rt solsystem men �nd� bara en tusendel av solens storlek!";

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
	std::string emptySaturnThomas = "H�r ska ju Saturnus, planeten med ringar, vara!";

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
	std::string uranusThomas = "Uranus �r en isplanet och den kallaste i v�rt solsystem.";

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
	std::string neptuneThomas = "Neptunus, en bl� isplanet med starka vindar.";

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
	std::string emptyPlutoThomas = "Pluto, dv�rgplaneten, �r borta!";

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
	std::string marsThomas = "Den h�r frukten liknar Mars, och den �r ungef�r lika stor!";

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
	std::string plutoThomas = "Den h�r p�rlan �r liten och gr�, likt Pluto.";

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
	std::string swordsHilma = "Vilka h�ftiga sv�rd!";

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
	std::string drawingsHilma = "Dem h�r ritningarna ser j�ttekomplicerade ut.";
	std::string drawingsThomas = "Dem �r ritningar p� en raket. Fast den h�r �r st�rre �n den jag och mormor byggde!";

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
	std::string balconyDoorHilma = "N�pp! D�r kommer vi inte igenom! Vi m�ste f� upp den p� n�got s�tt�";

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
	std::string dollHouseHilma2 = "Det kanske �r ett dockhus f�r dig men f�r mig ser det ju ut som en herrg�rd!";

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
	std::string putteHilma = "Den d�r Putte igen.";

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
	std::string putteFamilyHilma = "Nu �r hela familjen samlad!";

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