#include "LastLevel.h"

LastLevel::LastLevel(ResourceHandler &handler) :
mRects(),
mPlayRects(),
mIsActive(false),
handler(handler),
mLevelComplete(false),
mPlutoHanged(false),
mVenusHanged(false),
mEarthHanged(false),
mSaturnHanged(false),
mMarsHanged(false),
mMouseReleased(false),
mLookedAtBooks(false),
mLookedAtMask(false),
mLookedAtCrotchRocket(false),
mLookedAtFridge(false),
mLookedAtTap(false),
mLookedAtJewelryBox(false)
{
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
	
	music.play();
}


void LastLevel::playAmbience()
{
	mAmbientSound.play();
}


void LastLevel::drawBackground(sf::RenderWindow &window)
{
	window.setView(mView);
	if (mActiveScene == 0)
	{
		mView.setCenter(512, 288);
		window.draw(background);
		window.draw(playground);

	}

	else if (mActiveScene == 1)
	{
		
		window.draw(background2);
		window.draw(playground2);
	
		
	}

	else if (mActiveScene == 2)
	{
		mView.setCenter(512, 288);
		window.draw(background3);
		window.draw(playground3);
	}
	/*window.draw(rectangle);
	window.draw(rectangle2);
	window.draw(rectangle3);
	window.draw(rectangle4);
	window.draw(rectangle5);
	window.draw(rectangle6);
	window.draw(rectangle7);
	window.draw(rectangle8);
	window.draw(rectangle9);*/
	drawItems(mItems, window);
}

void LastLevel::drawForeground(sf::RenderWindow &window)
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

void LastLevel::drawUI(sf::RenderWindow &window)
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
		if (mActiveScene == 1) // && mInventory->selectedItem()->getId() == "Needle"
		{
			window.draw(mGramophoneGlow);
		}
		if (mActiveScene == 2) // && mInventory->selectedItem()->getId() == "Pearl"
		{
			window.draw(mTapGlow);
		}
		if (mActiveScene == 2) // && mInventory->selectedItem()->getId() == "Fish"
		{
			window.draw(mFoodbowlGlow);
		}
	}
}


void LastLevel::drawItems(ItemVector items, sf::RenderWindow &window)
{
	for (ItemVector::size_type i = 0; i < mItems.size(); i++)
	{
		if (mItems[i]->getActive())
		{
			mItems[i]->draw(window);

		}
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


void LastLevel::toggleActive(ResourceHandler &handler, sf::RenderWindow &window, UI *ui)
{
	if (!mIsActive)
	{
		handler.loadLastLevel(window);

		//Default bool values
		mLevelComplete = false;
		mPlutoHanged = false;
		mVenusHanged = false;
		mEarthHanged = false;
		mSaturnHanged = false;
		mMarsHanged = false;
		mMouseReleased = false;
		mLookedAtBooks = false;
		mLookedAtMask = false;
		mLookedAtCrotchRocket = false;
		mLookedAtFridge = false;
		mLookedAtTap = false;
		mLookedAtJewelryBox = false;

		//Background Texture scene 1
		background.setSize(sf::Vector2f(1024, 576));
		background.setTexture(handler.getTexture("ARBETSRUMbakgrund.png"));

		//Playground Texture scene 1
		playground.setSize(sf::Vector2f(1024, 576));
		playground.setTexture(handler.getTexture("ARBETSRUMmellangrund.png"));

		//Foreground Texture scene 1
		foreground.setSize(sf::Vector2f(1024, 576));
		foreground.setTexture(handler.getTexture("ARBETSRUMförgrund.png"));

		//Background Texture scene 2
		background2.setSize(sf::Vector2f(1536, 576));
		background2.setTexture(handler.getTexture("VARDAGSRUMbakgrund.png"));

		//Playground Texture scene 2
		playground2.setSize(sf::Vector2f(1536, 576));
		playground2.setTexture(handler.getTexture("VARDAGSRUMmellangrund.png"));

		//Foreground Texture scene 2
		foreground2.setSize(sf::Vector2f(1536, 576));
		foreground2.setTexture(handler.getTexture("VARDAGSRUMförgrund.png"));


		//Background Texture scene 3
		background3.setSize(sf::Vector2f(1024, 576));
		background3.setTexture(handler.getTexture("KÖKbakgrund.png"));

		//Playground Texture scene 3
		playground3.setSize(sf::Vector2f(1024, 576));
		playground3.setTexture(handler.getTexture("KÖKmellangrund.png"));

		//Foreground Texture scene 3
		foreground3.setSize(sf::Vector2f(1024, 576));
		foreground3.setTexture(handler.getTexture("KÖKförgrund.png"));

		//Add Music
		music.openFromFile(handler.getMusic("LastLevelMusic.ogg"));
		music.setLoop(true);
		music.setVolume(80);
		music.play();

		//Add Sounds
		mFishHitFloorSound.setBuffer(*handler.getSound("Fish_Hit_Floor.ogg"));
		mCatHissingSound.setBuffer(*handler.getSound("Cat_Hissing.ogg"));
		mCatSound.setBuffer(*handler.getSound("Cat.ogg"));
		mRegularItemSound.setBuffer(*handler.getSound("Regular_Item_Pickup.ogg"));
		mCriticalItemSound.setBuffer(*handler.getSound("Critical_Item.ogg"));
		mPlanetPuzzleSound.setBuffer(*handler.getSound("Planet_Puzzle.ogg"));
		mGramophoneSound.setBuffer(*handler.getSound("Gramophone.ogg"));
		mRunningWaterSound.setBuffer(*handler.getSound("Running_Water.ogg"));
		mScrewGlobeSound.setBuffer(*handler.getSound("Screw_Globe.ogg"));
		mJewelryBoxSound.setBuffer(*handler.getSound("Jewelry_Box.ogg"));
		mMenuInventorySound.setBuffer(*handler.getSound("Menu_Inventory.ogg"));
		mMenuMainUISound.setBuffer(*handler.getSound("Menu_MainUI.ogg"));
		mMenuHatSound.setBuffer(*handler.getSound("Menu_Hat.ogg"));

		//Add HelpRect
		rectangle.setPosition(sf::Vector2f(285, 0));
		rectangle.setSize(sf::Vector2f(25, 90));
		rectangle2.setPosition(sf::Vector2f(320, 0));
		rectangle2.setSize(sf::Vector2f(40, 100));
		rectangle3.setPosition(sf::Vector2f(375, 0));
		rectangle3.setSize(sf::Vector2f(40, 100));
		rectangle4.setPosition(sf::Vector2f(450, 0));
		rectangle4.setSize(sf::Vector2f(23, 70));
		rectangle5.setPosition(sf::Vector2f(495, 0));
		rectangle5.setSize(sf::Vector2f(70, 100));
		rectangle6.setPosition(sf::Vector2f(595, 0));
		rectangle6.setSize(sf::Vector2f(40, 85));
		rectangle7.setPosition(sf::Vector2f(666, 0));
		rectangle7.setSize(sf::Vector2f(33, 90));
		rectangle8.setPosition(sf::Vector2f(723, 0));
		rectangle8.setSize(sf::Vector2f(28, 85));
		rectangle9.setPosition(sf::Vector2f(775, 0));
		rectangle9.setSize(sf::Vector2f(25, 60));
		rectangle9.setTexture(handler.getTexture("LastLevel_ItemTest1.png"));


		//Add items
		mScrewDevice = new Item(handler, sf::Vector2f(0, 0), "Screwdevice");
		mMagicClam = new Item(handler, sf::Vector2f(0, 0), "Magic Clam");
		mHoolaHoop = new Item(handler, sf::Vector2f(0, 0), "Hoola Hoop");
		mBeigeBall = new Item(handler, sf::Vector2f(0, 0), "Beige Ball");
		mPearl = new Item(handler, sf::Vector2f(0, 0), "Pearl");

		mPutte = new Item(handler, sf::Vector2f(308, 316), "Putte");
		mKids = new Item(handler, sf::Vector2f(271, 335), "Kids");
		mDollhouse = new Item(handler, sf::Vector2f(194, 226), "Dollhouse");

		mNeedle = new Item(handler, sf::Vector2f(271, 255), "Needle");
		mEarth = new Item(handler, sf::Vector2f(286, 122), "Earth");
		mFish = new Item(handler, sf::Vector2f(830, 30), "Fish");
		mGramophone = new Item(handler, sf::Vector2f(437, 108), "Gramophone");

		mFruitbowl = new Item(handler, sf::Vector2f(673, 195), "Fruitbowl");
		mCat = new Item(handler, sf::Vector2f(236, 276), "Cat");
		mFoodBowl = new Item(handler, sf::Vector2f(705, 385), "Foodbowl");
		mHole = new Item(handler, sf::Vector2f(180, 335), "Hole");

		mSaturn = new Item(handler, sf::Vector2f(606, 44), "Saturn");
		mRedApple = new Item(handler, sf::Vector2f(454, 50), "Red Apple");
		mVenus = new Item(handler, sf::Vector2f(330, 56), "Venus");

		//Item Glow
		mGramophoneGlow.setTexture(*handler.getTexture("GramophoneGlow.png"));
		mGramophoneGlow.setPosition(395, 75);
		mGramophoneGlow.setScale(0.55f, 0.55f);
		mTapGlow.setTexture(*handler.getTexture("TapGlow.png"));
		mTapGlow.setPosition(340, 155);
		mTapGlow.setScale(0.55f, 0.55f);
		mFoodbowlGlow.setTexture(*handler.getTexture("FoodbowlGlow.png"));
		mFoodbowlGlow.setPosition(690, 368);
		mFoodbowlGlow.setScale(0.5f, 0.5f);

		//View
		mView.setSize(1024, 576);
		mView.setCenter(524, 288);

		//Player
		mPlayer = new Player(handler, sf::Vector2f(400, 580));

		//Inventory
		mInventory = new Inventory(handler);
		mInventory->setCraftableItems(handler, 3);

		//Cursor
		mCursor = new Cursor(handler);

		//Dialogue System
		mDialogueSystem = new DialogueSystem(handler, 2);

		//UI
		mUI = ui;
		mUI->setState(UI::INGAME);

		//Scene 2
		mActiveScene = 1;

		//Walkable Area
		mPlayRects.push_back(createRect(100, 354, 944, 216));
		mPlayRects.push_back(createRect(1044, 440, 476, 132));

		//Door to scene 3
		mRects.push_back(createRect(0, 39, 70, 357));

		//Books
		mRects.push_back(createRect(261, 314, 82, 33));

		//Jewelry Box
		mRects.push_back(createRect(486, 314, 84, 36));

		//Crotch Rocket
		mRects.push_back(createRect(377, 249, 23, 49));

		//Mask
		mRects.push_back(createRect(1158, 2, 70, 168));

		//Stairs to scene 1
		mRects.push_back(createRect(1466, 246, 44, 178));

		//Add items to ItemVector
		addItem(mNeedle);
		addItem(mEarth);
		addItem(mFish);
		addItem(mGramophone);

		//Items Active
		mNeedle->toggleActive();
		mEarth->toggleActive();
		mGramophone->toggleActive();
		mFish->toggleActive();
		mDollhouse->toggleActive();
		mCat->toggleActive();
		mFruitbowl->toggleActive();
		mFoodBowl->toggleActive();
		mHole->toggleActive();
		mPutte->toggleActive();
		mKids->toggleActive();
		

		//Items Lookable scene 1
		mDollhouse->toggleLookable();
		mPutte->toggleLookable();

		//Items interactable scene 1
		mDollhouse->toggleInteractable();
		mPutte->toggleInteractable();

		//Item Lookable scene 2
		mNeedle->toggleLookable();
		mEarth->toggleLookable();
		mFish->toggleLookable();
		mGramophone->toggleLookable();

		//Items Pickupable scene 2
		mNeedle->togglePickupable();
		mEarth->togglePickupable();

		//Items Interactable scene 2
		mGramophone->toggleInteractable();


		//Items Lookable scene 3
		mFruitbowl->toggleLookable();
		mCat->toggleLookable();
		mFoodBowl->toggleLookable();
		mHole->toggleLookable();

		//Items Interactable scene 3
		mFruitbowl->toggleInteractable();
		mFoodBowl->toggleInteractable();
		mHole->toggleInteractable();

		//Items Not Walkable
		mCat->toggleWalkable();
		mFoodBowl->toggleWalkable();
		mDollhouse->toggleWalkable();
		mKids->toggleWalkable();
		mPutte->toggleWalkable();

		mLastScene = 0;

		//Add Screwdevice and Venus to inventory
		mScrewDevice->setScale(0.3f, 0.3f);
		mInventory->addItem(mScrewDevice);
		mInventory->addItem(mVenus);
	}
	else
	{
		mView.setCenter(524, 288);
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
		mRects.push_back(createRect(285, 0, 25, 90));
		mRects.push_back(createRect(320, 0, 40, 100));
		mRects.push_back(createRect(375, 0, 50, 100));
		mRects.push_back(createRect(450, 0, 23, 70));
		mRects.push_back(createRect(495, 0, 70, 100));
		mRects.push_back(createRect(595, 0, 50, 85));
		mRects.push_back(createRect(666, 0, 33, 90));
		mRects.push_back(createRect(723, 0, 28, 85));
		mRects.push_back(createRect(775, 0, 25, 60));
	
		//BalconyDoor
		mRects.push_back(createRect(445, 186, 80, 50));

		//Stairs to scene 2
		mRects.push_back(createRect(0, 70, 108, 350));

		//Add item to vector
		if (mDollhouse->getActive())
		{
			addItem(mDollhouse);
		}

		if (mRedApple->getActive())
		{
			addItem(mRedApple);
		}

		if (mSaturn->getActive())
		{
			addItem(mSaturn);
		}

		if (mPearl->getActive())
		{
			addItem(mPearl);
		}

		if (mEarthPickedUp == true && mEarth->getActive())
		{
			addItem(mEarth);
		}
		
		if (mPutte->getActive() && mDollhouseInteracted == true)
		{
			addItem(mPutte);
		}

		if (mKids->getActive() && mKidsFound == true)
		{
			addItem(mKids);
		}

		if (mSaturn->getActive() && mSaturnHanged == true)
		{
			addItem(mSaturn);
		}

		addItem(mMagicClam);
		addItem(mVenus);
	}

	else if (num == 1)
	{
		if (mLastScene == 0)
		{
			mView.setCenter(1000, 288);
		}
		else if (mLastScene == 2)
		{
			mView.setCenter(524, 288);
		}

		//Scene 2
		mActiveScene = 1;

		//Walkable Area
		mPlayRects.push_back(createRect(100, 354, 944, 216));
		mPlayRects.push_back(createRect(1044, 440, 476, 132));

		//Door to scene 3
		mRects.push_back(createRect(0, 39, 70, 357));

		//Books
		mRects.push_back(createRect(261, 314, 82, 33));

		//Jewelry Box
		mRects.push_back(createRect(486, 314, 84, 36));

		//Crotch Rocket
		mRects.push_back(createRect(377, 249, 23, 49));


		//Mask
		mRects.push_back(createRect(1158, 2, 70, 168));

		//Stairs to scene 1
		mRects.push_back(createRect(1466, 246,44, 178));

		//Add items to ItemVector
		if (mNeedle->getActive())
		{
			addItem(mNeedle);
		}
		if (mEarth->getActive() && mEarthPickedUp == false)
		{
			addItem(mEarth);
		}
		if (mFish->getActive())
		{
			addItem(mFish);
		}
		if (mGramophone->getActive())
		{
			addItem(mGramophone);
		}


		
	
	}
	else if (num == 2)
	{
		//Scene 3
		mActiveScene = 2;

		//Walkable Area
		mPlayRects.push_back(createRect(133, 379,799 , 189));

		//Refrigerator
		mRects.push_back(createRect(789, 105, 126, 269));

		//Tap
		mRects.push_back(createRect(352, 167, 32, 67));

		//Door
		mRects.push_back(createRect(941, 93, 83, 302));

		
		//Add Items to vector
		
		if (mCat->getActive())
		{
			addItem(mCat);
		}
		if (mFruitbowl->getActive())
		{
			addItem(mFruitbowl);
		}
		if (mFoodBowl->getActive())
		{
			addItem(mFoodBowl);
		}
		if (mHole->getActive())
		{
			addItem(mHole);
		}
		addItem(mRedApple);
		addItem(mHoolaHoop);
		addItem(mBeigeBall);
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

//Check collision between a single rectangle and a point
int LastLevel::checkCollision(const sf::FloatRect &boundingBox, sf::Vector2f &point)
{
	if (boundingBox.contains(point))
	{
		return 1;
	}
	return 0;
}
//Check collision between a single rectangle and a point
int LastLevel::checkCollision(sf::FloatRect* &boundingBox, sf::Vector2f &point)
{
	if (boundingBox->contains(point))
	{
		return 1;
	}
	return 0;
}
//Check collision between a vector of rectangles and a point
int LastLevel::checkCollision(const std::vector<sf::FloatRect*> RectVector, sf::Vector2f &point)
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
int LastLevel::checkCollision(sf::FloatRect* boundingBox, sf::FloatRect &rect)
{
	if (boundingBox->intersects(rect))
	{
		return 1;
	}
	return 0;
}
//Check collision between a vector of rectangles and a rectangle
int LastLevel::checkCollision(const std::vector<sf::FloatRect*> RectVector, sf::FloatRect &rect)
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



void LastLevel::eventListen(sf::RenderWindow &window)
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
					mMenuInventorySound.play();
					if (mUI->getActiveAnimation() == "InventoryIconGlow" || mUI->getActiveAnimation() == "InventoryIconGlowOnce")
					{
						mUI->setActiveAnimation("None");
					}
				}
			}
			if (event.key.code == sf::Keyboard::P)
			{
				mPlayer->togglePlayer();
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


void LastLevel::mouseClick(sf::Event &event)
{
	std::cout << "Mouse Pressed" << std::endl;
	std::cout << "mouse x: " << event.mouseButton.x << std::endl;
	std::cout << "mouse y: " << event.mouseButton.y << std::endl;

	std::cout << "mapped mouse x: " << mWorldPos.x << std::endl;
	std::cout << "mapped mouse y: " << mWorldPos.y << std::endl;

	sf::Vector2f point(mWorldPos.x, mWorldPos.y);

	mMouseReleased = false;

	//Check if Inventory Icon is clicked
	if (checkCollision(mUI->getInventoryIconRect(), point))
	{
		mCursor->setMode(Cursor::INVENTORY);
		mUI->setState(UI::INVENTORY);
		if (mUI->getActiveAnimation() == "InventoryIconGlow" || mUI->getActiveAnimation() == "InventoryIconGlowOnce")
		{
			mUI->setActiveAnimation("None");
		}
		mMenuHatSound.play();
	}
	//Check if Clues Icon is clicked
	else if (checkCollision(mUI->getCluesIconRect(), point))
	{
		mCursor->setMode(Cursor::MENU);
		mUI->setState(UI::CLUES);
		if (mUI->getActiveAnimation() == "CluesIconGlow" || mUI->getActiveAnimation() == "CluesIconGlowOnce")
		{
			mUI->setActiveAnimation("None");
		}
		mMenuMainUISound.play();
	}
	//Check if Exit Icon is clicked
	else if (checkCollision(mUI->getExitIconRect(), point))
	{
		mCursor->setMode(Cursor::MENU);
		mUI->setState(UI::EXIT);
		if (mUI->getActiveAnimation() == "ExitIconGlow" || mUI->getActiveAnimation() == "ExitIconGlowOnce")
		{
			mUI->setActiveAnimation("None");
		}
		mMenuMainUISound.play();
	}
	//Check if playrect collision
	else if (checkCollision(getPlayRects(), point))
	{
		mPlayer->moveToPosition(point.x, point.y);
		mItemInteraction = false;
	}

	//Check Item collision
	mouseClickCheckItemCollision(point);

	//Check Rect Collisions
	mouseClickCheckRectCollision(point);
}

void LastLevel::mouseReleased(sf::Event & event)
{
	if (mInventory->selectedItem() != NULL
		&& mInventory->selectedItem()->getId() == "Needle"
		&& mGramophone->getRectangle().contains(mWorldPos)
		&& mActiveScene == 1)
	{
		mMouseReleased = true;
		mItemInteraction = true;
		mPlayer->moveToPosition(477, 366);
		mTargetItem = mGramophone;
	}
	else if (mInventory->selectedItem() != NULL
			&& mInventory->selectedItem()->getId() == "Screwdevice"
			&& mEarth->getRectangle().contains(mWorldPos)
			&& mActiveScene == 1)
	{
		mMouseReleased = true;
		mItemInteraction = true;
		mPlayer->moveToPosition(323, 368);
		mTargetItem = mEarth;
	}
	else if (mInventory->selectedItem() != NULL
			&& mInventory->selectedItem()->getId() == "Fish"
			&& mFoodBowl->getRectangle().contains(mWorldPos)
			&& mActiveScene == 2)
	{
		mMouseReleased = true;
		mItemInteraction = true;
		mPlayer->moveToPosition(700, 422);
		mTargetItem = mFoodBowl;
	}
	else if (mInventory->selectedItem() != NULL
			&& mInventory->selectedItem()->getId() == "Magic Clam"
			&& mActiveScene == 2
			&& mRects[1]->contains(mWorldPos))
	{
		mMouseReleased = true;
		mPlayer->moveToPosition(419, 388);
	}
	else if (mInventory->selectedItem() != NULL
		&& mInventory->selectedItem()->getId() == "Venus"
		&& mActiveScene == 0
		&& mRects[1]->contains(mWorldPos))
	{
		mMouseReleased = true;
		mPlayer->moveToPosition(535, 437);
		mInventory->removeItem(mInventory->getSelectedItem());
		mVenus->toggleActive();
		mVenus->setPosition(328, 56);
		mVenusHanged = true;
		if (mMarsHanged && mPlutoHanged && mSaturnHanged && mEarthHanged)
		{
			mPlanetPuzzleSound.play();
		}
		else
		{
			mCriticalItemSound.play();
		}
	}
	else if (mInventory->selectedItem() != NULL
		&& mInventory->selectedItem()->getId() == "Earth"
		&& mActiveScene == 0
		&& mRects[2]->contains(mWorldPos))
	{
		mMouseReleased = true;
		mPlayer->moveToPosition(535, 437);
		mInventory->removeItem(mInventory->getSelectedItem());
		addItem(mEarth);
		mEarth->toggleActive();
		mEarth->setPosition(374, 56);
		mEarth->setScale(0.15f, 0.15f);
		mEarthHanged = true;
		if (mMarsHanged && mPlutoHanged && mSaturnHanged && mVenusHanged)
		{
			mPlanetPuzzleSound.play();
		}
		else
		{
			mCriticalItemSound.play();
		}
	}
	else if (mInventory->selectedItem() != NULL
		&& mInventory->selectedItem()->getId() == "Red Apple"
		&& mActiveScene == 0
		&& mRects[3]->contains(mWorldPos))
	{
		mMouseReleased = true;
		mPlayer->moveToPosition(535, 437);
		mInventory->removeItem(mInventory->getSelectedItem());
		addItem(mRedApple);
		mRedApple->toggleActive();
		mRedApple->setPosition(452, 52);
		mRedApple->setScale(0.3f, 0.3f);
		mMarsHanged = true;
		if (mEarthHanged && mPlutoHanged && mSaturnHanged && mVenusHanged)
		{
			mPlanetPuzzleSound.play();
		}
		else
		{
			mCriticalItemSound.play();
		}
	}
	else if (mInventory->selectedItem() != NULL
		&& mInventory->selectedItem()->getId() == "Saturn"
		&& mActiveScene == 0
		&& mRects[5]->contains(mWorldPos))
	{
		mMouseReleased = true;
		mPlayer->moveToPosition(535, 437);
		mSaturn->toggleActive();
		mSaturn->setScale(0.7f, 0.7f);
		mSaturn->setPosition(592, 38);
		addItem(mSaturn);
		mInventory->removeItem(mInventory->getSelectedItem());
		mSaturnHanged = true;
		if (mMarsHanged && mPlutoHanged && mEarthHanged && mVenusHanged)
		{
			mPlanetPuzzleSound.play();
		}
		else
		{
			mCriticalItemSound.play();
		}
	}
	else if (mInventory->selectedItem() != NULL
		&& mInventory->selectedItem()->getId() == "Pearl"
		&& mActiveScene == 0
		&& mRects[8]->contains(mWorldPos))
	{
		mMouseReleased = true;
		mPlayer->moveToPosition(535, 437);
		mInventory->removeItem(mInventory->getSelectedItem());
		addItem(mPearl);
		mPearl->toggleActive();
		mPearl->setPosition(762, 30);
		mPearl->setScale(0.6f, 0.6f);
		mPlutoHanged = true;
		if (mMarsHanged && mEarthHanged && mSaturnHanged && mVenusHanged)
		{
			mPlanetPuzzleSound.play();
		}
		else
		{
			mCriticalItemSound.play();
		}
	}
	else
	{
		mInventory->deSelectCheck();
	}
}

void LastLevel::update(sf::RenderWindow &window, float deltaTime)
{
	//Only do this if the level needs moving camera
	//mLHandler->getLevel(1) is currently LastLevel, change as necessary
	//Scene 1 is the big, second room in LastLevel, change as necessary
	if (getActiveScene() == 1)
	{
		//520 is the distance the Player has to be from the left side of the level before the camera starts scrolling, change as necessary
		//1000 is the distance the Player has to be from the right side of the level before the camera starts scrolling, change as necessary
		//In this case the camera scrolls while the Player is between 520 and 1000.
		if (mPlayer->getPosition().x > 520 && mPlayer->getPosition().x < 1000)
		{
			//Make camera follow Player position
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

	//UI
	mUI->update(deltaTime);

	//Only update currently "Targeted" Item to avoid having to loop through and update all Items
	if (mTargetItem != NULL)
	{
		updateTargetItem(deltaTime);
	}

	//Cursor
	mCursor->update(window);

	//DialogueSystem update and reset when finished
	mDialogueSystem->update(deltaTime);
	if (mDialogueSystem->isDialogueFinished())
	{
		mCursor->setMode(Cursor::NORMAL);
		mUI->setState(UI::INGAME);
		mDialogueSystem->reset();
	}

	if (mCursor->getMode() != Cursor::DIALOGUE && mCursor->getMode() != Cursor::DISABLED && mUI->getState() == UI::INGAME)
	{
		mouseHover();
	}

	//Engage walk animation when player is moving
	if (!mPlayer->getIsOnPosition())
	{
		//mPlayer->navigate(mItems, deltaTime);
		mPlayer->setActiveAnimation("Walk");
	}

	//Make sure UI is in correct place at all times
	mUI->setUIPosition(mView.getCenter());
	mInventory->setGridPosition(mView.getCenter());

	//Update Cat when it is moving/eating
	if (mCatMoved)
	{
		mCat->update(deltaTime);
	}

	//Code for Clam
	if (mMouseReleased && mPlayer->getIsOnPosition() && mInventory->selectedItem() != NULL && mInventory->selectedItem()->getId() == "Magic Clam")
	{
		mRunningWaterSound.play();
		mInventory->removeItem(mInventory->getSelectedItem());
		mInventory->addItem(mPearl);
		mRegularItemSound.play();
	}
}

void LastLevel::mouseHover()
{
	mCursor->setMode(Cursor::NORMAL);

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
				if (getItems()[i]->getPickupable())
				{
					mCursor->setMode(Cursor::OPENHAND);
				}
				//Check if Item can be interacted with
				if (getItems()[i]->getInteractable())
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
			// i == 10 is stairs in scene 1
			if (i == 10)
			{
				if (mActiveScene == 0)
				{
					mCursor->setMode(Cursor::SCENECHANGE);
				}
				else
				{
					mCursor->setMode(Cursor::NORMAL);
				}
			}

			// i == 5 is stairs in scene 2
			else if (i == 5) 
			{
				if (mActiveScene == 1)
				{
					mCursor->setMode(Cursor::SCENECHANGE);
				}
				else
				{
					mCursor->setMode(Cursor::NORMAL);
				}
			}

			// i == 0 is door in scene 2
			else if (i == 0)
			{
				if (mActiveScene == 1)
				{
					mCursor->setMode(Cursor::SCENECHANGE);
				}
				else if (mActiveScene == 2 && !mLookedAtFridge)
				{
					mCursor->setMode(Cursor::EYE);
				}
				else
				{
					mCursor->setMode(Cursor::NORMAL);
				}
			}

			//i == 2 is door in scene 3
			else if (i == 2)
			{
				if (mActiveScene == 2)
				{
					mCursor->setMode(Cursor::SCENECHANGE);
				}
				else if (mActiveScene == 1 && !mLookedAtJewelryBox)
				{
					mCursor->setMode(Cursor::EYE);
				}
				else
				{
					mCursor->setMode(Cursor::NORMAL);
				}
			}
			else if (i == 1)
			{
				if (mActiveScene == 1 && !mLookedAtBooks)
				{
					mCursor->setMode(Cursor::EYE);
				}
				else if (mActiveScene == 2 && !mLookedAtTap)
				{
					mCursor->setMode(Cursor::EYE);
				}
				else
				{
					mCursor->setMode(Cursor::NORMAL);
				}
			}
			else if (i == 3)
			{
				if (mActiveScene == 1 && !mLookedAtCrotchRocket)
				{
					mCursor->setMode(Cursor::EYE);
				}
				else
				{
					mCursor->setMode(Cursor::NORMAL);
				}
			}
			else if (i == 4)
			{
				if (mActiveScene == 1 && !mLookedAtMask)
				{
					mCursor->setMode(Cursor::EYE);
				}
				else
				{
					mCursor->setMode(Cursor::NORMAL);
				}
			}

			else
			{
				mCursor->setMode(Cursor::NORMAL);
			}
		}
	}

	if (mInventory->selectedItem() != NULL)
	{
		mCursor->setMode(Cursor::CLOSEDHAND);
	}
}

bool LastLevel::isLevelComplete()
{
	return mLevelComplete;
}

UI* LastLevel::getUI()
{
	return mUI;
}

void LastLevel::updateTargetItem(float deltaTime)
{
	mTargetItem->update(deltaTime);
	//Put everything back to normal after the "Pushing cutscene"
	if (mTargetItem->getIsOnPosition())
	{
		if (mFishFalling)
		{
			mFishFalling = false;
			mCursor->setMode(Cursor::NORMAL);
			mTargetItem->setSpeed(100.0f);
			mFishHitFloorSound.play();
		}

		if (mCatWalking)
		{
			mCatWalking = false;
			mCursor->setMode(Cursor::NORMAL);
			mTargetItem->setSpeed(100.0f);
			mTargetItem->setActiveAnimation("CatEating");
			//mCatEatingSound.play();
		}
	}
}

void LastLevel::lookAtTargetItem()
{
	mTargetItem->toggleIsLookedAt(); //Fixa dialoger i funktion

	if (mTargetItem->getId() == "Putte")
	{
		if (mKidsFound)
		{
			mDialogueSystem->reset();
			mDialogueSystem->hasClicked("putteFamily", mPlayer);
			mUI->setState(UI::INGAME);
			mCursor->setMode(Cursor::DIALOGUE);
		}
		else
		{
			mDialogueSystem->reset();
			mDialogueSystem->hasClicked("putte2", mPlayer);
			mUI->setState(UI::INGAME);
			mCursor->setMode(Cursor::DIALOGUE);
		}
	}
	if (mTargetItem->getId() == "Kids")
	{
		/*mDialogueSystem->reset();
		mDialogueSystem->hasClicked("kids", mPlayer);*/
		mUI->setState(UI::INGAME);
		//mCursor->setMode(Cursor::DIALOGUE);
	}
	if (mTargetItem->getId() == "Dollhouse")
	{
		mDialogueSystem->reset();
		mDialogueSystem->hasClicked("dollHouse", mPlayer);
		mUI->setState(UI::INGAME);
		mCursor->setMode(Cursor::DIALOGUE);
	}
	if (mTargetItem->getId() == "Needle")
	{
		mDialogueSystem->reset();
		mDialogueSystem->hasClicked("textileCart", mPlayer);
		mUI->setState(UI::INGAME);
		mCursor->setMode(Cursor::DIALOGUE);
	}
	if (mTargetItem->getId() == "Earth" && !mMouseReleased)
	{
		if (!mEarthPickedUp)
		{
			mDialogueSystem->reset();
			mDialogueSystem->hasClicked("earthGlobe", mPlayer);
			mUI->setState(UI::INGAME);
			mCursor->setMode(Cursor::DIALOGUE);
		}
	}
	if (mTargetItem->getId() == "Fish")
	{
		mDialogueSystem->reset();
		mDialogueSystem->hasClicked("fishTrophy", mPlayer);
		mUI->setState(UI::INGAME);
		mCursor->setMode(Cursor::DIALOGUE);
	}
	if (mTargetItem->getId() == "Gramophone" && !mMouseReleased)
	{
		mDialogueSystem->reset();
		mDialogueSystem->hasClicked("gramophne", mPlayer);
		mUI->setState(UI::INGAME);
		mCursor->setMode(Cursor::DIALOGUE);
	}
	if (mTargetItem->getId() == "Fruitbowl")
	{
		mDialogueSystem->reset();
		mDialogueSystem->hasClicked("fruitBowl", mPlayer);
		mUI->setState(UI::INGAME);
		mCursor->setMode(Cursor::DIALOGUE);
	}
	if (mTargetItem->getId() == "Cat")
	{
		mDialogueSystem->reset();
		mDialogueSystem->hasClicked("cat", mPlayer);
		mUI->setState(UI::INGAME);
		mCursor->setMode(Cursor::DIALOGUE);
		mCatSound.play();
	}
	if (mTargetItem->getId() == "Foodbowl" && !mMouseReleased)
	{
		mDialogueSystem->reset();
		mDialogueSystem->hasClicked("catFoodBowl", mPlayer);
		mUI->setState(UI::INGAME);
		mCursor->setMode(Cursor::DIALOGUE);
	}
	if (mTargetItem->getId() == "Hole")
	{
		mDialogueSystem->reset();
		mDialogueSystem->hasClicked("mouseDwelling", mPlayer);
		mUI->setState(UI::INGAME);
		mCursor->setMode(Cursor::DIALOGUE);
	}
	mItemInteraction = false;
}

void LastLevel::pickupTargetItem()
{
	//Make Item inactive when it is picked up
	mTargetItem->toggleActive();

	if (mTargetItem->getId() == "Earth")
	{
		if (mMouseReleased)
		{
			mInventory->addItem(mTargetItem);
			mEarth->togglePickupable();
			mEarthPickedUp = true;
			std::cout << "Plockade upp Jordglob";
			mScrewGlobeSound.play();
			mRegularItemSound.play();
			mInventory->deSelectCheck();
		}
		else
		{
			mTargetItem->toggleActive();
		}

	}

	if (mTargetItem->getId() == "Needle")
	{
		mInventory->addItem(mTargetItem);
		mTargetItem->changeTexture(handler, "LastLevel_ItemTest1.png");
		std::cout << "Plockade upp nål!!";
		mRegularItemSound.play();
	}

	if (mTargetItem->getId() == "Fish")
	{
		mInventory->addItem(mTargetItem);
		mFish->changeTexture(handler, "Fisk1.png");
		std::cout << "Plockade upp fisk!";
		mRegularItemSound.play();
	}
}

void LastLevel::interactTargetItem()
{
	//Check if Item has already been interacted with
	if (!mTargetItem->isInteracted())
	{
		mTargetItem->toggleInteractable();

		//Grammophone
		if (mTargetItem->getId() == "Gramophone")
		{
			//mGramophoneSound.play();
			if (mMouseReleased)
			{
				mInventory->removeItem(mInventory->getSelectedItem());

				for (Level::ItemVector::size_type i = 0; i < getItems().size(); i++)
				{
					if (getItems()[i]->getId() == "Fish")
					{
						getItems()[i]->togglePickupable();
						getItems()[i]->setSpeed(300.0f);
						getItems()[i]->moveToPosition(861, 300);
						mTargetItem = getItems()[i];
						mCursor->setMode(Cursor::DISABLED);
						mFishFalling = true;
					}
				}
			}
			else
			{
				mTargetItem->toggleInteractable();
			}

			std::cout << "Spelar ljud, fisk ramlar ner";
		}

		//Fruitbowl
		if (mTargetItem->getId() == "Fruitbowl")
		{

			for (Level::ItemVector::size_type i = 0; i < getItems().size(); i++)
			{
				if (getItems()[i]->getId() == "Red Apple")
				{
					mTargetItem = getItems()[i];
					mInventory->addItem(mTargetItem);
					mRegularItemSound.play();
				}
			}
			std::cout << "Plockar upp äpple!";
		}

		//Foodbowl
		if (mTargetItem->getId() == "Foodbowl")
		{
			if (mMouseReleased)
			{
				mInventory->removeItem(mInventory->getSelectedItem());
				mCatMoved = true;
				for (Level::ItemVector::size_type i = 0; i < getItems().size(); i++)
				{
					if (getItems()[i]->getId() == "Cat")
					{
						mTargetItem = getItems()[i];
						mTargetItem->setActiveAnimation("CatWalking");
						mTargetItem->setPosition(367, 276);
						mTargetItem->setScale(-0.17f, 0.17f);
						mTargetItem->setSpeed(100.0f);
						mTargetItem->moveToPosition(715, 285);
						mCursor->setMode(Cursor::DISABLED);
						mCatWalking = true;
					}
				}
			}
			else
			{
				mTargetItem->toggleInteractable();
			}
			std::cout << "Katten flyttar på sig!" << std::endl;
		}

		//Putte
		if (mTargetItem->getId() == "Putte")
		{
			if (mKidsFound == true)
			{
				for (Level::ItemVector::size_type i = 0; i < getItems().size(); i++)
				{
					if (getItems()[i]->getId() == "Magic Clam")
					{
						mTargetItem = getItems()[i];
						mInventory->addItem(mTargetItem);
						mRegularItemSound.play();
						std::cout << "Putte ger dig en mussla!";
					}

				}
			}
			else
			{
				mTargetItem->toggleInteractable();
			}
		}

		//Dollhouse
		if (mTargetItem->getId() == "Dollhouse")
		{
			addItem(mPutte);
			mDollhouseInteracted = true;
		}

		//Hole
		if (mTargetItem->getId() == "Hole")
		{
			if (mCatMoved == true)
			{
				for (Level::ItemVector::size_type i = 0; i < getItems().size(); i++)
				{
					if (getItems()[i]->getId() == "Hoola Hoop")
					{
						mTargetItem = getItems()[i];
						mInventory->addItem(mTargetItem);
						mRegularItemSound.play();
					}

					if (getItems()[i]->getId() == "Beige Ball")
					{
						mTargetItem = getItems()[i];
						mInventory->addItem(mTargetItem);
						mRegularItemSound.play();
					}
				}
				std::cout << "Pratar med barnen, får saturnus!" << std::endl;
				mPutte->toggleIsLookedAt();
				mKidsFound = true;
			}
			else
			{
				mTargetItem->toggleInteractable();
				std::cout << "Flytta katten!" << std::endl;
				mCatHissingSound.play();
			}
		}
	}
}

void LastLevel::mouseClickCheckItemCollision(sf::Vector2f point)
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
				//Check Id of that Item
				if (getItems()[i]->getId() == "Gramophone")
				{
					//Move Player to the closest point that is still inside the playrect
					mPlayer->moveToPosition(477, 366);
					//Set the Item as "Target Item"
					mTargetItem = getItems()[i];
					//Enable Item interaction
					mItemInteraction = true;
					std::cout << "Klickade på grammofon";
				}

				if (getItems()[i]->getId() == "Earth")
				{
					mPlayer->moveToPosition(323, 368);
					mTargetItem = getItems()[i];
					mItemInteraction = true;
					std::cout << "Klickade på jordglob";
				}

				if (getItems()[i]->getId() == "Fish")
				{
					mPlayer->moveToPosition(930, 365);
					mTargetItem = getItems()[i];
					mItemInteraction = true;
					std::cout << "Klickade på fisk";
				}

				if (getItems()[i]->getId() == "Needle")
				{
					mPlayer->moveToPosition(323, 368);
					mTargetItem = getItems()[i];
					mItemInteraction = true;
					std::cout << "Klickade på nål";

				}

				if (getItems()[i]->getId() == "Cat")
				{
					mTargetItem = getItems()[i];
					mItemInteraction = true;
					std::cout << "Klickade på katt";
				}

				if (getItems()[i]->getId() == "Fruitbowl")
				{
					mPlayer->moveToPosition(643, 394);
					mTargetItem = getItems()[i];
					mItemInteraction = true;
					std::cout << "Klickade på fruktskål";
				}

				if (getItems()[i]->getId() == "Foodbowl")
				{
					mPlayer->moveToPosition(700, 422);
					mTargetItem = getItems()[i];
					mItemInteraction = true;
					std::cout << "Klickade på matskål";
				}

				if (getItems()[i]->getId() == "Putte")
				{

					mPlayer->moveToPosition(340, 382);
					mTargetItem = getItems()[i];
					mItemInteraction = true;
					std::cout << "Klickade på Putte";

				}

				if (getItems()[i]->getId() == "Dollhouse")
				{

					mPlayer->moveToPosition(348, 382);
					mTargetItem = getItems()[i];
					mItemInteraction = true;
					std::cout << "Klickade på dockhus";

				}

				if (getItems()[i]->getId() == "Kids")
				{

					mPlayer->moveToPosition(297, 422);
					mTargetItem = getItems()[i];
					mItemInteraction = true;
					std::cout << "Klickade på Barnen";

				}

				if (getItems()[i]->getId() == "Hole")
				{

					mPlayer->moveToPosition(220, 350);
					mTargetItem = getItems()[i];
					mItemInteraction = true;
					std::cout << "Klickade på Hål";

				}

				if (getItems()[i]->getId() == "Red Apple")
				{

					mTargetItem = getItems()[i];
					mItemInteraction = true;
					std::cout << "Klickade på Apelsin";

				}
			}
		}
	}
}

void LastLevel::mouseClickCheckRectCollision(sf::Vector2f point)
{
	for (Level::rectVector::size_type i = 0; i < getRects().size(); i++)
	{
		if (checkCollision(getRects()[i], point))
		{
			// i == 0 is Planet 1 if ActiveScene is 0, or Door if ActiveScene is 1, or Refrigerator if ActiveScene is 2.
			if (i == 0)
			{
				if (getActiveScene() == 0)
				{
					mDialogueSystem->reset();
					mDialogueSystem->hasClicked("mercury", mPlayer);
					mUI->setState(UI::INGAME);
					mCursor->setMode(Cursor::DIALOGUE);
					std::cout << "Planet 1!";
					mPlayer->moveToPosition(535, 437);
				}
				else if (getActiveScene() == 1)
				{
					std::cout << "Door to scene 3!";
					//Make Player get into position for Scene change
					mPlayer->moveToPosition(70, 370);
					//Set Collision Rect to Scene change position
					mSceneChangeRect = sf::FloatRect(sf::Vector2f(70, 370), sf::Vector2f(10, 10));
					//Set if Player should toggle on Scene Change
					mPlayerToggle = false;
					//Set starting position of Player in new Scene
					mSceneChangePlayerPos = sf::Vector2f(950, 480);
					//Set which Scene will be the new Scene
					mNewScene = 2;
					mLastScene = 1;
				}
				else if (getActiveScene() == 2 && !mLookedAtFridge)
				{
					mDialogueSystem->reset();
					mDialogueSystem->hasClicked("refridgerator", mPlayer);
					mUI->setState(UI::INGAME);
					mCursor->setMode(Cursor::DIALOGUE);
					std::cout << "Refrigerator!";
					mLookedAtFridge = true;
					//mPlayer->moveToPosition(870, 349);
				}
			}

			// i == 1 is Planet 2 if ActiveScene is 0, Books if ActiveLevel is 1, Tap if ActiveScene is 2
			else if (i == 1)
			{
				if (getActiveScene() == 0)
				{
					if (mVenusHanged)
					{
						mDialogueSystem->reset();
						mDialogueSystem->hasClicked("venus", mPlayer);
						mUI->setState(UI::INGAME);
						mCursor->setMode(Cursor::DIALOGUE);
					}
					else
					{
						/*mDialogueSystem->reset();
						mDialogueSystem->hasClicked("emptyVenus", mPlayer);
						mUI->setState(UI::INGAME);
						mCursor->setMode(Cursor::DIALOGUE);*/
					}
					std::cout << "Planet 2!";
					mPlayer->moveToPosition(535, 437);
				}
				else if (getActiveScene() == 1 && !mLookedAtBooks)
				{
					mDialogueSystem->reset();
					mDialogueSystem->hasClicked("books2", mPlayer);
					mUI->setState(UI::INGAME);
					mCursor->setMode(Cursor::DIALOGUE);
					std::cout << "Books!";
					mLookedAtBooks = true;
					//mPlayer->moveToPosition(356, 377);
				}
				else if (getActiveScene() == 2 && !mLookedAtTap)
				{
					mDialogueSystem->reset();
					mDialogueSystem->hasClicked("waterTap", mPlayer);
					mUI->setState(UI::INGAME);
					mCursor->setMode(Cursor::DIALOGUE);
					std::cout << "Tap!";
					mLookedAtTap = true;
				}

			}

			// i == 2 is Planet 3 if ActiveScene is 0, Jewelry Box if ActiveScene is 1, Door if ActiveScene is 2
			else if (i == 2)
			{
				if (getActiveScene() == 0)
				{
					if (mEarthHanged)
					{
						mDialogueSystem->reset();
						mDialogueSystem->hasClicked("earth", mPlayer);
						mUI->setState(UI::INGAME);
						mCursor->setMode(Cursor::DIALOGUE);
					}
					else
					{
						mDialogueSystem->reset();
						mDialogueSystem->hasClicked("emptyEarth", mPlayer);
						mUI->setState(UI::INGAME);
						mCursor->setMode(Cursor::DIALOGUE);
					}
					std::cout << "Planet 3!";
					mPlayer->moveToPosition(535, 437);
				}
				else if (getActiveScene() == 1 && !mLookedAtJewelryBox)
				{
					mDialogueSystem->reset();
					mDialogueSystem->hasClicked("jewelryCase", mPlayer);
					mUI->setState(UI::INGAME);
					mCursor->setMode(Cursor::DIALOGUE);
					//TODO - Play mJewelryBoxSound in the middle of dialogue here
					std::cout << "Jewelry Box!";
					mLookedAtJewelryBox = true;
					//mPlayer->moveToPosition(591, 391);
				}
				else
				{
					std::cout << "Door to scene 2!";

					mPlayer->moveToPosition(950, 480);
					mSceneChangeRect = sf::FloatRect(sf::Vector2f(950, 480), sf::Vector2f(10, 10));
					mPlayerToggle = false;
					mSceneChangePlayerPos = sf::Vector2f(70, 370);

					mNewScene = 1;
					mLastScene = 2;
				}
			}

			// i == 3 is Planet 4 if ActiveScene is 0, Rocket if ActiveScene is 1
			else if (i == 3)
			{
				if (getActiveScene() == 0)
				{
					if (mMarsHanged)
					{
						mDialogueSystem->reset();
						mDialogueSystem->hasClicked("mars", mPlayer);
						mUI->setState(UI::INGAME);
						mCursor->setMode(Cursor::DIALOGUE);
					}
					else
					{
						mDialogueSystem->reset();
						mDialogueSystem->hasClicked("emptyMars", mPlayer);
						mUI->setState(UI::INGAME);
						mCursor->setMode(Cursor::DIALOGUE);
					}

					std::cout << "Planet 4!";
					mPlayer->moveToPosition(535, 437);
				}
				else if (getActiveScene() == 1 && !mLookedAtCrotchRocket)
				{
					/*mDialogueSystem->reset();
					mDialogueSystem->hasClicked("crotchRocket", mPlayer);
					mUI->setState(UI::INGAME);
					mCursor->setMode(Cursor::DIALOGUE);*/
					std::cout << "Crotch Rocket!";
					mLookedAtCrotchRocket = true;
					//mPlayer->moveToPosition(452, 379);
				}

			}

			// i == 4 is Planet 5 if ActiveScene is 0, Mask if ActiveScene is 1
			else if (i == 4)
			{
				if (getActiveScene() == 0)
				{
					mDialogueSystem->reset();
					mDialogueSystem->hasClicked("jupiter", mPlayer);
					mUI->setState(UI::INGAME);
					mCursor->setMode(Cursor::DIALOGUE);
					std::cout << "Planet 5!";
					mPlayer->moveToPosition(535, 437);
				}
				else if (getActiveScene() == 1 && !mLookedAtMask)
				{
					mDialogueSystem->reset();
					mDialogueSystem->hasClicked("mask", mPlayer);
					mUI->setState(UI::INGAME);
					mCursor->setMode(Cursor::DIALOGUE);
					std::cout << "Mask!";
					mLookedAtMask = true;
					//mPlayer->moveToPosition(1263, 458);
				}

			}

			// i == 5 is Planet 6 if ActiveScene is 0, Stairs if ActiveScene is 1
			else if (i == 5)
			{
				if (getActiveScene() == 0)
				{
					if (mSaturnHanged)
					{
						mDialogueSystem->reset();
						mDialogueSystem->hasClicked("saturn", mPlayer);
						mUI->setState(UI::INGAME);
						mCursor->setMode(Cursor::DIALOGUE);
					}
					else
					{
						mDialogueSystem->reset();
						mDialogueSystem->hasClicked("emptySaturn", mPlayer);
						mUI->setState(UI::INGAME);
						mCursor->setMode(Cursor::DIALOGUE);
					}
					std::cout << "Planet 6!";
					mPlayer->moveToPosition(535, 437);
				}
				else if (getActiveScene() == 1)
				{
					std::cout << "Stairs to Scene 1!";

					//Make Player get into position for Scene change
					mPlayer->moveToPosition(1470, 450);
					//Set Collision Rect to Scene change position
					mSceneChangeRect = sf::FloatRect(sf::Vector2f(1470, 450), sf::Vector2f(10, 10));
					//Set if Player should toggle on Scene Change
					mPlayerToggle = false;
					//Set starting position of Player in new Scene
					mSceneChangePlayerPos = sf::Vector2f(101, 349);
					//Set which Scene will be the new Scene
					mNewScene = 0;
					mLastScene = 2;
				}

			}

			// i == 6 is Planet 7 if ActiveScene is 0
			else if (i == 6)
			{
				if (getActiveScene() == 0)
				{
					mDialogueSystem->reset();
					mDialogueSystem->hasClicked("uranus", mPlayer);
					mUI->setState(UI::INGAME);
					mCursor->setMode(Cursor::DIALOGUE);
					std::cout << "Planet 7!";
					mPlayer->moveToPosition(535, 437);
				}
			}

			// i == 7 is Planet 8 if ActiveScene is 0
			else if (i == 7)
			{
				if (getActiveScene() == 0)
				{
					mDialogueSystem->reset();
					mDialogueSystem->hasClicked("neptune", mPlayer);
					mUI->setState(UI::INGAME);
					mCursor->setMode(Cursor::DIALOGUE);
					std::cout << "Planet 8!";
					mPlayer->moveToPosition(535, 437);
				}
			}

			// i == 8 is Planet 9 if ActiveScene is 0
			else if (i == 8)
			{
				if (mPlutoHanged)
				{
					mDialogueSystem->reset();
					mDialogueSystem->hasClicked("pluto", mPlayer);
					mUI->setState(UI::INGAME);
					mCursor->setMode(Cursor::DIALOGUE);
				}
				else
				{
					mDialogueSystem->reset();
					mDialogueSystem->hasClicked("emptyPluto", mPlayer);
					mUI->setState(UI::INGAME);
					mCursor->setMode(Cursor::DIALOGUE);
				}
				std::cout << "Planet 9!";
				mPlayer->moveToPosition(535, 437);
			}

			// i == 9 is Balconydoor if ActiveScene is 0
			else if (i == 9)
			{
				if (mPlutoHanged && mVenusHanged && mEarthHanged && mSaturnHanged && mMarsHanged)
				{
					std::cout << "Game Completed!" << std::endl;
				}
				else
				{
					mDialogueSystem->reset();
					mDialogueSystem->hasClicked("balconyDoor", mPlayer);
					mUI->setState(UI::INGAME);
					mCursor->setMode(Cursor::DIALOGUE);
					std::cout << "BalconyDoor!";
				}
				mPlayer->moveToPosition(496, 334);
			}

			// i == 10 is Door if ActiveScene is 0
			else if (i == 10)
			{

				mPlayer->moveToPosition(101, 349);
				mSceneChangeRect = sf::FloatRect(sf::Vector2f(101, 349), sf::Vector2f(10, 10));
				mPlayerToggle = false;
				mSceneChangePlayerPos = sf::Vector2f(1437, 440);
				mNewScene = 1;

				std::cout << "Stairs to scene 2!";
				mLastScene = 0;
			}
		}
	}
}

