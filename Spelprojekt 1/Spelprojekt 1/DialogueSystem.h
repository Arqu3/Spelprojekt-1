#ifndef DIALOGUESYSTEM
#define DIALOGUESYSTEM

#include <string>
#include "Item.h"
#include "Player.h"
#include "LevelHandler.h"

class DialogueSystem
{
public:
	DialogueSystem(LevelHandler &levelHandler);
	~DialogueSystem();

	//Talk functions
	void text(std::string text, sf::Vector2f &position);

	//Talk Bubble
	void drawDialogue(sf::RenderWindow &window);

	//Function that checks if an object has been clicked on
	void hasClicked(std::string indexName);

	//Reset variables
	void reset();

	//Update function
	void update(float time);

	//Dialogues (functions with strings)
	void displayRubicCubeDialogue();
	void displayMagnetDialogue();

private:
	std::string mDialogue;
	float mTime;
	bool mHasClicked;
	bool mRubicCube;
	bool mMagnet;
	sf::Text mText;
	sf::Clock mClock;
	sf::Font mFont;

	Player *mPlayer;
	LevelHandler *mLevelHandler;
};

#endif