#include "DialogueSystem.h"
#include <iostream>
#include "SFML\System.hpp"

DialogueSystem::DialogueSystem():
mHasClicked(false),
mTime(0),
mText(),
mFont()
{
	mFont.loadFromFile("Resources/Fonts/ShadowsIntoLight.ttf");
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

void DialogueSystem::text(std::string text)
{
	mText.setFont(mFont);
	mText.setCharacterSize(14);
	mText.setStyle(sf::Text::Bold);
	mText.setColor(sf::Color::White);
	//Get Player position correctly
	mText.setPosition(400, 400);
	mText.setString(text);
}

void DialogueSystem::drawDialogue(sf::RenderWindow &window)
{
	window.draw(mText);
}

//Talk Bubble
void DialogueSystem::createTalkBubble(Player *player)
{
	player->getPosition();
}

void DialogueSystem::autoSizeTalkBubble()
{

}

void DialogueSystem::hasClicked(std::string indexName)
{
	if (indexName == "rubicCube")
	{
		mRubicCube = true;
	}
	if (indexName == "magnet")
	{
		mMagnet = true;
	}
	mHasClicked = true;
}

//Update function
void DialogueSystem::update(float time)
{
	if (mHasClicked == true)
	{
		mTime = mClock.getElapsedTime().asSeconds();
	}
	if (mHasClicked == false)
	{
		mTime = 0;
	}

	if (mRubicCube == true)
	{
		displayRubicCubeDialogue();
	}

	if (mMagnet == true)
	{
		displayMagnetDialogue();
	}
}

//Dialogue functions
void DialogueSystem::displayRubicCubeDialogue()
{
	std::string rubicHilma = "Vad är det här?";
	std::string rubicThomas = "En Rubiks kub, man ska få alla färgerna på varsin sida.";
	std::string rubicHilma2 = "Men vad är det för utmaning? Låter ju jättelätt!";

	if (mTime > 15)
	{
		mText.setString("");
		mHasClicked = false;
		mRubicCube = false;
		mClock.restart();
	}

	else if (mTime >= 0.1 && mTime <= 5)
	{
		text(rubicHilma);
	}
	else if (mTime > 5 && mTime <= 10)
	{
		text(rubicThomas);
	}
	else if (mTime > 10 && mTime <= 15)
	{
		text(rubicHilma2);
	}
}

void DialogueSystem::displayMagnetDialogue()
{
	std::string magnetHilma = "En magnet… hmm den kan vara användbar.";

	if (mTime > 5)
	{
		mText.setString("");
		mHasClicked = false;
		mMagnet = false;
		mClock.restart();
	}

	else if (mTime >= 0.1 && mTime <= 5)
	{
		text(magnetHilma);
	}
}