#include "LastLevel.h"

LastLevel::LastLevel(ResourceHandler &handler) :
mRects(),
mPlayRects(),
mIsActive(false)
{
	background.setSize(sf::Vector2f(1024, 576));
	background.setTexture(handler.getTexture(0)); //Add correct texture

	//Add sound

	//Add Rect

	//Add items

}

LastLevel::~LastLevel()
{
	mRects.clear();
	mPlayRects.clear();
}


LastLevel::ItemVector LastLevel::getItems()
{
	return mItems;
}


void LastLevel::addItem(Item *item)
{
	mItems.push_back(item);
}


void LastLevel::removeItem(Item *item)
{
	if (mItems.size() > 1)
	{
		for (ItemVector::size_type i = 0; i < mItems.size(); i++)
		{
			if (item->getId() == mItems[i]->getId())
			{
				std::swap(mItems[i], mItems.back());
				mItems.pop_back();
				break;
			}
		}
	}
}


void LastLevel::playBackgroundMusic()
{
	backgroundMusic.setPitch(0.5); //Does this even work??
	backgroundMusic.play();
}


void LastLevel::playAmbience()
{
	ambientSound.play();
}


void LastLevel::draw(sf::RenderWindow &window)
{
	window.draw(background);

	//Draw items etc.
}


void LastLevel::drawItems(ItemVector items, sf::RenderWindow &window)
{
	for (ItemVector::size_type i = 0; i < mItems.size(); i++)
	{
		mItems[i]->draw(window);
	}
}


void LastLevel::removeRect(int index)
{
	//std::swap(mRects[index], mRects.back()); 
}


const Level::rectVector LastLevel::getPlayRects()
{
	return mPlayRects;
}


void LastLevel::toggleActive()
{
	mIsActive = !mIsActive;
}


bool LastLevel::isActive()
{
	return mIsActive;
}


void LastLevel::clearScene()
{
	mRects.clear();
	mPlayRects.clear();
	mItems.clear();
}


void LastLevel::internalSwap(int num)
{
	//Zoom in on an object
}


void LastLevel::changeScene(int num)
{
	clearScene();
	internalSwap(num);
}


int LastLevel::getActiveScene()
{
	return mActiveScene;
}


LastLevel::rectVector LastLevel::getRects()
{
	return mRects;
}


sf::FloatRect* LastLevel::createRect(int positionX, int positionY, int sizeX, int sizeY)
{
	sf::FloatRect* floatRect = new sf::FloatRect(positionX, positionY, sizeX, sizeY);
	return floatRect;
}

