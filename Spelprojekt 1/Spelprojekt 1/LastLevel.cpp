#include "LastLevel.h"

LastLevel::LastLevel(ResourceHandler &handler) :
mRects(),
mPlayRects(),
mIsActive(false)
{

	//Background Texture scene 1
	background.setSize(sf::Vector2f(1024,576));  
	background.setTexture(handler.getTexture("flickrum.png")); //Add correct texture

	//Playground Texture scene 1

	//Foreground Texture scene 1

	//Background Texture scene 2
	background2.setSize(sf::Vector2f(1536, 576));
	background2.setTexture(handler.getTexture("Barn hem.png")); //Add correct texture

	//Playground Texture scene 2

	//Foreground Texture scene 2

	//Background Texture scene 3
	background3.setSize(sf::Vector2f(1024, 576));
	background3.setTexture(handler.getTexture("Barnhem_Scene3.jpg")); //Add correct texture

	//Playground Texture scene 3

	//Foreground Texture scene 3

	//Add sound

	//Add HelpRect
	rectangle.setPosition(sf::Vector2f(1158, 2));
	rectangle.setSize(sf::Vector2f(70, 168));
	rectangle.setTexture(handler.getTexture("LastLevel_ItemTest1.png"));
	
	//Add items
	
	mMagicClam = new Item(handler, sf::Vector2f(193, 257), "Magic Clam");
	mNeedle = new Item(handler, sf::Vector2f(271, 255), "Needle");
	mEarth = new Item(handler, sf::Vector2f(286, 122), "Earth");
	mFish = new Item(handler, sf::Vector2f(840, 37), "Fish");
	mHoolaHoop = new Item(handler, sf::Vector2f(0, 0), "Hoola Hoop");
	mBeigeBall = new Item(handler, sf::Vector2f(0, 0), "Beige Ball");
	mRedApple = new Item(handler, sf::Vector2f(0, 0), "Red Apple");
	mCat = new Item(handler, sf::Vector2f(0, 0), "Cat");
	mFruitbowl = new Item(handler, sf::Vector2f(0, 0),"Fruitbowl");

	//View
	mView.setCenter(512, 288);
	mView.setSize(1024, 576);

	
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
	window.setView(mView);
	if (mActiveScene == 0)
	{
		window.draw(background);

	}

	else if (mActiveScene == 1)
	{
		window.draw(background2);
		
	}
	else if (mActiveScene == 2)
	{
		mView.setCenter(512, 288);
		window.draw(background3);
	}
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
		

		//Add items to itemVector
		addItem(mMagicClam);
		

	}

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

		//BalconyDoor
		mRects.push_back(createRect(445, 186, 80, 50));

		//Stairs to scene 2
		mRects.push_back(createRect(0, 70, 108, 350));

	}
	else if (num == 1)
	{
		//Scene 2
		mActiveScene = 1;

		//Walkable Area
		mPlayRects.push_back(createRect(100, 354, 944, 216));
		mPlayRects.push_back(createRect(1044, 440, 476, 132));

		//Door
		mRects.push_back(createRect(0, 39, 70, 357));

		//Books
		mRects.push_back(createRect(261, 314, 82, 33));

		//Jewelry Box
		mRects.push_back(createRect(486, 314, 84, 36));

		//Yarn Basket
		mRects.push_back(createRect(271, 255, 74, 43));

		//Crotch Rocket
		mRects.push_back(createRect(377, 249, 23, 49));

		//Gramophone
		mRects.push_back(createRect(437, 108, 96, 123));

		//Mask
		mRects.push_back(createRect(1158, 2, 70, 168));

		//Stairs
		mRects.push_back(createRect(1466, 246,44, 178));

		


		//Items Active
		mNeedle->toggleActive();
		mEarth->toggleActive();
		mFish->toggleActive();

		//Add items to ItemVector
		addItem(mNeedle);
		addItem(mEarth);
		addItem(mFish);


	}
	else if (num == 2)
	{
		//Scene 3
		mActiveScene = 2;

		//Walkable Area
		mPlayRects.push_back(createRect(133, 379,799 , 189));

		//Refrigerator
		mRects.push_back(createRect(789, 105, 126, 269));

		//Catbowl
		mRects.push_back(createRect(714, 396, 54, 24));

		//Hole
		mRects.push_back(createRect(183, 346, 45, 31));

		//Tap
		mRects.push_back(createRect(352, 167, 32, 67));

		


		//Items active
		mHoolaHoop->toggleActive();
		mBeigeBall->toggleActive();
		mRedApple->toggleActive();
		mCat->toggleActive();
		mFruitbowl->toggleActive();

		//Add Items to vector
		addItem(mHoolaHoop);
		addItem(mBeigeBall);
		addItem(mRedApple);
		addItem(mCat);
		addItem(mFruitbowl);
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

