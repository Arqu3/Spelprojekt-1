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
	std::string talk();

	//Talk Bubble
	void createTalkBubble();
	void autoENDL();
	void autoSizeTalkBubble();
	void setTalkBubblePosition(Player *player);

	//Dialogues (functions with strings)
	void displayRubicCubeDialogue();
private:
	std::string mDialogue;
};

#endif