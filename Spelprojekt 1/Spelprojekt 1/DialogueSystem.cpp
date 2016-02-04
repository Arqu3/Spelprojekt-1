#include "DialogueSystem.h"
#include <iostream>
#include "SFML\System.hpp"

DialogueSystem::DialogueSystem(LevelHandler &levelHandler):
mHasClicked(false),
mTime(0),
mText(),
mFont(),
mLevelHandler(&levelHandler)
{
	mFont.loadFromFile("Resources/Fonts/ShadowsIntoLight.ttf");
}

DialogueSystem::~DialogueSystem()
{

}

void DialogueSystem::text(std::string text, sf::Vector2f &position)
{
	mText.setFont(mFont);
	mText.setCharacterSize(14);
	mText.setStyle(sf::Text::Bold);
	mText.setColor(sf::Color::White);
	//Get Player position correctly
	mText.setPosition(position);
	mText.setString(text);
}

void DialogueSystem::drawDialogue(sf::RenderWindow &window)
{
	window.draw(mText);
}

//Function to check if the player has clicked on an object
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

//Resets all variables
void DialogueSystem::reset()
{
	mHasClicked = false;
	mRubicCube = false;
	mMagnet = false;

	mText.setString("");

	mClock.restart();
	mTime = 0;
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
		mTime = 0;
		mClock.restart();
	}

	else if (mTime > 0 && mTime <= 5)
	{
		text(rubicHilma, mLevelHandler->getPlayer()->getPosition());
	}
	else if (mTime > 5 && mTime <= 10)
	{
		text(rubicThomas, mLevelHandler->getPlayer()->getPosition());
	}
	else if (mTime > 10 && mTime <= 15)
	{
		text(rubicHilma2, mLevelHandler->getPlayer()->getPosition());
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
		mTime = 0;
		mClock.restart();
	}

	else if (mTime > 0 && mTime <= 5)
	{
		text(magnetHilma, mLevelHandler->getPlayer()->getPosition());
	}
}