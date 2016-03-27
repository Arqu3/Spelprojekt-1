#include "Level3.h"

Level3::Level3(ResourceHandler &handler) :
mRects(),
mPlayRects(),
mIsActive(false),
handler(handler),
mLevelComplete(false),
mMouseReleased(false)
{
}

Level3::~Level3()
{
	mRects.clear();
	mPlayRects.clear();
}


Level3::ItemVector Level3::getItems()
{
	return mItems;
}


void Level3::addItem(Item *item)
{
	mItems.push_back(item);
}


void Level3::removeItem(Item *item)
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

Player* Level3::getPlayer()
{
	return mPlayer;
}


void Level3::playBackgroundMusic()
{

	music.play();
}


void Level3::playAmbience()
{
	ambientSound.play();
}


void Level3::drawBackground(sf::RenderWindow &window)
{
	window.setView(mView);
	if (mActiveScene == 0)
	{
		
		window.draw(background);
		//window.draw(playground);

	}

	else if (mActiveScene == 1)
	{

		window.draw(background2);
		window.draw(playground2);


	}

	else if (mActiveScene == 2)
	{
		window.draw(background3);
		
	}

	/*window.draw(rectangle);
	window.draw(rectangle2);
	window.draw(rectangle3);
	window.draw(rectangle4);
	window.draw(rectangle5);
	window.draw(rectangle6);
	window.draw(rectangle7);
	window.draw(rectangle8);
	window.draw(rectangle9);
	window.draw(rectangle10);
	window.draw(rectangle11);
	window.draw(rectangle12);
	window.draw(rectangle12);
	window.draw(rectangle13);
	window.draw(rectangle14);
	window.draw(rectangle15);
	window.draw(rectangle16);
	window.draw(rectangle17);*/ //ta bort

	drawItems(mItems, window);

}

void Level3::drawForeground(sf::RenderWindow &window)
{
	if (mActiveScene == 0)
	{
		window.draw(foreground);

	}

	else if (mActiveScene == 1)
	{
		window.draw(foreground2);
	}
	else if (mActiveScene == 2)
	{
		window.draw(foreground3);
	}

	if (mInventoryMode)
	{
		mInventory->draw(window);
	}
}

void Level3::drawUI(sf::RenderWindow &window)
{
	mUI->draw(window);

	if (mUI->getState() == UI::INVENTORY)
	{
		mInventory->draw(window);
	}
	if (mCursor->getMode() == Cursor::DIALOGUE)
	{
		mDialogueSystem->drawDialogue(window);
	}

	mCursor->draw(window);

	if (mInventory->getSelectedItem() != -1)
	{
		mInventory->drawCursorSprite(window);
	}
}


void Level3::drawItems(ItemVector items, sf::RenderWindow &window)
{
	for (ItemVector::size_type i = 0; i < mItems.size(); i++)
	{
		if (mItems[i]->getActive())
		{
			mItems[i]->draw(window);

		}
	}
}


void Level3::removeRect(int index)
{
	//std::swap(mRects[index], mRects.back()); 
}


const Level::rectVector Level3::getPlayRects()
{
	return mPlayRects;
}

void Level3::addRect(sf::FloatRect *rect)
{

}


void Level3::toggleActive(ResourceHandler &handler, sf::RenderWindow &window, UI *ui)
{
	if (!mIsActive)
	{
		handler.loadLevel3(window);

		//Background Texture scene 1
		background.setSize(sf::Vector2f(2048, 576));
		background.setTexture(handler.getTexture("Garden.png"));

		//Foreground Texture scene 1
		foreground.setSize(sf::Vector2f(2048, 576));
		foreground.setTexture(handler.getTexture("GardenForeground.png")); 

		//Background 2
		background2.setSize(sf::Vector2f(1511, 576));
		background2.setTexture(handler.getTexture("CabinBackground.png"));

		//Foreground 2
		foreground2.setSize(sf::Vector2f(1511, 576));
		foreground2.setTexture(handler.getTexture("CabinForeground.png"));

		//Playground 2
		playground2.setSize(sf::Vector2f(1511, 576));
		playground2.setTexture(handler.getTexture("CabinPlayground.png"));

		//Background 3
		background3.setSize(sf::Vector2f(2560, 576));
		background3.setTexture(handler.getTexture("magicworld_background.png"));

		//Foreground 3
		foreground3.setSize(sf::Vector2f(2560, 576));
		foreground3.setTexture(handler.getTexture("magicworld_foreground.png"));


		//Add sound
		music.openFromFile("Level1Music.ogg");

		//Add HelpRect
		rectangle.setPosition(sf::Vector2f(1973, 123));
		rectangle.setSize(sf::Vector2f(73, 278));
		rectangle.setTexture(handler.getTexture("LastLevel_ItemTest1.png"));

		//Add items
		mKey = new Item(handler, sf::Vector2f(-100, -100), "Key");
		mTrimmer = new Item(handler, sf::Vector2f(341, 367), "Trimmer");
		mStick = new Item(handler, sf::Vector2f(381, 220), "Stick");
		mFlowers = new Item(handler, sf::Vector2f(156, 525), "Flowers");
		mLeash = new Item(handler, sf::Vector2f(615, 303), "Leash");
		mDog = new Item(handler, sf::Vector2f(730, 370), "Dog");
		mFlagpole = new Item(handler, sf::Vector2f(1386, 195), "Flagpole");
		mSingleFlower = new Item(handler, sf::Vector2f(1390, 265), "Singleflower");
		mLady = new Item(handler, sf::Vector2f(565, 87), "Lady");

		mClover = new Item(handler, sf::Vector2f(241, 234), "Clover");
		mSawdust = new Item(handler, sf::Vector2f(831, 254), "Sawdust");
		mNail = new Item(handler, sf::Vector2f(285, 80), "Nail"); //Plockas upp
		mFjun = new Item(handler, sf::Vector2f(1192, 52), "Fjun");
		mFeatherball = new Item(handler, sf::Vector2f(200, 343), "Featherball");
		mJack = new Item(handler, sf::Vector2f(1190, 140), "Jack");
		mRippedCloth = new Item(handler, sf::Vector2f(169, 481), "RippedCloth");

		mPond = new Item(handler, sf::Vector2f(133, 416), "Pond");
		mStatue = new Item(handler, sf::Vector2f(685, 120), "Statue");
		mBlueStone = new Item(handler, sf::Vector2f(709, 56), "BlueStone");
		mRedStone = new Item(handler, sf::Vector2f(758, 30), "RedStone");
		mYellowStone = new Item(handler, sf::Vector2f(804, 57), "YellowStone");
		mGreenStone = new Item(handler, sf::Vector2f(759, 97), "GreenStone");
		mHideout1 = new Item(handler, sf::Vector2f(1067, 297), "Hideout 1");
		mHideout2 = new Item(handler, sf::Vector2f(1604, 194), "Hideout 2");
		mHideout3 = new Item(handler, sf::Vector2f(1831, 257), "Hideout 3");
		mHideout4 = new Item(handler, sf::Vector2f(2059, 216), "Hideout 4");
		mParent = new Item(handler, sf::Vector2f(1495, 333), "Parent");
		mSkatmara = new Item(handler, sf::Vector2f(2423, 232), "Skatmara");
		mCoin = new Item(handler, sf::Vector2f(0, 0), "Coin");
		

		//View
		mView.setSize(1024, 576);
		mView.setCenter(512, 288);
		//Player
		mPlayer = new Player(handler, sf::Vector2f(400, 400));


		//Inventory
		mInventory = new Inventory(handler);
		mInventory->setCraftableItems(handler, 1);

		//Cursor
		mCursor = new Cursor(handler);

		//UI
		mUI = ui;

		/*mDialogueSystem = new DialogueSystem(handler);*/

		//Rectangles
		mRects.push_back(createRect(1806, 96, 62, 74));
		mRects.push_back(createRect(1973, 123, 73, 278));

		
		//Playground
		mPlayRects.push_back(createRect(0, 360, 683, 160));

		//Item Active
		mKey->toggleActive();

		mTrimmer->toggleActive();
		mTrimmer->toggleLookable();
		mTrimmer->togglePickupable();

		mStick->toggleActive();
		mStick->toggleLookable();
		mStick->togglePickupable();

		mFlowers->toggleActive();
		mFlowers->togglePickupable();
		
		mSingleFlower->toggleInteractable();
		

		mLeash->toggleActive();
		mLeash->toggleLookable();
		mLeash->toggleInteractable();

		mDog->toggleActive();
		mDog->toggleLookable();
		mDog->toggleInteractable();

		mFlagpole->toggleActive();
		mFlagpole->toggleLookable();
		mFlagpole->toggleInteractable();

		mLady->toggleActive();
		mLady->setActiveAnimation("GardenLady");

		mClover->toggleActive();
		mClover->toggleLookable();
		mClover->togglePickupable();

		mSawdust->toggleActive();
		mSawdust->toggleLookable();
		mSawdust->togglePickupable();

		mFjun->toggleActive();
		mFjun->toggleLookable();
		mFjun->togglePickupable();

		mFeatherball->toggleActive();
		mFeatherball->toggleLookable();
		mFeatherball->togglePickupable();

		mJack->toggleActive();
		mJack->toggleLookable();
		mJack->toggleInteractable();

		mNail->toggleActive();
		mNail->toggleLookable();
		mNail->togglePickupable();

		mRippedCloth->toggleActive();
		mRippedCloth->toggleLookable();
		mRippedCloth->togglePickupable();

		mPond->toggleActive();
		mPond->toggleLookable();
		mPond->toggleInteractable();

		mStatue->toggleActive();
		mStatue->toggleLookable();
		mStatue->toggleInteractable();

		mBlueStone->toggleActive();
		mBlueStone->toggleLookable();
		mBlueStone->toggleInteractable();

		mRedStone->toggleActive();
		mRedStone->toggleLookable();
		mRedStone->toggleInteractable();

		mGreenStone->toggleActive();
		mGreenStone->toggleLookable();
		mGreenStone->toggleInteractable();

		mYellowStone->toggleActive();
		mYellowStone->toggleLookable();
		mYellowStone->toggleInteractable();

		mHideout1->toggleActive();
		mHideout1->toggleLookable();
		mHideout1->toggleInteractable();

		mHideout2->toggleActive();
		mHideout2->toggleLookable();
		mHideout2->toggleInteractable();

		mHideout3->toggleActive();
		mHideout3->toggleLookable();
		mHideout3->toggleInteractable();

		mHideout4->toggleActive();
		mHideout4->toggleLookable();
		mHideout4->toggleInteractable();

		mParent->toggleActive();
		mParent->toggleLookable();
		mParent->toggleInteractable();

		mSkatmara->toggleActive();
		mSkatmara->toggleLookable();
		mSkatmara->toggleInteractable();


		//Add to Itemvector
		addItem(mTrimmer);
		addItem(mStick);
		addItem(mFlowers);
		addItem(mLeash);
		addItem(mDog);
		addItem(mFlagpole);
		addItem(mSingleFlower);
		addItem(mLady);

		//changeScene(2);


		mInventory->addItem(mKey);
	}
	else
	{
		delete mPlayer;
		delete mInventory;
		delete mDialogueSystem;
		//delete mClues;
		mItems.clear();
		mRects.clear();
		mPlayRects.clear();
		mUI->setActiveAnimation("None");
		music.stop();
	}

	mIsActive = !mIsActive;
}


bool Level3::isActive()
{
	return mIsActive;
}

sf::View Level3::getView()
{
	return mView;
}

void Level3::moveViewWithPlayer(float playerPos)
{
	mView.setCenter(playerPos, 288);
}

void Level3::clearScene()
{
	mRects.clear();
	mPlayRects.clear();
	mItems.clear();
}


void Level3::internalSwap(int num)
{
	if (num == 0)
	{
		//Scene 1
		mActiveScene = 0;

		//Walkable Area
		mPlayRects.push_back(createRect(0, 360, 683, 160));
		mPlayRects.push_back(createRect(683, 360, 673, 160));
		mPlayRects.push_back(createRect(1356, 360, 500, 160));

		//Rectangles
		mRects.push_back(createRect(1806, 96, 62, 74));
		mRects.push_back(createRect(1973, 123, 73, 278));

		if (mTrimmer->getActive())
		{
			addItem(mTrimmer);
		}
		if (mFlagpole->getActive())
		{
			addItem(mFlagpole);
		}
		if (mSingleFlower->getActive())
		{
			addItem(mSingleFlower);
		}
		if (mLady->getActive())
		{
			addItem(mLady);
		}
	}

	else if (num == 1)
	{

		mView.setCenter(524, 288);
	
		mPlayer->togglePlayer();
		mPlayer->setScale(sf::Vector2f(0.4f, 0.4f));

		//Scene 2
		mActiveScene = 1;

		//Walkable Area
		mPlayRects.push_back(createRect(96, 287, 286, 38));
		mPlayRects.push_back(createRect(382, 249, 418, 323));
		mPlayRects.push_back(createRect(800, 354, 624, 77));

		//Rectangles

		//Dörr till trädgård
		mRects.push_back(createRect(72, 106, 70, 160));

		//nästa rum
		mRects.push_back(createRect(1432, 146, 76, 210));

		//Dialogrespons Rymdraket
		mRects.push_back(createRect(900, 67, 162, 169));

		//Dialogrespons Pensel
		mRects.push_back(createRect(1053, 423, 215, 102));

		////Knekt ?
		//mRects.push_back(createRect(1226, 157, 100, 200));


		if (mClover->getActive())
		{
			addItem(mClover);
		}
		if (mSawdust->getActive())
		{
			addItem(mSawdust);
		}
		if (mFjun->getActive())
		{
			addItem(mFjun);
		}
		if (mFeatherball->getActive())
		{
			addItem(mFeatherball);
		}
		if (mJack->getActive())
		{
			addItem(mJack);
		}
		if (mNail->getActive())
		{
			addItem(mNail);
		}
		if (mRippedCloth->getActive())
		{
			addItem(mRippedCloth);
		}
	}
	else if (num == 2)
	{
		//Scene 3
		mActiveScene = 2;
		mView.setCenter(524, 288);

		//Walkable Area
		mPlayRects.push_back(createRect(277, 387, 151, 79));
		mPlayRects.push_back(createRect(428, 294, 503, 201));
		mPlayRects.push_back(createRect(931, 412, 727, 83));
		mPlayRects.push_back(createRect(1658, 255, 73, 240));
		mPlayRects.push_back(createRect(1731, 355, 498, 140));
		mPlayRects.push_back(createRect(2229, 306, 150, 90));

		
		//Rectangles - (om inget annat anges: dialogrespons på alla rektanglar)

		//Använd magnetfiskare. Lägger "guldmynt" i inventory ITEM!!
		rectangle.setSize(sf::Vector2f(156, 78));
		rectangle.setPosition(133, 416);

		//Spelar melodi och ändrar sprite. (se: musikpussel)  ITEM!!
		rectangle2.setSize(sf::Vector2f(73, 85));
		rectangle2.setPosition(740, 158);

		//Spelar melodi och ändrar sprite. Ingen dialogrespons (se: musikpussel)  ITEM!!
		rectangle3.setSize(sf::Vector2f(47, 37));
		rectangle3.setPosition(709, 56);

		//Spelar melodi och ändrar sprite. Ingen dialogrespons (se: musikpussel)
		rectangle4.setSize(sf::Vector2f(41, 36));
		rectangle4.setPosition(758, 30);

		//Spelar melodi och ändrar sprite. Ingen dialogrespons (se: musikpussel)
		rectangle5.setSize(sf::Vector2f(44, 37));
		rectangle5.setPosition(804, 57);

		//Spelar melodi och ändrar sprite. Ingen dialogrespons (se: musikpussel)
		rectangle6.setSize(sf::Vector2f(45, 34));
		rectangle6.setPosition(759, 97);

		//(kurragömmapussel - prata med design)
		rectangle7.setSize(sf::Vector2f(82, 42));
		rectangle7.setPosition(1067, 297);

		//(kurragömmapussel - prata med design)
		rectangle8.setSize(sf::Vector2f(115, 31));
		rectangle8.setPosition(1831, 257);

		//(kurragömmapussel - prata med design)
		rectangle9.setSize(sf::Vector2f(141, 60));
		rectangle9.setPosition(2059, 216);

		//(kurragömmapussel - prata med design)
		rectangle10.setSize(sf::Vector2f(108, 24));
		rectangle10.setPosition(1604, 194);

		//om pussel avklarade > klara banan. Else: dialogrespons
		rectangle11.setSize(sf::Vector2f(122, 168));
		rectangle11.setPosition(322, 102);

		//triggers various dialogs
		rectangle12.setSize(sf::Vector2f(47, 96));
		rectangle12.setPosition(2423, 232);

		//endast dialogrespons
		rectangle13.setSize(sf::Vector2f(58, 83));
		rectangle13.setPosition(611, 415);

		//triggers various dialogs
		rectangle14.setSize(sf::Vector2f(63, 85));
		rectangle14.setPosition(1495, 333);

		//endast dialogrespons
		rectangle15.setSize(sf::Vector2f(160, 232));
		rectangle15.setPosition(25, 49);

		//endast dialogrespons
		rectangle16.setSize(sf::Vector2f(129, 173));
		rectangle16.setPosition(1342, 90);

		//endast dialogrespons
		rectangle17.setSize(sf::Vector2f(173, 92));
		rectangle17.setPosition(2337, 474);

		//Real rects
		/*mRects.push_back(createRect(133, 416, 156, 78));
		mRects.push_back(createRect(745, 160, 73, 85));
		mRects.push_back(createRect(709, 56, 47, 37));
		mRects.push_back(createRect(753, 30, 41, 31));
		mRects.push_back(createRect(804, 57, 44, 37));
		mRects.push_back(createRect(759, 97, 45, 34));
		mRects.push_back(createRect(1067, 297, 82, 42));
		mRects.push_back(createRect(1831, 257, 115, 31));
		mRects.push_back(createRect(2059, 216, 141, 60));
		mRects.push_back(createRect(1604, 194, 108, 24));*/
		mRects.push_back(createRect(322, 102, 122, 168));
		/*mRects.push_back(createRect(2423, 232, 47, 96));*/
		mRects.push_back(createRect(611, 415, 58, 83));
		/*mRects.push_back(createRect(1495, 333, 63, 85));*/
		mRects.push_back(createRect(25, 49, 160, 232));
		mRects.push_back(createRect(1342, 90, 129, 175));
		mRects.push_back(createRect(2337, 474, 173, 92));

		if (mPond->getActive())
		{
			addItem(mPond);
		}
		if (mStatue->getActive())
		{
			addItem(mStatue);
		}
		if (mBlueStone->getActive())
		{
			addItem(mBlueStone);
		}
		if (mRedStone->getActive())
		{
			addItem(mRedStone);
		}
		if (mGreenStone->getActive())
		{
			addItem(mGreenStone);
		}
		if (mYellowStone->getActive())
		{
			addItem(mYellowStone);
		}
		/*if (mHideout1->getActive())
		{
			addItem(mHideout1);
		}
		if (mHideout2->getActive())
		{
			addItem(mHideout2);
		}
		if (mHideout3->getActive())
		{
			addItem(mHideout3);
		}
		if (mHideout4->getActive())
		{
			addItem(mHideout4);
		}*/
		if (mParent->getActive())
		{
			addItem(mParent);
		}
		if (mSkatmara->getActive())
		{
			addItem(mSkatmara);
		}
		if (mCoin->getActive())
		{
			addItem(mCoin);
		}


	}
}


void Level3::changeScene(int num)
{
	clearScene();
	internalSwap(num);
}


int Level3::getActiveScene()
{
	return mActiveScene;
}


Level3::rectVector Level3::getRects()
{
	return mRects;
}


sf::FloatRect* Level3::createRect(int positionX, int positionY, int sizeX, int sizeY)
{
	sf::FloatRect* floatRect = new sf::FloatRect((float)positionX, (float)positionY, (float)sizeX, (float)sizeY);
	return floatRect;
}

//Check collision between a single rectangle and a point
int Level3::checkCollision(const sf::FloatRect &boundingBox, sf::Vector2f &point)
{
	if (boundingBox.contains(point))
	{
		return 1;
	}
	return 0;
}
//Check collision between a single rectangle and a point
int Level3::checkCollision(sf::FloatRect* &boundingBox, sf::Vector2f &point)
{
	if (boundingBox->contains(point))
	{
		return 1;
	}
	return 0;
}
//Check collision between a vector of rectangles and a point
int Level3::checkCollision(const std::vector<sf::FloatRect*> RectVector, sf::Vector2f &point)
{
	for (std::vector<sf::FloatRect*>::size_type i = 0; i < RectVector.size(); i++)
	{
		if (RectVector[i]->contains(point))
		{
			return 1;
		}
	}
	return 0;
}

//Check collision between two rectangles
int Level3::checkCollision(sf::FloatRect* boundingBox, sf::FloatRect &rect)
{
	if (boundingBox->intersects(rect))
	{
		return 1;
	}
	return 0;
}
//Check collision between a vector of rectangles and a rectangle
int Level3::checkCollision(const std::vector<sf::FloatRect*> RectVector, sf::FloatRect &rect)
{
	for (std::vector<sf::FloatRect*>::size_type i = 0; i < RectVector.size(); i++)
	{
		if (RectVector[i]->intersects(rect))
		{
			return 1;
		}
	}
	return 0;
}



void Level3::eventListen(sf::RenderWindow &window)
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		// get the current mouse position in the window
		mPixelPos = sf::Mouse::getPosition(window);
		// convert it to world coordinates
		mWorldPos = window.mapPixelToCoords(mPixelPos);
		switch (event.type)
		{
			//window closed
		case sf::Event::Closed:
			window.close();
			break;

			//mouse button pressed
		case sf::Event::MouseButtonPressed:
			//if Inventory Mode is enabled, only check for collisions with Items in Inventory
			if (mUI->getState() == UI::INVENTORY)
			{
				mInventory->checkCollision(mInventory->getItems(), mWorldPos, *mUI);

				mInventory->setCraftPos(mInventory->getSelectedItem());

				if (mInventory->craftCheck())
				{
					mInventory->craftItem(mInventory->getCraftSelect1(), mInventory->getCraftSelect2());
				}
			}
			else if (mCursor->getMode() == Cursor::DIALOGUE)
			{
				mDialogueSystem->setState();
			}
			else if (mUI->getState() != UI::INGAME)
			{
				mUI->checkCollision(mWorldPos);
			}
			else if (mCursor->getMode() != Cursor::DISABLED)
			{
				mouseClick(event);
			}
			break;

		case sf::Event::MouseButtonReleased:
			if (mUI->getState() == UI::INVENTORY)
			{
				mInventory->swapCheck();
				mInventory->deSelectCheck();
				mInventory->setCraftPos(mInventory->getSelectedItem());
			}
			else if (mCursor->getMode() != Cursor::DISABLED)
			{
				mouseReleased(event);
			}
			break;

		case sf::Event::KeyPressed:
			if (event.key.code == sf::Keyboard::I)
			{
				if (mUI->getState() == UI::INVENTORY)
				{
					mUI->setState(UI::INGAME);
					mCursor->setMode(Cursor::NORMAL);
				}
				else if (mCursor->getMode() != Cursor::DIALOGUE)
				{
					mUI->setState(UI::INVENTORY);
					mCursor->setMode(Cursor::INVENTORY);
					//mMenuInventorySound.play();
					if (mUI->getActiveAnimation() == "InventoryIconGlow" || mUI->getActiveAnimation() == "InventoryIconGlowOnce")
					{
						mUI->setActiveAnimation("None");
					}
				}
			}
			if (event.key.code == sf::Keyboard::P)
			{
				mPlayer->togglePlayer(); //TODO - Remove this
			}
			if (event.key.code == sf::Keyboard::Escape)
			{
				if (mUI->getState() == UI::EXIT || mUI->getState() == UI::INVENTORY || mUI->getState() == UI::CLUES)
				{
					mUI->setState(UI::INGAME);
					mCursor->setMode(Cursor::NORMAL);
				}
				else if (mCursor->getMode() != Cursor::DIALOGUE)
				{
					mUI->setState(UI::EXIT);
					mCursor->setMode(Cursor::MENU);
				}
			}
			break;
			
		default:
			break;


		}
	}
}


void Level3::mouseClick(sf::Event &event)
{
	std::cout << "Mouse Pressed" << std::endl;
	std::cout << "mouse x: " << event.mouseButton.x << std::endl;
	std::cout << "mouse y: " << event.mouseButton.y << std::endl;

	std::cout << "mapped mouse x: " << mWorldPos.x << std::endl;
	std::cout << "mapped mouse y: " << mWorldPos.y << std::endl;

	sf::Vector2f point(mWorldPos.x, mWorldPos.y);

	mMouseReleased = false;

	//Check if Exit Icon is clicked
	if (checkCollision(mUI->getExitIconRect(), point))
	{
		mCursor->setMode(Cursor::MENU);
		mUI->setState(UI::EXIT);
		if (mUI->getActiveAnimation() == "ExitIconGlow" || mUI->getActiveAnimation() == "ExitIconGlowOnce")
		{
			mUI->setActiveAnimation("None");
		}
		//mMenuMainUISound.play();
	}
	//Check if Inventory Icon is clicked
	else if (checkCollision(mUI->getInventoryIconRect(), point))
	{
		mCursor->setMode(Cursor::INVENTORY);
		mUI->setState(UI::INVENTORY);
		if (mUI->getActiveAnimation() == "InventoryIconGlow" || mUI->getActiveAnimation() == "InventoryIconGlowOnce")
		{
			mUI->setActiveAnimation("None");
		}
		//mMenuHatSound.play();
	}


	//Check if playrect collision
	if (checkCollision(getPlayRects(), point))
	{
		mPlayer->setActiveAnimation("Walk");
		mPlayer->moveToPosition(point.x, point.y);
		mItemInteraction = false;
	}

	//Check Item collision
	mouseClickCheckItemCollision(point);

	//Check Rect Collisions
	mouseClickCheckRectCollision(point);
}

void Level3::mouseReleased(sf::Event & event)
{
	if (mInventory->selectedItem() != NULL
		&& mInventory->selectedItem()->getId() == "Trimmer"
		&& mStick->getRectangle().contains(mWorldPos)
		&& mActiveScene == 0)
	{
		mMouseReleased = true;
		mItemInteraction = true;
		mPlayer->moveToPosition(349, 346);
		mTargetItem = mStick;
		//mInventory->deSelectCheck();
	}
	else if (mInventory->selectedItem() != NULL
		&& mInventory->selectedItem()->getId() == "Trimmer"
		&& mLeash->getRectangle().contains(mWorldPos)
		&& mActiveScene == 0)
	{
		mMouseReleased = true;
		mItemInteraction = true;
		mPlayer->moveToPosition(588, 380);
		mTargetItem = mLeash;
		//mInventory->deSelectCheck();
	}
	else if (mInventory->selectedItem() != NULL
		&& mInventory->selectedItem()->getId() == "Stick"
		&& mDog->getRectangle().contains(mWorldPos)
		&& mActiveScene == 0)
	{
		mMouseReleased = true;
		mItemInteraction = true;
		mPlayer->moveToPosition(666, 416);
		mTargetItem = mDog;
	}
	else if (mInventory->selectedItem() != NULL
		&& mInventory->selectedItem()->getId() == "Flowers"
		&& mFlagpole->getRectangle().contains(mWorldPos)
		&& mActiveScene == 0)
	{
		mMouseReleased = true;
		mItemInteraction = true;
		mPlayer->moveToPosition(1354, 374);
		mTargetItem = mFlagpole;
	}
	else if (mInventory->selectedItem() != NULL
		&& mInventory->selectedItem()->getId() == "Trimmer"
		&& mRippedCloth->getRectangle().contains(mWorldPos)
		&& mActiveScene == 1)
	{
		mMouseReleased = true;
		mItemInteraction = true;
		mPlayer->moveToPosition(386, 543);
		mTargetItem = mRippedCloth;
	}
	else if (mInventory->selectedItem() != NULL
		&& mInventory->selectedItem()->getId() == "Clover"
		&& mJack->getRectangle().contains(mWorldPos)
		&& mActiveScene == 1)
	{
		mMouseReleased = true;
		mItemInteraction = true;
		mPlayer->moveToPosition(1250, 370);
		mTargetItem = mJack;
	}
	else if (mInventory->selectedItem() != NULL
		&& mInventory->selectedItem()->getId() == "Sawdust"
		&& mJack->getRectangle().contains(mWorldPos)
		&& mActiveScene == 1)
	{
		mMouseReleased = true;
		mItemInteraction = true;
		mPlayer->moveToPosition(1250, 370);
		mTargetItem = mJack;
	}
	else if (mInventory->selectedItem() != NULL
		&& mInventory->selectedItem()->getId() == "RippedCloth"
		&& mJack->getRectangle().contains(mWorldPos)
		&& mActiveScene == 1)
	{
		mMouseReleased = true;
		mItemInteraction = true;
		mPlayer->moveToPosition(1250, 370);
		mTargetItem = mJack;
	}
	else if (mInventory->selectedItem() != NULL
		&& mInventory->selectedItem()->getId() == "Featherball"
		&& mJack->getRectangle().contains(mWorldPos)
		&& mActiveScene == 1)
	{
		mMouseReleased = true;
		mItemInteraction = true;
		mPlayer->moveToPosition(1250, 370);
		mTargetItem = mJack;
	}
	else if (mInventory->selectedItem() != NULL
		&& mInventory->selectedItem()->getId() == "Nail"
		&& mJack->getRectangle().contains(mWorldPos)
		&& mActiveScene == 1)
	{
		mMouseReleased = true;
		mItemInteraction = true;
		mPlayer->moveToPosition(1250, 370);
		mTargetItem = mJack;
	}
	else if (mInventory->selectedItem() != NULL
		&& mInventory->selectedItem()->getId() == "Fjun"
		&& mJack->getRectangle().contains(mWorldPos)
		&& mActiveScene == 1)
	{
		mMouseReleased = true;
		mItemInteraction = true;
		mPlayer->moveToPosition(1250, 370);
		mTargetItem = mJack;
	}
	else if (mInventory->selectedItem() != NULL
		&& mInventory->selectedItem()->getId() == "Key"
		&& mJack->getRectangle().contains(mWorldPos)
		&& mActiveScene == 1)
	{
		mMouseReleased = true;
		mItemInteraction = true;
		mPlayer->moveToPosition(1250, 370);
		mTargetItem = mJack;
	}
	else
	{
		mInventory->deSelectCheck();
	}
}



void Level3::update(sf::RenderWindow &window, float deltaTime)
{
	//Only do this if the level needs moving camera
	//mLHandler->getLevel(1) is currently LastLevel, change as necessary
	//Scene 1 is the big, second room in LastLevel, change as necessary
	if (getActiveScene() == 0)
	{
		//520 is the distance the Player has to be from the left side of the level before the camera starts scrolling, change as necessary
		//1000 is the distance the Player has to be from the right side of the level before the camera starts scrolling, change as necessary
		//In this case the camera scrolls while the Player is between 520 and 1000.
		if (mPlayer->getPosition().x > 520 && mPlayer->getPosition().x < 1530)
		{
			//Make camera follow Player position
			moveViewWithPlayer(mPlayer->getPosition().x);
		}
	}

	if (getActiveScene() == 1)
	{
		if (mPlayer->getPosition().x > 520 && mPlayer->getPosition().x < 1000)
		{
			moveViewWithPlayer(mPlayer->getPosition().x);
		}
	}
	if (getActiveScene() == 2)
	{
		if (mPlayer->getPosition().x > 520 && mPlayer->getPosition().x < 2000)
		{
			moveViewWithPlayer(mPlayer->getPosition().x);
		}
	}

	//Check if Player is in position to change Scene
	if (mPlayer->getRect().intersects(mSceneChangeRect))
	{
		//Toggle Player if the new Scene needs it
		if (mPlayerToggle)
		{
			mPlayer->togglePlayer();
		}
		//Set Player position to the starting position of the new Scene
		mPlayer->setPosition(mSceneChangePlayerPos.x, mSceneChangePlayerPos.y);
		mPlayer->moveToPosition(mSceneChangePlayerPos.x, mSceneChangePlayerPos.y);
		//Change to the new Scene
		changeScene(mNewScene);
	}

	//Check if Item interaction is enabled, which it only is when an Item is clicked
	if (mItemInteraction)
	{
		//Check if any part of the Player intersects with the Item
		if (mPlayer->getIsOnPosition())
		{
			//Check if Item has already been looked at
			if (!mTargetItem->isLookedAt())
			{
				lookAtTargetItem();
			}
			//Check if Item can be picked up
			if (mTargetItem->getPickupable())
			{
				pickupTargetItem();
			}
			//Check if Item can be interacted with
			if (mTargetItem->getInteractable())
			{
				interactTargetItem();
			}
			//Disable Item interaction when done
			mItemInteraction = false;
		}
	}

	if (!mPlayer->getIsOnPosition())
	{
		//mPlayer->navigate(mItems, deltaTime);
		mPlayer->setActiveAnimation("Walk");
	}

	//Animation updates
	mDog->update(deltaTime);
	mLady->update(deltaTime);

	//Inventory
	mInventory->update(window);

	if (mUI->getState() == UI::INVENTORY)
	{
		if (mInventory->getSelectedItem() != -1)
		{
			if (!mInventory->checkDistance(mWorldPos))
			{
				mUI->setState(UI::INGAME);
			}
		}
	}

	updateTargetItem(deltaTime);

	mCursor->setPosition(sf::Vector2f(mWorldPos));
	mCursor->update(window);

	if (mCursor->getMode() != Cursor::DIALOGUE && mCursor->getMode() != Cursor::INVENTORY && mCursor->getMode() != Cursor::DISABLED && mCursor->getMode() != Cursor::MENU)
	{
		mouseHover();
	}

	//Make sure UI is in correct place at all times
	mUI->setUIPosition(mView.getCenter());
	mInventory->setGridPosition(mView.getCenter());
}

void Level3::mouseHover()
{
	mCursor->setMode(Cursor::NORMAL);

	//Check if playrect collision
	if (checkCollision(getPlayRects(), mCursor->getRect()))
	{
		mCursor->setMode(Cursor::NORMAL); // TODO - Add walk cursor maybe?
	}

	//Check Item collision
	//Loop through all Items in active level
	for (Level::ItemVector::size_type i = 0; i < getItems().size(); i++)
	{
		//Check if mouse collided with Item
		if (getItems()[i]->getRectangle().intersects(mCursor->getRect()))
		{
			//Check if Item is Active
			if (getItems()[i]->getActive())
			{
				if (!getItems()[i]->isLookedAt())
				{
					mCursor->setMode(Cursor::EYE);
				}
				//Check if Item can be picked up
				else if (getItems()[i]->getPickupable())
				{
					mCursor->setMode(Cursor::OPENHAND);
				}
				//Check if Item can be interacted with
				else if (getItems()[i]->getInteractable())
				{
					//Check if Item has already been interacted with
					if (!getItems()[i]->isInteracted())
					{
						mCursor->setMode(Cursor::OPENHAND);
					}
				}
			}
		}
	}

	//Check Rect Collisions
	for (Level::rectVector::size_type i = 0; i < getRects().size(); i++)
	{
		if (checkCollision(getRects()[i], mCursor->getRect()))
		{
			//// i == 10 is stairs in scene 1
			//if (i == 10)
			//{
			//	if (mActiveScene == 0)
			//	{
			//		mCursor->setMode(Cursor::NORMAL);
			//	}
			//	else
			//	{
			//		mCursor->setMode(Cursor::EYE);
			//	}
			//}

			//// i == 5 is stairs in scene 2
			//else if (i == 5)
			//{
			//	if (mActiveScene == 1)
			//	{
			//		mCursor->setMode(Cursor::NORMAL);
			//	}
			//	else
			//	{
			//		mCursor->setMode(Cursor::EYE);
			//	}
			//}

			//// i == 0 is door in scene 2
			//else if (i == 0)
			//{
			//	if (mActiveScene == 1)
			//	{
			//		mCursor->setMode(Cursor::NORMAL);
			//	}
			//}

			////i == 2 is door in scene 3
			//else if (i == 2)
			//{
			//	if (mActiveScene == 2)
			//	{
			//		mCursor->setMode(Cursor::NORMAL);
			//	}
			//	else
			//	{
			//		mCursor->setMode(Cursor::NORMAL);
			//	}
			//}

			//else
			//{
				mCursor->setMode(Cursor::EYE);
			//}
		}
	}

	if (mInventory->selectedItem() != NULL)
	{
		mCursor->setMode(Cursor::CLOSEDHAND);
	}
}

bool Level3::isLevelComplete()
{
	return mLevelComplete;
}

void Level3::updateTargetItem(float deltaTime)
{
	//Only update currently "Targeted" Item to avoid having to loop through and update all Items
	if (mTargetItem != NULL)
	{
		mTargetItem->update(deltaTime);
		//Put everything back to normal after the "Pushing cutscene"
		if (mTargetItem->getIsOnPosition())
		{
			if (mDogRunning)
			{
				mDogRunning = false;
				mCursor->setMode(Cursor::NORMAL);
				mTargetItem->toggleActive();
			}
		}
	}
}

void Level3::lookAtTargetItem()
{
	mTargetItem->toggleIsLookedAt(); //Fixa dialoger i funktion
	mItemInteraction = false;
}

void Level3::pickupTargetItem()
{
	//Make Item inactive when it is picked up
	mTargetItem->toggleActive();
	if (mTargetItem->getId() == "Trimmer")
	{
		mInventory->addItem(mTargetItem);
		mTargetItem->changeTexture(handler, "TrimmerIcon.png");
		std::cout << "Plockade upp häcksax!";
	}

	if (mTargetItem->getId() == "Flowers")
	{
		mInventory->addItem(mTargetItem);
		std::cout << "Plockade upp blomma!";
	}

	if (mTargetItem->getId() == "Stick")
	{
		if (mMouseReleased)
		{
			mInventory->addItem(mTargetItem);
			mTargetItem->changeTexture(handler, "StickINV.png");
			std::cout << "Plockade upp Pinne!";
			mInventory->deSelectCheck();
		}
		else
		{
			mTargetItem->toggleActive();
			mTargetItem->toggleInteractable();
		}

	}

	if (mTargetItem->getId() == "Clover")
	{
		if (mItemPicked == false)
		{
			mInventory->addItem(mTargetItem);
			mItemPicked = true;
			std::cout << "Plockade upp klöver!";
		}
		else
		{
			mTargetItem->toggleActive();
		}
	}

	if (mTargetItem->getId() == "Sawdust")
	{
		if (mItemPicked == false)
		{
			mInventory->addItem(mTargetItem);
			mItemPicked = true;
			std::cout << "Plockade upp sågspån!";
		}
		else
		{
			mTargetItem->toggleActive();
		}
	}

	if (mTargetItem->getId() == "Fjun")
	{
		if (mItemPicked == false)
		{
			mInventory->addItem(mTargetItem);
			mItemPicked = true;
			std::cout << "Plockade upp fjun!";
		}
		else
		{
			mTargetItem->toggleActive();
		}
	}

	if (mTargetItem->getId() == "Featherball")
	{
		if (mItemPicked == false)
		{
			mInventory->addItem(mTargetItem);
			mItemPicked = true;
			std::cout << "Plockade upp fjäderboll!";
		}
		else
		{
			mTargetItem->toggleActive();
		}
	}

	if (mTargetItem->getId() == "Nail")
	{
		if (mItemPicked == false)
		{
			mInventory->addItem(mTargetItem);
			mItemPicked = true;
			std::cout << "Plockade upp spik!";
		}
		else
		{
			mTargetItem->toggleActive();
		}
	}

	if (mTargetItem->getId() == "RippedCloth")
	{
		if (mMouseReleased)
		{
			if (mItemPicked == false)
			{
				mInventory->addItem(mTargetItem);
				mItemPicked = true;
				std::cout << "Plockade upp tygbit!";
				mInventory->deSelectCheck();
			}
			else
			{
				mTargetItem->toggleActive();
			}
		}
		else
		{
			mTargetItem->toggleActive();
		}
	}

}

void Level3::interactTargetItem()
{
	//Check if Item has already been interacted with
	if (!mTargetItem->isInteracted())
	{
		mTargetItem->toggleInteractable();

		//Koppel
		if (mTargetItem->getId() == "Leash")
		{
			if (mMouseReleased)
			{
				mTargetItem->changeTexture(handler, "transparent.png"); //Add correct texture!
				mUnleashed = true;
				std::cout << "Klipper kopplet!";
				mInventory->deSelectCheck();
			}
			else
			{
				mTargetItem->toggleInteractable();
			}
		}

		//Hund
		if (mTargetItem->getId() == "Dog")
		{
			if (mMouseReleased && mUnleashed == true)
			{
				mInventory->removeItem(mInventory->getSelectedItem());

				mTargetItem->moveToPosition(1272, 500);
				std::cout << "Kastade pinnen!";
				mCursor->setMode(Cursor::DISABLED);
				mTargetItem->setActiveAnimation("Dog");
				mDogRunning = true;

				mPlayRects.push_back(createRect(683, 360, 673, 160));
			}
			else
			{
				mTargetItem->toggleInteractable();
			}


		}

		//Flaggstång
		if (mTargetItem->getId() == "Flagpole")
		{
			if (mMouseReleased)
			{
				mInventory->removeItem(mInventory->getSelectedItem());
				mSingleFlower->toggleActive();
			}
			else
			{

				mTargetItem->toggleInteractable();
			}

		}

		//Knippe blommor
		if (mTargetItem->getId() == "Singleflower")
		{
			mTargetItem->moveToPosition(1390, 121);
			mPlayRects.push_back(createRect(1356, 360, 500, 160));
		}

		//KNEKTEN 
		if (mTargetItem->getId() == "Jack")
		{
			if (mMouseReleased)
			{
				if (mInventory->selectedItem()->getId() == "Key" || mInventory->selectedItem()->getId() == "Clover" || mInventory->selectedItem()->getId() == "Nail" || mInventory->selectedItem()->getId() == "Featherball" || mInventory->selectedItem()->getId() == "Fjun" || mInventory->selectedItem()->getId() == "Sawdust" || mInventory->selectedItem()->getId() == "RippedCloth")
				{
					if (mInventory->selectedItem()->getId() == "Key")
					{
						mKey->toggleActive();
					}
					mInventory->removeItem(mInventory->getSelectedItem());
					mItemPicked = false;
					mTargetItem->toggleInteractable();

					if (!mKey->getActive() && !mClover->getActive() && !mNail->getActive() && !mFeatherball->getActive() && !mFjun->getActive() && !mSawdust->getActive() && !mRippedCloth->getActive())
					{
						mMagicWorldOpen = true;
					}

					//OBSOBS vad mer ska hända?
				}
				else
				{
					mTargetItem->toggleInteractable();
				}
			}
			else
			{
				mTargetItem->toggleInteractable();
			}
		}

		//Pond
		if (mTargetItem->getId() == "Pond")
		{
			if (mInventory->selectedItem() != NULL && mInventory->selectedItem()->getId() == "FishingRodMagnet")
			{
				std::cout << "Fiskade mynt!";
				mInventory->addItem(mCoin);
			}
			else
			{
				mTargetItem->toggleInteractable();
			}
		}

		//Statue
		if (mTargetItem->getId() == "Statue")
		{
			//Play sound and blink

			mTargetItem->toggleInteractable();

		}

		//Blue Stone
		if (mTargetItem->getId() == "BlueStone")
		{
			//Play sound and blink

			mTargetItem->toggleInteractable();
		}

		//Red Stone
		if (mTargetItem->getId() == "RedStone")
		{
			//Play sound and blink

			mTargetItem->toggleInteractable();
		}

		//Green Stone
		if (mTargetItem->getId() == "GreenStone")
		{
			//Play sound and blink

			mTargetItem->toggleInteractable();
		}

		//Yellow Stone
		if (mTargetItem->getId() == "YellowStone")
		{
			//Play sound and blink

			mTargetItem->toggleInteractable();
		}

		//Parent
		if (mTargetItem->getId() == "Parent")
		{
			if (mSkatmaraTalked == true)
			{
				//Talk about lost child
				mParentTalked = true;
				mTargetItem->toggleInteractable();

				addItem(mHideout1);
				addItem(mHideout2);
				addItem(mHideout3);
				addItem(mHideout4);



			}
			else
			{
				//Welcome to Magic World
				mTargetItem->toggleInteractable();
			}
		}

		//Hideout 1
		if (mTargetItem->getId() == "Hideout 1")
		{
			if (mHide2Looked == true && mHide3Looked == true && mHide4Looked == true)
			{
				//Kid found!
			}
			else
			{
				mHide1Looked = true;
			}
		}

		//Hideout 2
		if (mTargetItem->getId() == "Hideout 2")
		{
			if (mHide1Looked == true && mHide3Looked == true && mHide4Looked == true)
			{
				//Kid found!
			}
			else
			{
				mHide2Looked = true;
			}
		}

		//Hideout 3
		if (mTargetItem->getId() == "Hideout 3")
		{
			if (mHide1Looked == true && mHide2Looked == true && mHide4Looked == true)
			{
				//Kid found!
			}
			else
			{
				mHide3Looked = true;
			}
		}

		//Hideout 4
		if (mTargetItem->getId() == "Hideout 4")
		{
			if (mHide1Looked == true && mHide2Looked == true && mHide3Looked == true)
			{
				//Kid found!
			}
			else
			{
				mHide4Looked = true;
			}
		}

		//Skatmara
		if (mTargetItem->getId() == "Skatmara")
		{

			mSkatmaraTalked = true;
			std::cout << "mSkatmaraTalked = true";

			if (mInventory->selectedItem() != NULL && mInventory->selectedItem()->getId() == "Coin")
			{

				std::cout << "Ger bort mynt!";
				mInventory->removeItem(mInventory->getSelectedItem());
				mCoinGiven = true;

				if (mStoneGiven == true && mPinGiven == true)
				{
					//Play dialog
				}
			}

			else if (mInventory->selectedItem() != NULL && mInventory->selectedItem()->getId() == "BlueStone")
			{
				std::cout << "Ger bort sten";
				mInventory->removeItem(mInventory->getSelectedItem());
				mStoneGiven = true;

				if (mCoinGiven == true && mPinGiven == true)
				{
					//Play dialog
				}
			}

			else if (mInventory->selectedItem() != NULL && mInventory->selectedItem()->getId() == "Pin")
			{
				std::cout << "Ger bort brosch";
				mInventory->removeItem(mInventory->getSelectedItem());
				mPinGiven = true;

				if (mCoinGiven == true && mStoneGiven == true)
				{
					//Play dialog
				}
			}
			else
			{
				mTargetItem->toggleInteractable();
			}


		}

		//Next Item

	}
}

void Level3::mouseClickCheckItemCollision(sf::Vector2f point)
{
	//Loop through all Items in active level
	for (Level::ItemVector::size_type i = 0; i < getItems().size(); i++)
	{
		//Check if mouse collided with Item
		if (checkCollision(getItems()[i]->getRectangle(), point))
		{
			//Check if Item is Active
			if (getItems()[i]->getActive())
			{
				if (getItems()[i]->getId() == "Trimmer")
				{
					//Move Player to the closest point that is still inside the playrect
					mPlayer->moveToPosition(310, 375);
					//Set the Item as "Target Item"
					mTargetItem = getItems()[i];
					//Enable Item interaction
					mItemInteraction = true;
					std::cout << "Klickade på häcksax!";

				}

				if (getItems()[i]->getId() == "Stick")
				{
					//Move Player to the closest point that is still inside the playrect
					mPlayer->moveToPosition(349, 346);
					//Set the Item as "Target Item"
					mTargetItem = getItems()[i];
					//Enable Item interaction
					mItemInteraction = true;
					std::cout << "Klickade på häcksax!";

				}

				if (getItems()[i]->getId() == "Leash")
				{
					//Move Player to the closest point that is still inside the playrect
					mPlayer->moveToPosition(588, 380);
					//Set the Item as "Target Item"
					mTargetItem = getItems()[i];
					//Enable Item interaction
					mItemInteraction = true;
					std::cout << "Klickade på koppel!";

				}

				if (getItems()[i]->getId() == "Dog")
				{
					//Move Player to the closest point that is still inside the playrect
					mPlayer->moveToPosition(666, 416);
					//Set the Item as "Target Item"
					mTargetItem = getItems()[i];
					//Enable Item interaction
					mItemInteraction = true;
					std::cout << "Klickade på hunden!";

				}

				if (getItems()[i]->getId() == "Flowers")
				{

					//Move Player to the closest point that is still inside the playrect
					mPlayer->moveToPosition(466, 522);
					//Set the Item as "Target Item"
					mTargetItem = getItems()[i];
					//Enable Item interaction
					mItemInteraction = true;
					std::cout << "Klickade på blommor!";

				}

				if (getItems()[i]->getId() == "Flagpole")
				{
					//Move Player to the closest point that is still inside the playrect
					mPlayer->moveToPosition(1354, 374);
					//Set the Item as "Target Item"
					mTargetItem = getItems()[i];
					//Enable Item interaction
					mItemInteraction = true;
					std::cout << "Klickade på flaggstång!";

				}

				if (getItems()[i]->getId() == "Singleflower")
				{
					//Move Player to the closest point that is still inside the playrect
					//mPlayer->moveToPosition(1354, 374);
					//Set the Item as "Target Item"
					mTargetItem = getItems()[i];
					//Enable Item interaction
					mItemInteraction = true;
					std::cout << "Klickade på blomma!";

				}

				if (getItems()[i]->getId() == "Clover")
				{
					//Move Player to the closest point that is still inside the playrect
					mPlayer->moveToPosition(338, 316);
					//Set the Item as "Target Item"
					mTargetItem = getItems()[i];
					//Enable Item interaction
					mItemInteraction = true;
					std::cout << "Klickade på klöver!";

				}

				if (getItems()[i]->getId() == "Sawdust")
				{
					//Move Player to the closest point that is still inside the playrect
					mPlayer->moveToPosition(819, 301);
					//Set the Item as "Target Item"
					mTargetItem = getItems()[i];
					//Enable Item interaction
					mItemInteraction = true;
					std::cout << "Klickade på sågspån!";

				}

				if (getItems()[i]->getId() == "Fjun")
				{
					//Move Player to the closest point that is still inside the playrect
					mPlayer->moveToPosition(1200, 370);
					//Set the Item as "Target Item"
					mTargetItem = getItems()[i];
					//Enable Item interaction
					mItemInteraction = true;
					std::cout << "Klickade på fjun!";

				}

				if (getItems()[i]->getId() == "Nail")
				{
					//Move Player to the closest point that is still inside the playrect
					mPlayer->moveToPosition(424, 300);
					//Set the Item as "Target Item"
					mTargetItem = getItems()[i];
					//Enable Item interaction
					mItemInteraction = true;
					std::cout << "Klickade på spik!";

				}

				if (getItems()[i]->getId() == "Featherball")
				{
					//Move Player to the closest point that is still inside the playrect
					mPlayer->moveToPosition(463, 415);
					//Set the Item as "Target Item"
					mTargetItem = getItems()[i];
					//Enable Item interaction
					mItemInteraction = true;
					std::cout << "Klickade på fjäderboll!";
				}

				if (getItems()[i]->getId() == "Jack")
				{
					//Move Player to the closest point that is still inside the playrect
					mPlayer->moveToPosition(1250, 370);
					//Set the Item as "Target Item"
					mTargetItem = getItems()[i];
					//Enable Item interaction
					mItemInteraction = true;
					std::cout << "Klickade på knekt!";

				}

				if (getItems()[i]->getId() == "RippedCloth")
				{
					//Move Player to the closest point that is still inside the playrect
					mPlayer->moveToPosition(386, 543);
					//Set the Item as "Target Item"
					mTargetItem = getItems()[i];
					//Enable Item interaction
					mItemInteraction = true;
					std::cout << "Klickade på knekt!";

				}

				if (getItems()[i]->getId() == "Pond")
				{
					//Move Player to the closest point that is still inside the playrect
					mPlayer->moveToPosition(305, 416);
					//Set the Item as "Target Item"
					mTargetItem = getItems()[i];
					//Enable Item interaction
					mItemInteraction = true;
					std::cout << "Klickade på damm!";

				}

				if (getItems()[i]->getId() == "Statue")
				{
					//Move Player to the closest point that is still inside the playrect
					mPlayer->moveToPosition(696, 296);
					//Set the Item as "Target Item"
					mTargetItem = getItems()[i];
					//Enable Item interaction
					mItemInteraction = true;
					std::cout << "Klickade på staty!";

				}

				if (getItems()[i]->getId() == "BlueStone")
				{
					//Move Player to the closest point that is still inside the playrect
					mPlayer->moveToPosition(696, 296);
					//Set the Item as "Target Item"
					mTargetItem = getItems()[i];
					//Enable Item interaction
					mItemInteraction = true;
					std::cout << "Klickade på blå sten!";

				}

				if (getItems()[i]->getId() == "RedStone")
				{
					//Move Player to the closest point that is still inside the playrect
					mPlayer->moveToPosition(696, 296);
					//Set the Item as "Target Item"
					mTargetItem = getItems()[i];
					//Enable Item interaction
					mItemInteraction = true;
					std::cout << "Klickade på röd sten!";

				}

				if (getItems()[i]->getId() == "GreenStone")
				{
					//Move Player to the closest point that is still inside the playrect
					mPlayer->moveToPosition(696, 296);
					//Set the Item as "Target Item"
					mTargetItem = getItems()[i];
					//Enable Item interaction
					mItemInteraction = true;
					std::cout << "Klickade på grön sten!";

				}

				if (getItems()[i]->getId() == "YellowStone")
				{
					//Move Player to the closest point that is still inside the playrect
					mPlayer->moveToPosition(696, 296);
					//Set the Item as "Target Item"
					mTargetItem = getItems()[i];
					//Enable Item interaction
					mItemInteraction = true;
					std::cout << "Klickade på gul sten!";

				}

				if (getItems()[i]->getId() == "Hideout 1")
				{
					//Move Player to the closest point that is still inside the playrect
					mPlayer->moveToPosition(1164, 381);
					//Set the Item as "Target Item"
					mTargetItem = getItems()[i];
					//Enable Item interaction
					mItemInteraction = true;
					std::cout << "Klickade på gömställe 1!";

				}

				if (getItems()[i]->getId() == "Hideout 2")
				{
					//Move Player to the closest point that is still inside the playrect
					mPlayer->moveToPosition(1719, 231);
					//Set the Item as "Target Item"
					mTargetItem = getItems()[i];
					//Enable Item interaction
					mItemInteraction = true;
					std::cout << "Klickade på gömställe 2!";

				}

				if (getItems()[i]->getId() == "Hideout 3")
				{
					//Move Player to the closest point that is still inside the playrect
					mPlayer->moveToPosition(1751, 338);
					//Set the Item as "Target Item"
					mTargetItem = getItems()[i];
					//Enable Item interaction
					mItemInteraction = true;
					std::cout << "Klickade på gömställe 3!";

				}

				if (getItems()[i]->getId() == "Hideout 4")
				{
					//Move Player to the closest point that is still inside the playrect
					mPlayer->moveToPosition(2158, 325);
					//Set the Item as "Target Item"
					mTargetItem = getItems()[i];
					//Enable Item interaction
					mItemInteraction = true;
					std::cout << "Klickade på gömställe 4!";

				}

				if (getItems()[i]->getId() == "Parent")
				{
					//Move Player to the closest point that is still inside the playrect
					mPlayer->moveToPosition(1442, 427);
					//Set the Item as "Target Item"
					mTargetItem = getItems()[i];
					//Enable Item interaction
					mItemInteraction = true;
					std::cout << "Klickade på förälder!";

				}

				if (getItems()[i]->getId() == "Skatmara")
				{
					//Move Player to the closest point that is still inside the playrect
					mPlayer->moveToPosition(2300, 345);
					//Set the Item as "Target Item"
					mTargetItem = getItems()[i];
					//Enable Item interaction
					mItemInteraction = true;
					std::cout << "Klickade på Skatmara!";
				}
			}
		}
	}
}

void Level3::mouseClickCheckRectCollision(sf::Vector2f point)
{
	for (Level::rectVector::size_type i = 0; i < getRects().size(); i++)
	{
		if (checkCollision(getRects()[i], point))
		{
			// i == 0 Bees, Door to garden, 

			if (i == 0)
			{
				if (getActiveScene() == 0)
				{
					std::cout << "Bikupa! Bzzz";

				}
				else if (getActiveScene() == 1)
				{
					std::cout << "Door to scene 1!";
					//Make Player get into position for Scene change
					mPlayer->moveToPosition(70, 370);
					//Set Collision Rect to Scene change position
					mSceneChangeRect = sf::FloatRect(sf::Vector2f(70, 370), sf::Vector2f(10, 10));
					//Set if Player should toggle on Scene Change
					mPlayerToggle = true;
					//Set starting position of Player in new Scene           FIXA!!!
					mSceneChangePlayerPos = sf::Vector2f(950, 480);
					//Set which Scene will be the new Scene
					mNewScene = 0;
					mLastScene = 1;
				}
				else
				{
					std::cout << "Refrigerator!";
					mPlayer->moveToPosition(870, 349);
				}
			}

			// Door shed, magic world
			if (i == 1)
			{
				if (getActiveScene() == 0)
				{
					std::cout << "Dörr!";                  //Detta ska vara en annan rektangel sedan!!! OBS

														   //Make Player get into position for Scene change
					mPlayer->moveToPosition(1973, 370);
					//Set Collision Rect to Scene change position
					mSceneChangeRect = sf::FloatRect(sf::Vector2f(1973, 370), sf::Vector2f(10, 10));
					//Set if Player should toggle on Scene Change
					mPlayerToggle = false;
					//Set starting position of Player in new Scene           
					mSceneChangePlayerPos = sf::Vector2f(148, 276);
					//Set which Scene will be the new Scene
					mNewScene = 1;
					mLastScene = 0;
				}
				else if (getActiveScene() == 1)
				{
					if (mMagicWorldOpen)
					{
						std::cout << "Magic World!";

						//Make Player get into position for Scene change
						mPlayer->moveToPosition(1406, 362);
						//Set Collision Rect to Scene change position
						mSceneChangeRect = sf::FloatRect(sf::Vector2f(1406, 362), sf::Vector2f(10, 10));
						//Set if Player should toggle on Scene Change
						mPlayerToggle = false;
						//Set starting position of Player in new Scene           
						mSceneChangePlayerPos = sf::Vector2f(444, 291);
						//Set which Scene will be the new Scene
						mNewScene = 2;
						mLastScene = 1;
					}
					else
					{

					}
				}
			}


			//Rocket
			if (i == 2)
			{
				if (getActiveScene() == 1)
				{

				}
			}

			//Brush
			if (i == 3)
			{
				if (getActiveScene() == 1)
				{

				}
			}
		}
	}
}

UI* Level3::getUI()
{
	return mUI;
	//TODO - add ui stuff here
}