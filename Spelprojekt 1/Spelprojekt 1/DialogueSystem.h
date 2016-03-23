#ifndef DIALOGUESYSTEM
#define DIALOGUESYSTEM

#include <string>
#include "Item.h"
#include "Player.h"
#include "RiddleSpider.h"
#include <vector>

class DialogueSystem
{
public:
	DialogueSystem(ResourceHandler &handler, int level);
	~DialogueSystem();

	//Talk functions
	void text(std::string text, float posX, float posY, float offsetX, float offsetY);
	void advancedText(std::string advancedText, float posX, float posY, float offsetX, float offsetY/*, std::string sound*/);
	void actorText(std::string actorText, float posX, float posY, float offsetX, float offsetY);

	//Talk Bubble
	void drawDialogue(sf::RenderWindow &window);
	void createTalkBubble(float posX, float posY, float offsetX, float offsetY, float scaleX, float scaleY);
	void createTextBox(float posX, float posY, float offsetX, float offsetY, float scaleX, float scaleY);

	//Character Draw
	void drawFirstCharacter(ResourceHandler &handler, float posX, float posY, float offsetX, float offsetY, float scaleX, float scaleY, std::string character);
	void drawSecondCharacter(ResourceHandler &handler, float posX, float posY, float offsetX, float offsetY, float scaleX, float scaleY, std::string character);

	//Function that checks if an object has been clicked on
	void hasClicked(std::string indexName, Player *player);

	//Reset variables
	void reset();

	//Update function
	void update(float time);

	//Sets the state value
	void setState();
	//void setStateManual(int state);

	//Function to check in dialogue is finished
	bool isDialogueFinished();

	//Spider Dialogue
	void displaySpiderDialogue();

	//Advanced Dialogues
	//Level 1
	void displayLevel1StartAdvancedDialogue();
	void displayLevel1EndAdvancedDialogue();

	//Level 2
	void displayLevel2StartAdvancedDialogue();
	void displayLevel2EndAdvancedDialogue();
	void displayLevel2MissingRocketAdvancedDialogue();
	void displayLevel2PutteAdvancedDialogue();
	void displayLevel2SteamMachineAdvancedDialogue();
	void displayLevel2ArnoldAdvancedDialogue();
	void displayLevel2ArnoldMemoriesAdvancedDialogue();
	void displayLevel2PutteRescueAdvancedDialogue();
	void displayLevel2OpenBoxAdvancedDialogue();
	void displayLevel2MagpieStealsAdvancedDialogue();
	void displayLevel2GrandmasClothAdvancedDialogue();

	//Level 3
	void displayLevel3StartAdvancedDialogue();
	void displayLevel3EndAdvancedDialogue();
	void displayLevel3ShedAdvancedDialogue();
	void displayLevel3Skatmaran1AdvancedDialogue();
	void displayLevel3Skatmaran2AdvancedDialogue();
	void displayLevel3Skatmaran3AdvancedDialogue();
	void displayLevel3Skatmaran4AdvancedDialogue();

	//Level 4

	//Level 5
	void displayLevel5StartAdvancedDialogue();
	void displayLevel5EndAdvancedDialogue();
	void displayLevel5Letter1AdvancedDialogue();
	void displayLevel5Letter2AdvancedDialogue();
	void displayLevel5BalconyDoorAdvancedDialogue();
	void displayLevel5Putte2AdvancedDialogue();
	void displayLevel5SolarSystemAdvancedDialogue();
	void displayLevel5MouseHoleAdvancedDialogue();
	void displayLevel5VictoryAdvancedDialogue();
	void displayLevel5TogetherAdvancedDialogue();
	void displayLevel5SolutionAdvancedDialogue();
	void displayLevel5PaintingAdvancedDialogue();
	void displayLevel5RecordsAdvancedDialogue();
	void displayLevel5DrawingsAdvancedDialogue();

	//Ending Dialogues
	void displayEnding1AdvancedDialogue();
	void displayEnding2AdvancedDialogue();
	void displayEnding3AdvancedDialogue();
	void displayEnding4AdvancedDialogue();
	void displayEnding5AdvancedDialogue();
	void displayEnding6AdvancedDialogue();

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
	void displayGlassesAndNutsDialogue();

	//Grandma's Kitchen
	void displayRefridgeratorDialogue();
	void displayCatDialogue();
	void displayCatFoodBowlDialogue();
	void displayMouseDwellingDialogue();
	void displayWaterTapDialogue();
	void displayFruitBowlDialogue();
	void displayFlowersDialogue();
	void displayRocketDrawingsDialogue();
	void displayToolsDialogue();

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

	//Garden
	void displayShearsDialogue();
	void displayBushDialogue();
	void displayRopeDialogue();
	void displayDogDialogue();
	void displayGardenFlowersDialogue();
	void displayFlagpoleDialogue();
	void displayBeeDialogue();
	void displayTracksDialogue();

	//Shack
	void displayRocketDialogue();
	void displayWayInDialogue();
	void displayEntryFindersWorldDialogue();
	void displayCloverDialogue();
	void displayNailsDialogue();
	void displayHorseShoeDialogue();
	void displayClothDialogue();
	void displayBadmintonBallDialogue();
	void displaySawdustDialogue();
	void displayKnightDialogue();
	void displayKnightFirstDialogue();
	void displayKnightSecondDialogue();
	void displayKnightAllDialogue();

	//Finders' World
	void displayExitFindersWorld();
	void displayStatueDialogue();
	void displayJewelsDialogue();
	void displayBubblesDialogue();
	void displayParentDialogue();

	//Level1 start and end
	void setLevel1Start();
	void setLevel1End();
	bool getLevel1Start();
	bool getLevel1End();

	//Level2
	void setLevel2Start();
	void setLevel2End();
	bool getLevel2Start();
	bool getLevel2End();

	//Level3

	void setLevel3Start();
	void setLevel3End();
	bool getLevel3Start();
	bool getLevel3End();

	//Level5
	void setLevel5Start();
	void setLevel5End();
	bool getLevel5Start();
	bool getLevel5End();

private:
	std::string mDialogue;
	float mTime;
	bool mHasClicked;
	bool mIsActive;
	bool mAdvancedIsActive;
	bool mFinishedDialogue;
	int mState;
	std::string mTexture;
	sf::Text mText;
	sf::Text mActorText;
	sf::Clock mClock;
	sf::Font mFont;
	sf::Sprite mBubble;
	sf::Sprite mTextBox;
	sf::Sprite mFirstCharacter;
	sf::Sprite mSecondCharacter;
	sf::RectangleShape mSepia;
	RiddleSpider *mSpider;
	Player *mPlayer;
	ResourceHandler &mHandler;

	//Spider Dialogue
	bool mDialogueSpider;

	//Advanced Dialogue
	//Level 1
	bool mLevel1Start;
	bool mLevel1End;

	//Level 2
	bool mLevel2Start;
	bool mLevel2End;
	bool mLevel2MissingRocket;
	bool mLevel2Putte;
	bool mLevel2SteamMachine;
	bool mLevel2Arnold;
	bool mLevel2ArnoldMemories;
	bool mLevel2PutteRescue;
	bool mLevel2OpenBox;
	bool mLevel2MapieSteals;
	bool mLevel2GrandmasCloth;

	//Level 3
	bool mLevel3Start;
	bool mLevel3End;
	bool mLevel3Shed;
	bool mLevel3Skatmaran1;
	bool mLevel3Skatmaran2;
	bool mLevel3Skatmaran3;
	bool mLevel3Skatmaran4;

	//Level 4

	//Level 5
	bool mEnding1;
	bool mEnding2;
	bool mEnding3;
	bool mEnding4;
	bool mEnding5;
	bool mEnding6;
	bool mLevel5Start;
	bool mLevel5End;
	bool mLevel5Letter1;
	bool mLevel5Letter2;
	bool mLevel5BalconyDoor;
	bool mLevel5Putte2;
	bool mLevel5SolarSystem;
	bool mLevel5MouseHole;
	bool mLevel5Victory;
	bool mLevel5Together;
	bool mLevel5Solution;
	bool mLevel5Painting;
	bool mLevel5Records;
	bool mLevel5Drawings;

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
	bool mGlassesAndNuts;

	//Item bools (Grandma's Kitchen)
	bool mRefridgerator;
	bool mCat;
	bool mCatFoodBowl;
	bool mMouseDwelling;
	bool mWaterTap;
	bool mFruitBowl;
	bool mFlowers;
	bool mRocketDrawings;
	bool mTools;

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

	//Item bools (Garden)
	bool mShears;
	bool mBush;
	bool mRope;
	bool mDog;
	bool mGardenFlowers;
	bool mFlagpole;
	bool mBee;
	bool mTracks;

	//Item bools (Shack)
	bool mRocket;
	bool mWayIn;
	bool mEntryFindersWorld;
	bool mClover;
	bool mNails;
	bool mHorseShoe;
	bool mCloth;
	bool mBadmintonBall;
	bool mSawdust;
	bool mKnight;
	bool mKnightFirst;
	bool mKnightSecond;
	bool mKnightAll;

	//Item bools (Finders' World)
	bool mExitFindersWorld;
	bool mStatue;
	bool mJewels;
	bool mBubbles;
	bool mParent;

	sf::Music voiceActingTest;
	sf::Music voiceActingTest2;

	//Voice Acting
	//Narrator
	sf::Music NarratorLvl1Part1;
	sf::Music NarratorLvl1Part2;
	sf::Music NarratorLvl1Part3;
	sf::Music NarratorLvl1Part4;
	sf::Music NarratorLvl1Part5;
	sf::Music NarratorLvl1Part6;
	sf::Music NarratorLvl1Part7;
	sf::Music NarratorLvl1Part8;
	sf::Music NarratorLvl1Part9;

	//Thomas
	sf::Music ThomasLvl1Part1;
	sf::Music ThomasLvl1Part2;
	sf::Music ThomasLvl1Part3;
	sf::Music ThomasLvl1Part4;
	sf::Music ThomasLvl1Part5;
	sf::Music ThomasLvl1Part6;
	sf::Music ThomasLvl1Part7;
	sf::Music ThomasLvl1EndPart1;
	sf::Music ThomasLvl1EndPart2;
	sf::Music ThomasLvl1EndPart3;
	sf::Music ThomasLvl1EndPart4;
	sf::Music ThomasLvl1EndPart5;
	sf::Music ThomasLvl1EndPart6;
	sf::Music ThomasLvl1EndPart7;
	sf::Music ThomasLvl1EndPart8;
	sf::Music ThomasLvl1EndPart9;
	sf::Music ThomasLvl1EndPart10;
	sf::Music ThomasLvl1EndPart11;
	sf::Music ThomasLvl1EndPart12;

	//Hilma
	sf::Music HilmaLvl1BeginningPart1;
	sf::Music HilmaLvl1BeginningPart2;
	sf::Music HilmaLvl1BeginningPart3;
	sf::Music HilmaLvl1BeginningPart4;
	sf::Music HilmaLvl1BeginningPart5;
	sf::Music HilmaLvl1BeginningPart6;
	sf::Music HilmaLvl1BeginningPart7;
	sf::Music HilmaLvl1BeginningPart8;
	sf::Music HilmaLvl1BeginningPart9;
	sf::Music HilmaLvl1BeginningPart10;
	sf::Music HilmaLvl1BeginningPart11;
	sf::Music HilmaLvl1BeginningPart12;
	sf::Music HilmaLvl1BeginningPart13;
	sf::Music HilmaLvl1BeginningPart14;
	sf::Music HilmaLvl1EndPart1;
	sf::Music HilmaLvl1EndPart2;
	sf::Music HilmaLvl1EndPart3;
	sf::Music HilmaLvl1EndPart4;
	sf::Music HilmaLvl1EndPart5;
	sf::Music HilmaLvl1EndPart6;
	sf::Music HilmaLvl1EndPart7;
	sf::Music HilmaLvl1EndPart8;
	sf::Music HilmaLvl1EndPart9;
	sf::Music HilmaLvl1EndPart10;
	sf::Music HilmaLvl1EndPart11;
	sf::Music HilmaLvl1EndPart12;

	bool mLineStarted;
};

#endif