#include "DialogueSystem.h"
#include <ctime>
#include <iostream>

DialogueSystem::DialogueSystem()
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

//Dialogue functions
void DialogueSystem::displayRubicCubeDialogue()
{
	std::string rubicHilma = "Vad �r det h�r?";
	std::string rubicThomas = "En Rubiks kub, man ska f� alla f�rgerna p� varsin sida.";
	std::string rubicHilma2 = "Men vad �r det f�r utmaning? L�ter ju j�ttel�tt!";

	std::cout << rubicHilma << std::endl;
	std::cout << rubicThomas << std::endl;
	std::cout << rubicHilma2 << std::endl;
}