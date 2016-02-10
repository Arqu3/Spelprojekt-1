#include "DialogueSystem.h"
#include <iostream>
#include "SFML\System.hpp"

DialogueSystem::DialogueSystem(LevelHandler &levelHandler, ResourceHandler &handler):
mHasClicked(false),
mTime(0),
mText(),
mFont(),
mIsActive(false),
mLevelHandler(&levelHandler)
{
	mFont.loadFromFile("Resources/Fonts/ShadowsIntoLight.ttf");
	mBubble.setTexture(*handler.getTexture("textbubble.png"));
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
	mText.setColor(sf::Color::White);
	mText.setPosition(position);
	mText.move(x, y);
	mText.setString(text);
}

//Draw function for game to use
void DialogueSystem::drawDialogue(sf::RenderWindow &window)
{
	if (mIsActive)
	{
		window.draw(mBubble);
	}
	window.draw(mText);
}

void DialogueSystem::createTalkBubble(sf::Vector2f &position, float OffSetX, float OffSetY, float x, float y)
{
	mBubble.setPosition(position);
	mBubble.setScale(sf::Vector2f(x, y));
	mBubble.move(OffSetX, OffSetY);
}

//Function to check if the player has clicked on an object
void DialogueSystem::hasClicked(std::string indexName)
{
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
	mHasClicked = false;
	mState = 0;

	mText.setString("");
}

//Update function
void DialogueSystem::update(float time)
{
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

//Dialogue functions down below
//Thomas' Room
void DialogueSystem::displayBooksDialogue()
{
	std::string booksHilma = "Hur m�nga b�cker har du egentligen?";
	std::string booksThomas = "Senast jag r�knade var det tjugofyra, men� det var ju ett tag sen�";

	if (mState == 2)
	{
		mText.setString("");
		mHasClicked = false;
		mBooks = false;
		mIsActive = false;
	}
	if (mState == 0)
	{
		mIsActive = true;
		text(booksHilma, mLevelHandler->getPlayer()->getPosition(), -180, -180);
		createTalkBubble(mLevelHandler->getPlayer()->getPosition(), -180, -200, 2.1f, 1.f);
	}
	if (mState == 1)
	{
		text(booksThomas, mLevelHandler->getPlayer()->getPosition(), 60, -250);
		createTalkBubble(mLevelHandler->getPlayer()->getPosition(), 60, -250, 2.5f, 1.f);
	}
}

void DialogueSystem::displayLampDialogue()
{
	std::string lampHilma = "Vad f�r oansvarig m�nniska placerar en lampa vid sitt f�nster ? Jag fl�g n�stan in i den innan!";
	std::string lampThomas = "Jag visste inte att det var farligt med lampor�";
	std::string lampHilma2 = "Ni m�nniskor �r s� v�rdsl�sa.";
	std::string lampThomas2 = "Det var ju faktiskt du som krashade i mitt rum. Det tycker jag l�ter v�rdsl�st.";
	std::string lampHilma3 = "Hmpf.";

	if (mState == 5)
	{
		mText.setString("");
		mHasClicked = false;
		mLamp = false;
		mIsActive = false;
	}

	if (mState == 0)
	{
		mIsActive = true;
		text(lampHilma, mLevelHandler->getPlayer()->getPosition(), -180, -180);
		createTalkBubble(mLevelHandler->getPlayer()->getPosition(), -180, -200, 2.1f, 1.f);
	}

	if (mState == 1)
	{
		text(lampThomas, mLevelHandler->getPlayer()->getPosition(), 60, -250);
		createTalkBubble(mLevelHandler->getPlayer()->getPosition(), 60, -250, 2.5f, 1.f);
	}

	if (mState == 2)
	{
		text(lampHilma2, mLevelHandler->getPlayer()->getPosition(), -250, -250);
		createTalkBubble(mLevelHandler->getPlayer()->getPosition(), -250, -250, 2.5f, 1.f);
	}

	if (mState == 3)
	{
		text(lampThomas2, mLevelHandler->getPlayer()->getPosition(), 60, -250);
		createTalkBubble(mLevelHandler->getPlayer()->getPosition(), 60, -250, 2.5f, 1.f);
	}
	if (mState == 4)
	{
		text(lampHilma3, mLevelHandler->getPlayer()->getPosition(), -250, -250);
		createTalkBubble(mLevelHandler->getPlayer()->getPosition(), -250, -250, 2.5f, 1.f);
	}
}

void DialogueSystem::displayRubicCubeDialogue()
{
	std::string rubicHilma = "Vad �r det h�r?";
	std::string rubicThomas = "En Rubiks kub, man ska \nf� alla f�rgerna p� varsin sida.";
	std::string rubicHilma2 = "Men vad �r det f�r utmaning? \nL�ter ju j�ttel�tt!";

	if (mState == 3)
	{
		mText.setString("");
		mHasClicked = false;
		mRubicCube = false;
		mIsActive = false;
	}

	if (mState == 0)
	{
		mIsActive = true;
		text(rubicHilma, mLevelHandler->getPlayer()->getPosition(), -180, -180);
		createTalkBubble(mLevelHandler->getPlayer()->getPosition(), -180, -200, 2.1f, 1.f);
	}
	if (mState == 1)
	{
		text(rubicThomas, mLevelHandler->getPlayer()->getPosition(), 60, -250);
		createTalkBubble(mLevelHandler->getPlayer()->getPosition(), 60, -250, 2.5f, 1.f);
	}
	if (mState == 2)
	{
		text(rubicHilma2, mLevelHandler->getPlayer()->getPosition(), -250, -250);
		createTalkBubble(mLevelHandler->getPlayer()->getPosition(), -250, -250, 2.5f, 1.f);
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
	}

	if (mState == 0)
	{
		mIsActive = true;
		text(posterHilma, mLevelHandler->getPlayer()->getPosition(), -180, -180);
		createTalkBubble(mLevelHandler->getPlayer()->getPosition(), -180, -200, 2.1f, 1.f);
	}

	if (mState == 1)
	{
		text(posterThomas, mLevelHandler->getPlayer()->getPosition(), 60, -250);
		createTalkBubble(mLevelHandler->getPlayer()->getPosition(), 60, -250, 2.5f, 1.f);
	}
}

void DialogueSystem::displayBackpackDialogue()
{
	std::string backpackHilma = "Vad �r det f�r en massa papper i v�skan?";
	std::string backpackThomas = "L�xor� de var roliga ett tag men sen fick jag bara fler och fler!";

	if (mState == 2)
	{
		mText.setString("");
		mHasClicked = false;
		mBackpack = false;
		mIsActive = false;
	}

	if (mState == 0)
	{
		mIsActive = true;
		text(backpackHilma, mLevelHandler->getPlayer()->getPosition(), -180, -180);
		createTalkBubble(mLevelHandler->getPlayer()->getPosition(), -180, -200, 2.1f, 1.f);
	}

	if (mState == 1)
	{
		text(backpackThomas, mLevelHandler->getPlayer()->getPosition(), 60, -250);
		createTalkBubble(mLevelHandler->getPlayer()->getPosition(), 60, -250, 2.5f, 1.f);
	}
}

void DialogueSystem::displayBowlDialogue()
{
	std::string bowlHilma = "Anv�nde du den h�r n�r du klippte dig eller?";
	std::string bowlThomas = "Vad menar du?";
	std::string bowlHilma2 = "�h, gl�m det�";

	if (mState == 3)
	{
		mText.setString("");
		mHasClicked = false;
		mBowl = false;
		mIsActive = false;
	}

	if (mState == 0)
	{
		mIsActive = true;
		text(bowlHilma, mLevelHandler->getPlayer()->getPosition(), -180, -180);
		createTalkBubble(mLevelHandler->getPlayer()->getPosition(), -180, -200, 2.1f, 1.f);
	}

	if (mState == 1)
	{
		text(bowlThomas, mLevelHandler->getPlayer()->getPosition(), 60, -250);
		createTalkBubble(mLevelHandler->getPlayer()->getPosition(), 60, -250, 2.5f, 1.f);
	}

	if (mState == 2)
	{
		text(bowlHilma2, mLevelHandler->getPlayer()->getPosition(), -180, -180);
		createTalkBubble(mLevelHandler->getPlayer()->getPosition(), -180, -200, 2.1f, 1.f);
	}
}

void DialogueSystem::displayRadioDialogue()
{
	std::string radioHilma = "En radio! De brukar vara fulla av anv�ndbara delar!";
	std::string radioThomas = "Sn�lla f�rst�r inte min radio.";
	std::string radioHilma2 = "Okej d�";

	if (mState == 3)
	{
		mText.setString("");
		mHasClicked = false;
		mRadio = false;
		mIsActive = false;
	}

	if (mState == 0)
	{
		mIsActive = true;
		text(radioHilma, mLevelHandler->getPlayer()->getPosition(), -180, -180);
		createTalkBubble(mLevelHandler->getPlayer()->getPosition(), -180, -200, 2.1f, 1.f);
	}

	if (mState == 1)
	{
		text(radioThomas, mLevelHandler->getPlayer()->getPosition(), 60, -250);
		createTalkBubble(mLevelHandler->getPlayer()->getPosition(), 60, -250, 2.5f, 1.f);
	}

	if (mState == 2)
	{
		text(radioHilma2, mLevelHandler->getPlayer()->getPosition(), -180, -180);
		createTalkBubble(mLevelHandler->getPlayer()->getPosition(), -180, -200, 2.1f, 1.f);
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
	}

	if (mState == 0)
	{
		mIsActive = true;
		text(matHilma, mLevelHandler->getPlayer()->getPosition(), -180, -180);
		createTalkBubble(mLevelHandler->getPlayer()->getPosition(), -180, -200, 2.1f, 1.f);
	}
}

void DialogueSystem::displayStarDialogue()
{
	std::string starHilma = "Den h�r stj�rnan ser inte ut som de andra... tror du att..?";

	if (mState == 1)
	{
		mText.setString("");
		mHasClicked = false;
		mStar = false;
		mIsActive = false;
	}

	if (mState == 0)
	{
		mIsActive = true;
		text(starHilma, mLevelHandler->getPlayer()->getPosition(), -180, -180);
		createTalkBubble(mLevelHandler->getPlayer()->getPosition(), -180, -200, 2.1f, 1.f);
	}
}

void DialogueSystem::displayAquariumDialogue()
{
	std::string aquariumHilma = "Varf�r har du en fisk inne p� rummet? Dem ska ja vara i sj�ar!";
	std::string aquariumThomas = "Men det �r mitt husdjur, han heter Roger.";
	std::string aquariumHilma2 = "Kan Roger ha �tit upp astronauten?";
	std::string aquariumThomas2 = "N�, inte Roger, han �r sn�ll.";

	if (mState == 4)
	{
		mText.setString("");
		mHasClicked = false;
		mAquarium = false;
		mIsActive = false;
	}

	if (mState == 0)
	{
		mIsActive = true;
		text(aquariumHilma, mLevelHandler->getPlayer()->getPosition(), -180, -180);
		createTalkBubble(mLevelHandler->getPlayer()->getPosition(), -180, -200, 2.1f, 1.f);
	}

	if (mState == 1)
	{
		text(aquariumThomas, mLevelHandler->getPlayer()->getPosition(), 60, -250);
		createTalkBubble(mLevelHandler->getPlayer()->getPosition(), 60, -250, 2.5f, 1.f);
	}

	if (mState == 2)
	{
		text(aquariumHilma2, mLevelHandler->getPlayer()->getPosition(), -180, -180);
		createTalkBubble(mLevelHandler->getPlayer()->getPosition(), -180, -200, 2.1f, 1.f);
	}

	if (mState == 3)
	{
		text(aquariumThomas2, mLevelHandler->getPlayer()->getPosition(), 60, -250);
		createTalkBubble(mLevelHandler->getPlayer()->getPosition(), 60, -250, 2.5f, 1.f);
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
	}

	if (mState == 0)
	{
		mIsActive = true;
		text(blockHilma, mLevelHandler->getPlayer()->getPosition(), -180, -180);
		createTalkBubble(mLevelHandler->getPlayer()->getPosition(), -180, -200, 2.1f, 1.f);
	}
}

void DialogueSystem::displayAstronautDialogue()
{
	std::string astronautHilma = "D�r �r astronauten! Titta Thomas! Jag hittade den!";
	std::string astronautThomas = "Ja� men den �r ju i akvariet. Jag vill ha den i handen!";
	std::string astronautHilma2 = "Okej d�, jag f�r v�l hitta ett s�tt att fiska upp den.";

	if (mState == 3)
	{
		mText.setString("");
		mHasClicked = false;
		mAstronaut = false;
		mIsActive = false;
	}

	if (mState == 0)
	{
		mIsActive = true;
		text(astronautHilma, mLevelHandler->getPlayer()->getPosition(), -180, -180);
		createTalkBubble(mLevelHandler->getPlayer()->getPosition(), -180, -200, 2.1f, 1.f);
	}

	if (mState == 1)
	{
		text(astronautThomas, mLevelHandler->getPlayer()->getPosition(), 60, -250);
		createTalkBubble(mLevelHandler->getPlayer()->getPosition(), 60, -250, 2.5f, 1.f);
	}

	if (mState == 2)
	{
		text(astronautHilma2, mLevelHandler->getPlayer()->getPosition(), -180, -180);
		createTalkBubble(mLevelHandler->getPlayer()->getPosition(), -180, -200, 2.1f, 1.f);
	}
}

void DialogueSystem::displayMagnetDialogue()
{
	std::string magnetHilma = "En magnet� hmm \nden kan vara anv�ndbar.";

	if (mState == 1)
	{
		mText.setString("");
		mHasClicked = false;
		mMagnet = false;
		mIsActive = false;
	}

	if (mState == 0)
	{
		mIsActive = true;
		text(magnetHilma, mLevelHandler->getPlayer()->getPosition(), -180, -180);
		createTalkBubble(mLevelHandler->getPlayer()->getPosition(), -180, -200, 2.1f, 1.f);
	}
}

void DialogueSystem::displayStringDialogue()
{
	std::string stringHilma = "En l�s tr�d.";

	if (mState == 1)
	{
		mText.setString("");
		mHasClicked = false;
		mString = false;
		mIsActive = false;
	}

	if (mState == 0)
	{
		mIsActive = true;
		text(stringHilma, mLevelHandler->getPlayer()->getPosition(), -180, -180);
		createTalkBubble(mLevelHandler->getPlayer()->getPosition(), -180, -200, 2.1f, 1.f);
	}
}

//Grandma's Livingroom
void DialogueSystem::displayBooks2Dialogue()
{
	std::string books2Thomas = "Rymdb�cker� precis som mina d�r hemma.";

	if (mState == 1)
	{
		mText.setString("");
		mHasClicked = false;
		mBooks2 = false;
		mIsActive = false;
	}

	if (mState == 0)
	{
		mIsActive = true;
		text(books2Thomas, mLevelHandler->getPlayer()->getPosition(), 60, -250);
		createTalkBubble(mLevelHandler->getPlayer()->getPosition(), 60, -250, 2.5f, 1.f);
	}
}

void DialogueSystem::displayJewelryCaseDialogue()
{
	std::string jewelryCaseThomas = "Mormors smyckesskrin.";
	std::string jewelryCaseHilma = "Vi �ppnar och kollar vad som finns i den!";
	std::string jewelryCaseHilma2 = "Den �r bara full av muttrar!";

	if (mState == 3)
	{
		mText.setString("");
		mHasClicked = false;
		mJewelryCase = false;
		mIsActive = false;
	}

	if (mState == 0)
	{
		mIsActive = true;
		text(jewelryCaseThomas, mLevelHandler->getPlayer()->getPosition(), 60, -250);
		createTalkBubble(mLevelHandler->getPlayer()->getPosition(), 60, -250, 2.5f, 1.f);
	}

	if (mState == 1)
	{
		text(jewelryCaseHilma, mLevelHandler->getPlayer()->getPosition(), -180, -180);
		createTalkBubble(mLevelHandler->getPlayer()->getPosition(), -180, -200, 2.1f, 1.f);
	}

	if (mState == 2)
	{
		text(jewelryCaseHilma2, mLevelHandler->getPlayer()->getPosition(), -180, -180);
		createTalkBubble(mLevelHandler->getPlayer()->getPosition(), -180, -200, 2.1f, 1.f);
	}
}

void DialogueSystem::displayMaskDialogue()
{
	std::string maskHilma = "Vilken lustig mask! Var kommer den ifr�n?";
	std::string maskThomas = "N�gonstans i Afrika tror jag. Mormor reste mycket n�r hon var ung.";

	if (mState == 2)
	{
		mText.setString("");
		mHasClicked = false;
		mMask = false;
		mIsActive = false;
	}

	if (mState == 0)
	{
		mIsActive = true;
		text(maskHilma, mLevelHandler->getPlayer()->getPosition(), -180, -180);
		createTalkBubble(mLevelHandler->getPlayer()->getPosition(), -180, -200, 2.1f, 1.f);
	}

	if (mState == 1)
	{
		text(maskThomas, mLevelHandler->getPlayer()->getPosition(), 60, -250);
		createTalkBubble(mLevelHandler->getPlayer()->getPosition(), 60, -250, 2.5f, 1.f);
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
	}

	if (mState == 0)
	{
		mIsActive = true;
		text(textileCartHilma, mLevelHandler->getPlayer()->getPosition(), -180, -180);
		createTalkBubble(mLevelHandler->getPlayer()->getPosition(), -180, -200, 2.1f, 1.f);
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
	}

	if (mState == 0)
	{
		mIsActive = true;
		text(earthGlobeThomas, mLevelHandler->getPlayer()->getPosition(), 60, -250);
		createTalkBubble(mLevelHandler->getPlayer()->getPosition(), 60, -250, 2.5f, 1.f);
	}

	if (mState == 1)
	{
		text(earthGlobeHilma, mLevelHandler->getPlayer()->getPosition(), -180, -180);
		createTalkBubble(mLevelHandler->getPlayer()->getPosition(), -180, -200, 2.1f, 1.f);
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
	}

	if (mState == 0)
	{
		mIsActive = true;
		text(gramophoneHilma, mLevelHandler->getPlayer()->getPosition(), -180, -180);
		createTalkBubble(mLevelHandler->getPlayer()->getPosition(), -180, -200, 2.1f, 1.f);
	}

	if (mState == 1)
	{
		text(gramophoneThomas, mLevelHandler->getPlayer()->getPosition(), 60, -250);
		createTalkBubble(mLevelHandler->getPlayer()->getPosition(), 60, -250, 2.5f, 1.f);
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
	}

	if (mState == 0)
	{
		mIsActive = true;
		text(fishTrophyHilma, mLevelHandler->getPlayer()->getPosition(), -180, -180);
		createTalkBubble(mLevelHandler->getPlayer()->getPosition(), -180, -200, 2.1f, 1.f);
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
	}

	if (mState == 0)
	{
		mIsActive = true;
		text(plantHilma, mLevelHandler->getPlayer()->getPosition(), -180, -180);
		createTalkBubble(mLevelHandler->getPlayer()->getPosition(), -180, -200, 2.1f, 1.f);
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
	}

	if (mState == 0)
	{
		mIsActive = true;
		text(armchairHilma, mLevelHandler->getPlayer()->getPosition(), -180, -180);
		createTalkBubble(mLevelHandler->getPlayer()->getPosition(), -180, -200, 2.1f, 1.f);
	}
}

//Grandma's Kitchen
void DialogueSystem::displayRefridgeratorDialogue()
{
	std::string refridgeratorThomas = "Ett gammalt kylsk�p";

	if (mState == 1)
	{
		mText.setString("");
		mHasClicked = false;
		mRefridgerator = false;
		mIsActive = false;
	}

	if (mState == 0)
	{
		mIsActive = true;
		text(refridgeratorThomas, mLevelHandler->getPlayer()->getPosition(), 60, -250);
		createTalkBubble(mLevelHandler->getPlayer()->getPosition(), 60, -250, 2.5f, 1.f);
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
	}

	if (mState == 0)
	{
		mIsActive = true;
		text(catHilma, mLevelHandler->getPlayer()->getPosition(), -180, -180);
		createTalkBubble(mLevelHandler->getPlayer()->getPosition(), -180, -200, 2.1f, 1.f);
	}

	if (mState == 1)
	{
		text(catThomas, mLevelHandler->getPlayer()->getPosition(), 60, -250);
		createTalkBubble(mLevelHandler->getPlayer()->getPosition(), 60, -250, 2.5f, 1.f);
	}

	if (mState == 2)
	{
		text(catHilma2, mLevelHandler->getPlayer()->getPosition(), -180, -180);
		createTalkBubble(mLevelHandler->getPlayer()->getPosition(), -180, -200, 2.1f, 1.f);
	}

	if (mState == 3)
	{
		text(catThomas2, mLevelHandler->getPlayer()->getPosition(), 60, -250);
		createTalkBubble(mLevelHandler->getPlayer()->getPosition(), 60, -250, 2.5f, 1.f);
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
	}

	if (mState == 0)
	{
		mIsActive = true;
		text(catFoodBowlThomas, mLevelHandler->getPlayer()->getPosition(), 60, -250);
		createTalkBubble(mLevelHandler->getPlayer()->getPosition(), 60, -250, 2.5f, 1.f);
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
	}

	if (mState == 0)
	{
		mIsActive = true;
		text(mouseDwellingHilma, mLevelHandler->getPlayer()->getPosition(), -180, -180);
		createTalkBubble(mLevelHandler->getPlayer()->getPosition(), -180, -200, 2.1f, 1.f);
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
	}

	if (mState == 0)
	{
		mIsActive = true;
		text(waterTapThomas, mLevelHandler->getPlayer()->getPosition(), 60, -250);
		createTalkBubble(mLevelHandler->getPlayer()->getPosition(), 60, -250, 2.5f, 1.f);
	}

	if (mState == 1)
	{
		text(waterTapHilma, mLevelHandler->getPlayer()->getPosition(), -180, -180);
		createTalkBubble(mLevelHandler->getPlayer()->getPosition(), -180, -200, 2.1f, 1.f);
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
	}

	if (mState == 0)
	{
		mIsActive = true;
		text(fruitBowlThomas, mLevelHandler->getPlayer()->getPosition(), 60, -250);
		createTalkBubble(mLevelHandler->getPlayer()->getPosition(), 60, -250, 2.5f, 1.f);
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
	}

	if (mState == 0)
	{
		mIsActive = true;
		text(planetsThomas, mLevelHandler->getPlayer()->getPosition(), 60, -250);
		createTalkBubble(mLevelHandler->getPlayer()->getPosition(), 60, -250, 2.5f, 1.f);
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
	}

	if (mState == 0)
	{
		mIsActive = true;
		text(mercuryThomas, mLevelHandler->getPlayer()->getPosition(), 60, -250);
		createTalkBubble(mLevelHandler->getPlayer()->getPosition(), 60, -250, 2.5f, 1.f);
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
	}

	if (mState == 0)
	{
		mIsActive = true;
		text(venusThomas, mLevelHandler->getPlayer()->getPosition(), 60, -250);
		createTalkBubble(mLevelHandler->getPlayer()->getPosition(), 60, -250, 2.5f, 1.f);
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
	}

	if (mState == 0)
	{
		mIsActive = true;
		text(emptyEarthThomas, mLevelHandler->getPlayer()->getPosition(), 60, -250);
		createTalkBubble(mLevelHandler->getPlayer()->getPosition(), 60, -250, 2.5f, 1.f);
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
	}

	if (mState == 0)
	{
		mIsActive = true;
		text(emptyMarsThomas, mLevelHandler->getPlayer()->getPosition(), 60, -250);
		createTalkBubble(mLevelHandler->getPlayer()->getPosition(), 60, -250, 2.5f, 1.f);
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
	}

	if (mState == 0)
	{
		mIsActive = true;
		text(jupiterThomas, mLevelHandler->getPlayer()->getPosition(), 60, -250);
		createTalkBubble(mLevelHandler->getPlayer()->getPosition(), 60, -250, 2.5f, 1.f);
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
	}

	if (mState == 0)
	{
		mIsActive = true;
		text(emptySaturnThomas, mLevelHandler->getPlayer()->getPosition(), 60, -250);
		createTalkBubble(mLevelHandler->getPlayer()->getPosition(), 60, -250, 2.5f, 1.f);
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
	}

	if (mState == 0)
	{
		mIsActive = true;
		text(uranusThomas, mLevelHandler->getPlayer()->getPosition(), 60, -250);
		createTalkBubble(mLevelHandler->getPlayer()->getPosition(), 60, -250, 2.5f, 1.f);
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
	}

	if (mState == 0)
	{
		mIsActive = true;
		text(neptuneThomas, mLevelHandler->getPlayer()->getPosition(), 60, -250);
		createTalkBubble(mLevelHandler->getPlayer()->getPosition(), 60, -250, 2.5f, 1.f);
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
	}

	if (mState == 0)
	{
		mIsActive = true;
		text(emptyPlutoThomas, mLevelHandler->getPlayer()->getPosition(), 60, -250);
		createTalkBubble(mLevelHandler->getPlayer()->getPosition(), 60, -250, 2.5f, 1.f);
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
	}

	if (mState == 0)
	{
		mIsActive = true;
		text(marsThomas, mLevelHandler->getPlayer()->getPosition(), 60, -250);
		createTalkBubble(mLevelHandler->getPlayer()->getPosition(), 60, -250, 2.5f, 1.f);
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
	}

	if (mState == 0)
	{
		mIsActive = true;
		text(earthHilma, mLevelHandler->getPlayer()->getPosition(), 60, -250);
		createTalkBubble(mLevelHandler->getPlayer()->getPosition(), -180, -200, 2.1f, 1.f);
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
	}

	if (mState == 0)
	{
		mIsActive = true;
		text(saturnThomas, mLevelHandler->getPlayer()->getPosition(), 60, -250);
		createTalkBubble(mLevelHandler->getPlayer()->getPosition(), 60, -250, 2.5f, 1.f);
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
	}

	if (mState == 0)
	{
		mIsActive = true;
		text(plutoThomas, mLevelHandler->getPlayer()->getPosition(), 60, -250);
		createTalkBubble(mLevelHandler->getPlayer()->getPosition(), 60, -250, 2.5f, 1.f);
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
	}

	if (mState == 0)
	{
		mIsActive = true;
		text(swordsHilma, mLevelHandler->getPlayer()->getPosition(), 60, -250);
		createTalkBubble(mLevelHandler->getPlayer()->getPosition(), -180, -200, 2.1f, 1.f);
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
	}

	if (mState == 0)
	{
		mIsActive = true;
		text(drawingsHilma, mLevelHandler->getPlayer()->getPosition(), -180, -180);
		createTalkBubble(mLevelHandler->getPlayer()->getPosition(), -180, -200, 2.1f, 1.f);
	}

	if (mState == 1)
	{
		text(drawingsThomas, mLevelHandler->getPlayer()->getPosition(), 60, -250);
		createTalkBubble(mLevelHandler->getPlayer()->getPosition(), 60, -250, 2.5f, 1.f);
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
	}

	if (mState == 0)
	{
		mIsActive = true;
		text(balconyDoorHilma, mLevelHandler->getPlayer()->getPosition(), 60, -250);
		createTalkBubble(mLevelHandler->getPlayer()->getPosition(), -180, -200, 2.1f, 1.f);
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
	}

	if (mState == 0)
	{
		mIsActive = true;
		text(dollHouseHilma, mLevelHandler->getPlayer()->getPosition(), -180, -180);
		createTalkBubble(mLevelHandler->getPlayer()->getPosition(), -180, -200, 2.1f, 1.f);
	}

	if (mState == 1)
	{
		text(dollHouseThomas, mLevelHandler->getPlayer()->getPosition(), 60, -250);
		createTalkBubble(mLevelHandler->getPlayer()->getPosition(), 60, -250, 2.5f, 1.f);
	}

	if (mState == 2)
	{
		text(dollHouseHilma2, mLevelHandler->getPlayer()->getPosition(), -180, -180);
		createTalkBubble(mLevelHandler->getPlayer()->getPosition(), -180, -200, 2.1f, 1.f);
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
	}

	if (mState == 0)
	{
		mIsActive = true;
		text(putteHilma, mLevelHandler->getPlayer()->getPosition(), 60, -250);
		createTalkBubble(mLevelHandler->getPlayer()->getPosition(), -180, -200, 2.1f, 1.f);
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
	}

	if (mState == 0)
	{
		mIsActive = true;
		text(putteFamilyHilma, mLevelHandler->getPlayer()->getPosition(), 60, -250);
		createTalkBubble(mLevelHandler->getPlayer()->getPosition(), -180, -200, 2.1f, 1.f);
	}
}