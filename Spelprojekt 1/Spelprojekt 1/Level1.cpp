#include "Level1.h"

Level1::Level1(ResourceHandler &handler):
mRects(),
mPlayRects(),
mIsActive(false)
{
	// Room Textures
	//Background texture
	background.setSize(sf::Vector2f(1024, 576));
	background.setTexture(handler.getTexture("thomasbg.png"));

	//Playground texture
	playground.setSize(sf::Vector2f(1024, 576));
	playground.setTexture(handler.getTexture("thomaspg.png"));

	//Foreground texture
	foreground.setSize(sf::Vector2f(1024, 576));
	foreground.setTexture(handler.getTexture("thomasfg.png"));

	// Zoom Textures
	//Background Zoom texture
	backgroundZoom.setSize(sf::Vector2f(1024, 576));
	backgroundZoom.setTexture(handler.getTexture("thomaszoombg.png"));

	//Playground Zoom texture
	playgroundZoom.setSize(sf::Vector2f(1024, 576));
	playgroundZoom.setTexture(handler.getTexture("thomaszoompg.png"));

	//Foreground Zoom texture
	foregroundZoom.setSize(sf::Vector2f(1024, 576));
	foregroundZoom.setTexture(handler.getTexture("thomaszoomfg.png"));

	//Sound/music
	music.openFromFile("Level1Music.ogg");

	//Help rectangles
	rectangle.setPosition(sf::Vector2f(140, 480));
	rectangle.setSize(sf::Vector2f(400, 30));

	//Playground rectangles
	mPlayRects.push_back(createRect(110, 360, 660, 200));
	mRects.push_back(createRect(440, 150, 210, 70));

	//Items
	mMagnet = new Item(handler, sf::Vector2f(100, 100), sf::FloatRect(100, 100, 100, 100), "Magnet");
	mMagnet->toggleActive();
	mScrewdevice = new Item(handler, sf::Vector2f(300, 300), sf::FloatRect(300, 300, 100, 100), "Screwdevice");
	mScrewdevice->toggleActive();

	addItem(mMagnet);
	addItem(mScrewdevice);
}

Level1::~Level1()
{
	mRects.clear();
	mPlayRects.clear();
}

Level1::ItemVector Level1::getItems()
{
	return mItems;
}

void Level1::addItem(Item* item)
{
	mItems.push_back(item);
}

void Level1::removeItem(Item* item)
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

void Level1::playBackgroundMusic()
{
	music.play();
}

void Level1::playAmbience()
{
	ambientSound.play();
}

void Level1::drawBackground(sf::RenderWindow &window)
{
	if (mActiveScene == 0)
	{
		window.draw(background);
		window.draw(playground);
	}
	else
	{
		window.draw(backgroundZoom);
		window.draw(playgroundZoom);
	}
	drawItems(mItems, window);
	//window.draw(rectangle);
}

void Level1::drawForeground(sf::RenderWindow &window)
{
	if (mActiveScene == 0)
	{
		window.draw(foreground);
	}
	else
	{
		window.draw(foregroundZoom);
	}
}

void Level1::drawItems(ItemVector items, sf::RenderWindow &window)
{
	for (ItemVector::size_type i = 0; i < mItems.size(); i++)
	{
		if (mItems[i]->getActive())
		{
			mItems[i]->draw(window);
		}
	}
}

void Level1::addRect(sf::FloatRect* rect)
{
	mRects.push_back(rect);
}

void Level1::removeRect(int index)
{
	//std::swap(mRects[index], mRects.back());
}

const Level::rectVector Level1::getPlayRects()
{
	return mPlayRects;
}

void Level1::toggleActive()
{
	mIsActive = !mIsActive;
}

bool Level1::isActive()
{
	return mIsActive;
}

void Level1::clearScene()
{
	mRects.clear();
	mPlayRects.clear();
	mItems.clear();
}

void Level1::internalSwap(int num)
{
	if (num == 0)
	{
		mActiveScene = 0;
		mPlayRects.push_back(createRect(110, 360, 660, 200));
		mRects.push_back(createRect(440, 150, 210, 70));
		if (mMagnet->getActive())
		{
			mItems.push_back(mMagnet);
		}
		if (mScrewdevice->getActive())
		{
			mItems.push_back(mScrewdevice);
		}
	}
	else
	{
		mActiveScene = 1;
		mPlayRects.push_back(createRect(140, 480, 400, 30));
		mRects.push_back(createRect(440, 150, 210, 70));
	}
}

void Level1::changeScene(int num)
{
	clearScene();
	internalSwap(num);
}

int Level1::getActiveScene()
{
	return mActiveScene;
}

Level1::rectVector Level1::getRects()
{
	return mRects;
}

sf::FloatRect* Level1::createRect(float positionX, float positionY, float sizeX, float sizeY)
{
	sf::FloatRect* floatRect = new sf::FloatRect(positionX, positionY, sizeX, sizeY);
	return floatRect;
}