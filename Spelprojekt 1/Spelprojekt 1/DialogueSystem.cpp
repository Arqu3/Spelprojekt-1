#include "DialogueSystem.h"
#include <iostream>
#include "SFML\System.hpp"

DialogueSystem::DialogueSystem(ResourceHandler &handler, int level) :
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
mLevel1Start(false),
mLevel1End(false),
mLevel2Start(false),
mLevel2End(false),
mLineStarted(false)
{
	mFont.loadFromFile("Resources/Fonts/Lora-Regular.ttf");
	mBubble.setTexture(*handler.getTexture("textboxSmall.png"));
	mTextBox.setTexture(*handler.getTexture("textbox.png"));
	mSepia.setSize(sf::Vector2f(1024, 576));
	mSepia.setTexture(handler.getTexture("sepia.png"));

	if (level == 0)
	{
		//Narrator
		NarratorLvl1Part1.openFromFile(handler.getMusic("Dialogue Narrator lvl1 part 1.ogg"));
		NarratorLvl1Part2.openFromFile(handler.getMusic("Dialogue Narrator lvl1 part 2.ogg"));
		NarratorLvl1Part3.openFromFile(handler.getMusic("Dialogue Narrator lvl1 part 3.ogg"));
		NarratorLvl1Part4.openFromFile(handler.getMusic("Dialogue Narrator lvl1 part 4.ogg"));
		NarratorLvl1Part5.openFromFile(handler.getMusic("Dialogue Narrator lvl1 part 5.ogg"));
		NarratorLvl1Part6.openFromFile(handler.getMusic("Dialogue Narrator lvl1 part 6.ogg"));
		NarratorLvl1Part7.openFromFile(handler.getMusic("Dialogue Narrator lvl1 part 7.ogg"));
		NarratorLvl1Part8.openFromFile(handler.getMusic("Dialogue Narrator lvl1 part 8.ogg"));
		NarratorLvl1Part9.openFromFile(handler.getMusic("Dialogue Narrator lvl1 part 9.ogg"));
		//Thomas
		ThomasLvl1Part1.openFromFile(handler.getMusic("Thomas lvl 1 Beginning part 1.ogg"));
		ThomasLvl1Part2.openFromFile(handler.getMusic("Thomas lvl 1 Beginning part 2.ogg"));
		ThomasLvl1Part3.openFromFile(handler.getMusic("Thomas lvl 1 Beginning part 3.ogg"));
		ThomasLvl1Part4.openFromFile(handler.getMusic("Thomas lvl 1 Beginning part 4.ogg"));
		ThomasLvl1Part5.openFromFile(handler.getMusic("Thomas lvl 1 Beginning part 5.ogg"));
		ThomasLvl1Part6.openFromFile(handler.getMusic("Thomas lvl 1 Beginning part 6.ogg"));
		ThomasLvl1Part7.openFromFile(handler.getMusic("Thomas lvl 1 Beginning part 7.ogg"));
		ThomasLvl1EndPart1.openFromFile(handler.getMusic("Thomas lvl 1 End part 1.ogg"));
		ThomasLvl1EndPart2.openFromFile(handler.getMusic("Thomas lvl 1 End part 2.ogg"));
		ThomasLvl1EndPart3.openFromFile(handler.getMusic("Thomas lvl 1 End part 3.ogg"));
		ThomasLvl1EndPart4.openFromFile(handler.getMusic("Thomas lvl 1 End part 4.ogg"));
		ThomasLvl1EndPart5.openFromFile(handler.getMusic("Thomas lvl 1 End part 5.ogg"));
		ThomasLvl1EndPart6.openFromFile(handler.getMusic("Thomas lvl 1 End part 6.ogg"));
		ThomasLvl1EndPart7.openFromFile(handler.getMusic("Thomas lvl 1 End part 7.ogg"));
		ThomasLvl1EndPart8.openFromFile(handler.getMusic("Thomas lvl 1 End part 8.ogg"));
		ThomasLvl1EndPart9.openFromFile(handler.getMusic("Thomas lvl 1 End part 9.ogg"));
		ThomasLvl1EndPart10.openFromFile(handler.getMusic("Thomas lvl 1 End part 10.ogg"));
		ThomasLvl1EndPart11.openFromFile(handler.getMusic("Thomas lvl 1 End part 11.ogg"));
		ThomasLvl1EndPart12.openFromFile(handler.getMusic("Thomas lvl 1 End part 12.ogg"));
		//Hilma
		HilmaLvl1BeginningPart1.openFromFile(handler.getMusic("Hilma lvl 1 Beginning part 1.ogg"));
		HilmaLvl1BeginningPart2.openFromFile(handler.getMusic("Hilma lvl 1 Beginning part 2.ogg"));
		HilmaLvl1BeginningPart3.openFromFile(handler.getMusic("Hilma lvl 1 Beginning part 3.ogg"));
		HilmaLvl1BeginningPart4.openFromFile(handler.getMusic("Hilma lvl 1 Beginning part 4.ogg"));
		HilmaLvl1BeginningPart5.openFromFile(handler.getMusic("Hilma lvl 1 Beginning part 5.ogg"));
		HilmaLvl1BeginningPart6.openFromFile(handler.getMusic("Hilma lvl 1 Beginning part 6.ogg"));
		HilmaLvl1BeginningPart7.openFromFile(handler.getMusic("Hilma lvl 1 Beginning part 7.ogg"));
		HilmaLvl1BeginningPart8.openFromFile(handler.getMusic("Hilma lvl 1 Beginning part 8.ogg"));
		HilmaLvl1BeginningPart9.openFromFile(handler.getMusic("Hilma lvl 1 Beginning part 9.ogg"));
		HilmaLvl1BeginningPart10.openFromFile(handler.getMusic("Hilma lvl 1 Beginning part 10.ogg"));
		HilmaLvl1BeginningPart11.openFromFile(handler.getMusic("Hilma lvl 1 Beginning part 11.ogg"));
		HilmaLvl1BeginningPart12.openFromFile(handler.getMusic("Hilma lvl 1 Beginning part 12.ogg"));
		HilmaLvl1BeginningPart13.openFromFile(handler.getMusic("Hilma lvl 1 Beginning part 13.ogg"));
		HilmaLvl1BeginningPart14.openFromFile(handler.getMusic("Hilma lvl 1 Beginning part 14.ogg"));
		HilmaLvl1EndPart1.openFromFile(handler.getMusic("Hilma lvl 1 End part 1.ogg"));
		HilmaLvl1EndPart2.openFromFile(handler.getMusic("Hilma lvl 1 End part 2.ogg"));
		HilmaLvl1EndPart3.openFromFile(handler.getMusic("Hilma lvl 1 End part 3.ogg"));
		HilmaLvl1EndPart4.openFromFile(handler.getMusic("Hilma lvl 1 End part 4.ogg"));
		HilmaLvl1EndPart5.openFromFile(handler.getMusic("Hilma lvl 1 End part 5.ogg"));
		HilmaLvl1EndPart6.openFromFile(handler.getMusic("Hilma lvl 1 End part 6.ogg"));
		HilmaLvl1EndPart7.openFromFile(handler.getMusic("Hilma lvl 1 End part 7.ogg"));
		HilmaLvl1EndPart8.openFromFile(handler.getMusic("Hilma lvl 1 End part 8.ogg"));
		HilmaLvl1EndPart9.openFromFile(handler.getMusic("Hilma lvl 1 End part 9.ogg"));
		HilmaLvl1EndPart10.openFromFile(handler.getMusic("Hilma lvl 1 End part 10.ogg"));
		HilmaLvl1EndPart11.openFromFile(handler.getMusic("Hilma lvl 1 End part 11.ogg"));
		HilmaLvl1EndPart12.openFromFile(handler.getMusic("Hilma lvl 1 End part 12.ogg"));
	}
}

DialogueSystem::~DialogueSystem()
{

}

//Function for all text in dialogues
void DialogueSystem::text(std::string text, float posX, float posY, float offsetX, float offsetY)
{
	mText.setFont(mFont);
	mText.setCharacterSize(18);
	//mText.setStyle(sf::Text::Bold);
	mText.setColor(sf::Color::Black);
	mText.move(offsetX, offsetY);

	std::string::size_type tempChar = 0;

	if (text.length() > 60)
	{
		std::string::size_type spacePos = text.rfind(' ', 60);
		if (spacePos == std::string::npos)
		{
			spacePos = text.find(' ', 60);
		}
		if (spacePos != std::string::npos)
		{
			text[spacePos] = '\n';
			tempChar = spacePos;
		}
	}
	if (text.length() > tempChar + 60)
	{
		std::string::size_type spacePos = text.rfind(' ', tempChar + 60);
		if (spacePos == std::string::npos)
		{
			spacePos = text.find(' ', tempChar + 60);
		}
		if (spacePos != std::string::npos)
		{
			text[spacePos] = '\n';
			posY = posY - 15;
			tempChar = spacePos;
		}
	}
	else
		tempChar = 0;

	mText.setPosition(posX, posY);
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
		window.draw(mActorText);
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

void DialogueSystem::createTalkBubble(float posX, float posY, float offsetX, float offsetY, float scaleX, float scaleY)
{
	mBubble.setPosition(posX, posY);
	mBubble.setScale(scaleX, scaleY);
	mBubble.move(offsetX, offsetY);
}

void DialogueSystem::createTextBox(float posX, float posY, float offsetX, float offsetY, float scaleX, float scaleY)
{
	mTextBox.setPosition(posX, posY);
	mTextBox.setScale(scaleX, scaleY);
	mTextBox.move(offsetX, offsetY);
}

void DialogueSystem::drawFirstCharacter(ResourceHandler &handler, float posX, float posY, float offsetX, float offsetY, float scaleX, float scaleY, std::string character)
{
	mFirstCharacter.setPosition(posX, posY);
	mFirstCharacter.setScale(scaleX, scaleY);
	mFirstCharacter.move(offsetX, offsetY);
	mFirstCharacter.setTexture(*handler.getTexture(character));
}

void DialogueSystem::drawSecondCharacter(ResourceHandler &handler, float posX, float posY, float offsetX, float offsetY, float scaleX, float scaleY, std::string character)
{
	mSecondCharacter.setPosition(posX, posY);
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
		mDialogueSpider = true;
		mHasClicked = true;
	}

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
	else if (indexName == "gramophone" && mHasClicked == false)
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

	//Garden
	else if (indexName == "shears" && mHasClicked == false)
	{
		mShears = true;
		mHasClicked = true;
	}
	else if (indexName == "bush" && mHasClicked == false)
	{
		mBush = true;
		mHasClicked = true;
	}
	else if (indexName == "rope" && mHasClicked == false)
	{
		mRope = true;
		mHasClicked = true;
	}
	else if (indexName == "dog" && mHasClicked == false)
	{
		mDog = true;
		mHasClicked = true;
	}
	else if (indexName == "gardenFlowers" && mHasClicked == false)
	{
		mGardenFlowers = true;
		mHasClicked = true;
	}
	else if (indexName == "flagpole" && mHasClicked == false)
	{
		mFlagpole = true;
		mHasClicked = true;
	}
	else if (indexName == "bee" && mHasClicked == false)
	{
		mBee = true;
		mHasClicked = true;
	}
	else if (indexName == "tracks" && mHasClicked == false)
	{
		mTracks = true;
		mHasClicked = false;
	}

	//Shack
	else if (indexName == "rocket" && mHasClicked == false)
	{
		mRocket = true;
		mHasClicked = true;
	}
	else if (indexName == "wayIn" && mHasClicked == false)
	{
		mWayIn = true;
		mHasClicked = true;
	}
	else if (indexName == "entryFindersWorld" && mHasClicked == false)
	{
		mEntryFindersWorld = true;
		mHasClicked = true;
	}
	else if (indexName == "clover" && mHasClicked == false)
	{
		mClover = true;
		mHasClicked = true;
	}
	else if (indexName == "nails" && mHasClicked == false)
	{
		mNails = true;
		mHasClicked = true;
	}
	else if (indexName == "horseShoe" && mHasClicked == false)
	{
		mHorseShoe = true;
		mHasClicked = true;
	}
	else if (indexName == "cloth" && mHasClicked == false)
	{
		mCloth = true;
		mHasClicked = true;
	}
	else if (indexName == "badmintonBall" && mHasClicked == false)
	{
		mBadmintonBall = true;
		mHasClicked = true;
	}
	else if (indexName == "sawdust" && mHasClicked == false)
	{
		mSawdust = true;
		mHasClicked = true;
	}
	else if (indexName == "knight" && mHasClicked == false)
	{
		mKnight = true;
		mHasClicked = true;
	}
	else if (indexName == "knightFirst" && mHasClicked == false)
	{
		mKnightFirst = true;
		mHasClicked = true;
	}
	else if (indexName == "knightSecond" && mHasClicked == false)
	{
		mKnightSecond = true;
		mHasClicked = true;
	}
	else if (indexName == "knightAll" && mHasClicked == false)
	{
		mKnightAll = true;
		mHasClicked = true;
	}

	//Finders' World
	else if (indexName == "exitFindersWorld" && mHasClicked == false)
	{
		mExitFindersWorld = true;
		mHasClicked = true;
	}
	else if (indexName == "statue" && mHasClicked == false)
	{
		mStatue = true;
		mHasClicked = true;
	}
	else if (indexName == "jewels" && mHasClicked == false)
	{
		mJewels = true;
		mHasClicked = true;
	}
	else if (indexName == "bubbles" && mHasClicked == false)
	{
		mBubbles = true;
		mHasClicked = true;
	}
	else if (indexName == "parent" && mHasClicked == false)
	{
		mParent = true;
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
	//Spider Dialogue
	if (mDialogueSpider == true)
	{
		displaySpiderDialogue();
	}

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
		displayEmptyEarthDialogue();
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

	//Garden
	else if (mShears == true)
	{
		displayShearsDialogue();
	}
	else if (mBush == true)
	{
		displayBushDialogue();
	}
	else if (mRope == true)
	{
		displayRopeDialogue();
	}
	else if (mDog == true)
	{
		displayDogDialogue();
	}
	else if (mGardenFlowers == true)
	{
		displayGardenFlowersDialogue();
	}
	else if (mFlagpole == true)
	{
		displayFlagpoleDialogue();
	}
	else if (mBee == true)
	{
		displayBeeDialogue();
	}
	else if (mTracks == true)
	{
		displayTracksDialogue();
	}

	//Shack
	else if (mRocket == true)
	{
		displayRocketDialogue();
	}
	else if (mWayIn == true)
	{
		displayWayInDialogue();
	}
	else if (mEntryFindersWorld == true)
	{
		displayEntryFindersWorldDialogue();
	}
	else if (mClover == true)
	{
		displayCloverDialogue();
	}
	else if (mNails == true)
	{
		displayNailsDialogue();
	}
	else if (mHorseShoe == true)
	{
		displayHorseShoeDialogue();
	}
	else if (mCloth == true)
	{
		displayClothDialogue();
	}
	else if (mBadmintonBall == true)
	{
		displayBadmintonBallDialogue();
	}
	else if (mSawdust == true)
	{
		displaySawdustDialogue();
	}
	else if (mKnight == true)
	{
		displayKnightDialogue();
	}
	else if (mKnightFirst == true)
	{
		displayKnightFirstDialogue();
	}
	else if (mKnightSecond == true)
	{
		displayKnightSecondDialogue();
	}
	else if (mKnightAll == true)
	{
		displayKnightAllDialogue();
	}

	//Finders' World
	else if (mExitFindersWorld == true)
	{
		displayExitFindersWorld();
	}
	else if (mStatue == true)
	{
		displayStatueDialogue();
	}
	else if (mJewels == true)
	{
		displayJewelsDialogue();
	}
	else if (mBubbles == true)
	{
		displayBubblesDialogue();
	}
	else if (mParent == true)
	{
		displayParentDialogue();
	}
}

void DialogueSystem::setState()
{
	mLineStarted = false;
	mState++;
}

//void DialogueSystem::setStateManual(int state)
//{
//	mState = state;
//}

bool DialogueSystem::isDialogueFinished()
{
	return mFinishedDialogue;
}

//Spider Dialogue
void DialogueSystem::displaySpiderDialogue()
{
	if (mState >= 1)
	{
		mText.setString("");
		mActorText.setString("");
		mHasClicked = false;
		mDialogueSpider = false;
		mAdvancedIsActive = false;
		mFinishedDialogue = true;
	}

	else if (mState >= 0)
	{
		mAdvancedIsActive = true;
		advancedText(mSpider->getText(), 100.f, 420.f, 1.f, 1.f);
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
	std::string level1StartTeller2 = "Pojken tyckte det var lite synd om den lilla varelsen och undrade om han kunde hj�lpa till. D� kom han p� en id�.";
	std::string level1StartThomas2 = "J-jag kanske... har en skruvmackap�r-";
	std::string level1StartHilma5 = "Jamen d� s�! Var har du den?";
	std::string level1StartThomas3 = "Eh... jag vet inte...";
	std::string level1StartHilma6 = "Men oj d�, det var verkligen till stor hj�lp! Kan det vara s� att du har tappat bort den?";
	std::string level1StartHilma7 = "Du f�r v�l tacka vinden f�r att den var s� b�ngstyrig idag. F�r du fick turen att tr�ffa p� mig! Det r�kar vara s� att jag �r en hittare!";
	std::string level1StartTeller3 = "En hittare? Vad kunde det vara? Pojken hade aldrig h�rt talas om dem innan.";
	std::string level1StartHilma8 = "Vi Hittare har funnits l�nge och h�llit reda p� er slarviga m�nniskor. Tappar ni bort n�got s� hittar vi det �t er. Jag och min egna hittarbyr� kan hitta vad som helst, var som helst!";
	std::string level1StartThomas4 = "O-om du verkligen �r en h-hittare. Kan du... Kan du hitta tre saker �t mig-";
	std::string level1StartHilma9 = "F�r att bevisa f�r dig att jag �r en hittare? Utmaning godtagen! Vad �r det du vill att jag ska hitta? Kom igen nu, vela inte s� mycket!";
	std::string level1StartThomas5 = "En sj�lvlysande stj�rna... den f�ll ner fr�n v�ggen, min favoritastronaut och... skruvmackap�ren...";
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
		HilmaLvl1BeginningPart14.stop();
	}

	if (mState == 0)
	{
		mAdvancedIsActive = true;
		advancedText(level1StartHilma, 100.f, 420.f, 1.f, 1.f);
		drawFirstCharacter(mHandler, 300.f, 30.f, 1.f, 1.f, -0.2f, 0.2f, "expressionHilmaGrumpy.png");
		createTextBox(-1.f, 280.f, 1.f, 1.f, 0.267f, 0.45f);
		actorText("Hilma", 480.f, 307.f, 1.f, 1.f);

		//Voice Acting
		if (!mLineStarted && HilmaLvl1BeginningPart1.getStatus() != 2)
		{
			HilmaLvl1BeginningPart1.play();
			mLineStarted = true;
		}
		if (mLineStarted && HilmaLvl1BeginningPart1.getStatus() == 0)
		{
			mLineStarted = false;
			setState();
		}
	}
	if (mState == 1)
	{
		advancedText(level1StartTeller, 100.f, 420.f, 1.f, 1.f);
		actorText("Ber�ttare", 462.f, 307.f, 1.f, 1.f);

		//Voice Acting
		HilmaLvl1BeginningPart1.stop();
		if (!mLineStarted && NarratorLvl1Part1.getStatus() != 2)
		{
			NarratorLvl1Part1.play();
			mLineStarted = true;
		}
		if (mLineStarted && NarratorLvl1Part1.getStatus() == 0)
		{
			mLineStarted = false;
			setState();
		}
	}
	if (mState == 2)
	{
		advancedText(level1StartHilma2, 100.f, 420.f, 1.f, 1.f);
		drawFirstCharacter(mHandler, 300.f, 30.f, 1.f, 1.f, -0.2f, 0.2f, "expressionHilmaAngry.png");
		actorText("Hilma", 480.f, 307.f, 1.f, 1.f);

		//Voice Acting Template
		NarratorLvl1Part1.stop();
		if (!mLineStarted && HilmaLvl1BeginningPart2.getStatus() != 2)
		{
			HilmaLvl1BeginningPart2.play();
			mLineStarted = true;
		}
		if (mLineStarted && HilmaLvl1BeginningPart2.getStatus() == 0)
		{
			mLineStarted = false;
			setState();
		}
	}
	if (mState == 3)
	{
		advancedText(level1StartHilma3, 100.f, 420.f, 1.f, 1.f);
		drawFirstCharacter(mHandler, 300.f, 30.f, 1.f, 1.f, -0.2f, 0.2f, "expressionHilmaAbject.png");

		HilmaLvl1BeginningPart2.stop();
		if (!mLineStarted && HilmaLvl1BeginningPart3.getStatus() != 2)
		{
			HilmaLvl1BeginningPart3.play();
			mLineStarted = true;
		}
		if (mLineStarted && HilmaLvl1BeginningPart3.getStatus() == 0)
		{
			mLineStarted = false;
			setState();
		}
	}
	if (mState == 4)
	{
		advancedText(level1StartThomas, 100.f, 420.f, 1.f, 1.f);
		drawSecondCharacter(mHandler, 700.f, 30.f, 1.f, 1.f, 0.2f, 0.2f, "expressionThomasThoughtful.png");
		actorText("Thomas", 472.f, 307.f, 1.f, 1.f);

		HilmaLvl1BeginningPart3.stop();
		if (!mLineStarted && ThomasLvl1Part1.getStatus() != 2)
		{
			ThomasLvl1Part1.play();
			mLineStarted = true;
		}
		if (mLineStarted && ThomasLvl1Part1.getStatus() == 0)
		{
			mLineStarted = false;
			setState();
		}
	}
	if (mState == 5)
	{
		advancedText(level1StartHilma4, 100.f, 420.f, 1.f, 1.f);
		drawFirstCharacter(mHandler, 300.f, 30.f, 1.f, 1.f, -0.2f, 0.2f, "expressionHilmaGrumpy.png");
		actorText("Hilma", 480.f, 307.f, 1.f, 1.f);

		ThomasLvl1Part1.stop();
		if (!mLineStarted && HilmaLvl1BeginningPart4.getStatus() != 2)
		{
			HilmaLvl1BeginningPart4.play();
			mLineStarted = true;
		}
		if (mLineStarted && HilmaLvl1BeginningPart4.getStatus() == 0)
		{
			mLineStarted = false;
			setState();
		}
	}
	if (mState == 6)
	{
		advancedText(level1StartTeller2, 100.f, 420.f, 1.f, 1.f);
		actorText("Ber�ttare", 462.f, 307.f, 1.f, 1.f);

		HilmaLvl1BeginningPart4.stop();
		if (!mLineStarted && NarratorLvl1Part2.getStatus() != 2)
		{
			NarratorLvl1Part2.play();
			mLineStarted = true;
		}
		if (mLineStarted && NarratorLvl1Part2.getStatus() == 0)
		{
			mLineStarted = false;
			setState();
		}
	}
	if (mState == 7)
	{
		advancedText(level1StartThomas2, 100.f, 420.f, 1.f, 1.f);
		drawSecondCharacter(mHandler, 700.f, 30.f, 1.f, 1.f, 0.2f, 0.2f, "expressionThomasThoughtful.png");
		actorText("Thomas", 472.f, 307.f, 1.f, 1.f);

		NarratorLvl1Part2.stop();
		if (!mLineStarted && ThomasLvl1Part2.getStatus() != 2)
		{
			ThomasLvl1Part2.play();
			mLineStarted = true;
		}
		if (mLineStarted && ThomasLvl1Part2.getStatus() == 0)
		{
			mLineStarted = false;
			setState();
		}
	}
	if (mState == 8)
	{
		advancedText(level1StartHilma5, 100.f, 420.f, 1.f, 1.f);
		drawFirstCharacter(mHandler, 300.f, 30.f, 1.f, 1.f, -0.2f, 0.2f, "expressionHilmaHappy.png");
		actorText("Hilma", 480.f, 307.f, 1.f, 1.f);

		ThomasLvl1Part2.stop();
		if (!mLineStarted && HilmaLvl1BeginningPart5.getStatus() != 2)
		{
			HilmaLvl1BeginningPart5.play();
			mLineStarted = true;
		}
		if (mLineStarted && HilmaLvl1BeginningPart5.getStatus() == 0)
		{
			mLineStarted = false;
			setState();
		}
	}
	if (mState == 9)
	{
		advancedText(level1StartThomas3, 100.f, 420.f, 1.f, 1.f);
		drawSecondCharacter(mHandler, 700.f, 30.f, 1.f, 1.f, 0.2f, 0.2f, "expressionThomasSurprised.png");
		actorText("Thomas", 472.f, 307.f, 1.f, 1.f);

		HilmaLvl1BeginningPart5.stop();
		if (!mLineStarted && ThomasLvl1Part3.getStatus() != 2)
		{
			ThomasLvl1Part3.play();
			mLineStarted = true;
		}
		if (mLineStarted && ThomasLvl1Part3.getStatus() == 0)
		{
			mLineStarted = false;
			setState();
		}
	}
	if (mState == 10)
	{
		advancedText(level1StartHilma6, 100.f, 420.f, 1.f, 1.f);
		drawFirstCharacter(mHandler, 300.f, 30.f, 1.f, 1.f, -0.2f, 0.2f, "expressionHilmaGrumpy.png");
		actorText("Hilma", 480.f, 307.f, 1.f, 1.f);

		ThomasLvl1Part3.stop();
		if (!mLineStarted && HilmaLvl1BeginningPart6.getStatus() != 2)
		{
			HilmaLvl1BeginningPart6.play();
			mLineStarted = true;
		}
		if (mLineStarted && HilmaLvl1BeginningPart6.getStatus() == 0)
		{
			mLineStarted = false;
			setState();
		}
	}
	if (mState == 11)
	{
		advancedText(level1StartHilma7, 100.f, 420.f, 1.f, 1.f);
		drawFirstCharacter(mHandler, 300.f, 30.f, 1.f, 1.f, -0.2f, 0.2f, "expressionHilmaConfident.png");

		HilmaLvl1BeginningPart6.stop();
		if (!mLineStarted && HilmaLvl1BeginningPart7.getStatus() != 2)
		{
			HilmaLvl1BeginningPart7.play();
			mLineStarted = true;
		}
		if (mLineStarted && HilmaLvl1BeginningPart7.getStatus() == 0)
		{
			mLineStarted = false;
			setState();
		}
	}
	if (mState == 12)
	{
		advancedText(level1StartTeller3, 100.f, 420.f, 1.f, 1.f);
		actorText("Ber�ttare", 462.f, 307.f, 1.f, 1.f);

		HilmaLvl1BeginningPart7.stop();
		if (!mLineStarted && NarratorLvl1Part3.getStatus() != 2)
		{
			NarratorLvl1Part3.play();
			mLineStarted = true;
		}
		if (mLineStarted && NarratorLvl1Part3.getStatus() == 0)
		{
			mLineStarted = false;
			setState();
		}
	}
	if (mState == 13)
	{
		advancedText(level1StartHilma8, 100.f, 420.f, 1.f, 1.f);
		drawFirstCharacter(mHandler, 300.f, 30.f, 1.f, 1.f, -0.2f, 0.2f, "expressionHilmaDetermined.png");
		actorText("Hilma", 480.f, 307.f, 1.f, 1.f);

		NarratorLvl1Part3.stop();
		if (!mLineStarted && HilmaLvl1BeginningPart8.getStatus() != 2)
		{
			HilmaLvl1BeginningPart8.play();
			mLineStarted = true;
		}
		if (mLineStarted && HilmaLvl1BeginningPart8.getStatus() == 0)
		{
			mLineStarted = false;
			setState();
		}
	}
	if (mState == 14)
	{
		advancedText(level1StartThomas4, 100.f, 420.f, 1.f, 1.f);
		drawSecondCharacter(mHandler, 700.f, 30.f, 1.f, 1.f, 0.2f, 0.2f, "expressionThomasWorried.png");
		actorText("Thomas", 472.f, 307.f, 1.f, 1.f);

		HilmaLvl1BeginningPart8.stop();
		if (!mLineStarted && ThomasLvl1Part4.getStatus() != 2)
		{
			ThomasLvl1Part4.play();
			mLineStarted = true;
		}
		if (mLineStarted && ThomasLvl1Part4.getStatus() == 0)
		{
			mLineStarted = false;
			setState();
		}
	}
	if (mState == 15)
	{
		advancedText(level1StartHilma9, 100.f, 420.f, 1.f, 1.f);
		drawFirstCharacter(mHandler, 300.f, 30.f, 1.f, 1.f, -0.2f, 0.2f, "expressionHilmaConfident.png");
		actorText("Hilma", 480.f, 307.f, 1.f, 1.f);

		ThomasLvl1Part4.stop();
		if (!mLineStarted && HilmaLvl1BeginningPart9.getStatus() != 2)
		{
			HilmaLvl1BeginningPart9.play();
			mLineStarted = true;
		}
		if (mLineStarted && HilmaLvl1BeginningPart9.getStatus() == 0)
		{
			mLineStarted = false;
			setState();
		}
	}
	if (mState == 16)
	{
		advancedText(level1StartThomas5, 100.f, 420.f, 1.f, 1.f);
		drawSecondCharacter(mHandler, 700.f, 30.f, 1.f, 1.f, 0.2f, 0.2f, "expressionThomasThoughtful.png");
		actorText("Thomas", 472.f, 307.f, 1.f, 1.f);

		HilmaLvl1BeginningPart9.stop();
		if (!mLineStarted && ThomasLvl1Part5.getStatus() != 2)
		{
			ThomasLvl1Part5.play();
			mLineStarted = true;
		}
		if (mLineStarted && ThomasLvl1Part5.getStatus() == 0)
		{
			mLineStarted = false;
			setState();
		}
	}
	if (mState == 17)
	{
		advancedText(level1StartHilma10, 100.f, 420.f, 1.f, 1.f);
		drawFirstCharacter(mHandler, 300.f, 30.f, 1.f, 1.f, -0.2f, 0.2f, "expressionHilmaDetermined.png");
		actorText("Hilma", 480.f, 307.f, 1.f, 1.f);

		ThomasLvl1Part5.stop();
		if (!mLineStarted && HilmaLvl1BeginningPart10.getStatus() != 2)
		{
			HilmaLvl1BeginningPart10.play();
			mLineStarted = true;
		}
		if (mLineStarted && HilmaLvl1BeginningPart10.getStatus() == 0)
		{
			mLineStarted = false;
			setState();
		}
	}
	if (mState == 18)
	{
		advancedText(level1StartThomas6, 100.f, 420.f, 1.f, 1.f);
		drawSecondCharacter(mHandler, 700.f, 30.f, 1.f, 1.f, 0.2f, 0.2f, "expressionThomasWorried.png");
		actorText("Thomas", 472.f, 307.f, 1.f, 1.f);

		HilmaLvl1BeginningPart10.stop();
		if (!mLineStarted && ThomasLvl1Part6.getStatus() != 2)
		{
			ThomasLvl1Part6.play();
			mLineStarted = true;
		}
		if (mLineStarted && ThomasLvl1Part6.getStatus() == 0)
		{
			mLineStarted = false;
			setState();
		}
	}
	if (mState == 19)
	{
		advancedText(level1StartHilma11, 100.f, 420.f, 1.f, 1.f);
		actorText("Hilma", 480.f, 307.f, 1.f, 1.f);

		ThomasLvl1Part6.stop();
		if (!mLineStarted && HilmaLvl1BeginningPart11.getStatus() != 2)
		{
			HilmaLvl1BeginningPart11.play();
			mLineStarted = true;
		}
		if (mLineStarted && HilmaLvl1BeginningPart11.getStatus() == 0)
		{
			mLineStarted = false;
			setState();
		}
	}
	if (mState == 20)
	{
		advancedText(level1StartHilma12, 100.f, 420.f, 1.f, 1.f);
		drawFirstCharacter(mHandler, 300.f, 30.f, 1.f, 1.f, -0.2f, 0.2f, "expressionHilmaSigh.png");
		actorText("Hilma", 480.f, 307.f, 1.f, 1.f);

		HilmaLvl1BeginningPart11.stop();
		if (!mLineStarted && HilmaLvl1BeginningPart12.getStatus() != 2)
		{
			HilmaLvl1BeginningPart12.play();
			mLineStarted = true;
		}
		if (mLineStarted && HilmaLvl1BeginningPart12.getStatus() == 0)
		{
			mLineStarted = false;
			setState();
		}
	}
	if (mState == 21)
	{
		advancedText(level1StartInterlude, 100.f, 420.f, 1.f, 1.f);
		drawSecondCharacter(mHandler, 700.f, 30.f, 1.f, 1.f, 0.2f, 0.2f, "expressionThomasSigh.png");
		actorText("Thomas", 472.f, 307.f, 1.f, 1.f);

		HilmaLvl1BeginningPart12.stop();
		//Only used to make autoskip in dialogue work
		HilmaLvl1BeginningPart10.setVolume(0);
		if (!mLineStarted && HilmaLvl1BeginningPart10.getStatus() != 2)
		{
			HilmaLvl1BeginningPart10.play();
			mLineStarted = true;
		}
		if (mLineStarted && HilmaLvl1BeginningPart10.getStatus() == 0)
		{
			mLineStarted = false;
			setState();
		}
	}
	if (mState == 22)
	{
		advancedText(level1StartHilma13, 100.f, 420.f, 1.f, 1.f);
		drawFirstCharacter(mHandler, 300.f, 30.f, 1.f, 1.f, -0.2f, 0.2f, "expressionHilmaHappy.png");
		actorText("Hilma", 480.f, 307.f, 1.f, 1.f);

		HilmaLvl1BeginningPart10.stop();
		if (!mLineStarted && HilmaLvl1BeginningPart13.getStatus() != 2)
		{
			HilmaLvl1BeginningPart13.play();
			mLineStarted = true;
		}
		if (mLineStarted && HilmaLvl1BeginningPart13.getStatus() == 0)
		{
			mLineStarted = false;
			setState();
		}
	}
	if (mState == 23)
	{
		advancedText(level1StartThomas7, 100.f, 420.f, 1.f, 1.f);
		drawSecondCharacter(mHandler, 700.f, 30.f, 1.f, 1.f, 0.2f, 0.2f, "expressionThomasBlush.png");
		actorText("Thomas", 472.f, 307.f, 1.f, 1.f);

		HilmaLvl1BeginningPart13.stop();
		if (!mLineStarted && ThomasLvl1Part7.getStatus() != 2)
		{
			ThomasLvl1Part7.play();
			mLineStarted = true;
		}
		if (mLineStarted && ThomasLvl1Part7.getStatus() == 0)
		{
			mLineStarted = false;
			setState();
		}
	}
	if (mState == 24)
	{
		advancedText(level1StartHilma14, 100.f, 420.f, 1.f, 1.f);
		drawFirstCharacter(mHandler, 300.f, 30.f, 1.f, 1.f, -0.2f, 0.2f, "expressionHilmaConfident.png");
		actorText("Hilma", 480.f, 307.f, 1.f, 1.f);

		ThomasLvl1Part7.stop();
		if (!mLineStarted && HilmaLvl1BeginningPart14.getStatus() != 2)
		{
			HilmaLvl1BeginningPart14.play();
			mLineStarted = true;
		}
		if (mLineStarted && HilmaLvl1BeginningPart14.getStatus() == 0)
		{
			mLineStarted = false;
			setState();
		}
	}
}

void DialogueSystem::displayLevel1EndAdvancedDialogue()
{
	std::string level1EndHilma = "H�r �r alla! Precis vad du bad om. Har jag �vertygat dig tillr�ckligt?";
	std::string level1EndTeller = "N�r Thomas fick syn p� alla f�rem�l kunde han inte tro sina �gon. Han som hade letat s� mycket sj�lv! Hans mamma hade sagt att n�r n�got f�rsvann i hans st�kiga rum, var det f�rsvunnet f�r alltid. Tydligen inte f�r en hittare.";
	std::string level1EndHilma2 = "Jag sa ju det! Jag hittar vad som helst, var som helst!";
	std::string level1EndTeller2 = "D� fick han ett litet, litet leende p� l�pparna och tackade s� mycket f�r Hilmas hj�lp. Men leendet f�rsvann snabbt n�r han s�g p� skruvmackap�ren.";
	std::string level1EndTeller3 = "Han blev alldeles tyst och stirrade p� den. Pl�tsligt kunde han inte bara ge den till den hj�lpsamma hittaren. Han h�ll h�rdare i skruvmackap�ren. Nu b�rjade Hilma bli lite ot�lig.";
	std::string level1EndHilma3 = "Hall�? Thomas? Jorden anropar!";
	std::string level1EndThomas = "F-f�rl�t jag... jag... Det �r bara det att det inte �r min skruvmackap�r jag ger dig.";
	std::string level1EndHilma4 = "Jaha ja, vems �r det d� om man f�r fr�ga? Har du stulit den?";
	std::string level1EndThomas2 = "N-nej! Absolut inte! Det... Jag l�nade den av min... mormor.";
	std::string level1EndHilma5 = "Din mormor? Vem �r denna tankspridda mormor som l�ter en slarvgosse som du ta hand om en s�dan fantastisk skruvmackap�r?";
	std::string level1EndThomas3 = "S�g inte s� om henne! Hon �r den b�sta mekanikern som n�gonsin funnits!";
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
		ThomasLvl1EndPart12.stop();
	}

	if (mState == 0)
	{
		mAdvancedIsActive = true;
		advancedText(level1EndHilma, 100.f, 420.f, 1.f, 1.f);
		drawFirstCharacter(mHandler, 300.f, 30.f, 1.f, 1.f, -0.2f, 0.2f, "expressionHilmaConfident.png");
		drawSecondCharacter(mHandler, 700.f, 30.f, 1.f, 1.f, 0.2f, 0.2f, "expressionThomasSurprised.png");
		createTextBox(-1.f, 280.f, 1.f, 1.f, 0.267f, 0.45f);
		actorText("Hilma", 480.f, 307.f, 1.f, 1.f);

		if (!mLineStarted && HilmaLvl1EndPart1.getStatus() != 2)
		{
			HilmaLvl1EndPart1.play();
			mLineStarted = true;
		}
		if (mLineStarted && HilmaLvl1EndPart1.getStatus() == 0)
		{
			mLineStarted = false;
			setState();
		}
	}
	if (mState == 1)
	{
		advancedText(level1EndTeller, 100.f, 420.f, 1.f, 1.f);
		actorText("Ber�ttare", 462.f, 307.f, 1.f, 1.f);

		HilmaLvl1EndPart1.stop();
		if (!mLineStarted && NarratorLvl1Part4.getStatus() != 2)
		{
			NarratorLvl1Part4.play();
			mLineStarted = true;
		}
		if (mLineStarted && NarratorLvl1Part4.getStatus() == 0)
		{
			mLineStarted = false;
			setState();
		}
	}
	if (mState == 2)
	{
		advancedText(level1EndHilma2, 100.f, 420.f, 1.f, 1.f);
		drawSecondCharacter(mHandler, 700.f, 30.f, 1.f, 1.f, 0.2f, 0.2f, "expressionThomasHappy.png");
		actorText("Hilma", 480.f, 307.f, 1.f, 1.f);

		NarratorLvl1Part4.stop();
		if (!mLineStarted && HilmaLvl1EndPart2.getStatus() != 2)
		{
			HilmaLvl1EndPart2.play();
			mLineStarted = true;
		}
		if (mLineStarted && HilmaLvl1EndPart2.getStatus() == 0)
		{
			mLineStarted = false;
			setState();
		}
	}
	if (mState == 3)
	{
		advancedText(level1EndTeller2, 100.f, 420.f, 1.f, 1.f);
		drawSecondCharacter(mHandler, 700.f, 30.f, 1.f, 1.f, 0.2f, 0.2f, "expressionThomasSad.png");
		actorText("Ber�ttare", 462.f, 307.f, 1.f, 1.f);

		HilmaLvl1EndPart2.stop();
		if (!mLineStarted && NarratorLvl1Part5.getStatus() != 2)
		{
			NarratorLvl1Part5.play();
			mLineStarted = true;
		}
		if (mLineStarted && NarratorLvl1Part5.getStatus() == 0)
		{
			mLineStarted = false;
			setState();
		}
	}
	if (mState == 4)
	{
		advancedText(level1EndTeller3, 100.f, 420.f, 1.f, 1.f);

		NarratorLvl1Part5.stop();
		if (!mLineStarted && NarratorLvl1Part6.getStatus() != 2)
		{
			NarratorLvl1Part6.play();
			mLineStarted = true;
		}
		if (mLineStarted && NarratorLvl1Part6.getStatus() == 0)
		{
			mLineStarted = false;
			setState();
		}
	}
	if (mState == 5)
	{
		advancedText(level1EndHilma3, 100.f, 420.f, 1.f, 1.f);
		drawFirstCharacter(mHandler, 300.f, 30.f, 1.f, 1.f, -0.2f, 0.2f, "expressionHilmaGrumpy.png");
		actorText("Hilma", 480.f, 307.f, 1.f, 1.f);

		NarratorLvl1Part6.stop();
		if (!mLineStarted && HilmaLvl1EndPart3.getStatus() != 2)
		{
			HilmaLvl1EndPart3.play();
			mLineStarted = true;
		}
		if (mLineStarted && HilmaLvl1EndPart3.getStatus() == 0)
		{
			mLineStarted = false;
			setState();
		}
	}
	if (mState == 6)
	{
		advancedText(level1EndThomas, 100.f, 420.f, 1.f, 1.f);
		actorText("Thomas", 472.f, 307.f, 1.f, 1.f);

		HilmaLvl1EndPart3.stop();
		if (!mLineStarted && ThomasLvl1EndPart1.getStatus() != 2)
		{
			ThomasLvl1EndPart1.play();
			mLineStarted = true;
		}
		if (mLineStarted && ThomasLvl1EndPart1.getStatus() == 0)
		{
			mLineStarted = false;
			setState();
		}
	}
	if (mState == 7)
	{
		advancedText(level1EndHilma4, 100.f, 420.f, 1.f, 1.f);
		actorText("Hilma", 480.f, 307.f, 1.f, 1.f);

		ThomasLvl1EndPart1.stop();
		if (!mLineStarted && HilmaLvl1EndPart4.getStatus() != 2)
		{
			HilmaLvl1EndPart4.play();
			mLineStarted = true;
		}
		if (mLineStarted && HilmaLvl1EndPart4.getStatus() == 0)
		{
			mLineStarted = false;
			setState();
		}
	}
	if (mState == 8)
	{
		advancedText(level1EndThomas2, 100.f, 420.f, 1.f, 1.f);
		drawSecondCharacter(mHandler, 700.f, 30.f, 1.f, 1.f, 0.2f, 0.2f, "expressionThomasWorried.png");
		actorText("Thomas", 472.f, 307.f, 1.f, 1.f);

		HilmaLvl1EndPart4.stop();
		if (!mLineStarted && ThomasLvl1EndPart2.getStatus() != 2)
		{
			ThomasLvl1EndPart2.play();
			mLineStarted = true;
		}
		if (mLineStarted && ThomasLvl1EndPart2.getStatus() == 0)
		{
			mLineStarted = false;
			setState();
		}
	}
	if (mState == 9)
	{
		advancedText(level1EndHilma5, 100.f, 420.f, 1.f, 1.f);
		actorText("Hilma", 480.f, 307.f, 1.f, 1.f);

		ThomasLvl1EndPart2.stop();
		if (!mLineStarted && HilmaLvl1EndPart5.getStatus() != 2)
		{
			HilmaLvl1EndPart5.play();
			mLineStarted = true;
		}
		if (mLineStarted && HilmaLvl1EndPart5.getStatus() == 0)
		{
			mLineStarted = false;
			setState();
		}
	}
	if (mState == 10)
	{
		advancedText(level1EndThomas3, 100.f, 420.f, 1.f, 1.f);
		drawSecondCharacter(mHandler, 700.f, 30.f, 1.f, 1.f, 0.2f, 0.2f, "expressionThomasDetermined.png");
		actorText("Thomas", 472.f, 307.f, 1.f, 1.f);

		if (!mLineStarted && ThomasLvl1EndPart3.getStatus() != 2)
		{
			ThomasLvl1EndPart3.play();
			mLineStarted = true;
		}
		if (mLineStarted && ThomasLvl1EndPart3.getStatus() == 0)
		{
			mLineStarted = false;
			setState();
		}
	}
	if (mState == 11)
	{
		advancedText(level1EndHilma6, 100.f, 420.f, 1.f, 1.f);
		drawFirstCharacter(mHandler, 300.f, 30.f, 1.f, 1.f, -0.2f, 0.2f, "expressionHilmaThoughtful.png");
		actorText("Hilma", 480.f, 307.f, 1.f, 1.f);

		ThomasLvl1EndPart3.stop();
		if (!mLineStarted && HilmaLvl1EndPart6.getStatus() != 2)
		{
			HilmaLvl1EndPart6.play();
			mLineStarted = true;
		}
		if (mLineStarted && HilmaLvl1EndPart6.getStatus() == 0)
		{
			mLineStarted = false;
			setState();
		}
	}
	if (mState == 12)
	{
		advancedText(level1EndThomas4, 100.f, 420.f, 1.f, 1.f);
		drawSecondCharacter(mHandler, 700.f, 30.f, 1.f, 1.f, 0.2f, 0.2f, "expressionThomasHappy.png");
		actorText("Thomas", 472.f, 307.f, 1.f, 1.f);

		HilmaLvl1EndPart6.stop();
		if (!mLineStarted && ThomasLvl1EndPart4.getStatus() != 2)
		{
			ThomasLvl1EndPart4.play();
			mLineStarted = true;
		}
		if (mLineStarted && ThomasLvl1EndPart4.getStatus() == 0)
		{
			mLineStarted = false;
			setState();
		}
	}
	if (mState == 13)
	{
		advancedText(level1EndThomas5, 100.f, 420.f, 1.f, 1.f);
		drawSecondCharacter(mHandler, 700.f, 30.f, 1.f, 1.f, 0.2f, 0.2f, "expressionThomasSad.png");

		ThomasLvl1EndPart4.stop();
		if (!mLineStarted && ThomasLvl1EndPart5.getStatus() != 2)
		{
			ThomasLvl1EndPart5.play();
			mLineStarted = true;
		}
		if (mLineStarted && ThomasLvl1EndPart5.getStatus() == 0)
		{
			mLineStarted = false;
			setState();
		}
	}
	if (mState == 14)
	{
		advancedText(level1EndHilma7, 100.f, 420.f, 1.f, 1.f);
		actorText("Hilma", 480.f, 307.f, 1.f, 1.f);

		ThomasLvl1EndPart5.stop();
		if (!mLineStarted && HilmaLvl1EndPart7.getStatus() != 2)
		{
			HilmaLvl1EndPart7.play();
			mLineStarted = true;
		}
		if (mLineStarted && HilmaLvl1EndPart7.getStatus() == 0)
		{
			mLineStarted = false;
			setState();
		}
	}
	if (mState == 15)
	{
		advancedText(level1EndThomas6, 100.f, 420.f, 1.f, 1.f);
		drawSecondCharacter(mHandler, 700.f, 30.f, 1.f, 1.f, 0.2f, 0.2f, "expressionThomasDetermined.png");
		actorText("Thomas", 472.f, 307.f, 1.f, 1.f);

		HilmaLvl1EndPart7.stop();
		if (!mLineStarted && ThomasLvl1EndPart6.getStatus() != 2)
		{
			ThomasLvl1EndPart6.play();
			mLineStarted = true;
		}
		if (mLineStarted && ThomasLvl1EndPart6.getStatus() == 0)
		{
			mLineStarted = false;
			setState();
		}
	}
	if (mState == 16)
	{
		advancedText(level1EndThomas7, 100.f, 420.f, 1.f, 1.f);
		drawSecondCharacter(mHandler, 700.f, 30.f, 1.f, 1.f, 0.2f, 0.2f, "expressionThomasCry.png");

		ThomasLvl1EndPart6.stop();
		if (!mLineStarted && ThomasLvl1EndPart7.getStatus() != 2)
		{
			ThomasLvl1EndPart7.play();
			mLineStarted = true;
		}
		if (mLineStarted && ThomasLvl1EndPart7.getStatus() == 0)
		{
			mLineStarted = false;
			setState();
		}
	}
	if (mState == 17)
	{
		advancedText(level1EndTeller4, 100.f, 420.f, 1.f, 1.f);
		drawFirstCharacter(mHandler, 300.f, 30.f, 1.f, 1.f, -0.2f, 0.2f, "expressionHilmaSigh.png");
		actorText("Ber�ttare", 462.f, 307.f, 1.f, 1.f);

		ThomasLvl1EndPart7.stop();
		if (!mLineStarted && NarratorLvl1Part7.getStatus() != 2)
		{
			NarratorLvl1Part7.play();
			mLineStarted = true;
		}
		if (mLineStarted && NarratorLvl1Part7.getStatus() == 0)
		{
			mLineStarted = false;
			setState();
		}
	}
	if (mState == 18)
	{
		advancedText(level1EndHilma8, 100.f, 420.f, 1.f, 1.f);
		drawFirstCharacter(mHandler, 300.f, 30.f, 1.f, 1.f, -0.2f, 0.2f, "expressionHilmaThoughtful.png");
		actorText("Hilma", 480.f, 307.f, 1.f, 1.f);

		NarratorLvl1Part7.stop();
		if (!mLineStarted && HilmaLvl1EndPart8.getStatus() != 2)
		{
			HilmaLvl1EndPart8.play();
			mLineStarted = true;
		}
		if (mLineStarted && HilmaLvl1EndPart8.getStatus() == 0)
		{
			mLineStarted = false;
			setState();
		}
	}
	if (mState == 19)
	{
		advancedText(level1EndThomas8, 100.f, 420.f, 1.f, 1.f);
		drawSecondCharacter(mHandler, 700.f, 30.f, 1.f, 1.f, 0.2f, 0.2f, "expressionThomasSad.png");
		actorText("Thomas", 472.f, 307.f, 1.f, 1.f);

		HilmaLvl1EndPart8.stop();
		if (!mLineStarted && ThomasLvl1EndPart8.getStatus() != 2)
		{
			ThomasLvl1EndPart8.play();
			mLineStarted = true;
		}
		if (mLineStarted && ThomasLvl1EndPart8.getStatus() == 0)
		{
			mLineStarted = false;
			setState();
		}
	}
	if (mState == 20)
	{
		advancedText(level1EndHilma9, 100.f, 420.f, 1.f, 1.f);
		drawFirstCharacter(mHandler, 300.f, 30.f, 1.f, 1.f, -0.2f, 0.2f, "expressionHilmaHappy.png");
		actorText("Hilma", 480.f, 307.f, 1.f, 1.f);

		ThomasLvl1EndPart8.stop();
		if (!mLineStarted && HilmaLvl1EndPart9.getStatus() != 2)
		{
			HilmaLvl1EndPart9.play();
			mLineStarted = true;
		}
		if (mLineStarted && HilmaLvl1EndPart9.getStatus() == 0)
		{
			mLineStarted = false;
			setState();
		}
	}
	if (mState == 21)
	{
		advancedText(level1EndThomas9, 100.f, 420.f, 1.f, 1.f);
		drawSecondCharacter(mHandler, 700.f, 30.f, 1.f, 1.f, 0.2f, 0.2f, "expressionThomasWorried.png");
		actorText("Thomas", 472.f, 307.f, 1.f, 1.f);

		HilmaLvl1EndPart9.stop();
		if (!mLineStarted && ThomasLvl1EndPart9.getStatus() != 2)
		{
			ThomasLvl1EndPart9.play();
			mLineStarted = true;
		}
		if (mLineStarted && ThomasLvl1EndPart9.getStatus() == 0)
		{
			mLineStarted = false;
			setState();
		}
	}
	if (mState == 22)
	{
		advancedText(level1EndHilma10, 100.f, 420.f, 1.f, 1.f);
		drawFirstCharacter(mHandler, 300.f, 30.f, 1.f, 1.f, -0.2f, 0.2f, "expressionHilmaConfident.png");
		actorText("Hilma", 480.f, 307.f, 1.f, 1.f);

		ThomasLvl1EndPart9.stop();
		if (!mLineStarted && HilmaLvl1EndPart10.getStatus() != 2)
		{
			HilmaLvl1EndPart10.play();
			mLineStarted = true;
		}
		if (mLineStarted && HilmaLvl1EndPart10.getStatus() == 0)
		{
			mLineStarted = false;
			setState();
		}
	}
	if (mState == 23)
	{
		advancedText(level1EndTeller5, 100.f, 420.f, 1.f, 1.f);
		actorText("Ber�ttare", 462.f, 307.f, 1.f, 1.f);

		HilmaLvl1EndPart10.stop();
		if (!mLineStarted && NarratorLvl1Part8.getStatus() != 2)
		{
			NarratorLvl1Part8.play();
			mLineStarted = true;
		}
		if (mLineStarted && NarratorLvl1Part8.getStatus() == 0)
		{
			mLineStarted = false;
			setState();
		}
	}
	if (mState == 24)
	{
		advancedText(level1EndThomas10, 100.f, 420.f, 1.f, 1.f);
		drawSecondCharacter(mHandler, 700.f, 30.f, 1.f, 1.f, 0.2f, 0.2f, "expressionThomasSurprised.png");
		actorText("Thomas", 472.f, 307.f, 1.f, 1.f);

		NarratorLvl1Part8.stop();
		if (!mLineStarted && ThomasLvl1EndPart10.getStatus() != 2)
		{
			ThomasLvl1EndPart10.play();
			mLineStarted = true;
		}
		if (mLineStarted && ThomasLvl1EndPart10.getStatus() == 0)
		{
			mLineStarted = false;
			setState();
		}
	}
	if (mState == 25)
	{
		advancedText(level1EndHilma11, 100.f, 420.f, 1.f, 1.f);
		drawFirstCharacter(mHandler, 300.f, 30.f, 1.f, 1.f, -0.2f, 0.2f, "expressionHilmaDetermined.png");
		actorText("Hilma", 480.f, 307.f, 1.f, 1.f);

		ThomasLvl1EndPart10.stop();
		if (!mLineStarted && HilmaLvl1EndPart11.getStatus() != 2)
		{
			HilmaLvl1EndPart11.play();
			mLineStarted = true;
		}
		if (mLineStarted && HilmaLvl1EndPart11.getStatus() == 0)
		{
			mLineStarted = false;
			setState();
		}
	}
	if (mState == 26)
	{
		advancedText(level1EndThomas11, 100.f, 420.f, 1.f, 1.f);
		drawSecondCharacter(mHandler, 700.f, 30.f, 1.f, 1.f, 0.2f, 0.2f, "expressionThomasWorried.png");
		actorText("Thomas", 472.f, 307.f, 1.f, 1.f);

		HilmaLvl1EndPart11.stop();
		if (!mLineStarted && ThomasLvl1EndPart11.getStatus() != 2)
		{
			ThomasLvl1EndPart11.play();
			mLineStarted = true;
		}
		if (mLineStarted && ThomasLvl1EndPart11.getStatus() == 0)
		{
			mLineStarted = false;
			setState();
		}
	}
	if (mState == 27)
	{
		advancedText(level1EndHilma12, 100.f, 420.f, 1.f, 1.f);
		drawFirstCharacter(mHandler, 300.f, 30.f, 1.f, 1.f, -0.2f, 0.2f, "expressionHilmaConfident.png");
		actorText("Hilma", 480.f, 307.f, 1.f, 1.f);

		ThomasLvl1EndPart11.stop();
		if (!mLineStarted && HilmaLvl1EndPart12.getStatus() != 2)
		{
			HilmaLvl1EndPart12.play();
			mLineStarted = true;
		}
		if (mLineStarted && HilmaLvl1EndPart12.getStatus() == 0)
		{
			mLineStarted = false;
			setState();
		}
	}
	if (mState == 28)
	{
		advancedText(level1EndTeller6, 100.f, 420.f, 1.f, 1.f);
		drawSecondCharacter(mHandler, 700.f, 30.f, 1.f, 1.f, 0.2f, 0.2f, "expressionThomasHappy.png");
		actorText("Ber�ttare", 462.f, 307.f, 1.f, 1.f);

		HilmaLvl1EndPart12.stop();
		if (!mLineStarted && NarratorLvl1Part9.getStatus() != 2)
		{
			NarratorLvl1Part9.play();
			mLineStarted = true;
		}
		if (mLineStarted && NarratorLvl1Part9.getStatus() == 0)
		{
			mLineStarted = false;
			setState();
		}
	}
	if (mState == 29)
	{
		advancedText(level1EndThomas12, 100.f, 420.f, 1.f, 1.f);
		actorText("Thomas", 472.f, 307.f, 1.f, 1.f);

		NarratorLvl1Part9.stop();
		if (!mLineStarted && ThomasLvl1EndPart12.getStatus() != 2)
		{
			ThomasLvl1EndPart12.play();
			mLineStarted = true;
		}
		if (mLineStarted && ThomasLvl1EndPart12.getStatus() == 0)
		{
			mLineStarted = false;
			setState();
		}
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

//Level3

void DialogueSystem::displayLevel3StartAdvancedDialogue()
{
	std::string level3StartHilma = "D�r! Skatan fl�g in i skjulet! Thomas, skynda p�, vi m�ste f�lja efter den!";
	std::string level3StartThomas = "V�nta Hilma, du kan inte bara springa in. Det h�r �r Surtantens tr�dg�rd!";
	std::string level3StartHilma2 = "Surtanten?";
	std::string level3StartThomas2 = "Det �r vad alla kallar henne. Hon �r alltid h�r i hennes tr�dg�rd och planterar och pysslar. Hon HATAR n�r ungar leker i den.";
	std::string level3StartThomas3 = "En g�ng skj�t jag och mormor upp en modellraket som fl�g j�tteh�gt!";
	std::string level3StartThomas4 = "Men s� exploderade den och f�rst�rde Surtantens tr�dg�rd. Sedan dess �r vi bannlysta h�rifr�n...";
	std::string level3StartHilma3 = "L�ter som hon hade en bra anledning.";
	std::string level3StartThomas5 = "Vi bad om urs�kt j�ttem�nga g�nger! Mormor bakade henne till och med en kaka men den...";
	std::string level3StartHilma4 = "V�nta! Tyst! H�r du det d�r Thomas?";
	std::string level3StartSurtanten = "Muttranden";
	std::string level3StartThomas6 = "�h nej! Hon �r h�r!";
	std::string level3StartHilma5 = "Ser ut som att vi f�r smyga f�rbi henne d�, borde vara l�tt f�r n�gon i min storlek!";
	std::string level3StartThomas7 = "Kanske det, s� l�nge hennes hund inte m�rker dig�";
	std::string level3StartHilma6 = "Hund? Det sa du inget om! Jag har inget till �vers f�r s�na stora bestar!";
	std::string level3StartThomas8 = "Vi kanske kan hitta ett s�tt att f� bort den... �h just det, det bor ocks� bin i tr�dg�rden.";
	std::string level3StartHilma7 = "L�t mig gissa, bina bor utanf�r skjulet?";
	std::string level3StartThomas9 = "Jag... jag har f�r mig det.";
	std::string level3StartHilma8 = "Typiskt, just d�r ing�ngen �r...";
	std::string level3StartHilma9 = "Vi har inget val, vi m�ste f� tag i det d�r fickuret! Kom Thomas, nu g�r vi det h�r.";

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
	std::string level3ShedThomas = "Wow! Jag trodde aldrig vi skulle ta oss f�rbi!";
	std::string level3ShedHilma = "Du borde lita mer p� mig Thomas! Varken vidunder eller ilskna bin kan st� i min v�g!";
	std::string level3ShedThomas2 = "S� hur tar vi oss till Hittarnas V�rld?";
	std::string level3ShedHilma2 = "Tyv�rr Thomas. Du �r f�r stor f�r att f� plats d�r nere. H�rifr�n m�ste jag forts�tta ensam.";
	std::string level3ShedThomas3 = "Men...";
	std::string level3ShedHilma3 = "Det �r okej, jag �r tillbaka p� nolltid och med fickuret i hand! Dessutom beh�ver jag n�gon som kan st� vakt, s� att inte hunden eller bina kommer tillbaka.";
	std::string level3ShedThomas4 = "Okej, men om du ser n�t h�ftigt kom ih�g att ber�tta det f�r mig sen!";
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
	std::string level3Skatmaran1Hilma = "H�rru du din tjuv! Ge tillbaka det du stulit!";
	std::string level3Skatmaran1Skatmaran = "Vem �r det som skriker h�r? Och vem anklagar mig f�r att vara en tjuv?";
	std::string level3Skatmaran1Skatmaran2 = "Hilma? �r det du som st�r h�r och gormar?";
	std::string level3Skatmaran1Hilma2 = "Klart det �r jag din h�nshj�rna! N�gon m�ste komma och s�ga till n�r dina skator �r ute och stj�l fr�n hederligt folk!";
	std::string level3Skatmaran1Skatmaran3 = "Vad �r det h�r f�r hemska anklagelser? Hur v�gar du p�sta att jag, Skatmaran, den fr�msta bland hittare, �r en tjuv?";
	std::string level3Skatmaran1Hilma3 = "Din dumma skata tog ett fickur fr�n m�nniskan jag hj�lper. Vi f�ljde den hela v�gen hit och alla vet att det skatorna stj�l h�romkring hamnar i dina h�nder.";
	std::string level3Skatmaran1Skatmaran4 = "Det st�mmer v�l och det st�mmer att en av mina skator nyss d�k upp med ett vackert fickur. Men mina skator �r tr�nade att aldrig stj�la, det du p�st�r �r om�jligt.";
	std::string level3Skatmaran1Hilma4 = "Om�jligt? Jag s�g det ju h�nda med mina egna �gon! En m�nniska och Tapparen Putte s�g det med!";
	std::string level3Skatmaran1Skatmaran5 = "Den d�r tapparen kan ha sett vad som helst, hans ord �r lika goda som den m�nniskans. Och du vet att vi inte lyssnar p� m�nniskor.";
	std::string level3Skatmaran1Hilma5 = "";
	std::string level3Skatmaran1Skatmaran6 = "Det HAR h�nt att mina skator tagit saker fr�n n�gon som inte tillh�rt dem. Var det m�nniskans fickur?";
	std::string level3Skatmaran1Hilma6 = "Nej... det var hans mormors.";
	std::string level3Skatmaran1Skatmaran7 = "Aha! D� �r det ju knappast stulet! Och den h�r mormorn, letar hon efter sitt fickur?";
	std::string level3Skatmaran1Hilma7 = "Nej hon �r f�rsvunnen och det d�r fickuret �r en ledtr�d som kan hj�lpa mig hitta henne!";
	std::string level3Skatmaran1Skatmaran8 = "Reglerna s�ger att jag bara m�ste ge bort f�rem�l till personen som �ger det. Om den h�r mormor nu �r f�rsvunnen spelar det ju ingen roll om fickuret �r borttappat eller i mina h�nder!";
	std::string level3Skatmaran1Hilma8 = "Lyssna h�r din fj�derskalle, jag m�ste ha det d�r fickuret och du kommer att ge det till mig.";
	std::string level3Skatmaran1Skatmaran9 = "Inte d�! Det �r en av de finaste skatterna jag n�gonsin hittat! Dessutom hj�lper den mig att h�lla koll p� tiden f�r min bokf�ring.";
	std::string level3Skatmaran1Skatmaran10 = "Enda anledningen till att jag skulle ge den till dig �r om du ger mig n�got annat jag vill ha mer.";
	std::string level3Skatmaran1Hilma9 = "Jaha? Vad d� f�r n�t?";
	std::string level3Skatmaran1Skatmaran11 = "Jag vet till exempel att hon d�r borta har en mycket fin brosch jag l�nge haft �gonen p�.";
	std::string level3Skatmaran1Hilma10 = "Va? Vill du att jag g�r och stj�l �t dig nu f�r att f� tillbaka n�got du stulit?";
	std::string level3Skatmaran1Skatmaran12 = "Jag har inte sagt n�gonting om att stj�la. Hur du f�r tag i den �r din ensak.";
	std::string level3Skatmaran1Hilma11 = "Okej d�, jag g�r och fr�gar om det finns n�gonting jag kan g�ra f�r att f� den. Men det �r b�st f�r dig att du h�ller ditt l�fte.";
	std::string level3Skatmaran1Skatmaran13 = "Har jag n�gonsin ljugit f�r dig?";
	std::string level3Skatmaran1Hilma12 = "Flera g�nger.";
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
	std::string level5StartTeller = "Efter att ha cyklat i full fart kom de till slut fram till skogens hj�rta. D�r stod ett stort, gammalt hus. Tomten var alldeles igenvuxen med vildblomster och huset s�g �vergivet ut. Kunde mormor verkligen vara h�r?";
	std::string level5StartHilma = "Det ser ju st�dat ut h�r inne.";
	std::string level5StartThomas = "Tror du kanske att...";
	std::string level5StartHilma2 = "Ja, hon m�ste vara h�r, Thomas.";
	std::string level5StartTeller2 = "Det klappade till i Thomas hj�rta. Hon var h�r, det var han s�ker p�. Thomas kunde knappt h�lla inne sin lycka.";
	std::string level5StartThomas2 = "Vad v�ntar vi p�! Kom s� hittar vi henne! Hon skrev i brevet att hon skulle se kometen idag; hon borde vara p� �verv�ningen!";
	std::string level5StartHilma3 = "Jag tror jag s�g en balkong f�rut, hon kanske �r d�r?";

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
		actorText("Ber�ttare", 462.f, 307.f, 1.f, 1.f);
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
		actorText("Ber�ttare", 462.f, 307.f, 1.f, 1.f);
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
	std::string level5ClosedTeller = "G�ng p� g�ng knackade Thomas p� d�rren i hopp om att mormor skulle h�ra. Men de fick inget svar.";
	std::string level5ClosedHilma = "Hm� Detta var v�ldigt m�rkligt. L�st? Varf�r �r det l�st om hon vill tr�ffa oss? Det h�r g�r verkligen inte ihop!";
	std::string level5ClosedThomas = "Mormor kanske st�ngde av h�rapparaten? Hon brukade i alla fall g�ra det n�r hon inte ville bli st�rd eller om surtanten kom och knackade p�.";
	std::string level5ClosedHilma2 = "Hmph! gamla m�nniskor� Men det f�rklarar fortfarande inte varf�r d�rren �r l�st!";
	std::string level5ClosedThomas2 = "Jag vet inte,  ibland brukar d�rrar l�sas av sig sj�lva n�r man st�nger dem. Hon l�ste s�kert ut sig sj�lv och har inte m�rkt det. Och nu h�r hon oss inte f�r att h�rapparaten �r avst�ngd.";
	std::string level5ClosedThomas3 = "Vi m�ste hitta ett s�tt att l�sa upp d�rren!";
	std::string level5ClosedHilma3 = "Jag har f�tt nog av l�sta d�rrar f�r idag...";
	std::string level5ClosedTeller2 = "Hilma och Thomas f�rs�kte t�nka ut hur de skulle kunna l�sa upp d�rren. De hade ingen nyckel och hon s�g inget kryph�l eller annat s�tt att ta sig f�rbi den. Men d� h�rde de pl�tsligt en r�st. Det var n�gon de k�nde igen.";

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
		actorText("Ber�ttare", 462.f, 307.f, 1.f, 1.f);
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
		actorText("Ber�ttare", 462.f, 307.f, 1.f, 1.f);
	}
}
//Saknar Putte, fel expressions
void DialogueSystem::displayLevel5Putte2AdvancedDialogue()
{
	std::string level5ReunionPutte = "Lisa! Totte! Var �r ni? �h vart har ni tagit v�gen? Det h�r kan inte vara sant...";
	std::string level5ReunionHilma = "Vad �r det nu d� Putte? Hur kommer det sig att du alltid �r d�r vi �r? F�ljer du efter oss eller?";
	std::string level5ReunionThomas = "Vad har h�nt Putte?";
	std::string level5ReunionPutte2 = "Jag �r s� v�rdel�s...Jag �r Tapparen Putte� som inte ens kan h�lla reda p� sina egna barn.";
	std::string level5ReunionThomas2 = "Har du barn?";
	std::string level5ReunionHilma2 = "�h nej, tv� Putte till...";
	std::string level5ReunionPutte3 = "Ja� Lisa och Totte heter dem. Jag vet inte hur m�nga g�nger jag har sagt �t dem att ta det f�rsiktigt... Och nu... nu �r de borta...";
	std::string level5ReunionTeller = "Bakom Putte kom en annan hittare fram och la en tr�stande hand p� hans axel. Denna hittare hade en sjal ist�llet f�r en m�ssa och var kl�dd i solens f�rger.";
	std::string level5ReunionLillemor = "S�ja, Puttinutten, var inte orolig! De �r s�kert n�gonstans p� nederv�ningen och leker. Kanske har de hittat ett nytt g�mst�lle? Du vet ju vilka duktiga hittare de �r!";
	std::string level5ReunionHilma3 = "Puttinutten?";
	std::string level5ReunionPutte4 = "Men t�nk om katten har tagit dem! Eller om de har fastnat i r�ttf�llan? Eller blivit tagna av f�glarna? Ack! Jag kan inte ens h�lla reda p� mina barn�";
	std::string level5ReunionPutte5 = "Jag �r den s�msta hittaren n�gonsin...";
	std::string level5ReunionLillemor2 = "Men �lskade v�n. Nog kan du vara slarvig, men inte den s�msta! De kommer s�kert tillbaka snart. Du m�ste l�ta dem breda ut sina vingar!";
	std::string level5ReunionPutte6 = "";
	std::string level5ReunionThomas3 = "Du Hilma, jag tror vi borde hj�lpa honom att hitta sina barn.";
	std::string level5ReunionHilma4 = "Borde och borde? Vi m�ste v�l om han ska sluta gr�ta n�gon g�ng det h�r �rhundradet! H�rrudu Putte!";
	std::string level5ReunionHilma5 = "Vi hj�lper dig, men det h�r �r sista g�ngen!";
	std::string level5ReunionPutte7 = "Verkligen?";
	std::string level5ReunionTeller2 = "Putte blev �verlycklig och kramade om Hilma s� h�rt att hon n�stan h�ll p� att kv�vas. Hon slet sig ifr�n hans famn och ramlade bakl�nges ner i Thomas hand.";
	std::string level5ReunionLillemor3 = "Tack att ni hj�lper min el�ndiga make! Han brukar bli v�ldigt orolig f�r v�ra barn. Jag har sagt �t honom flera g�nger att de m�ste f� leka sj�lva och l�ra sig om livet. Men vad jag �n s�ger kan han inte sluta oroa sig �ver dem. ";
	std::string level5ReunionLillemor4 = "Lillemor heter jag f�rresten! Och ni gissar jag �r Hilma och Thomas? Putte har pratat s� mycket om er tv� sedan han tr�ffade er.";
	std::string level5ReunionThomas4 = "Vi ska hitta dem, Lillemor! Det lovar vi!";
	std::string level5ReunionHilma6 = "Var brukar Lisa och Totte leka?";
	std::string level5ReunionLillemor5 = "De brukar ofta leka p� nederv�ningen. Kolla i vardagsrummet eller k�ket: de brukar h�lla till d�r!";
	std::string level5ReunionHilma7 = "D� s�! D� b�rjar vi leta d�r. Ah! just ja! Vet ni hur man �ppnar balkongd�rren?";
	std::string level5ReunionLillemor6 = "Jag vet inte riktigt i detalj, men ibland har jag sett en �ldre kvinna kl�ttra upp f�r en stege och s�tta upp konstiga bollar i taket f�r att �ppna balkongd�rren.";

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
		actorText("Ber�ttare", 462.f, 307.f, 1.f, 1.f);
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
		actorText("Ber�ttare", 462.f, 307.f, 1.f, 1.f);
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
	std::string level5SolarSystemHilma = "Varf�r h�nger det en massa bollar i taket?";
	std::string level5SolarSystemThomas = "Det �r planeterna i v�rt solsystem!";
	std::string level5SolarSystemHilma2 = "Planeter? Solsystem? Vad pratar du om?";
	std::string level5SolarSystemThomas2 = "Mormor ber�ttade en g�ng, att rymden �r J�TTESTOR. Och i rymden finns det massa stj�rnor, planeter och galaxer. Vissa har man hittat, men det finns fortfarande en massa som ingen har hittat �nnu!";
	std::string level5SolarSystemHilma3 = "Inte hittade? Heh, de skulle beh�va en hittare i rymden!";
	std::string level5SolarSystemThomas3 = "N�r jag blir astronaut kan du f� f�lja med och hj�lpa mig! Jag vet! Du kan ocks� bli astronaut!";
	std::string level5SolarSystemHilma4 = "En hittare som astronaut?";
	std::string level5SolarSystemHilma5 = "Ja du, det l�ter inte dumt. Men jag f�rst�r fortfarande inte det d�r med planeterna. Jag f�rst�r att man vill hitta dem f�r att de inte �r hittade, men vad mer? Vill man samla p� planeter? Vad f�r man i utbyte?";
	std::string level5SolarSystemThomas4 = "Hm� Mormor sa att planeter �r som olika hem. V�rt hem �r planeten jorden och �r den enda planeten i v�rt solsystem d�r man kan bo. Men det �r lite ensamt s� vi vill hitta andra planeter som ocks� har liv!";
	std::string level5SolarSystemHilma6 = "Jass� jaha ja, vilken planet �r jorden d�?";
	std::string level5SolarSystemThomas5 = "D�r...";
	std::string level5SolarSystemThomas6 = "Jorden �r inte med? Inte Mars,Venus, Pluto, och Saturnus heller! Det h�r �r j�ttekonstigt. Mormor skulle aldrig ha ett of�rdigt solsystem. Hon kan namnet p� alla planeter och till och med m�narna!";
	std::string level5SolarSystemHilma7 = "Ja du, Thomas, De kanske gick s�nder? Eller� har f�rsvunnit?";
	std::string level5SolarSystemThomas7 = "Jag vet! Vi f�rs�ker hitta dem och s�tta dem p� r�tt plats. D� blir mormor j�tteglad!";
	std::string level5SolarSystemHilma8 = "Se d�r Thomas! Det �r r�tta tankar! Du �r en riktig snilleblixt du!";

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
	std::string level5MouseHoleVoices = "N�gon skriker p� hj�lp.";
	std::string level5MouseHoleThomas = "Kan det d�r vara Lisa och Totte?";
	std::string level5MouseHoleHilma = "Definitivt! Och kattskr�llet har jagat in dem i mush�let! Vi m�ste locka bort den p� n�got vis.";

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
		actorText("R�ster", 480.f, 307.f, 1.f, 1.f);
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
	std::string level5VictoryHilma = "S� det �r ni som �r Lisa och Totte? Varf�r jagade katten efter er?";
	std::string level5VictoryLisa = "Vi lekte med tusse! Och, och, och sen, s� �ppnade den sin STORA MUN!! Den hade J�TTESTORA T�NDER och f�rs�kte �ta upp oss!";
	std::string level5VictoryTotte = "Tusse brukar annars vara sn�ll. Den var s�kert hungrig, f�r matsk�len �r tom.";
	std::string level5VictoryHilma2 = "N�ja, eran pappa har varit j�tteorolig f�r er. G� upp nu s� han slutar att b�la!";
	std::string level5VictoryLisa2 = "Ja ja tjatmaja! Vi lekte ju bara.";
	std::string level5VictoryTotte2 = "Tack f�r att ni hj�lpte oss. H�r, ni kan f� l�na v�ra leksaker!";

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
	std::string level5TogetherTeller = "Nu var Puttes familj tillsammans igen. Puttes kinder var alldeles v�ta av lyckot�rar. Han kramade om sina barn, n�stan h�rdare �n vad han kramade Hilma, och lovade att han aldrig skulle tappa bort dem igen.";
	std::string level5TogetherTotte = "Vi var aldrig borttappade pappa.";
	std::string level5TogetherLisa = "Pappa, pappa, pappa! Du skulle ha sett hur Hilma man�vrade den stora BESTEN!";
	std::string level5TogetherLillemor = "Tack f�r att ni hj�lpt Putte s� m�nga g�nger.";
	std::string level5TogetherHilma = "�sch, det var inget. Jag f�rst�r mig bara inte p� honom. Hur kan en hittare vara s� slarvig?";
	std::string level5TogetherThomas = "Men Hilma, han hittade faktiskt mormors guldklocka!";
	std::string level5TogetherLillemor2 = "Han m� vara klumpig och tappar bort saker. Men han k�mpar varje dag f�r att vara en bra hittare, en bra far, och en god man. Det han lyckas beh�lla bevarar han v�ldigt k�rt.";
	std::string level5TogetherLillemor3 = "H�r! Ni f�r denna mussla jag hittade i medelhavet f�r flera �r sedan. Det g�r inte att �ppna denna skatt som en vanlig skattkista. Bara d�r den k�nner sig som hemma �ppnar den upp sig.";
	std::string level5TogetherThomas2 = "Tack s� mycket, Lillemor!";
	std::string level5TogetherHilma2 = "Tja... tack.";
	std::string level5TogetherLillemor4 = "Inget att tacka f�r! Lycka till att hitta det ni s�ker!";

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
		actorText("Ber�ttare", 462.f, 307.f, 1.f, 1.f);
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
	std::string level5SolutionTeller = "N�r alla planeterna var p� plats h�rdes ett m�rkligt ljud. Det kom fr�n balkongsd�rren...";
	std::string level5SolutionThomas = "Hilma! Jag tror balkongd�rren �ppnades nu!";
	std::string level5SolutionTeller2 = "Sannerligen var det �ppet! De gick fram till balkongd�rren. Thomas h�ll i handtaget och tog ett djupt andetag.";
	std::string level5SolutionHilma = "Redo?";
	std::string level5SolutionThomas2 = "�Redo!";
	std::string level5SolutionTeller3 = "De �ppnade balkongd�rrarna...";

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
		actorText("Ber�ttare", 462.f, 307.f, 1.f, 1.f);
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
		actorText("Ber�ttare", 462.f, 307.f, 1.f, 1.f);
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
		actorText("Ber�ttare", 462.f, 307.f, 1.f, 1.f);
	}
}

void DialogueSystem::displayLevel5PaintingAdvancedDialogue()
{
	std::string level5PaintingThomas = "Wow... vilken vacker tavla.";
	std::string level5PaintingHilma = "Har mormor m�lat den?";
	std::string level5PaintingThomas2 = "Nej... mormor m�lar inte s� fint. Mormor har ber�ttat att man kan se i h�rnet p� tavlor vem som har m�lat. Det st�r� E-e-ez... Ez-i-o� Sen kan jag inte l�sa mer. Det var ett j�tte l�ngt och kr�ngligt efternamn.";
	std::string level5PaintingHilma2 = "Suck� M�nniskor kr�nglar alltid till sina namn...";

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
	std::string level5RecordsHilma = "Vad vacker hon �r p� bilden! Vad �r det f�r skiva?";
	std::string level5RecordsThomas = "Det �r en s�dan d�r j�ttegammal skiva med musik som min mormor brukade lyssna p� n�r hon var ung. Det finns j�ttem�nga s�na h�r skivor i bokhyllan.";
	std::string level5RecordsHilma2 = "Vad f�r musik?";
	std::string level5RecordsThomas2 = "J.-j-ag vet inte. Det st�r p� ett v�ldigt lustigt spr�k...";

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
	std::string level5DrawingsHilma = "�r det dina teckningar? Det ser i alla fall ut som barnteckningar.";
	std::string level5DrawingsThomas = "Nej... jag har aldrig sett de h�r teckningarna f�rut...";
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
void DialogueSystem::displayBooksDialogue()
{
	std::string booksHilma = "Hur m�nga b�cker har du egentligen?";
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
		actorText("Hilma", 480.f, 480.f, 1.f, 1.f);
		text(booksHilma, 225, 510, 0, 0);
		createTalkBubble(210, 470, 0, 0, 1.f, 0.25f);
	}
	if (mState == 1)
	{
		actorText("Thomas", 472.f, 480.f, 1.f, 1.f);
		text(booksThomas, 225, 510, 0, 0);
		createTalkBubble(210, 470, 0, 0, 1.f, 0.25f);
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
		actorText("Hilma", 480.f, 480.f, 1.f, 1.f);
		text(lampHilma, 225, 510, 0, 0);
		createTalkBubble(210, 470, 0, 0, 1.f, 0.25f);
	}

	if (mState == 1)
	{
		actorText("Thomas", 472.f, 480.f, 1.f, 1.f);
		text(lampThomas, 225, 510, 0, 0);
		createTalkBubble(210, 470, 0, 0, 1.f, 0.25f);
	}

	if (mState == 2)
	{
		actorText("Hilma", 480.f, 480.f, 1.f, 1.f);
		text(lampHilma2, 225, 510, 0, 0);
		createTalkBubble(210, 470, 0, 0, 1.f, 0.25f);
	}

	if (mState == 3)
	{
		actorText("Thomas", 472.f, 480.f, 1.f, 1.f);
		text(lampThomas2, 225, 510, 0, 0);
		createTalkBubble(210, 470, 0, 0, 1.f, 0.25f);
	}
	if (mState == 4)
	{
		actorText("Hilma", 480.f, 480.f, 1.f, 1.f);
		text(lampHilma3, 225, 510, 0, 0);
		createTalkBubble(210, 470, 0, 0, 1.f, 0.25f);
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
		actorText("Hilma", 480.f, 480.f, 1.f, 1.f);
		text(rubicHilma, 225, 510, 0, 0);
		createTalkBubble(210, 470, 0, 0, 1.f, 0.25f);
	}
	if (mState == 1)
	{
		actorText("Thomas", 472.f, 480.f, 1.f, 1.f);
		text(rubicThomas, 225, 510, 0, 0);
		createTalkBubble(210, 470, 0, 0, 1.f, 0.25f);
	}
	if (mState == 2)
	{
		actorText("Hilma", 480.f, 480.f, 1.f, 1.f);
		text(rubicHilma2, 225, 510, 0, 0);
		createTalkBubble(210, 470, 0, 0, 1.f, 0.25f);
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
		actorText("Hilma", 480.f, 480.f, 1.f, 1.f);
		text(posterHilma, 225, 510, 0, 0);
		createTalkBubble(210, 470, 0, 0, 1.f, 0.25f);
	}

	if (mState == 1)
	{
		actorText("Thomas", 472.f, 480.f, 1.f, 1.f);
		text(posterThomas, 225, 510, 0, 0);
		createTalkBubble(210, 470, 0, 0, 1.f, 0.25f);
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
		actorText("Hilma", 480.f, 480.f, 1.f, 1.f);
		text(backpackHilma, 225, 510, 0, 0);
		createTalkBubble(210, 470, 0, 0, 1.f, 0.25f);
	}

	if (mState == 1)
	{
		actorText("Thomas", 472.f, 480.f, 1.f, 1.f);
		text(backpackThomas, 225, 510, 0, 0);
		createTalkBubble(210, 470, 0, 0, 1.f, 0.25f);
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
		actorText("Hilma", 480.f, 480.f, 1.f, 1.f);
		text(bowlHilma, 225, 510, 0, 0);
		createTalkBubble(210, 470, 0, 0, 1.f, 0.25f);
	}

	if (mState == 1)
	{
		actorText("Thomas", 472.f, 480.f, 1.f, 1.f);
		text(bowlThomas, 225, 510, 0, 0);
		createTalkBubble(210, 470, 0, 0, 1.f, 0.25f);
	}

	if (mState == 2)
	{
		actorText("Hilma", 480.f, 480.f, 1.f, 1.f);
		text(bowlHilma2, 225, 510, 0, 0);
		createTalkBubble(210, 470, 0, 0, 1.f, 0.25f);
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
		actorText("Hilma", 480.f, 480.f, 1.f, 1.f);
		text(radioHilma, 225, 510, 0, 0);
		createTalkBubble(210, 470, 0, 0, 1.f, 0.25f);
	}

	if (mState == 1)
	{
		actorText("Thomas", 472.f, 480.f, 1.f, 1.f);
		text(radioThomas, 225, 510, 0, 0);
		createTalkBubble(210, 470, 0, 0, 1.f, 0.25f);
	}

	if (mState == 2)
	{
		actorText("Hilma", 480.f, 480.f, 1.f, 1.f);
		text(radioHilma2, 225, 510, 0, 0);
		createTalkBubble(210, 470, 0, 0, 1.f, 0.25f);
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
		actorText("Hilma", 480.f, 480.f, 1.f, 1.f);
		text(matHilma, 225, 510, 0, 0);
		createTalkBubble(210, 470, 0, 0, 1.f, 0.25f);
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
		actorText("Hilma", 480.f, 480.f, 1.f, 1.f);
		text(starHilma, 225, 510, 0, 0);
		createTalkBubble(210, 470, 0, 0, 1.f, 0.25f);
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
		actorText("Hilma", 480.f, 480.f, 1.f, 1.f);
		text(aquariumHilma, 225, 510, 0, 0);
		createTalkBubble(210, 470, 0, 0, 1.f, 0.25f);
	}

	if (mState == 1)
	{
		actorText("Thomas", 472.f, 480.f, 1.f, 1.f);
		text(aquariumThomas, 225, 510, 0, 0);
		createTalkBubble(210, 470, 0, 0, 1.f, 0.25f);
	}

	if (mState == 2)
	{
		actorText("Hilma", 480.f, 480.f, 1.f, 1.f);
		text(aquariumHilma2, 225, 510, 0, 0);
		createTalkBubble(210, 470, 0, 0, 1.f, 0.25f);
	}

	if (mState == 3)
	{
		actorText("Thomas", 472.f, 480.f, 1.f, 1.f);
		text(aquariumThomas2, 225, 510, 0, 0);
		createTalkBubble(210, 470, 0, 0, 1.f, 0.25f);
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
		actorText("Hilma", 480.f, 480.f, 1.f, 1.f);
		text(blockHilma, 225, 510, 0, 0);
		createTalkBubble(210, 470, 0, 0, 1.f, 0.25f);
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
		actorText("Hilma", 480.f, 480.f, 1.f, 1.f);
		text(astronautHilma, 225, 510, 0, 0);
		createTalkBubble(210, 470, 0, 0, 1.f, 0.25f);
	}

	if (mState == 1)
	{
		actorText("Thomas", 472.f, 480.f, 1.f, 1.f);
		text(astronautThomas, 225, 510, 0, 0);
		createTalkBubble(210, 470, 0, 0, 1.f, 0.25f);
	}

	if (mState == 2)
	{
		actorText("Hilma", 480.f, 480.f, 1.f, 1.f);
		text(astronautHilma2, 225, 510, 0, 0);
		createTalkBubble(210, 470, 0, 0, 1.f, 0.25f);
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
		actorText("Hilma", 480.f, 480.f, 1.f, 1.f);
		text(magnetHilma, 225, 510, 0, 0);
		createTalkBubble(210, 470, 0, 0, 1.f, 0.25f);
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
		actorText("Hilma", 480.f, 480.f, 1.f, 1.f);
		text(stringHilma, 225, 510, 0, 0);
		createTalkBubble(210, 470, 0, 0, 1.f, 0.25f);
	}
}

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
		actorText("Thomas", 472.f, 480.f, 1.f, 1.f);
		text(books2Thomas, 225, 510, 0, 0);
		createTalkBubble(210, 470, 0, 0, 1.f, 0.25f);
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
		actorText("Thomas", 472.f, 480.f, 1.f, 1.f);
		text(jewelryCaseThomas, 225, 510, 0, 0);
		createTalkBubble(210, 470, 0, 0, 1.f, 0.25f);
	}

	if (mState == 1)
	{
		actorText("Hilma", 480.f, 480.f, 1.f, 1.f);
		text(jewelryCaseHilma, 225, 510, 0, 0);
		createTalkBubble(210, 470, 0, 0, 1.f, 0.25f);
	}

	if (mState == 2)
	{
		actorText("Hilma", 480.f, 480.f, 1.f, 1.f);
		text(jewelryCaseHilma2, 225, 510, 0, 0);
		createTalkBubble(210, 470, 0, 0, 1.f, 0.25f);
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
		actorText("Hilma", 480.f, 480.f, 1.f, 1.f);
		text(maskHilma, 225, 510, 0, 0);
		createTalkBubble(210, 470, 0, 0, 1.f, 0.25f);
	}

	if (mState == 1)
	{
		actorText("Thomas", 472.f, 480.f, 1.f, 1.f);
		text(maskThomas, 225, 510, 0, 0);
		createTalkBubble(210, 470, 0, 0, 1.f, 0.25f);
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
		actorText("Hilma", 480.f, 480.f, 1.f, 1.f);
		text(textileCartHilma, 225, 510, 0, 0);
		createTalkBubble(210, 470, 0, 0, 1.f, 0.25f);
	}
}

void DialogueSystem::displayEarthGlobeDialogue()
{
	std::string earthGlobeThomas = "En jordglob. Jag har alltid velat ha en s�n...";
	std::string earthGlobeHilma = "Vet du vad Thomas, vi kanske kan ha anv�ndning f�r den...";

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
		actorText("Thomas", 472.f, 480.f, 1.f, 1.f);
		text(earthGlobeThomas, 225, 510, 0, 0);
		createTalkBubble(210, 470, 0, 0, 1.f, 0.25f);
	}

	if (mState == 1)
	{
		actorText("Hilma", 480.f, 480.f, 1.f, 1.f);
		text(earthGlobeHilma, 225, 510, 0, 0);
		createTalkBubble(210, 470, 0, 0, 1.f, 0.25f);
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
		actorText("Hilma", 480.f, 480.f, 1.f, 1.f);
		text(gramophoneHilma, 225, 510, 0, 0);
		createTalkBubble(210, 470, 0, 0, 1.f, 0.25f);
	}

	if (mState == 1)
	{
		actorText("Thomas", 472.f, 480.f, 1.f, 1.f);
		text(gramophoneThomas, 225, 510, 0, 0);
		createTalkBubble(210, 470, 0, 0, 1.f, 0.25f);
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
		actorText("Hilma", 480.f, 480.f, 1.f, 1.f);
		text(fishTrophyHilma, 225, 510, 0, 0);
		createTalkBubble(210, 470, 0, 0, 1.f, 0.25f);
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
		actorText("Hilma", 480.f, 480.f, 1.f, 1.f);
		text(plantHilma, 225, 510, 0, 0);
		createTalkBubble(210, 470, 0, 0, 1.f, 0.25f);
	}
}

void DialogueSystem::displayArmchairDialogue()
{
	std::string armchairHilma = "Tjugo sp�nn p� att det �r d�r din mormor brukar sitta!";

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
		actorText("Hilma", 480.f, 480.f, 1.f, 1.f);
		text(armchairHilma, 225, 510, 0, 0);
		createTalkBubble(210, 470, 0, 0, 1.f, 0.25f);
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
		actorText("Hilma", 480.f, 480.f, 1.f, 1.f);
		text(glassesAndNutsHilma, 225, 510, 0, 0);
		createTalkBubble(210, 470, 0, 0, 1.f, 0.25f);
	}

	if (mState == 1)
	{
		actorText("Thomas", 472.f, 480.f, 1.f, 1.f);
		text(glassesAndNutsThomas, 225, 510, 0, 0);
		createTalkBubble(210, 470, 0, 0, 1.f, 0.25f);
	}
}

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
		actorText("Thomas", 472.f, 480.f, 1.f, 1.f);
		text(refridgeratorThomas, 225, 510, 0, 0);
		createTalkBubble(210, 470, 0, 0, 1.f, 0.25f);
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
		actorText("Hilma", 480.f, 480.f, 1.f, 1.f);
		text(catHilma, 225, 510, 0, 0);
		createTalkBubble(210, 470, 0, 0, 1.f, 0.25f);
	}

	if (mState == 1)
	{
		actorText("Thomas", 472.f, 480.f, 1.f, 1.f);
		text(catThomas, 225, 510, 0, 0);
		createTalkBubble(210, 470, 0, 0, 1.f, 0.25f);
	}

	if (mState == 2)
	{
		actorText("Hilma", 480.f, 480.f, 1.f, 1.f);
		text(catHilma2, 225, 510, 0, 0);
		createTalkBubble(210, 470, 0, 0, 1.f, 0.25f);
	}

	if (mState == 3)
	{
		actorText("Thomas", 472.f, 480.f, 1.f, 1.f);
		text(catThomas2, 225, 510, 0, 0);
		createTalkBubble(210, 470, 0, 0, 1.f, 0.25f);
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
		actorText("Thomas", 472.f, 480.f, 1.f, 1.f);
		text(catFoodBowlThomas, 225, 510, 0, 0);
		createTalkBubble(210, 470, 0, 0, 1.f, 0.25f);
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
		actorText("Hilma", 480.f, 480.f, 1.f, 1.f);
		text(mouseDwellingHilma, 225, 510, 0, 0);
		createTalkBubble(210, 470, 0, 0, 1.f, 0.25f);
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
		actorText("Thomas", 472.f, 480.f, 1.f, 1.f);
		text(waterTapThomas, 225, 510, 0, 0);
		createTalkBubble(210, 470, 0, 0, 1.f, 0.25f);
	}

	if (mState == 1)
	{
		actorText("Hilma", 480.f, 480.f, 1.f, 1.f);
		text(waterTapHilma, 225, 510, 0, 0);
		createTalkBubble(210, 470, 0, 0, 1.f, 0.25f);
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
		actorText("Thomas", 472.f, 480.f, 1.f, 1.f);
		text(fruitBowlThomas, 225, 510, 0, 0);
		createTalkBubble(210, 470, 0, 0, 1.f, 0.25f);
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
		actorText("Thomas", 472.f, 480.f, 1.f, 1.f);
		text(flowersThomas, 225, 510, 0, 0);
		createTalkBubble(210, 470, 0, 0, 1.f, 0.25f);
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
		actorText("Thomas", 472.f, 480.f, 1.f, 1.f);
		text(rocketDrawingsThomas, 225, 510, 0, 0);
		createTalkBubble(210, 470, 0, 0, 1.f, 0.25f);
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
		actorText("Thomas", 472.f, 480.f, 1.f, 1.f);
		text(toolsThomas, 225, 510, 0, 0);
		createTalkBubble(210, 470, 0, 0, 1.f, 0.25f);
	}
}

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
		actorText("Thomas", 472.f, 480.f, 1.f, 1.f);
		text(planetsThomas, 225, 510, 0, 0);
		createTalkBubble(210, 470, 0, 0, 1.f, 0.25f);
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
		actorText("Thomas", 472.f, 480.f, 1.f, 1.f);
		text(mercuryThomas, 225, 510, 0, 0);
		createTalkBubble(210, 470, 0, 0, 1.f, 0.25f);
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
		actorText("Thomas", 472.f, 480.f, 1.f, 1.f);
		text(venusThomas, 225, 510, 0, 0);
		createTalkBubble(210, 470, 0, 0, 1.f, 0.25f);
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
		actorText("Thomas", 472.f, 480.f, 1.f, 1.f);
		text(emptyEarthThomas, 225, 510, 0, 0);
		createTalkBubble(210, 470, 0, 0, 1.f, 0.25f);
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
		actorText("Thomas", 472.f, 480.f, 1.f, 1.f);
		text(emptyMarsThomas, 225, 510, 0, 0);
		createTalkBubble(210, 470, 0, 0, 1.f, 0.25f);
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
		actorText("Thomas", 472.f, 480.f, 1.f, 1.f);
		text(jupiterThomas, 225, 510, 0, 0);
		createTalkBubble(210, 470, 0, 0, 1.f, 0.25f);
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
		actorText("Thomas", 472.f, 480.f, 1.f, 1.f);
		text(emptySaturnThomas, 225, 510, 0, 0);
		createTalkBubble(210, 470, 0, 0, 1.f, 0.25f);
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
		actorText("Thomas", 472.f, 480.f, 1.f, 1.f);
		text(uranusThomas, 225, 510, 0, 0);
		createTalkBubble(210, 470, 0, 0, 1.f, 0.25f);
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
		actorText("Thomas", 472.f, 480.f, 1.f, 1.f);
		text(neptuneThomas, 225, 510, 0, 0);
		createTalkBubble(210, 470, 0, 0, 1.f, 0.25f);
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
		actorText("Thomas", 472.f, 480.f, 1.f, 1.f);
		text(emptyPlutoThomas, 225, 510, 0, 0);
		createTalkBubble(210, 470, 0, 0, 1.f, 0.25f);
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
		actorText("Thomas", 472.f, 480.f, 1.f, 1.f);
		text(marsThomas, 225, 510, 0, 0);
		createTalkBubble(210, 470, 0, 0, 1.f, 0.25f);
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
		actorText("Hilma", 480.f, 480.f, 1.f, 1.f);
		text(earthHilma, 225, 510, 0, 0);
		createTalkBubble(210, 470, 0, 0, 1.f, 0.25f);
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
		actorText("Thomas", 472.f, 480.f, 1.f, 1.f);
		text(saturnThomas, 225, 510, 0, 0);
		createTalkBubble(210, 470, 0, 0, 1.f, 0.25f);
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
		actorText("Thomas", 472.f, 480.f, 1.f, 1.f);
		text(plutoThomas, 225, 510, 0, 0);
		createTalkBubble(210, 470, 0, 0, 1.f, 0.25f);
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
		actorText("Hilma", 480.f, 480.f, 1.f, 1.f);
		text(swordsHilma, 225, 510, 0, 0);
		createTalkBubble(210, 470, 0, 0, 1.f, 0.25f);
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
		actorText("Hilma", 480.f, 480.f, 1.f, 1.f);
		text(drawingsHilma, 225, 510, 0, 0);
		createTalkBubble(210, 470, 0, 0, 1.f, 0.25f);
	}

	if (mState == 1)
	{
		actorText("Thomas", 472.f, 480.f, 1.f, 1.f);
		text(drawingsThomas, 225, 510, 0, 0);
		createTalkBubble(210, 470, 0, 0, 1.f, 0.25f);
	}
}

void DialogueSystem::displayBalconyDoorDialogue()
{
	std::string balconyDoorHilma = "N�pp! D�r kommer vi inte igenom! Vi m�ste f� upp den p� n�got s�tt...";

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
		actorText("Hilma", 480.f, 480.f, 1.f, 1.f);
		text(balconyDoorHilma, 225, 510, 0, 0);
		createTalkBubble(210, 470, 0, 0, 1.f, 0.25f);
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
		actorText("Hilma", 480.f, 480.f, 1.f, 1.f);
		text(dollHouseHilma, 225, 510, 0, 0);
		createTalkBubble(210, 470, 0, 0, 1.f, 0.25f);
	}

	if (mState == 1)
	{
		actorText("Thomas", 472.f, 480.f, 1.f, 1.f);
		text(dollHouseThomas, 225, 510, 0, 0);
		createTalkBubble(210, 470, 0, 0, 1.f, 0.25f);
	}

	if (mState == 2)
	{
		actorText("Hilma", 480.f, 480.f, 1.f, 1.f);
		text(dollHouseHilma2, 225, 510, 0, 0);
		createTalkBubble(210, 470, 0, 0, 1.f, 0.25f);
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
		actorText("Hilma", 480.f, 480.f, 1.f, 1.f);
		text(putteHilma, 225, 510, 0, 0);
		createTalkBubble(210, 470, 0, 0, 1.f, 0.25f);
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
		actorText("Hilma", 480.f, 480.f, 1.f, 1.f);
		text(putteFamilyHilma, 225, 510, 0, 0);
		createTalkBubble(210, 470, 0, 0, 1.f, 0.25f);
	}
}

void DialogueSystem::displayShearsDialogue()
{
	std::string shearsThomas = "Saxen kan vara anv�ndbar men vi borde inte anv�nda den utan en vuxen.";
	std::string shearsHilma = "Men hall�, jag �r ju vuxen!";
	std::string shearsThomas2 = "Oj, f�rl�t...";

	if (mState == 3)
	{
		mText.setString("");
		mHasClicked = false;
		mShears = false;
		mIsActive = false;
		mFinishedDialogue = true;
	}

	if (mState == 0)
	{
		mIsActive = true;
		actorText("Thomas", 472.f, 480.f, 1.f, 1.f);
		text(shearsThomas, 225, 510, 0, 0);
		createTalkBubble(210, 470, 0, 0, 1.f, 0.25f);
	}

	if (mState == 1)
	{
		actorText("Hilma", 480.f, 480.f, 1.f, 1.f);
		text(shearsHilma, 225, 510, 0, 0);
		createTalkBubble(210, 470, 0, 0, 1.f, 0.25f);
	}

	if (mState == 2)
	{
		actorText("Thomas", 472.f, 480.f, 1.f, 1.f);
		text(shearsThomas2, 225, 510, 0, 0);
		createTalkBubble(210, 470, 0, 0, 1.f, 0.25f);
	}
}

void DialogueSystem::displayBushDialogue()
{
	std::string BushHilma = "Den d�r pinnen kan vara bra att ha";

	if (mState == 1)
	{
		mText.setString("");
		mHasClicked = false;
		mBush = false;
		mIsActive = false;
		mFinishedDialogue = true;
	}

	if (mState == 0)
	{
		mIsActive = true;
		actorText("Hilma", 480.f, 480.f, 1.f, 1.f);
		text(BushHilma, 225, 510, 0, 0);
		createTalkBubble(210, 470, 0, 0, 1.f, 0.25f);
	}
}

void DialogueSystem::displayRopeDialogue()
{
	std::string ropeHilma = "Vi m�ste klippa upp repet om vi ska lura bort hunden.";

	if (mState == 1)
	{
		mText.setString("");
		mHasClicked = false;
		mRope = false;
		mIsActive = false;
		mFinishedDialogue = true;
	}

	if (mState == 0)
	{
		mIsActive = true;
		actorText("Hilma", 480.f, 480.f, 1.f, 1.f);
		text(ropeHilma, 225, 510, 0, 0);
		createTalkBubble(210, 470, 0, 0, 1.f, 0.25f);
	}
}

void DialogueSystem::displayDogDialogue()
{
	std::string dogHilma = "Om djurets mun kan sluka mig hel, kommer jag d� g� n�ra den? Fel.";

	if (mState == 1)
	{
		mText.setString("");
		mHasClicked = false;
		mDog = false;
		mIsActive = false;
		mFinishedDialogue = true;
	}

	if (mState == 0)
	{
		mIsActive = true;
		actorText("Hilma", 480.f, 480.f, 1.f, 1.f);
		text(dogHilma, 225, 510, 0, 0);
		createTalkBubble(210, 470, 0, 0, 1.f, 0.25f);
	}
}

void DialogueSystem::displayGardenFlowersDialogue()
{
	std::string gardenFlowersThomas = "�h vilka vackra blommor... jag �ngrar verkligen att vi f�rst�rde hennes tr�dg�rd.";
	std::string gardenFlowersHilma = "Gjort �r gjort Thomas.";
	std::string gardenFlowersHilma2 = "Du och mormor hittar s�kert ett s�tt att gottg�ra det.";

	if (mState == 3)
	{
		mText.setString("");
		mHasClicked = false;
		mGardenFlowers = false;
		mIsActive = false;
		mFinishedDialogue = true;
	}

	if (mState == 0)
	{
		mIsActive = true;
		actorText("Thomas", 472.f, 480.f, 1.f, 1.f);
		text(gardenFlowersThomas, 225, 510, 0, 0);
		createTalkBubble(210, 470, 0, 0, 1.f, 0.25f);
	}

	if (mState == 1)
	{
		actorText("Hilma", 480.f, 480.f, 1.f, 1.f);
		text(gardenFlowersHilma, 225, 510, 0, 0);
		createTalkBubble(210, 470, 0, 0, 1.f, 0.25f);
	}

	if (mState == 2)
	{
		actorText("Hilma", 480.f, 480.f, 1.f, 1.f);
		text(gardenFlowersHilma2, 225, 510, 0, 0);
		createTalkBubble(210, 470, 0, 0, 1.f, 0.25f);
	}
}

void DialogueSystem::displayFlagpoleDialogue()
{
	std::string flagpoleThomas = "Om bikupan varit d�r uppe ist�llet hade bina inte n�tt oss.";
	std::string flagpoleHilma = "Vi kanske bara beh�ver locka dit bina.";

	if (mState == 2)
	{
		mText.setString("");
		mHasClicked = false;
		mFlagpole = false;
		mIsActive = false;
		mFinishedDialogue = true;
	}

	if (mState == 0)
	{
		mIsActive = true;
		actorText("Thomas", 472.f, 480.f, 1.f, 1.f);
		text(flagpoleThomas, 225, 510, 0, 0);
		createTalkBubble(210, 470, 0, 0, 1.f, 0.25f);
	}

	if (mState == 1)
	{
		actorText("Hilma", 480.f, 480.f, 1.f, 1.f);
		text(flagpoleHilma, 225, 510, 0, 0);
		createTalkBubble(210, 470, 0, 0, 1.f, 0.25f);
	}
}

void DialogueSystem::displayBeeDialogue()
{
	std::string beeThomas = "Jag trodde bara du var r�dd f�r saker st�rre �n dig.";
	std::string beeHilma = "Jo, men f�r mig �r ju bin j�ttestora, stora som t�r!";
	std::string beeHilma2 = "Hade du velat bli stucken av en sv�rm t�r?";

	if (mState == 3)
	{
		mText.setString("");
		mHasClicked = false;
		mBee = false;
		mIsActive = false;
		mFinishedDialogue = true;
	}

	if (mState == 0)
	{
		mIsActive = true;
		actorText("Thomas", 472.f, 480.f, 1.f, 1.f);
		text(beeThomas, 225, 510, 0, 0);
		createTalkBubble(210, 470, 0, 0, 1.f, 0.25f);
	}

	if (mState == 1)
	{
		actorText("Hilma", 480.f, 480.f, 1.f, 1.f);
		text(beeHilma, 225, 510, 0, 0);
		createTalkBubble(210, 470, 0, 0, 1.f, 0.25f);
	}

	if (mState == 2)
	{
		actorText("Hilma", 480.f, 480.f, 1.f, 1.f);
		text(beeHilma2, 225, 510, 0, 0);
		createTalkBubble(210, 470, 0, 0, 1.f, 0.25f);
	}
}

void DialogueSystem::displayTracksDialogue()
{
	std::string tracksHilma = "Kolla p� dem h�r sp�ren! Det ser ut som Surtanten sl�pat n�got tungt in i skjulet.";
	std::string tracksThomas = "Vad skulle det kunna vara som �r s� tungt?";

	if (mState == 2)
	{
		mText.setString("");
		mHasClicked = false;
		mTracks = false;
		mIsActive = false;
		mFinishedDialogue = true;
	}

	if (mState == 0)
	{
		mIsActive = true;
		actorText("Hilma", 480.f, 480.f, 1.f, 1.f);
		text(tracksHilma, 225, 510, 0, 0);
		createTalkBubble(210, 470, 0, 0, 1.f, 0.25f);
	}

	if (mState == 1)
	{
		actorText("Thomas", 472.f, 480.f, 1.f, 1.f);
		text(tracksThomas, 225, 510, 0, 0);
		createTalkBubble(210, 470, 0, 0, 1.f, 0.25f);
	}
}

void DialogueSystem::displayRocketDialogue()
{
	std::string rocketHilma = "Vad g�r Thomas och mormors raket h�r?";

	if (mState == 1)
	{
		mText.setString("");
		mHasClicked = false;
		mRocket = false;
		mIsActive = false;
		mFinishedDialogue = true;
	}

	if (mState == 0)
	{
		actorText("Hilma", 480.f, 480.f, 1.f, 1.f);
		text(rocketHilma, 225, 510, 0, 0);
		createTalkBubble(210, 470, 0, 0, 1.f, 0.25f);
	}
}

void DialogueSystem::displayWayInDialogue()
{
	std::string wayInHilma = "Jag kan inte g� h�rifr�n f�rr�n jag f�tt tag i fickuret.";

	if (mState == 1)
	{
		mText.setString("");
		mHasClicked = false;
		mWayIn = false;
		mIsActive = false;
		mFinishedDialogue = true;
	}

	if (mState == 0)
	{
		actorText("Hilma", 480.f, 480.f, 1.f, 1.f);
		text(wayInHilma, 225, 510, 0, 0);
		createTalkBubble(210, 470, 0, 0, 1.f, 0.25f);
	}
}

void DialogueSystem::displayEntryFindersWorldDialogue()
{
	std::string entryFindersWorldHilma = "Ing�ngen till Hittarnas V�rld.";

	if (mState == 1)
		{
			mText.setString("");
			mHasClicked = false;
			mEntryFindersWorld = false;
			mIsActive = false;
			mFinishedDialogue = true;
		}

	if (mState == 0)
	{
		actorText("Hilma", 480.f, 480.f, 1.f, 1.f);
		text(entryFindersWorldHilma, 225, 510, 0, 0);
		createTalkBubble(210, 470, 0, 0, 1.f, 0.25f);
	}
}

void DialogueSystem::displayCloverDialogue()
{
	std::string cloverHilma = "Vem kan vilja ha en trekl�ver?";

	if (mState == 1)
	{
		mText.setString("");
		mHasClicked = false;
		mClover = false;
		mIsActive = false;
		mFinishedDialogue = true;
	}

	if (mState == 0)
	{
		actorText("Hilma", 480.f, 480.f, 1.f, 1.f);
		text(cloverHilma, 225, 510, 0, 0);
		createTalkBubble(210, 470, 0, 0, 1.f, 0.25f);
	}
}

void DialogueSystem::displayNailsDialogue()
{
	std::string nailsHilma = "En burk med spikar.";

	if (mState == 1)
	{
		mText.setString("");
		mHasClicked = false;
		mNails = false;
		mIsActive = false;
		mFinishedDialogue = true;
	}

	if (mState == 0)
	{
		actorText("Hilma", 480.f, 480.f, 1.f, 1.f);
		text(nailsHilma, 225, 510, 0, 0);
		createTalkBubble(210, 470, 0, 0, 1.f, 0.25f);
	}
}

void DialogueSystem::displayHorseShoeDialogue()
{
	std::string horseShoeHilma = "Jag f�rst�r inte po�ngen med h�stskor.";
	std::string horseShoeHilma2 = "H�star beh�ver ju inte skor!";

	if (mState == 2)
	{
		mText.setString("");
		mHasClicked = false;
		mHorseShoe = false;
		mIsActive = false;
		mFinishedDialogue = true;
	}

	if (mState == 0)
	{
		actorText("Hilma", 480.f, 480.f, 1.f, 1.f);
		text(horseShoeHilma, 225, 510, 0, 0);
		createTalkBubble(210, 470, 0, 0, 1.f, 0.25f);
	}

	if (mState == 1)
	{
		actorText("Hilma", 480.f, 480.f, 1.f, 1.f);
		text(horseShoeHilma2, 225, 510, 0, 0);
		createTalkBubble(210, 470, 0, 0, 1.f, 0.25f);
	}
}

void DialogueSystem::displayClothDialogue()
{
	std::string clothHilma = "En picknickkorg med n�t rutigt tyg. Jag kanske kan klippa bort en bit av det?";

	if (mState == 1)
	{
		mText.setString("");
		mHasClicked = false;
		mCloth = false;
		mIsActive = false;
		mFinishedDialogue = true;
	}

	if (mState == 0)
	{
		actorText("Hilma", 480.f, 480.f, 1.f, 1.f);
		text(clothHilma, 225, 510, 0, 0);
		createTalkBubble(210, 470, 0, 0, 1.f, 0.25f);
	}
}

void DialogueSystem::displayBadmintonBallDialogue()
{
	std::string badmintonBallHilma = "Det �r ju en s�n man har n�r man spelar badminton! Vi brukade spela det med maskrosstr�n n�r jag var liten.";

	if (mState == 1)
	{
		mText.setString("");
		mHasClicked = false;
		mBadmintonBall = false;
		mIsActive = false;
		mFinishedDialogue = true;
	}

	if (mState == 0)
	{
		actorText("Hilma", 480.f, 480.f, 1.f, 1.f);
		text(badmintonBallHilma, 225, 510, 0, 0);
		createTalkBubble(210, 470, 0, 0, 1.f, 0.25f);
	}
}

void DialogueSystem::displaySawdustDialogue()
{
	std::string sawdustHilma = "S�gsp�n �r sm� tr�flagor man f�r n�r man s�gar n�got. Hittarsnickare anv�nder dem ibland som sm� br�dor n�r de bygger.";

	if (mState == 1)
	{
		mText.setString("");
		mHasClicked = false;
		mSawdust = false;
		mIsActive = false;
		mFinishedDialogue = true;
	}

	if (mState == 0)
	{
		actorText("Hilma", 480.f, 480.f, 1.f, 1.f);
		text(sawdustHilma, 225, 510, 0, 0);
		createTalkBubble(210, 470, 0, 0, 1.f, 0.25f);
	}
}

void DialogueSystem::displayKnightDialogue()
{
	std::string knightHilma = "Jag m�ste hitta saker �t knekten innan han flyttar sig.";

	if (mState == 1)
	{
		mText.setString("");
		mHasClicked = false;
		mKnight = false;
		mIsActive = false;
		mFinishedDialogue = true;
	}

	if (mState == 0)
	{
		actorText("Hilma", 480.f, 480.f, 1.f, 1.f);
		text(knightHilma, 225, 510, 0, 0);
		createTalkBubble(210, 470, 0, 0, 1.f, 0.25f);
	}
}

void DialogueSystem::displayKnightFirstDialogue()
{
	std::string knightFirstHilma = "Nu beh�ver jag bara ge honom tv� f�rem�l till!";

	if (mState == 1)
	{
		mText.setString("");
		mHasClicked = false;
		mKnightFirst = false;
		mIsActive = false;
		mFinishedDialogue = true;
	}

	if (mState == 0)
	{
		actorText("Hilma", 480.f, 480.f, 1.f, 1.f);
		text(knightFirstHilma, 225, 510, 0, 0);
		createTalkBubble(210, 470, 0, 0, 1.f, 0.25f);
	}
}

void DialogueSystem::displayKnightSecondDialogue()
{
	std::string knightSecondHilma = "Nu m�ste jag bara ge honom ett f�rem�l till!";

	if (mState == 1)
	{
		mText.setString("");
		mHasClicked = false;
		mKnightSecond = false;
		mIsActive = false;
		mFinishedDialogue = true;
	}

	if (mState == 0)
	{
		actorText("Hilma", 480.f, 480.f, 1.f, 1.f);
		text(knightSecondHilma, 225, 510, 0, 0);
		createTalkBubble(210, 470, 0, 0, 1.f, 0.25f);
	}
}

void DialogueSystem::displayKnightAllDialogue()
{
	std::string knightAllHilma = "Vilken prydlig knekt han blev! Och nu st�r han inte iv�gen l�ngre!";

	if (mState == 1)
	{
		mText.setString("");
		mHasClicked = false;
		mKnightAll = false;
		mIsActive = false;
		mFinishedDialogue = true;
	}

	if (mState == 0)
	{
		actorText("Hilma", 480.f, 480.f, 1.f, 1.f);
		text(knightAllHilma, 225, 510, 0, 0);
		createTalkBubble(210, 470, 0, 0, 1.f, 0.25f);
	}
}

void DialogueSystem::displayExitFindersWorld()
{
	std::string exitFindersWorldHilma = "Jag kan inte �terv�nda f�rr�n jag f�tt fickuret fr�n Skatmaran.";

	if (mState == 1)
	{
		mText.setString("");
		mHasClicked = false;
		mExitFindersWorld = false;
		mIsActive = false;
		mFinishedDialogue = true;
	}

	if (mState == 0)
	{
		actorText("Hilma", 480.f, 480.f, 1.f, 1.f);
		text(exitFindersWorldHilma, 225, 510, 0, 0);
		createTalkBubble(210, 470, 0, 0, 1.f, 0.25f);
	}
}

void DialogueSystem::displayStatueDialogue()
{
	std::string statueHilma = "Vem �r det stenansiktet?";

	if (mState == 1)
	{
		mText.setString("");
		mHasClicked = false;
		mStatue = false;
		mIsActive = false;
		mFinishedDialogue = true;
	}

	if (mState == 0)
	{
		actorText("Hilma", 480.f, 480.f, 1.f, 1.f);
		text(statueHilma, 225, 510, 0, 0);
		createTalkBubble(210, 470, 0, 0, 1.f, 0.25f);
	}
}

void DialogueSystem::displayJewelsDialogue()
{
	std::string jewelsHilma = "Wow, de m�ste vara v�rda en f�rm�genhet!";

	if (mState == 1)
	{
		mText.setString("");
		mHasClicked = false;
		mJewels = false;
		mIsActive = false;
		mFinishedDialogue = true;
	}

	if (mState == 0)
	{
		actorText("Hilma", 480.f, 480.f, 1.f, 1.f);
		text(jewelsHilma, 225, 510, 0, 0);
		createTalkBubble(210, 470, 0, 0, 1.f, 0.25f);
	}
}

void DialogueSystem::displayBubblesDialogue()
{
	std::string bubblesHilma = "Hmm. Det �r lite mystiskt att det bara bubblar s�d�r.";
	std::string bubblesHilma2 = "N�got m�ste vara d�r.";

	if (mState == 2)
	{
		mText.setString("");
		mHasClicked = false;
		mBubbles = false;
		mIsActive = false;
		mFinishedDialogue = true;
	}

	if (mState == 0)
	{
		actorText("Hilma", 480.f, 480.f, 1.f, 1.f);
		text(bubblesHilma, 225, 510, 0, 0);
		createTalkBubble(210, 470, 0, 0, 1.f, 0.25f);
	}

	if (mState == 1)
	{
		actorText("Hilma", 480.f, 480.f, 1.f, 1.f);
		text(bubblesHilma2, 225, 510, 0, 0);
		createTalkBubble(210, 470, 0, 0, 1.f, 0.25f);
	}
}

void DialogueSystem::displayParentDialogue()
{
	std::string parentHilma = "En hittarf�r�lder. Jag har ocks� en s�n. N�nstans.";

	if (mState == 1)
	{
		mText.setString("");
		mHasClicked = false;
		mParent = false;
		mIsActive = false;
		mFinishedDialogue = true;
	}

	if (mState == 0)
	{
		actorText("Hilma", 480.f, 480.f, 1.f, 1.f);
		text(parentHilma, 225, 510, 0, 0);
		createTalkBubble(210, 470, 0, 0, 1.f, 0.25f);
	}
}