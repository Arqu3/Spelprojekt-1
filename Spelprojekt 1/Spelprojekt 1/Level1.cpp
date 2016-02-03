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
	rectangle.setPosition(sf::Vector2f(0, 0));
	rectangle.setSize(sf::Vector2f(0, 0));

	//Create Items
	mScrewdevice = new Item(handler, sf::Vector2f(380, 400), "Screwdevice");
	mMagnet = new Item(handler, sf::Vector2f(325, 270), "Magnet");
	mStar = new Item(handler, sf::Vector2f(475, 435), "Star");
	mAstronaut = new Item(handler, sf::Vector2f(560, 160), "Astronaut");
	mBlock = new Item(handler, sf::Vector2f(570, 160), "Block");
	mString = new Item(handler, sf::Vector2f(250, 370), "String");
	mBowl = new Item(handler, sf::Vector2f(320, 158), "Bowl");
	mCube = new Item(handler, sf::Vector2f(352, 222), "Cube");

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
	window.draw(rectangle); // Help rectangle
	drawItems(mItems, window);
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
	//TODO - Should set Rect size to 0 and/or move it outside screen bounds
}

const Level::rectVector Level1::getPlayRects()
{
	return mPlayRects;
}

void Level1::toggleActive()
{
	if (!mIsActive)
	{
		//Playground rectangles
		mPlayRects.push_back(createRect(110, 360, 610, 200));
		mPlayRects.push_back(createRect(670, 330, 160, 80));

		//Fishtank, Zoom
		mRects.push_back(createRect(440, 150, 125, 70));

		//Books in bookcase
		mRects.push_back(createRect(200, 50, 100, 200));
		//Lamp
		mRects.push_back(createRect(75, 165, 50, 100));
		//Radio
		mRects.push_back(createRect(10, 245, 50, 60));
		//Posters
		mRects.push_back(createRect(410, 20, 260, 120));
		//Backpack
		mRects.push_back(createRect(750, 420, 50, 70));

		//Items - Set as Active
		mMagnet->toggleActive();
		mMagnet->togglePickupable();

		mStar->toggleActive();
		mStar->toggleInteractable();

		mBlock->toggleActive();

		mString->toggleActive();
		mString->togglePickupable();

		mBowl->toggleActive();

		mCube->toggleActive();

		//Add to ItemVector
		addItem(mMagnet);
		addItem(mStar);
		addItem(mAstronaut);
		addItem(mBlock);
		addItem(mString);
		addItem(mBowl);
		addItem(mCube);
	}

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
	// Thomas Rum
	if (num == 0)
	{
		mActiveScene = 0;
		//Walkable area
		mPlayRects.push_back(createRect(110, 360, 660, 200));
		mPlayRects.push_back(createRect(670, 330, 160, 80));

		//Fishtank, Zoom
		mRects.push_back(createRect(440, 150, 210, 70));

		//Books in bookcase
		mRects.push_back(createRect(200, 50, 100, 200));
		//Lamp
		mRects.push_back(createRect(75, 165, 50, 100));
		//Radio
		mRects.push_back(createRect(10, 245, 50, 60));
		//Posters
		mRects.push_back(createRect(410, 20, 260, 120));
		//Backpack
		mRects.push_back(createRect(750, 420, 50, 70));

		//Repopulate ItemVector with active items
		if (mMagnet->getActive())
		{
			addItem(mMagnet);
		}
		if (mStar->getActive())
		{
			addItem(mStar);
		}
		if (mAstronaut->getActive())
		{
			addItem(mAstronaut);
		}
		if (mBlock->getActive())
		{
			mBlock->setPosition(570, 160);
			mBlock->setScale(0.3, 0.3);
			addItem(mBlock);
		}
		if (mString->getActive())
		{
			addItem(mString);
		}
		if (mBowl->getActive())
		{
			addItem(mBowl);
		}
		if (mCube->getActive())
		{
			addItem(mCube);
		}
	}
	// Fishtank Zoom
	else
	{
		mActiveScene = 1;
		//Walkable area
		mPlayRects.push_back(createRect(140, 490, 350, 25));
		//Back to room, left side of screen
		mRects.push_back(createRect(0, 30, 120, 470));

		//mBlock toggle interactable only if not already moved
		//isInteracted() in Item?

		//Repopulate ItemVector with active items
		if (mBlock->getActive())
		{
			mBlock->setPosition(500, 315);
			mBlock->setScale(1, 1);
			addItem(mBlock);
		}
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