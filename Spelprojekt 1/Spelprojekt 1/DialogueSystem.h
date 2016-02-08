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
};

#endif