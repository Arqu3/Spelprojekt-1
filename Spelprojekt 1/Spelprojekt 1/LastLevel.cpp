#include "LastLevel.h"

LastLevel::LastLevel(ResourceHandler &handler) :
mRects(),
mPlayRects(),
mIsActive(false)
{
	background.setSize(sf::Vector2f(1024, 576));
	background.setTexture(handler.getTexture("LastLevel_BackgroundTest1.png")); //Add correct texture

	//Add sound

	//Add Rect

	//Add items
	mMagicClam = new Item(handler, sf::Vector2f(0, 0), "Magic Clam");
	mMagicClam->toggleActive();

	mNeedle = new Item(handler, sf::Vector2f(0, 0), "Needle");
	mNeedle->toggleActive();
	mNeedle->togglePickupable();

	mEarth = new Item(handler, sf::Vector2f(0, 0), "Earth");
	mEarth->toggleActive();
	mEarth->togglePickupable();

	mFish = new Item(handler, sf::Vector2f(0, 0), "Fish");
	mFish->toggleActive();

	mHoolaHoop = new Item(handler, sf::Vector2f(0, 0), "Hoola Hoop");
	mHoolaHoop->toggleActive();

	mBeigeBall = new Item(handler, sf::Vector2f(0, 0), "Beige Ball");
	mBeigeBall->toggleActive();

	mRedApple = new Item(handler, sf::Vector2f(0, 0), "Red Apple");
	mRedApple->toggleActive();

	//Add to itemVector
	addItem(mMagicClam);
	addItem(mNeedle);
	addItem(mEarth);
	addItem(mFish);
	addItem(mHoolaHoop);
	addItem(mBeigeBall);
	addItem(mRedApple);
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

Player* LastLevel::getPlayer()
{
	return mPlayer;
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


void LastLevel::drawBackground(sf::RenderWindow &window)
{
	window.draw(background);

	drawItems(mItems, window);
	
}

void LastLevel::drawForeground(sf::RenderWindow &window)
{

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

void LastLevel::addRect(sf::FloatRect *rect)
{

}


void LastLevel::toggleActive()
{
	mIsActive = !mIsActive;
}


bool LastLevel::isActive()
{
	return mIsActive;
}

sf::View LastLevel::getView()
{
	return mView;
}

void LastLevel::moveViewWithPlayer(float playerPos)
{
	mView.setCenter(playerPos, 288);
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
	sf::FloatRect* floatRect = new sf::FloatRect((float)positionX, (float)positionY, (float)sizeX, (float)sizeY);
	return floatRect;
}

void LastLevel::eventListen(sf::RenderWindow &window)
{

}

void LastLevel::mouseClick(sf::Event &event)
{

}

void LastLevel::update(sf::RenderWindow &window, float deltaTime)
{

}