#include "LastLevel.h"

LastLevel::LastLevel(ResourceHandler &handler) :
mRects(),
mPlayRects(),
mIsActive(false)
{

	//Background Texture scene 1
	background.setSize(sf::Vector2f(1024,576));  //(1536, 576) f�r scen 2
	background.setTexture(handler.getTexture("flickrum.png")); //Add correct texture

	//Playground Texture scene 1

	//Foreground Texture scene 1

	//Background Texture scene 2

	//Playground Texture scene 2

	//Foreground Texture scene 2

	//Background Texture scene 3

	//Background Texture scene 3

	//Foreground Texture scene 3

	//Add sound

	//Add HelpRect
	rectangle.setPosition(sf::Vector2f(0, 70));
	rectangle.setSize(sf::Vector2f(108, 350));
	rectangle.setTexture(handler.getTexture("LastLevel_ItemTest1.png"));
	
	//Add items
	mMagicClam = new Item(handler, sf::Vector2f(0, 0), "Magic Clam");
	mNeedle = new Item(handler, sf::Vector2f(0, 0), "Needle");
	mEarth = new Item(handler, sf::Vector2f(0, 0), "Earth");
	mFish = new Item(handler, sf::Vector2f(0, 0), "Fish");
	mHoolaHoop = new Item(handler, sf::Vector2f(0, 0), "Hoola Hoop");
	mBeigeBall = new Item(handler, sf::Vector2f(0, 0), "Beige Ball");
	mRedApple = new Item(handler, sf::Vector2f(0, 0), "Red Apple");

	
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


void LastLevel::drawBackground(sf::RenderWindow &window)
{
	window.draw(background);
	//window.draw(rectangle);
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
	if (!mIsActive)
	{
		//Rectangles

		//Dollhouse
		mRects.push_back(createRect(193, 257, 150, 100));

		//Planets 1-9
		mRects.push_back(createRect(243, 44, 25, 25));
		mRects.push_back(createRect(317, 52, 40, 40));
		mRects.push_back(createRect(395, 47, 25, 25));
		mRects.push_back(createRect(458, 42, 23, 23));
		mRects.push_back(createRect(518, 38, 70, 70));
		mRects.push_back(createRect(620, 50, 30, 30));
		mRects.push_back(createRect(680, 55, 28, 28));
		mRects.push_back(createRect(742, 55, 28, 28));
		mRects.push_back(createRect(797, 56, 13, 13));

		//Door
		mRects.push_back(createRect(445, 186, 80, 50));

		//Stairs to scene 2
		mRects.push_back(createRect(0, 70, 108, 350));

		//Playground
		mPlayRects.push_back(createRect(108, 378, 610, 192));
		mPlayRects.push_back(createRect(347, 324, 370, 52));

		


		//Items - set as active
		mMagicClam->toggleActive();
		mNeedle->toggleActive();
		mNeedle->togglePickupable();
		mEarth->toggleActive();
		mEarth->togglePickupable();
		mFish->toggleActive();
		mHoolaHoop->toggleActive();
		mBeigeBall->toggleActive();
		mRedApple->toggleActive();

		//Add items to itemVector
		addItem(mMagicClam);
		addItem(mNeedle);
		addItem(mEarth);
		addItem(mFish);
		addItem(mHoolaHoop);
		addItem(mBeigeBall);
		addItem(mRedApple);

	}

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
	if (num == 0)
	{
		mActiveScene = 0;

		//Walkable Area
		mPlayRects.push_back(createRect(108, 378, 610, 192));
		mPlayRects.push_back(createRect(347, 324, 370, 52));

		//Planets 1-9
		mRects.push_back(createRect(243, 44, 25, 25));
		mRects.push_back(createRect(317, 52, 40, 40));
		mRects.push_back(createRect(395, 47, 25, 25));
		mRects.push_back(createRect(458, 42, 23, 23));
		mRects.push_back(createRect(518, 38, 70, 70));
		mRects.push_back(createRect(620, 50, 30, 30));
		mRects.push_back(createRect(680, 55, 28, 28));
		mRects.push_back(createRect(742, 55, 28, 28));
		mRects.push_back(createRect(797, 56, 13, 13));

		//Dollhouse
		mRects.push_back(createRect(193, 257, 150, 100));

		//Door
		mRects.push_back(createRect(445, 186, 80, 50));

		//Stairs to scene 2
		mRects.push_back(createRect(0, 70, 108, 350));

	}
	else if (num == 1)
	{
		//Scene 2
		mActiveScene = 1;
	}
	else
	{
		//Scene 3
		mActiveScene = 2;
	}
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

