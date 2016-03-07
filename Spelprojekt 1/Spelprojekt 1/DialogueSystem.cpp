#include "DialogueSystem.h"
#include <iostream>
#include "SFML\System.hpp"

DialogueSystem::DialogueSystem(ResourceHandler &handler) :
mHasClicked(false),
mTime(0),
mText(),
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
mLineStarted(false)
{
	mFont.loadFromFile("Resources/Fonts/ShadowsIntoLight.ttf");
	mBubble.setTexture(*handler.getTexture("textbubble.png"));
	mTextBox.setTexture(*handler.getTexture("textbox.png"));
	mSepia.setSize(sf::Vector2f(1024, 576));
	mSepia.setTexture(handler.getTexture("sepia.png"));

	voiceActingTest.openFromFile(handler.getMusic("VoiceActingTest.ogg"));
	voiceActingTest2.openFromFile(handler.getMusic("VoiceActingTest2.ogg"));
}

DialogueSystem::~DialogueSystem()
{

}

//Function for all text in dialogues
void DialogueSystem::text(std::string text, sf::Vector2f &position, float x, float y)
{
	mText.setFont(mFont);
	mText.setCharacterSize(18);
	mText.setStyle(sf::Text::Bold);
	mText.setColor(sf::Color::Black);
	mText.setPosition(position);

	if (text.length() > 25)
	{
		std::string::size_type spacePos = text.rfind(' ', 25);
		if (spacePos == std::string::npos)
		{
			spacePos = text.find(' ', 25);
		}
		if (spacePos != std::string::npos)
		{
			text[spacePos] = '\n';
		}
	}
	if (text.length() > 55)
	{
		std::string::size_type spacePos = text.rfind(' ', 50);
		if (spacePos == std::string::npos)
		{
			spacePos = text.find(' ', 50);
		}
		if (spacePos != std::string::npos)
		{
			text[spacePos] = '\n';
			y = y - 15;
		}
	}
	if (text.length() > 75)
	{
		std::string::size_type spacePos = text.rfind(' ', 75);
		if (spacePos == std::string::npos)
		{
			spacePos = text.find(' ', 75);
		}
		if (spacePos != std::string::npos)
		{
			text[spacePos] = '\n';
			y = y - 15;
		}
	}

	mText.move(x, y);
	mText.setString(text);
}

void DialogueSystem::advancedText(std::string advancedText, float posX, float posY, float offsetX, float offsetY)
{
	mText.setFont(mFont);
	mText.setCharacterSize(24);
	mText.setStyle(sf::Text::Bold);
	mText.setColor(sf::Color::White);
	mText.move(offsetX, offsetY);

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
		}
	}

	if (advancedText.length() > 140)
	{
		std::string::size_type spacePos = advancedText.rfind(' ', 140);
		if (spacePos == std::string::npos)
		{
			spacePos = advancedText.find(' ', 140);
		}
		if (spacePos != std::string::npos)
		{
			advancedText[spacePos] = '\n';
			posY = posY -25;
		}
	}

	if (advancedText.length() > 210)
	{
		std::string::size_type spacePos = advancedText.rfind(' ', 210);
		if (spacePos == std::string::npos)
		{
			spacePos = advancedText.find(' ', 210);
		}
		if (spacePos != std::string::npos)
		{
			advancedText[spacePos] = '\n';
			posY = posY - 25;
		}
	}

	mText.setPosition(posX, posY);
	mText.setString(advancedText);
}

//Draw function for game to use
void DialogueSystem::drawDialogue(sf::RenderWindow &window)
{
	if (mIsActive)
	{
		window.draw(mBubble);
	}
	if (mAdvancedIsActive)
	{
		window.draw(mSepia);
		window.draw(mFirstCharacter);
		window.draw(mSecondCharacter);
		window.draw(mTextBox);
	}
	window.draw(mText);
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
	//if (indexName == "level1Start" && mHasClicked == false)
	//{
	//	mLevel1Start = true;
	//	mHasClicked = true;
	//}
	if (indexName == "ScrewDevice" && mHasClicked == false)
	{
		mLevel1End = true;
		mHasClicked = true;
	}

	//Thomas' Room
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

//Update function
void DialogueSystem::update(float time)
{
	//Advanced Dialogue
	if (mLevel1Start == true)
	{
		displayLevel1StartAdvancedDialogue();
	}
	if (mLevel1End == true)
	{
		displayLevel1EndAdvancedDialogue();
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
		displayEmptyEarthDialogue();
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
	mLineStarted = false;
	mState++;
}

bool DialogueSystem::isDialogueFinished()
{
	return mFinishedDialogue;
}

//Advanced Dialogues
void DialogueSystem::displayLevel1StartAdvancedDialogue()
{
	std::string level1StartHilma = "För bövelingen! Nu är min flygfarkost alldeles förstörd! Förbaskade flygfän som alltid ska vara så livliga... Nähej, nu måste jag laga detta!";
	std::string level1StartTeller = "Den vresiga lilla hittaren tog av sin mössa och började leta i den. Hon letade och letade längre ned i mössan. Det enda man kunde se av henne var hennes små, små fötter. Det var som om det inte fanns någon botten i mössan! Till slut hoppade hittaren ut ur mössan.\nMen nu var hon helt röd i hela ansiktet.";
	std::string level1StartHilma2 = "MEN VAD SJUTTON ÄR DET HÄR??? ÄR DEN BORTA? ALLT ÄR BORTA?!! DET HÄR KAN INTE VARA SANT!";
	std::string level1StartHilma3 = "Det var det bästa utbytet jag hittills har fått! Jag som hade hittat så bra...";
	std::string level1StartThomas = "V-v- vad har du tappat?";
	std::string level1StartHilma4 = "För det första, jag har inte tappat bort något. För det andra, är det en mycket ovärderlig sak som tog väldigt lång tid att få. Det var en fantastisk skruvmackapär. Med den skulle jag bygga en mycket finare flygfarkost än denna... skrothög. Men nu har jag INGENTING att laga skrothögen med.";
	std::string level1StartTeller2 = "Pojken tyckte synd om den lilla varelsen. Han tänkte och tänkte. Till slut kom han på en idé.";
	std::string level1StartThomas2 = "J-jag kanske... har en skruvmackapär-";
	std::string level1StartHilma5 = "Jamen då så! Var har du den?";
	std::string level1StartThomas3 = "Eumh... jag vet inte...";
	std::string level1StartHilma6 = "Men oj då, det var verkligen till stor hjälp! Kan det vara så att du har tappat bort den?";
	std::string level1StartHilma7 = "Du får väl tacka vinden för att den var så bångstyrig idag. För du fick turen att träffa på mig! Det råkar vara så att jag är en hittare!";
	std::string level1StartTeller3 = "En hittare? Vad kunde det vara? Pojken hade aldrig hört talas om det innan.";
	std::string level1StartHilma8 = "Jajamän! Vi Hittare har funnits länge och hållit reda på er slarviga människor. Tappar ni bort något så hittar vi det åt er. Det råkar vara så att jag har en egen hittarbyrå! Jag kan hitta vad och var som helst!";
	std::string level1StartThomas4 = "O-o-m du verkligen är en h-hittare. Kan du... Kan du hitta tre saker åt mig-";
	std::string level1StartHilma9 = "För att bevisa för dig att jag är en hittare? Utmaning godtagen! Vad är det du vill att jag ska hitta? Kom igen nu, vela inte så mycket!";
	std::string level1StartThomas5 = "Hitta en självlysande stjärna... den föll från väggen, min favorit Astronaut och... Skruvmackapären...";
	std::string level1StartHilma10 = "Vad får jag i utbyte? Jag måste få min hittarbyrå att gå runt på något sätt!";
	std::string level1StartThomas6 = "Hur mycket kostar det?";
	std::string level1StartHilma11 = "Inte pengar! Ge mig något användbart som jag kan bygga med!";
	std::string level1StartHilma12 = "Ge mig skruvmackapären sen när jag har hittat den, det blir ett bra utbyte!";
	std::string level1StartHilma13 = "Justja! Hilma heter jag. Vad är ditt namn?";
	std::string level1StartThomas7 = "... Thomas";
	std::string level1StartHilma14 = "Då så, Thomas. Då ska jag hitta en stjärna, en astronaut och en skruvmackapär åt dig!";
	std::string level1StartInterlude = "*Thomas nickar tveksamt*";

	if (mState >= 25)
	{
		mText.setString("");
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
		createTextBox(-250.f, 300.f, 1.f, 1.f, 0.4f, 0.40f);  //(-1.0f, 280.0f, 1.0f, 1.0f, 0.267f, 0.45f)

		//Voice Acting Template
		if (!mLineStarted && voiceActingTest.getStatus() != 2)
		{
			voiceActingTest.play();
			mLineStarted = true;
		}
		if (mLineStarted && voiceActingTest.getStatus() == 0)
		{
			mLineStarted = false;
			setState();
		}
	}
	if (mState == 1)
	{
		advancedText(level1StartTeller, 100.f, 420.f, 1.f, 1.f);

		//Voice Acting Template
		voiceActingTest.stop();
		if (!mLineStarted && voiceActingTest2.getStatus() != 2)
		{
			voiceActingTest2.play();
			mLineStarted = true;
		}
		if (mLineStarted && voiceActingTest2.getStatus() == 0)
		{
			mLineStarted = false;
			setState();
		}
	}
	if (mState == 2)
	{
		advancedText(level1StartHilma2, 100.f, 420.f, 1.f, 1.f);
		drawFirstCharacter(mHandler, 300.f, 30.f, 1.f, 1.f, -0.2f, 0.2f, "expressionHilmaAngry.png");

		//Voice Acting Template
		voiceActingTest2.stop();
		if (!mLineStarted && voiceActingTest.getStatus() != 2)
		{
			voiceActingTest.play();
			mLineStarted = true;
		}
		if (mLineStarted && voiceActingTest.getStatus() == 0)
		{
			mLineStarted = false;
			setState();
		}
	}
	if (mState == 3)
	{
		advancedText(level1StartHilma3, 100.f, 420.f, 1.f, 1.f);
		drawFirstCharacter(mHandler, 300.f, 30.f, 1.f, 1.f, -0.2f, 0.2f, "expressionHilmaSad.png");

		voiceActingTest.stop();
	}
	if (mState == 4)
	{
		advancedText(level1StartThomas, 100.f, 420.f, 1.f, 1.f);
		drawSecondCharacter(mHandler, 700.f, 30.f, 1.f, 1.f, 0.2f, 0.2f, "expressionThomasHappy.png");
	}
	if (mState == 5)
	{
		advancedText(level1StartHilma4, 100.f, 420.f, 1.f, 1.f);
		drawFirstCharacter(mHandler, 300.f, 30.f, 1.f, 1.f, -0.2f, 0.2f, "expressionHilmaGrumpy.png");
	}
	if (mState == 6)
	{
		advancedText(level1StartTeller2, 100.f, 420.f, 1.f, 1.f);
	}
	if (mState == 7)
	{
		advancedText(level1StartThomas2, 100.f, 420.f, 1.f, 1.f);
		drawSecondCharacter(mHandler, 700.f, 30.f, 1.f, 1.f, 0.2f, 0.2f, "expressionThomasSmile.png");
	}
	if (mState == 8)
	{
		advancedText(level1StartHilma5, 100.f, 420.f, 1.f, 1.f);
		drawFirstCharacter(mHandler, 300.f, 30.f, 1.f, 1.f, -0.2f, 0.2f, "expressionHilmaHappy.png");
	}
	if (mState == 9)
	{
		advancedText(level1StartThomas3, 100.f, 420.f, 1.f, 1.f);
		drawSecondCharacter(mHandler, 700.f, 30.f, 1.f, 1.f, 0.2f, 0.2f, "expressionThomasSurprised.png");
	}
	if (mState == 10)
	{
		advancedText(level1StartHilma6, 100.f, 420.f, 1.f, 1.f);
		drawFirstCharacter(mHandler, 300.f, 30.f, 1.f, 1.f, -0.2f, 0.2f, "expressionHilmaDetermined.png");
	}
	if (mState == 11)
	{
		advancedText(level1StartHilma7, 100.f, 420.f, 1.f, 1.f);
		drawFirstCharacter(mHandler, 300.f, 30.f, 1.f, 1.f, -0.2f, 0.2f, "expressionHilmaConfident.png");
	}
	if (mState == 12)
	{
		advancedText(level1StartTeller3, 100.f, 420.f, 1.f, 1.f);
	}
	if (mState == 13)
	{
		advancedText(level1StartHilma8, 100.f, 420.f, 1.f, 1.f);
		drawFirstCharacter(mHandler, 300.f, 30.f, 1.f, 1.f, -0.2f, 0.2f, "expressionHilmaDetermined.png");
	}
	if (mState == 14)
	{
		advancedText(level1StartThomas4, 100.f, 420.f, 1.f, 1.f);
		drawSecondCharacter(mHandler, 700.f, 30.f, 1.f, 1.f, 0.2f, 0.2f, "expressionThomasSigh.png");
	}
	if (mState == 15)
	{
		advancedText(level1StartHilma9, 100.f, 420.f, 1.f, 1.f);
		drawFirstCharacter(mHandler, 300.f, 30.f, 1.f, 1.f, -0.2f, 0.2f, "expressionHilmaConfident.png");
	}
	if (mState == 16)
	{
		advancedText(level1StartThomas5, 100.f, 420.f, 1.f, 1.f);
		drawSecondCharacter(mHandler, 700.f, 30.f, 1.f, 1.f, 0.2f, 0.2f, "expressionThomasGrumpy.png");
	}
	if (mState == 17)
	{
		advancedText(level1StartHilma10, 100.f, 420.f, 1.f, 1.f);
		drawFirstCharacter(mHandler, 300.f, 30.f, 1.f, 1.f, -0.2f, 0.2f, "expressionHilmaDetermined.png");
	}
	if (mState == 18)
	{
		advancedText(level1StartThomas6, 100.f, 420.f, 1.f, 1.f);
		drawSecondCharacter(mHandler, 700.f, 30.f, 1.f, 1.f, 0.2f, 0.2f, "expressionThomasSad.png");
	}
	if (mState == 19)
	{
		advancedText(level1StartHilma11, 100.f, 420.f, 1.f, 1.f);
		drawFirstCharacter(mHandler, 300.f, 30.f, 1.f, 1.f, -0.2f, 0.2f, "expressionHilmaGrumpy.png");
	}
	if (mState == 20)
	{
		advancedText(level1StartHilma12, 100.f, 420.f, 1.f, 1.f);
		drawFirstCharacter(mHandler, 300.f, 30.f, 1.f, 1.f, -0.2f, 0.2f, "expressionHilmaSigh.png");
	}
	if (mState == 21)
	{
		advancedText(level1StartInterlude, 100.f, 420.f, 1.f, 1.f);
		drawSecondCharacter(mHandler, 700.f, 30.f, 1.f, 1.f, 0.2f, 0.2f, "expressionThomasSigh.png");
	}
	if (mState == 22)
	{
		advancedText(level1StartHilma13, 100.f, 420.f, 1.f, 1.f);
		drawFirstCharacter(mHandler, 300.f, 30.f, 1.f, 1.f, -0.2f, 0.2f, "expressionHilmaHappy.png");
	}
	if (mState == 23)
	{
		advancedText(level1StartThomas7, 100.f, 420.f, 1.f, 1.f);
	}
	if (mState == 24)
	{
		advancedText(level1StartHilma14, 100.f, 420.f, 1.f, 1.f);
	}
}

void DialogueSystem::displayLevel1EndAdvancedDialogue()
{
	std::string level1EndHilma = "Här är alla! Precis vad du bad om. Har jag övertygat dig tillräckligt?";
	std::string level1EndTeller = "När Thomas fick syn på alla föremål kunde han inte tro sina ögon. Han som hade letat så mycket själv! Hans mamma hade sagt att när något försvann i hans stökiga rum, var det försvunnet för alltid. Tydligen inte för en hittare.";
	std::string level1EndHilma2 = "Jag sa ju det! Jag hittar vad som helst, var som helst!";
	std::string level1EndTeller2 = "Då fick han ett litet, litet leende på läpparna. Han tackade så mycket för Hilmas hjälp. Men hans leende försvann snabbt när han såg skruvmackapären.";
	std::string level1EndTeller3 = "Han blev alldeles tyst och stirrade på den. Plötsligt kunde han inte bara ge den till den hjälpsamma hittaren. Han höll hårdare i skruvmackapären. Nu började Hilma bli otålig med Thomas tvekanden.";
	std::string level1EndHilma3 = "Hallå? Jorden anropar!";
	std::string level1EndThomas = "F- förlåt jag- jag... *tar ett andetag* Det är bara det att det inte är min skruvmackapär jag ger dig.";
	std::string level1EndHilma4 = "Jaha ja, vems är det då om man får fråga? Har du stulit den?";
	std::string level1EndThomas2 = "Ne-Nej! Absolut inte! Det... *djupt andetag* Jag lånade den av min... mormor.";
	std::string level1EndHilma5 = "Din mormors? Vem är denne mormor då som låter en slarvgosse som du ta hand om en skruvmackapär?";
	std::string level1EndThomas3 = "Min mormor är den bästa mekanikern och rymdpiloten som någonsin har funnits!";
	std::string level1EndHilma6 = "Jaha jaså ja... Vad kan den här mormor bygga då?";
	std::string level1EndThomas4 = "Hon kan bygga allt... och laga allt. Hon lagar bilar, cykelpunkor och bygger de bästa lådbilarna, flygplanen... och! Och just nu bygger vi en rymdraket som ska ta oss till månen! Där ska vi bo och jobba som rymdcowboys-";
	std::string level1EndThomas5 = "Det var det hon sa vi skulle göra i alla fall...";
	std::string level1EndHilma7 = "Jaså vad då då, törs hon inte eller?";
	std::string level1EndThomas6 = "Så klart hon törs! Det är inte det... Hon... hon är- hon är borta...";
	std::string level1EndThomas7 = "Hon har försvunnit och ingen har hittat henne!";
	std::string level1EndTeller4 = "Stackars pojke! Skulle de flesta ha sagt. Det råkar vara så att Hilma inte är så förtjust i gråtande barn. Men det pojken sade, gav henne en idé. Hon visste inte själv om hon kunde göra det, men om pojken skulle sluta gråta var det nog till hjälp.";
	std::string level1EndHilma8 = "Din mormor är borttappad eller hur? Och vad är mitt jobb?";
	std::string level1EndThomas8 = "...Att hitta bortappade saker?";
	std::string level1EndHilma9 = "Jamen se där ja! Du är ju inte helt bakom flötet! Du förstår, jag har aldrig letat efter borttappade människor. Men det ska nog gå ändå, för jag är den bästa hittaren och hantverkaren du någonsin kommer få träffa! Jag ska hitta mormor åt dig!";
	std::string level1EndTeller5 = "Ja, Hilmas plan verkade fungera. För nu slutade tårarna rinna på Thomas. Kunde verkligen Hilma hitta mormor? Thomas sken upp i lycka.";
	std::string level1EndThomas9 = "Verkligen? Kan du hitta henne?";
	std::string level1EndHilma10 = "Ja! Men! På ett villkor!";
	std::string level1EndThomas10 = "Vad vill du ha i utbyte?";
	std::string level1EndHilma11 = "Rymdskeppet som du och mormor byggde på. Om hon verkligen kan bygga fantastiska saker borde den vara bättre än min flygfarkost, vilket jag tvivlar på. Men, men! Vad väntar vi på? Nu ska vi hitta din mormor!";
	std::string level1EndTeller6 = "Thomas nickade och leendet kom sakta tillbaka. Ett hopp hade grott inom honom. Det var en början på ett äventyr han aldrig skulle glömma.";

	if (mState == 27)
	{
		mText.setString("");
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
		createTextBox(-250.f, 300.f, 1.f, 1.f, 0.4f, 0.40f);  //(-1.0f, 280.0f, 1.0f, 1.0f, 0.267f, 0.45f)
	}
	if (mState == 1)
	{
		advancedText(level1EndTeller, 100.f, 420.f, 1.f, 1.f);
	}
	if (mState == 2)
	{
		advancedText(level1EndHilma2, 100.f, 420.f, 1.f, 1.f);
		drawSecondCharacter(mHandler, 700.f, 30.f, 1.f, 1.f, 0.2f, 0.2f, "expressionThomasHappy.png");
	}
	if (mState == 3)
	{
		advancedText(level1EndTeller2, 100.f, 420.f, 1.f, 1.f);
		drawSecondCharacter(mHandler, 700.f, 30.f, 1.f, 1.f, 0.2f, 0.2f, "expressionThomasSad.png");
	}
	if (mState == 4)
	{
		advancedText(level1EndTeller3, 100.f, 420.f, 1.f, 1.f);
	}
	if (mState == 5)
	{
		advancedText(level1EndHilma3, 100.f, 420.f, 1.f, 1.f);
		drawFirstCharacter(mHandler, 300.f, 30.f, 1.f, 1.f, -0.2f, 0.2f, "expressionHilmaGrumpy.png");
	}
	if (mState == 6)
	{
		advancedText(level1EndThomas, 100.f, 420.f, 1.f, 1.f);
	}
	if (mState == 7)
	{
		advancedText(level1EndHilma4, 100.f, 420.f, 1.f, 1.f);
		drawFirstCharacter(mHandler, 300.f, 30.f, 1.f, 1.f, -0.2f, 0.2f, "expressionHilmaConfident.png");
	}
	if (mState == 8)
	{
		advancedText(level1EndThomas2, 100.f, 420.f, 1.f, 1.f);
		drawSecondCharacter(mHandler, 700.f, 30.f, 1.f, 1.f, 0.2f, 0.2f, "expressionThomasSigh.png");
	}
	if (mState == 9)
	{
		advancedText(level1EndHilma5, 100.f, 420.f, 1.f, 1.f);
	}
	if (mState == 10)
	{
		advancedText(level1EndThomas3, 100.f, 420.f, 1.f, 1.f);
		drawSecondCharacter(mHandler, 700.f, 30.f, 1.f, 1.f, 0.2f, 0.2f, "expressionThomasGrumpy.png");
	}
	if (mState == 11)
	{
		advancedText(level1EndHilma6, 100.f, 420.f, 1.f, 1.f);
		drawFirstCharacter(mHandler, 300.f, 30.f, 1.f, 1.f, -0.2f, 0.2f, "expressionHilmaGrumpy.png");
	}
	if (mState == 12)
	{
		advancedText(level1EndThomas4, 100.f, 420.f, 1.f, 1.f);
		drawSecondCharacter(mHandler, 700.f, 30.f, 1.f, 1.f, 0.2f, 0.2f, "expressionThomasHappy.png");
	}
	if (mState == 13)
	{
		advancedText(level1EndThomas5, 100.f, 420.f, 1.f, 1.f);
		drawSecondCharacter(mHandler, 700.f, 30.f, 1.f, 1.f, 0.2f, 0.2f, "expressionThomasSigh.png");
	}
	if (mState == 14)
	{
		advancedText(level1EndHilma7, 100.f, 420.f, 1.f, 1.f);
		drawFirstCharacter(mHandler, 300.f, 30.f, 1.f, 1.f, -0.2f, 0.2f, "expressionHilmaNeutral.png");
	}
	if (mState == 15)
	{
		advancedText(level1EndThomas6, 100.f, 420.f, 1.f, 1.f);
		drawSecondCharacter(mHandler, 700.f, 30.f, 1.f, 1.f, 0.2f, 0.2f, "expressionThomasGrumpy.png");
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
	}
	if (mState == 18)
	{
		advancedText(level1EndHilma8, 100.f, 420.f, 1.f, 1.f);
		drawFirstCharacter(mHandler, 300.f, 30.f, 1.f, 1.f, -0.2f, 0.2f, "expressionHilmaConfident.png");
	}
	if (mState == 19)
	{
		advancedText(level1EndThomas8, 100.f, 420.f, 1.f, 1.f);
		drawSecondCharacter(mHandler, 700.f, 30.f, 1.f, 1.f, 0.2f, 0.2f, "expressionThomasSad.png");
	}
	if (mState == 20)
	{
		advancedText(level1EndHilma9, 100.f, 420.f, 1.f, 1.f);
		drawFirstCharacter(mHandler, 300.f, 30.f, 1.f, 1.f, -0.2f, 0.2f, "expressionHilmaHappy.png");
	}
	if (mState == 21)
	{
		advancedText(level1EndTeller5, 100.f, 420.f, 1.f, 1.f);
	}
	if (mState == 22)
	{
		advancedText(level1EndThomas9, 100.f, 420.f, 1.f, 1.f);
		drawSecondCharacter(mHandler, 700.f, 30.f, 1.f, 1.f, 0.2f, 0.2f, "expressionThomasSmile.png");
	}
	if (mState == 23)
	{
		advancedText(level1EndHilma10, 100.f, 420.f, 1.f, 1.f);
		drawFirstCharacter(mHandler, 300.f, 30.f, 1.f, 1.f, -0.2f, 0.2f, "expressionHilmaDetermined.png");
	}
	if (mState == 24)
	{
		advancedText(level1EndThomas10, 100.f, 420.f, 1.f, 1.f);
		drawSecondCharacter(mHandler, 700.f, 30.f, 1.f, 1.f, 0.2f, 0.2f, "expressionThomasHappy.png");
	}
	if (mState == 25)
	{
		advancedText(level1EndHilma11, 100.f, 420.f, 1.f, 1.f);
		drawFirstCharacter(mHandler, 300.f, 30.f, 1.f, 1.f, -0.2f, 0.2f, "expressionHilmaConfident.png");
	}
	if (mState == 26)
	{
		advancedText(level1EndTeller6, 100.f, 420.f, 1.f, 1.f);
	}
}

//Dialogue functions down below
//Thomas' Room
void DialogueSystem::displayBooksDialogue()
{
	std::string booksHilma = "Hur många böcker har du egentligen?";
	std::string booksThomas = "Senast jag räknade var det tjugofyra, men... det var ju ett tag sen…";

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
			text(booksHilma, mPlayer->getPosition(), -280, -220);
			createTalkBubble(mPlayer->getPosition(), -305, -235, 0.3f, 0.2f);
		}
		if (mPlayer->isFacingLeft() == false)
		{
			text(booksHilma, mPlayer->getPosition(), 60, -220);
			createTalkBubble(mPlayer->getPosition(), 40, -235, 0.3f, 0.2f);
		}
	}
	if (mState == 1)
	{
		if (mPlayer->isFacingLeft() == true)
		{
			text(booksThomas, mPlayer->getPosition(), 60, -250);
			createTalkBubble(mPlayer->getPosition(), 40, -280, 0.25f, 0.25f);
		}
		if (mPlayer->isFacingLeft() == false)
		{
			text(booksThomas, mPlayer->getPosition(), -260, -250);
			createTalkBubble(mPlayer->getPosition(), -285, -280, 0.25f, 0.25f);
		}
	}
}

void DialogueSystem::displayLampDialogue()
{
	std::string lampHilma = "Vad för oansvarig människa placerar en lampa vid sitt fönster? Jag flög nästan in i den innan!";
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
			text(lampHilma, mPlayer->getPosition(), -300, -220);
			createTalkBubble(mPlayer->getPosition(), -325, -265, 0.32f, 0.3f);
		}
		if (mPlayer->isFacingLeft() == false)
		{
			text(lampHilma, mPlayer->getPosition(), 60, -220);
			createTalkBubble(mPlayer->getPosition(), 40, -265, 0.32f, 0.3f);
		}
	}

	if (mState == 1)
	{
		if (mPlayer->isFacingLeft() == true)
		{
			text(lampThomas, mPlayer->getPosition(), 60, -250);
			createTalkBubble(mPlayer->getPosition(), 40, -265, 0.25f, 0.2f);
		}
		if (mPlayer->isFacingLeft() == false)
		{
			text(lampThomas, mPlayer->getPosition(), -260, -250);
			createTalkBubble(mPlayer->getPosition(), -285, -265, 0.25f, 0.2f);
		}
	}

	if (mState == 2)
	{
		if (mPlayer->isFacingLeft() == true)
		{
			text(lampHilma2, mPlayer->getPosition(), -230, -220);
			createTalkBubble(mPlayer->getPosition(), -250, -235, 0.22f, 0.2f);
		}
		if (mPlayer->isFacingLeft() == false)
		{
			text(lampHilma2, mPlayer->getPosition(), 60, -220);
			createTalkBubble(mPlayer->getPosition(), 40, -235, 0.22f, 0.2f);
		}
	}

	if (mState == 3)
	{
		if (mPlayer->isFacingLeft() == true)
		{
			text(lampThomas2, mPlayer->getPosition(), 60, -250);
			createTalkBubble(mPlayer->getPosition(), 40, -295, 0.25f, 0.3f);
		}
		if (mPlayer->isFacingLeft() == false)
		{
			text(lampThomas2, mPlayer->getPosition(), -260, -250);
			createTalkBubble(mPlayer->getPosition(), -285, -295, 0.25f, 0.3f);
		}
	}
	if (mState == 4)
	{
		if (mPlayer->isFacingLeft() == true)
		{
			text(lampHilma3, mPlayer->getPosition(), -100, -180);
			createTalkBubble(mPlayer->getPosition(), -115, -190, 0.09f, 0.1f);
		}
		if (mPlayer->isFacingLeft() == false)
		{
			text(lampHilma3, mPlayer->getPosition(), 60, -180);
			createTalkBubble(mPlayer->getPosition(), 40, -190, 0.09f, 0.1f);
		}
	}
}

void DialogueSystem::displayRubicCubeDialogue()
{
	std::string rubicHilma = "Vad är det här?";
	std::string rubicThomas = "En Rubiks kub, man ska få alla färgerna på varsin sida.";
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
			text(rubicHilma, mPlayer->getPosition(), -180, -180);
			createTalkBubble(mPlayer->getPosition(), -195, -190, 0.18f, 0.1f);
		}
		if (mPlayer->isFacingLeft() == false)
		{
			text(rubicHilma, mPlayer->getPosition(), 60, -180);
			createTalkBubble(mPlayer->getPosition(), 40, -190, 0.18f, 0.1f);
		}
	}
	if (mState == 1)
	{
		if (mPlayer->isFacingLeft() == true)
		{
			text(rubicThomas, mPlayer->getPosition(), 60, -250);
			createTalkBubble(mPlayer->getPosition(), 40, -265, 0.3f, 0.2f);
		}
		if (mPlayer->isFacingLeft() == false)
		{
			text(rubicThomas, mPlayer->getPosition(), -280, -250);
			createTalkBubble(mPlayer->getPosition(), -305, -265, 0.3f, 0.2f);
		}
	}
	if (mState == 2)
	{
		if (mPlayer->isFacingLeft() == true)
		{
			text(rubicHilma2, mPlayer->getPosition(), -280, -220);
			createTalkBubble(mPlayer->getPosition(), -305, -235, 0.3f, 0.2f);
		}
		if (mPlayer->isFacingLeft() == false)
		{
			text(rubicHilma2, mPlayer->getPosition(), 60, -220);
			createTalkBubble(mPlayer->getPosition(), 40, -235, 0.3f, 0.2f);
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
			text(posterHilma, mPlayer->getPosition(), -200, -220);
			createTalkBubble(mPlayer->getPosition(), -220, -235, 0.2f, 0.2f);
		}
		if (mPlayer->isFacingLeft() == false)
		{
			text(posterHilma, mPlayer->getPosition(), 60, -220);
			createTalkBubble(mPlayer->getPosition(), 40, -235, 0.2f, 0.2f);
		}
	}

	if (mState == 1)
	{
		if (mPlayer->isFacingLeft() == true)
		{
			text(posterThomas, mPlayer->getPosition(), 70, -250);
			createTalkBubble(mPlayer->getPosition(), 45, -295, 0.3f, 0.3f);
		}
		if (mPlayer->isFacingLeft() == false)
		{
			text(posterThomas, mPlayer->getPosition(), -295, -250);
			createTalkBubble(mPlayer->getPosition(), -315, -295, 0.3f, 0.3f);
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
			text(backpackHilma, mPlayer->getPosition(), -250, -220);
			createTalkBubble(mPlayer->getPosition(), -270, -235, 0.25f, 0.2f);
		}
		if (mPlayer->isFacingLeft() == false)
		{
			text(backpackHilma, mPlayer->getPosition(), 60, -220);
			createTalkBubble(mPlayer->getPosition(), 40, -235, 0.25f, 0.2f);
		}
	}

	if (mState == 1)
	{
		if (mPlayer->isFacingLeft() == true)
		{
			text(backpackThomas, mPlayer->getPosition(), 70, -250);
			createTalkBubble(mPlayer->getPosition(), 50, -280, 0.25f, 0.25f);
		}
		if (mPlayer->isFacingLeft() == false)
		{
			text(backpackThomas, mPlayer->getPosition(), -260, -250);
			createTalkBubble(mPlayer->getPosition(), -280, -280, 0.25f, 0.25f);
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
			text(bowlHilma, mPlayer->getPosition(), -270, -220);
			createTalkBubble(mPlayer->getPosition(), -290, -235, 0.28f, 0.2f);
		}
		if (mPlayer->isFacingLeft() == false)
		{
			text(bowlHilma, mPlayer->getPosition(), 60, -220);
			createTalkBubble(mPlayer->getPosition(), 40, -235, 0.28f, 0.2f);
		}
	}

	if (mState == 1)
	{
		if (mPlayer->isFacingLeft() == true)
		{
			text(bowlThomas, mPlayer->getPosition(), 60, -220);
			createTalkBubble(mPlayer->getPosition(), 40, -230, 0.17f, 0.1f);
		}
		if (mPlayer->isFacingLeft() == false)
		{
			text(bowlThomas, mPlayer->getPosition(), -200, -220);
			createTalkBubble(mPlayer->getPosition(), -215, -230, 0.17f, 0.1f);
		}
	}

	if (mState == 2)
	{
		if (mPlayer->isFacingLeft() == true)
		{
			text(bowlHilma2, mPlayer->getPosition(), -160, -180);
			createTalkBubble(mPlayer->getPosition(), -175, -190, 0.15f, 0.1f);
		}
		if (mPlayer->isFacingLeft() == false)
		{
			text(bowlHilma2, mPlayer->getPosition(), 60, -180);
			createTalkBubble(mPlayer->getPosition(), 40, -190, 0.15f, 0.1f);
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
			text(radioHilma, mPlayer->getPosition(), -280, -220);
			createTalkBubble(mPlayer->getPosition(), -305, -235, 0.3f, 0.2f);
		}
		if (mPlayer->isFacingLeft() == false)
		{
			text(radioHilma, mPlayer->getPosition(), 60, -220);
			createTalkBubble(mPlayer->getPosition(), 40, -235, 0.3f, 0.2f);
		}
	}

	if (mState == 1)
	{
		if (mPlayer->isFacingLeft() == true)
		{
			text(radioThomas, mPlayer->getPosition(), 60, -250);
			createTalkBubble(mPlayer->getPosition(), 40, -265, 0.25f, 0.2f);
		}
		if (mPlayer->isFacingLeft() == false)
		{
			text(radioThomas, mPlayer->getPosition(), -260, -250);
			createTalkBubble(mPlayer->getPosition(), -285, -265, 0.25f, 0.2f);
		}
	}

	if (mState == 2)
	{
		if (mPlayer->isFacingLeft() == true)
		{
			text(radioHilma2, mPlayer->getPosition(), -115, -170);
			createTalkBubble(mPlayer->getPosition(), -130, -180, 0.1f, 0.1f);
		}
		if (mPlayer->isFacingLeft() == false)
		{
			text(radioHilma2, mPlayer->getPosition(), 60, -180);
			createTalkBubble(mPlayer->getPosition(), 40, -190, 0.1f, 0.1f);
		}
	}
}

void DialogueSystem::displayMatDialogue()
{
	std::string matHilma = "Magneten dras mot mattan.";

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
			text(matHilma, mPlayer->getPosition(), -260, -180);
			createTalkBubble(mPlayer->getPosition(), -275, -190, 0.27f, 0.1f);
		}
		if (mPlayer->isFacingLeft() == false)
		{
			text(matHilma, mPlayer->getPosition(), 60, -220);
			createTalkBubble(mPlayer->getPosition(), 40, -235, 0.27f, 0.1f);
		}
	}
}

void DialogueSystem::displayStarDialogue()
{
	std::string starHilma = "Den här stjärnan ser inte ut som de andra... tror du att..?";

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
			text(starHilma, mPlayer->getPosition(), -260, -220);
			createTalkBubble(mPlayer->getPosition(), -275, -250, 0.27f, 0.25f);
		}
		if (mPlayer->isFacingLeft() == false)
		{
			text(starHilma, mPlayer->getPosition(), 60, -220);
			createTalkBubble(mPlayer->getPosition(), 40, -250, 0.27f, 0.25f);
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
			text(aquariumHilma, mPlayer->getPosition(), -280, -220);
			createTalkBubble(mPlayer->getPosition(), -305, -250, 0.3f, 0.25f);
		}
		if (mPlayer->isFacingLeft() == false)
		{
			text(aquariumHilma, mPlayer->getPosition(), 60, -220);
			createTalkBubble(mPlayer->getPosition(), 40, -250, 0.3f, 0.25f);
		}
	}

	if (mState == 1)
	{
		if (mPlayer->isFacingLeft() == true)
		{
			text(aquariumThomas, mPlayer->getPosition(), 60, -250);
			createTalkBubble(mPlayer->getPosition(), 40, -265, 0.26f, 0.2f);
		}
		if (mPlayer->isFacingLeft() == false)
		{
			text(aquariumThomas, mPlayer->getPosition(), -260, -250);
			createTalkBubble(mPlayer->getPosition(), -285, -265, 0.26f, 0.2f);
		}
	}

	if (mState == 2)
	{
		if (mPlayer->isFacingLeft() == true)
		{
			text(aquariumHilma2, mPlayer->getPosition(), -230, -220);
			createTalkBubble(mPlayer->getPosition(), -250, -235, 0.25f, 0.2f);
		}
		if (mPlayer->isFacingLeft() == false)
		{
			text(aquariumHilma2, mPlayer->getPosition(), 60, -220);
			createTalkBubble(mPlayer->getPosition(), 40, -235, 0.25f, 0.2f);
		}
	}

	if (mState == 3)
	{
		if (mPlayer->isFacingLeft() == true)
		{
			text(aquariumThomas2, mPlayer->getPosition(), 60, -250);
			createTalkBubble(mPlayer->getPosition(), 40, -265, 0.25f, 0.2f);
		}
		if (mPlayer->isFacingLeft() == false)
		{
			text(aquariumThomas2, mPlayer->getPosition(), -260, -250);
			createTalkBubble(mPlayer->getPosition(), -285, -265, 0.25f, 0.2f);
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
			text(blockHilma, mPlayer->getPosition(), -230, -220);
			createTalkBubble(mPlayer->getPosition(), -250, -235, 0.22f, 0.2f);
		}
		if (mPlayer->isFacingLeft() == false)
		{
			text(blockHilma, mPlayer->getPosition(), 60, -220);
			createTalkBubble(mPlayer->getPosition(), 40, -235, 0.22f, 0.2f);
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
			text(astronautHilma, mPlayer->getPosition(), -280, -220);
			createTalkBubble(mPlayer->getPosition(), -305, -250, 0.26f, 0.25f);
		}
		if (mPlayer->isFacingLeft() == false)
		{
			text(astronautHilma, mPlayer->getPosition(), 60, -220);
			createTalkBubble(mPlayer->getPosition(), 40, -250, 0.26f, 0.25f);
		}
	}

	if (mState == 1)
	{
		if (mPlayer->isFacingLeft() == true)
		{
			text(astronautThomas, mPlayer->getPosition(), 60, -250);
			createTalkBubble(mPlayer->getPosition(), 40, -280, 0.27f, 0.25f);
		}
		if (mPlayer->isFacingLeft() == false)
		{
			text(astronautThomas, mPlayer->getPosition(), -285, -250);
			createTalkBubble(mPlayer->getPosition(), -300, -280, 0.27f, 0.25f);
		}
	}

	if (mState == 2)
	{
		if (mPlayer->isFacingLeft() == true)
		{
			text(astronautHilma2, mPlayer->getPosition(), -280, -220);
			createTalkBubble(mPlayer->getPosition(), -305, -250, 0.32f, 0.25f);
		}
		if (mPlayer->isFacingLeft() == false)
		{
			text(astronautHilma2, mPlayer->getPosition(), 60, -220);
			createTalkBubble(mPlayer->getPosition(), 40, -250, 0.32f, 0.25f);
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
			text(magnetHilma, mPlayer->getPosition(), -270, -220);
			createTalkBubble(mPlayer->getPosition(), -290, -235, 0.27f, 0.2f);
		}
		if (mPlayer->isFacingLeft() == false)
		{
			text(magnetHilma, mPlayer->getPosition(), 60, -220);
			createTalkBubble(mPlayer->getPosition(), 40, -235, 0.27f, 0.2f);
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
			text(stringHilma, mPlayer->getPosition(), -160, -180);
			createTalkBubble(mPlayer->getPosition(), -175, -190, 0.14f, 0.1f);
		}
		if (mPlayer->isFacingLeft() == false)
		{
			text(stringHilma, mPlayer->getPosition(), 60, -180);
			createTalkBubble(mPlayer->getPosition(), 40, -190, 0.14f, 0.1f);
		}
	}
}

//Grandma's Livingroom
void DialogueSystem::displayBooks2Dialogue()
{
	std::string books2Thomas = "Rymdböcker… precis som mina där hemma.";

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
		createTalkBubble(mPlayer->getPosition(), 60, -250, 2.5f, 1.f);
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