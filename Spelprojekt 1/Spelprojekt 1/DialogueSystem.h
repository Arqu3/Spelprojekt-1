#ifndef DIALOGUESYSTEM
#define DIALOGUESYSTEM

#include <string>
#include "Item.h"
#include "Player.h"

class DialogueSystem
{
public:
	DialogueSystem();
	~DialogueSystem();

	//Dialogue functions
	void setDialogue();
	std::string getDialogue();

	//Talk functions
	void text(std::string text);

	//Talk Bubble
	void createTalkBubble(Player *player);
	void drawDialogue(sf::RenderWindow &window);
	void autoSizeTalkBubble();

	void hasClicked(std::string indexName);

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
};

#endif