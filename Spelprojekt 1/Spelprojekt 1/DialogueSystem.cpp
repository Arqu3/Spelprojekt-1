#include "DialogueSystem.h"
#include <iostream>
#include "SFML\System.hpp"

DialogueSystem::DialogueSystem(LevelHandler &levelHandler, ResourceHandler &handler):
mHasClicked(false),
mTime(0),
mText(),
mFont(),
mIsActive(false),
mLevelHandler(&levelHandler)
{
	mFont.loadFromFile("Resources/Fonts/ShadowsIntoLight.ttf");
	mBubble.setTexture(*handler.getTexture("textbubble.png"));
}

DialogueSystem::~DialogueSystem()
{

}

//Function for all text in dialogues
void DialogueSystem::text(std::string text, sf::Vector2f &position, float x, float y)
{
	mText.setFont(mFont);
	mText.setCharacterSize(18);
	mText.setStyle(sf::Text::Bold);
	mText.setColor(sf::Color::White);
	mText.setPosition(position);
	mText.move(x, y);
	mText.setString(text);
}

//Draw function for game to use
void DialogueSystem::drawDialogue(sf::RenderWindow &window)
{
	if (mIsActive)
	{
		window.draw(mBubble);
	}
	window.draw(mText);
}

void DialogueSystem::createTalkBubble(sf::Vector2f &position, float OffSetX, float OffSetY, float x, float y)
{
	mBubble.setPosition(position);
	mBubble.setScale(sf::Vector2f(x, y));
	mBubble.move(OffSetX, OffSetY);
}

//Function to check if the player has clicked on an object
void DialogueSystem::hasClicked(std::string indexName)
{
	if (indexName == "rubicCube" && mHasClicked == false)
	{
		mRubicCube = true;
		mHasClicked = true;
	}
	if (indexName == "magnet" && mHasClicked == false)
	{
		mMagnet = true;
		mHasClicked = true;
	}
	if (indexName == "books" && mHasClicked == false)
	{
		mBooks = true;
		mHasClicked = true;
	}
	if (indexName == "lamp" && mHasClicked == false)
	{
		mLamp = true;
		mHasClicked = true;
	}
	if (indexName == "poster" && mHasClicked == false)
	{
		mPoster = true;
		mHasClicked = true;
	}
	if (indexName == "backpack" && mHasClicked == false)
	{
		mBackpack = true;
		mHasClicked = true;
	}
	if (indexName == "bowl" && mHasClicked == false)
	{
		mBowl = true;
		mHasClicked = true;
	}
	else
		mHasClicked = false;
}

//Resets all variables
void DialogueSystem::reset()
{
	mHasClicked = false;
	mState = 0;

	mText.setString("");
}

//Update function
void DialogueSystem::update(float time)
{
	if (mRubicCube == true)
	{
		displayRubicCubeDialogue();
	}

	if (mMagnet == true)
	{
		displayMagnetDialogue();
	}

	if (mBooks == true)
	{
		displayBooksDialogue();
	}

	if (mLamp == true)
	{
		displayLampDialogue();
	}
	if (mPoster == true)
	{
		displayPosterDialogue();
	}
	if (mBackpack == true)
	{
		displayBackpackDialogue();
	}
	if (mBowl == true)
	{
		displayBowlDialogue();
	}
}

void DialogueSystem::setState()
{
	mState++;
}

//Dialogue functions down below
void DialogueSystem::displayBooksDialogue()
{
	std::string booksHilma = "Hur m�nga b�cker har du egentligen?";
	std::string booksThomas = "Senast jag r�knade var det tjugofyra, men� det var ju ett tag sen�";

	if (mState == 2)
	{
		mText.setString("");
		mHasClicked = false;
		mBooks = false;
		mIsActive = false;
	}
	if (mState == 0)
	{
		mIsActive = true;
		text(booksHilma, mLevelHandler->getPlayer()->getPosition(), -180, -180);
		createTalkBubble(mLevelHandler->getPlayer()->getPosition(), -180, -200, 2.1f, 1.f);
	}
	if (mState == 1)
	{
		text(booksThomas, mLevelHandler->getPlayer()->getPosition(), 60, -250);
		createTalkBubble(mLevelHandler->getPlayer()->getPosition(), 60, -250, 2.5f, 1.f);
	}
}

void DialogueSystem::displayLampDialogue()
{
	std::string lampHilma = "Vad f�r oansvarig m�nniska placerar en lampa vid sitt f�nster ? Jag fl�g n�stan in i den innan!";
	std::string lampThomas = "Jag visste inte att det var farligt med lampor�";
	std::string lampHilma2 = "Ni m�nniskor �r s� v�rdsl�sa.";
	std::string lampThomas2 = "Det var ju faktiskt du som krashade i mitt rum. Det tycker jag l�ter v�rdsl�st.";
	std::string lampHilma3 = "Hmpf.";

	if (mState == 5)
	{
		mText.setString("");
		mHasClicked = false;
		mLamp = false;
		mIsActive = false;
	}

	if (mState == 0)
	{
		mIsActive = true;
		text(lampHilma, mLevelHandler->getPlayer()->getPosition(), -180, -180);
		createTalkBubble(mLevelHandler->getPlayer()->getPosition(), -180, -200, 2.1f, 1.f);
	}

	if (mState == 1)
	{
		text(lampThomas, mLevelHandler->getPlayer()->getPosition(), 60, -250);
		createTalkBubble(mLevelHandler->getPlayer()->getPosition(), 60, -250, 2.5f, 1.f);
	}

	if (mState == 2)
	{
		text(lampHilma2, mLevelHandler->getPlayer()->getPosition(), -250, -250);
		createTalkBubble(mLevelHandler->getPlayer()->getPosition(), -250, -250, 2.5f, 1.f);
	}

	if (mState == 3)
	{
		text(lampThomas2, mLevelHandler->getPlayer()->getPosition(), 60, -250);
		createTalkBubble(mLevelHandler->getPlayer()->getPosition(), 60, -250, 2.5f, 1.f);
	}
	if (mState == 4)
	{
		text(lampHilma3, mLevelHandler->getPlayer()->getPosition(), -250, -250);
		createTalkBubble(mLevelHandler->getPlayer()->getPosition(), -250, -250, 2.5f, 1.f);
	}
}

void DialogueSystem::displayRubicCubeDialogue()
{
	std::string rubicHilma = "Vad �r det h�r?";
	std::string rubicThomas = "En Rubiks kub, man ska \nf� alla f�rgerna p� varsin sida.";
	std::string rubicHilma2 = "Men vad �r det f�r utmaning? \nL�ter ju j�ttel�tt!";

	if (mState == 3)
	{
		mText.setString("");
		mHasClicked = false;
		mRubicCube = false;
		mIsActive = false;
	}

	if (mState == 0)
	{
		mIsActive = true;
		text(rubicHilma, mLevelHandler->getPlayer()->getPosition(), -180, -180);
		createTalkBubble(mLevelHandler->getPlayer()->getPosition(), -180, -200, 2.1f, 1.f);
	}
	if (mState == 1)
	{
		text(rubicThomas, mLevelHandler->getPlayer()->getPosition(), 60, -250);
		createTalkBubble(mLevelHandler->getPlayer()->getPosition(), 60, -250, 2.5f, 1.f);
	}
	if (mState == 2)
	{
		text(rubicHilma2, mLevelHandler->getPlayer()->getPosition(), -250, -250);
		createTalkBubble(mLevelHandler->getPlayer()->getPosition(), -250, -250, 2.5f, 1.f);
	}
}


void DialogueSystem::displayMagnetDialogue()
{
	std::string magnetHilma = "En magnet� hmm \nden kan vara anv�ndbar.";

	if (mState == 1)
	{
		mText.setString("");
		mHasClicked = false;
		mMagnet = false;
		mIsActive = false;
	}

	if (mState == 0)
	{
		mIsActive = true;
		text(magnetHilma, mLevelHandler->getPlayer()->getPosition(), -180, -180);
		createTalkBubble(mLevelHandler->getPlayer()->getPosition(), -180, -200, 2.1f, 1.f);
	}
}

void DialogueSystem::displayPosterDialogue()
{
	std::string posterHilma = "Varf�r �r det bara rymdbilder?";
	std::string posterThomas = "Jag gillar rymden och planeter och s�nt. Min mormor gav mig de flesta av dem.";

	if (mState == 2)
	{
		mText.setString("");
		mHasClicked = false;
		mPoster = false;
		mIsActive = false;
	}

	if (mState == 0)
	{
		mIsActive = true;
		text(posterHilma, mLevelHandler->getPlayer()->getPosition(), -180, -180);
		createTalkBubble(mLevelHandler->getPlayer()->getPosition(), -180, -200, 2.1f, 1.f);
	}

	if (mState == 1)
	{
		text(posterThomas, mLevelHandler->getPlayer()->getPosition(), 60, -250);
		createTalkBubble(mLevelHandler->getPlayer()->getPosition(), 60, -250, 2.5f, 1.f);
	}
}

void DialogueSystem::displayBackpackDialogue()
{
	std::string backpackHilma = "Vad �r det f�r en massa papper i v�skan?";
	std::string backpackThomas = "L�xor� de var roliga ett tag men sen fick jag bara fler och fler!";

	if (mState == 2)
	{
		mText.setString("");
		mHasClicked = false;
		mBackpack = false;
		mIsActive = false;
	}

	if (mState == 0)
	{
		mIsActive = true;
		text(backpackHilma, mLevelHandler->getPlayer()->getPosition(), -180, -180);
		createTalkBubble(mLevelHandler->getPlayer()->getPosition(), -180, -200, 2.1f, 1.f);
	}

	if (mState == 1)
	{
		text(backpackThomas, mLevelHandler->getPlayer()->getPosition(), 60, -250);
		createTalkBubble(mLevelHandler->getPlayer()->getPosition(), 60, -250, 2.5f, 1.f);
	}
}

void DialogueSystem::displayBowlDialogue()
{
	std::string bowlHilma = "Anv�nde du den h�r n�r du klippte dig eller?";
	std::string bowlThomas = "Vad menar du?";
	std::string bowlHilma2 = "�h, gl�m det�";

	if (mState == 3)
	{
		mText.setString("");
		mHasClicked = false;
		mBowl = false;
		mIsActive = false;
	}

	if (mState == 0)
	{
		mIsActive = true;
		text(bowlHilma, mLevelHandler->getPlayer()->getPosition(), -180, -180);
		createTalkBubble(mLevelHandler->getPlayer()->getPosition(), -180, -200, 2.1f, 1.f);
	}

	if (mState == 1)
	{
		text(bowlThomas, mLevelHandler->getPlayer()->getPosition(), 60, -250);
		createTalkBubble(mLevelHandler->getPlayer()->getPosition(), 60, -250, 2.5f, 1.f);
	}

	if (mState == 2)
	{
		text(bowlHilma2, mLevelHandler->getPlayer()->getPosition(), -180, -180);
		createTalkBubble(mLevelHandler->getPlayer()->getPosition(), -180, -200, 2.1f, 1.f);
	}
}