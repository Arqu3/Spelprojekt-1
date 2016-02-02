#include "DialogueSystem.h"
#include <iostream>
#include "SFML\System.hpp"

using namespace std;

DialogueSystem::DialogueSystem():
mHasClicked(false),
mTime(0),
test(0)
{

}

DialogueSystem::~DialogueSystem()
{

}

void DialogueSystem::setDialogue()
{

}

std::string DialogueSystem::getDialogue()
{
	return mDialogue;
}

std::string DialogueSystem::talk()
{
	return 0;
}

//Talk Bubble
void DialogueSystem::createTalkBubble()
{

}

void DialogueSystem::autoENDL()
{

}

void DialogueSystem::autoSizeTalkBubble()
{

}

void DialogueSystem::setTalkBubblePosition(Player *player)
{
	
}

//Update function
void DialogueSystem::update(float time)
{
	if (mHasClicked == true)
	{
		mTime = mClock.getElapsedTime().asSeconds();
	}
	else
	{
		mTime = 0;
	}

	displayRubicCubeDialogue();
}

void DialogueSystem::hasClicked()
{
	mHasClicked = true;
}

//Dialogue functions
void DialogueSystem::displayRubicCubeDialogue()
{
	std::string rubicHilma = "Vad �r det h�r?";
	std::string rubicThomas = "En Rubiks kub, man ska f� alla f�rgerna p� varsin sida.";
	std::string rubicHilma2 = "Men vad �r det f�r utmaning? L�ter ju j�ttel�tt!";

	if (mTime > 20)
	{
		mHasClicked = false;
		mClock.restart();
	}

	else if (mTime >= 1 && mTime <= 5)
	{
		std::cout << rubicHilma << std::endl;
	}
	else if (mTime > 5 && mTime <= 10)
	{
		std::cout << rubicThomas << std::endl;
	}
}