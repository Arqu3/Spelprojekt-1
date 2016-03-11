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
	DialogueSystem(ResourceHandler &handler);
	~DialogueSystem();

	typedef std::vector<sf::Text> TextVector;

	//Talk functions
	void text(std::string text, sf::Vector2f &position, float x, float y);
	void advancedText(std::string advancedText, float posX, float posY, float offsetX, float offsetY/*, std::string sound*/);
	void actorText(std::string actorText, float posX, float posY, float offsetX, float offsetY);

	//Talk Bubble
	void drawDialogue(sf::RenderWindow &window);
	void createTalkBubble(sf::Vector2f &position, float offsetX, float offsetY, float scaleX, float scaleY);
	void createTextBox(float x, float y, float offsetX, float offsetY, float scaleX, float scaleY);

	//Character Draw
	void drawFirstCharacter(ResourceHandler &handler, float x, float y, float offsetX, float offsetY, float scaleX, float scaleY, std::string character);
	void drawSecondCharacter(ResourceHandler &handler, float x, float y, float offsetX, float offsetY, float scaleX, float scaleY, std::string character);

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
	void displayLevel3ReturnAdvancedDialogue();

	//Level 4

	//Level 5
	void displayLevel5StartAdvancedDialogue();
	void displayLevel5EndAdvancedDialogue();
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
	TextVector mTexts;
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
	bool mLevel3Return;

	//Level 4

	//Level 5
	bool mLevel5Start;
	bool mLevel5End;
	bool mLevel5BalconyDoor;
	bool mLevel5Putte2;
	bool mLevel5SolarSystem;
	bool mLevel5MouseHole;
	bool mLevel5Victory;
	bool mLevel5Together;
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

	sf::Music voiceActingTest;
	sf::Music voiceActingTest2;
	bool mLineStarted;
};

#endif