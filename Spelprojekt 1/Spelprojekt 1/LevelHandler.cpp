#include "LevelHandler.h"

using namespace std;

LevelHandler::LevelHandler(ResourceHandler &handler):
mLevels(),
mItems()
{
	mPlayer = new Player(handler, sf::Vector2f(400, 400));

	//Initialize new levels
	mLevel1 = new Level1(handler);
	mLastLevel = new LastLevel(handler);

	//Add levels to member list
	mLevels.push_back(mLevel1);
	mLevels.push_back(mLastLevel);
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
			mLevels[i]->drawBackground(window);
			mPlayer->draw(window);
			mLevels[i]->drawForeground(window);
		}
	}
}

void LevelHandler::setActiveLevel(int index)
{
	assert(index >= 0);
	//Toggles active level
	//if (index > 0) // ADD THIS BACK LATER
	//{
	//	//If level to be toggled is greater than 0, toggle last level to be inactive
	//	mLevels[index - 1]->toggleActive();
	//}
	mLevels[index]->toggleActive();
}

LevelHandler::ItemVector LevelHandler::getActiveItems()
{
	return getActiveLevel()->getItems();
}

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

Level* LevelHandler::getLevel(int index)
{
	return mLevels[index];
}

Player* LevelHandler::getPlayer()
{
	return mPlayer;
}