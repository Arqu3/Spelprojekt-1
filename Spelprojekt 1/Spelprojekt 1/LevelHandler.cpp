#include "LevelHandler.h"

using namespace std;

LevelHandler::LevelHandler(ResourceHandler &handler):
mLevels()
{
	//Initialize new levels
	mLevel1 = new Level1(handler);
	mLevel3 = new Level3(handler);
	mLastLevel = new LastLevel(handler);

	//Add levels to member list
	mLevels.push_back(mLevel1);
	mLevels.push_back(mLevel3);
	mLevels.push_back(mLastLevel);
}

LevelHandler::~LevelHandler()
{
	mLevels.clear();
}

void LevelHandler::update(float deltaTime, sf::RenderWindow &window, ResourceHandler &handler)
{
	for (LevelVector::size_type i = 0; i < mLevels.size(); i++)
	{
		//Only update active level
		if (mLevels[i]->isActive())
		{
			mLevels[i]->getPlayer()->update(deltaTime);
			mLevels[i]->update(window, deltaTime);
			if (mLevels[i]->isLevelComplete())
			{
				setActiveLevel(i + 1, handler, false); //TODO - Add safety check for last level in LevelVector
			}
		}
	}
}

void LevelHandler::draw(sf::RenderWindow &window)
{
	for (LevelVector::size_type i = 0; i < mLevels.size(); i++)
	{
		//Only draw active level
		if (mLevels[i]->isActive())
		{
			mLevels[i]->drawBackground(window);
			mLevels[i]->getPlayer()->draw(window);
			mLevels[i]->drawForeground(window);
			mLevels[i]->drawUI(window);
		}
	}
}

void LevelHandler::setActiveLevel(int index, ResourceHandler &handler, bool isFirstLevel)
{
	assert(index >= 0);

	//If level to be toggled is greater than 0, toggle last level to be inactive
	if (isFirstLevel)
	{
		//Toggles active level
		mLevels[index]->toggleActive(handler);
	}
	else
	{
		mLevels[index]->toggleActive(handler);
		if (index > 0)
		{
			mLevels[index - 1]->toggleActive(handler);
		}
	}
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