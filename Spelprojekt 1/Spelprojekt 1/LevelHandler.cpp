#include "LevelHandler.h"

using namespace std;

LevelHandler::LevelHandler(ResourceHandler &handler):
mLevels(),
mItems()
{
	mPlayer = new Player(handler, sf::Vector2f(400, 400));

	//Initialize new levels
	mLevel1 = new Level1(handler);

	//Add levels to member list
	mLevels.push_back(mLevel1);
}

LevelHandler::~LevelHandler()
{
	mLevels.clear();
}

void LevelHandler::update(float deltaTime)
{
	mPlayer->update(deltaTime);
}

void LevelHandler::draw(sf::RenderWindow &window)
{
	for (LevelVector::size_type i = 0; i < mLevels.size(); i++)
	{
		//Only draw active level
		if (mLevels[i]->isActive())
		{
			mLevels[i]->draw(window);
		}
	}

	mPlayer->draw(window);
}

void LevelHandler::setActiveLevel(int index)
{
	assert(index >= 0);
	//Toggles active level
	if (index > 0)
	{
		//If level to be toggled is greater than 0, toggle last level to be inactive
		mLevels[index - 1]->toggleActive();
	}
	mLevels[index]->toggleActive();
}

//LevelHandler::ItemVector LevelHandler::getActiveItems()
//{
//
//}

Level* LevelHandler::getActiveLevel()
{
	//Returns current active level
	for (LevelVector::size_type i = 0; i < mLevels.size(); i++)
	{
		if (mLevels[i]->isActive())
		{
			return mLevels[i];
			break;
		}
	}
	return NULL;
}

Player* LevelHandler::getPlayer()
{
	return mPlayer;
}