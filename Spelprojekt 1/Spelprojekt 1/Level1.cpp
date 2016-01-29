#include "Level1.h"

Level1::Level1(ResourceHandler &handler):
mRects(),
mPlayRects(),
mIsActive(false)
{
	background.setSize(sf::Vector2f(1024, 576));
	background.setTexture(handler.getTexture("Test3.png"));
	backgroundfishtank.setSize(sf::Vector2f(1024, 576));
	backgroundfishtank.setTexture(handler.getTexture("test_2.png"));
	//backgroundMusic = *handler.getMusic(0);
	//ambientSound.setBuffer(*handler.getSound(0));

	rectangle.setPosition(sf::Vector2f(140, 480));
	rectangle.setSize(sf::Vector2f(400, 30));

	mPlayRects.push_back(createRect(110, 360, 660, 200));
	mRects.push_back(createRect(440, 150, 210, 70));

	mMagnet = new Item(handler, sf::Vector2f(100, 100), sf::FloatRect(100, 100, 100, 100), "Magnet");
	mSkruvmakapär = new Item(handler, sf::Vector2f(300, 300), sf::FloatRect(300, 300, 100, 100), "Skruvmakapär");

	addItem(mMagnet);
	addItem(mSkruvmakapär);
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
	backgroundMusic.setPitch(0.5);
	backgroundMusic.play();
}

void Level1::playAmbience()
{
	ambientSound.play();
}

void Level1::draw(sf::RenderWindow &window)
{
	if (mActiveScene == 0)
	{
		window.draw(background);
	}
	else
	{
		window.draw(backgroundfishtank);
	}
	drawItems(mItems, window);
	window.draw(rectangle);
}

void Level1::drawItems(ItemVector items, sf::RenderWindow &window)
{
	for (ItemVector::size_type i = 0; i < mItems.size(); i++)
	{
		mItems[i]->draw(window);
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
		mItems.push_back(mMagnet);
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

sf::FloatRect* Level1::createRect(int positionX, int positionY, int sizeX, int sizeY)
{
	sf::FloatRect* floatRect = new sf::FloatRect(positionX, positionY, sizeX, sizeY);
	return floatRect;
}