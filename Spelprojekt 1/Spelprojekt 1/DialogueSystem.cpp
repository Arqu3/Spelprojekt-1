#include "DialogueSystem.h"
#include <iostream>
#include <chrono>

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
	std::string rubicHilma = "Vad är det här?";
	std::string rubicThomas = "En Rubiks kub, man ska få alla färgerna på varsin sida.";
	std::string rubicHilma2 = "Men vad är det för utmaning? Låter ju jättelätt!";

	std::chrono::seconds(2);
	std::cout << rubicHilma << std::endl;
	std::chrono::seconds(2);
	std::cout << rubicThomas << std::endl;
	std::chrono::seconds(2);
	std::cout << rubicHilma2 << std::endl;
}