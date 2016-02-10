#ifndef DIALOGUESYSTEM
#define DIALOGUESYSTEM

#include <string>
#include "Item.h"
#include "Player.h"
#include "LevelHandler.h"

class DialogueSystem
{
public:
	DialogueSystem(LevelHandler &levelHandler, ResourceHandler &handler);
	~DialogueSystem();

	//Talk functions
	void text(std::string text, sf::Vector2f &position, float x, float y);

	//Talk Bubble
	void drawDialogue(sf::RenderWindow &window);
	void createTalkBubble(sf::Vector2f &position, float OffSetX, float OffSetY, float x, float y);

	//Function that checks if an object has been clicked on
	void hasClicked(std::string indexName);

	//Reset variables
	void reset();

	//Update function
	void update(float time);

	//Sets the state value
	void setState();

	//Dialogues (functions with strings)
	//Thomas' room
	void displayBooksDialogue();
	void displayLampDialogue();
	void displayRubicCubeDialogue();
	void displayPosterDialogue();
	void displayBackpackDialogue();
	void displayBowlDialogue();
	void displayRadioDialogue();
	void displayMatDialogue();
	void displayStarDialogue();
	void displayAquariumDialogue();
	void displayBlockDialogue();
	void displayAstronautDialogue();
	void displayMagnetDialogue();
	void displayStringDialogue();

	//Grandma's Livingroom
	void displayBooks2Dialogue();
	void displayJewelryCaseDialogue();
	void displayMaskDialogue();
	void displayTextileCartDialogue();
	void displayEarthGlobeDialogue();
	void displayGramophoneDialogue();
	void displayFishTrophyDialogue();
	void displayPlantDialogue();
	void displayArmchairDialogue();

	//Grandma's Kitchen
	void displayRefridgeratorDialogue();
	void displayCatDialogue();
	void displayCatFoodBowlDialogue();
	void displayMouseDwellingDialogue();
	void displayWaterTapDialogue();
	void displayFruitBowlDialogue();

	//Grandma's Room
	void displayPlanetsDialogue();
	void displayMercuryDialogue();
	void displayVenusDialogue();
	void displayEmptyEarthDialogue();
	void displayEmptyMarsDialogue();
	void displayJupiterDialogue();
	void displayEmptySaturnDialogue();
	void displayUranusDialogue();
	void displayNeptuneDialogue();
	void displayEmptyPlutoDialogue();
	void displayMarsDialogue();
	void displayEarthDialogue();
	void displaySaturnDialogue();
	void displayPlutoDialogue();
	void displaySwordsDialogue();
	void displayDrawingsDialogue();
	void displayBalconyDoorDialogue();
	void displayDollHouseDialogue();
	void displayPutteDialogue();
	void displayPutteFamilyDialogue();

private:
	std::string mDialogue;
	float mTime;
	bool mHasClicked;
	bool mIsActive;
	int mState;
	sf::Text mText;
	sf::Clock mClock;
	sf::Font mFont;
	sf::Sprite mBubble;

	Player *mPlayer;
	LevelHandler *mLevelHandler;

	//Item bools (Thomas' Room)
	bool mBooks;
	bool mLamp;
	bool mRubicCube;
	bool mPoster;
	bool mBackpack;
	bool mBowl;
	bool mRadio;
	bool mMat;
	bool mStar;
	bool mAquarium;
	bool mBlock;
	bool mAstronaut;
	bool mMagnet;
	bool mString;

	//Item bools (Grandma's Livingroom)
	bool mBooks2;
	bool mJewelryCase;
	bool mMask;
	bool mTextileCart;
	bool mEarthGlobe;
	bool mGramophone;
	bool mFishTrophy;
	bool mPlant;
	bool mArmchair;

	//Item bools (Grandma's Kitchen)
	bool mRefridgerator;
	bool mCat;
	bool mCatFoodBowl;
	bool mMouseDwelling;
	bool mWaterTap;
	bool mFruitBowl;

	//Item bools (Grandma's Room)
	bool mPlanets;
	bool mMercury;
	bool mVenus;
	bool mEmptyEarth;
	bool mEmptyMars;
	bool mJupiter;
	bool mEmptySaturn;
	bool mUranus;
	bool mNeptune;
	bool mEmptyPluto;
	bool mMars;
	bool mEarth;
	bool mSaturn;
	bool mPluto;
	bool mSwords;
	bool mDrawings;
	bool mBalconyDoor;
	bool mDollHouse;
	bool mPutte;
	bool mPutteFamily;
};

#endif