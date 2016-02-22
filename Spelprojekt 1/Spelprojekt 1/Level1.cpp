#include "Level1.h"

Level1::Level1(ResourceHandler &handler) :
mRects(),
mPlayRects(),
mIsActive(false),
mItemInteraction(false),
mLookedAtAquarium(false),
mPushingBlock(false),
mReadyForScrewdevice(false),
mPickedUpScrewdevice(false),
mMovedStar(false),
mReadyToLeave(false),
mLevelComplete(false),
mUpdateTime(0)
{
}


Level1::~Level1()
{
	mRects.clear();
	mPlayRects.clear();
	mItems.clear();
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


Player* Level1::getPlayer()
{
	return mPlayer;
}


void Level1::playBackgroundMusic()
{
	music.play();
}


void Level1::playAmbience()
{
	mAmbientSound.play();
}


void Level1::drawBackground(sf::RenderWindow &window)
{	
	window.setView(mView);
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
		if (mItems[i]->getActive() && mItems[i]->getId() != "Screwdevice")
		{
			mItems[i]->draw(window);
		}
	}
}

void Level1::drawUI(sf::RenderWindow &window)
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


void Level1::toggleActive(ResourceHandler &handler)
{
	if (!mIsActive)
	{
		handler.loadLevel1();

		//Room Textures
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

		//Help rectangles
		rectangle.setPosition(sf::Vector2f(0, 0));
		rectangle.setSize(sf::Vector2f(0, 0));

		//Sound/music
		music.openFromFile(handler.getMusic("Level1Music.ogg"));
		music.setLoop(true);
		music.setVolume(80);
		music.play();

		mAmbientSound.setBuffer(*handler.getSound("Level1_Ambience.ogg"));
		mAmbientSound.setLoop(true);
		mAmbientSound.play();

		mAquariumSound.setBuffer(*handler.getSound("Aquarium.ogg"));
		mAquariumSound.setLoop(true);
		mAquariumSound.setVolume(5);
		mAquariumSound.play();

		mRadioSound.setBuffer(*handler.getSound("Radio_Noise.ogg"));
		//mRadioSound.setLoop(true);
		//mRadioSound.play();

		mCriticalItemSound.setBuffer(*handler.getSound("Critical_Item.ogg"));
		mCriticalItemSound.setVolume(70);

		mMagnetCatchSound.setBuffer(*handler.getSound("Magnet_Catch.ogg"));
		mMagnetDropSound.setBuffer(*handler.getSound("Magnet_Drop.ogg"));
		mPushingObjectSound.setBuffer(*handler.getSound("Pushing_Object.ogg"));
		mRegularItemSound.setBuffer(*handler.getSound("Regular_Item_Pickup.ogg"));
		mMenuMainUISound.setBuffer(*handler.getSound("Menu_MainUI.ogg"));
		mMenuHatSound.setBuffer(*handler.getSound("Menu_Hat.ogg"));
		mMenuInventorySound.setBuffer(*handler.getSound("Menu_Inventory.ogg"));
		mCraftingSound.setBuffer(*handler.getSound("Crafting.ogg"));

		//View
		mView.setCenter(512, 288);
		mView.setSize(1024, 576);

		//Player
		mPlayer = new Player(handler, sf::Vector2f(705, 500));

		//Inventory
		mInventory = new Inventory(handler);
		mInventory->setCraftableItems(handler, 0);

		//DialogueSystem
		mDialogueSystem = new DialogueSystem(handler);
		mDialogueSystem->setLevel1Start();

		//Mouse Cursor
		mCursor = new Cursor(handler);
		mCursor->setMode(Cursor::DIALOGUE);

		//Menu
		mUI = new UI(handler);

		//Create Items
		mScrewdevice = new Item(handler, sf::Vector2f(380, 400), "Screwdevice");
		mMagnet = new Item(handler, sf::Vector2f(325, 270), "Magnet");
		mStar = new Item(handler, sf::Vector2f(475, 435), "Star");
		mAstronaut = new Item(handler, sf::Vector2f(560, 160), "Astronaut");
		mBlock = new Item(handler, sf::Vector2f(570, 160), "Block");
		mString = new Item(handler, sf::Vector2f(250, 370), "String");
		mBowl = new Item(handler, sf::Vector2f(320, 158), "Bowl");
		mCube = new Item(handler, sf::Vector2f(352, 222), "Cube");
		mWallStar = new Item(handler, sf::Vector2f(900, 190), "WallStar");
		mRoger = new Item(handler, sf::Vector2f(530, 150), "Roger");

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
		//Rug
		mRects.push_back(createRect(380, 400, 40, 40));
		//Door
		mRects.push_back(createRect(690, 50, 150, 275));

		//Items - Set as Active, Pickupable, Interactable
		mScrewdevice->toggleActive();

		mMagnet->toggleActive();
		mMagnet->togglePickupable();

		mStar->toggleActive();
		mStar->toggleInteractable();

		mBlock->toggleActive();

		mString->toggleActive();
		mString->togglePickupable();

		mBowl->toggleActive();

		mCube->toggleActive();

		mWallStar->toggleIsLookedAt();

		mRoger->toggleActive();
		mRoger->toggleIsLookedAt();
		mRoger->setActiveAnimation("RogerSwim");
		mRoger->moveToPosition(470, 150);
		mRoger->setSpeed(10.0f);

		//Add to ItemVector
		addItem(mScrewdevice);
		addItem(mMagnet);
		addItem(mStar);
		addItem(mBlock);
		addItem(mAstronaut);
		addItem(mString);
		addItem(mBowl);
		addItem(mCube);
		addItem(mRoger);
	}
	else
	{
		delete mPlayer;
	}
	mIsActive = !mIsActive;
}


bool Level1::isActive()
{
	return mIsActive;
}


sf::View Level1::getView()
{
	return mView;
}


void Level1::moveViewWithPlayer(float playerPos)
{
	mView.setCenter(playerPos, 288);
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
		if (mReadyForScrewdevice && !mPickedUpScrewdevice)
		{
			mDialogueSystem->reset();
			mDialogueSystem->hasClicked("mat", mPlayer);
			mUI->setState(UI::INGAME);
			mCursor->setMode(Cursor::DIALOGUE);
		}

		mActiveScene = 0;
		//Walkable area
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
		//Rug
		mRects.push_back(createRect(380, 400, 40, 40));
		//Door
		mRects.push_back(createRect(690, 50, 150, 275));

		mAquariumSound.setVolume(5);

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
			mAstronaut->setPosition(565, 150);
			mAstronaut->setScale(0.4f, 0.4f);
			addItem(mAstronaut);
		}
		if (mBlock->getActive())
		{
			if (!mBlock->isInteracted())
			{
				mBlock->toggleInteractable();
				mBlock->setPosition(570, 160);
			}
			else
			{
				mBlock->setPosition(615, 160);
			}
			mBlock->setScale(0.3f, 0.3f);
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
		if (mScrewdevice->getActive())
		{
			addItem(mScrewdevice);
		}
		if (mWallStar->getActive())
		{
			addItem(mWallStar);
		}
		if (mRoger->getActive())
		{
			mRoger->setPosition(530, 150);
			mRoger->moveToPosition(470, 150);
			mRoger->setScale(0.07f, 0.07f);
			mRoger->setSpeed(10.0f);
			addItem(mRoger);
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

		mAquariumSound.setVolume(30);

		//Repopulate ItemVector with active items
		if (mBlock->getActive())
		{
			mAstronaut->setPosition(500, 315);
			mAstronaut->setScale(1.0f, 1.0f);
			addItem(mAstronaut);
			if (!mBlock->isInteracted())
			{
				mBlock->toggleInteractable();
				mBlock->setPosition(500, 315);
			}
			else
			{
				mBlock->setPosition(630, 315);
			}
			mBlock->setScale(1.0f, 1.0f);
			addItem(mBlock);
		}
		if (mRoger->getActive())
		{
			mRoger->setPosition(450, 310);
			mRoger->moveToPosition(170, 310);
			mRoger->setScale(0.2f, 0.2f);
			mRoger->setSpeed(15.0f);
			addItem(mRoger);
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


//Check collision between a single rectangle and a point
int Level1::checkCollision(const sf::FloatRect &boundingBox, sf::Vector2f &point)
{
	if (boundingBox.contains(point))
	{
		return 1;
	}
	return 0;
}
//Check collision between a single rectangle and a point
int Level1::checkCollision(sf::FloatRect* boundingBox, sf::Vector2f &point)
{
	if (boundingBox->contains(point))
	{
		return 1;
	}
	return 0;
}
//Check collision between a vector of rectangles and a point
int Level1::checkCollision(const std::vector<sf::FloatRect*> RectVector, sf::Vector2f &point)
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
int Level1::checkCollision(sf::FloatRect* boundingBox, sf::FloatRect &rect)
{
	if (boundingBox->intersects(rect))
	{
		return 1;
	}
	return 0;
}
//Check collision between a vector of rectangles and a rectangle
int Level1::checkCollision(const std::vector<sf::FloatRect*> RectVector, sf::FloatRect &rect)
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


void Level1::eventListen(sf::RenderWindow &window)
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
					mCraftingSound.play();
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
			else if (mCursor->getMode() != Cursor::DISABLED && !mPushingBlock)
			{
				mouseClick(event);
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
				}
			}
			if (event.key.code == sf::Keyboard::P)
			{
				mPlayer->togglePlayer();
			}
			if (event.key.code == sf::Keyboard::Escape)
			{
				mUI->setState(UI::MAINUI);
				mCursor->setMode(Cursor::MENU);
			}
			break;

		default:
			break;
		}
	}
}


void Level1::mouseClick(sf::Event &event)
{
	std::cout << "Mouse Pressed" << std::endl;
	std::cout << "mouse x: " << event.mouseButton.x << std::endl;
	std::cout << "mouse y: " << event.mouseButton.y << std::endl;

	std::cout << "mapped mouse x: " << mWorldPos.x << std::endl;
	std::cout << "mapped mouse y: " << mWorldPos.y << std::endl;

	sf::Vector2f point(mWorldPos.x, mWorldPos.y);

	//Check if Hat Icon is clicked
	if (checkCollision(mUI->getHatIconRect(), point))
	{
		mCursor->setMode(Cursor::MENU);
		mUI->setState(UI::HAT);
		mMenuHatSound.play();
	}

	//Check if Menu Icon is clicked
	else if (checkCollision(mUI->getMenuIconRect(), point))
	{
		mCursor->setMode(Cursor::MENU);
		mUI->setState(UI::MAINUI);
		mMenuMainUISound.play();
	}

	//Check if playrect collision
	else if (checkCollision(getPlayRects(), point))
	{
		mPlayer->moveToPosition(point.x, point.y);
		mItemInteraction = false;
	}

	//Use this to try fishing animation, TODO - Remove when fixed
	/*else if (checkCollision(getPlayRects(), point))
	{
		mPlayer->setActiveAnimation("Fishing");
	}*/

	//Check Item collision
	mouseClickCheckItemCollision(point);

	//Check Rect Collisions
	mouseClickCheckRectCollision(point);
}

//Change mouse cursor depending on what it is hovering over
void Level1::mouseHover()
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
			if (getItems()[i]->getActive() && getItems()[i]->getId() != "Screwdevice")
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
			// i == 0 is the fishtankplace, or Thomas Room if in fishtankplace
			if (i == 0)
			{
				if (getActiveScene() == 0)
				{
					if (!mLookedAtAquarium)
					{
						mCursor->setMode(Cursor::EYE);
					}
					else
					{
						mCursor->setMode(Cursor::NORMAL); // TODO - Add scenechange cursor maybe?
					}
				}
				else
				{
					mCursor->setMode(Cursor::NORMAL); // TODO - Add scenechange cursor maybe?
				}
			}
			// i == 6 is bump in the rug
			else if (i == 6)
			{
				if (mReadyForScrewdevice && !mPickedUpScrewdevice)
				{
					mCursor->setMode(Cursor::OPENHAND);
				}
				else
				{
					mCursor->setMode(Cursor::NORMAL);
				}
			}
			// i == 7 is door
			else if (i == 7)
			{
				if (mPickedUpScrewdevice && mMovedStar)
				{
					mCursor->setMode(Cursor::NORMAL);
				}
				else
				{
					mCursor->setMode(Cursor::EYE);
				}
			}
			else
			{
				mCursor->setMode(Cursor::EYE);
			}
		}
	}

	if (mInventory->selectedItem() != NULL)
	{
		mCursor->setMode(Cursor::CLOSEDHAND);
	}
}

void Level1::update(sf::RenderWindow &window, float deltaTime)
{
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
		if (mPlayer->getGlobalRect().intersects(mTargetItem->getRectangle()) && mPlayer->getIsOnPosition())
		{
			//Check if Item has already been looked at
			if (!mTargetItem->isLookedAt())
			{
				lookAtTargetItem();
			}
			//Check if Item can be picked up
			else if (mTargetItem->getPickupable())
			{
				pickupTargetItem();
			}
			//Check if Item can be interacted with
			else if (mTargetItem->getInteractable())
			{
				interactTargetItem();
			}
			//Disable Item interaction when done
			mItemInteraction = false;
		}
	}

	//Inventory update
	mInventory->update(window);

	//DialogueSystem update and reset when finished
	mDialogueSystem->update(deltaTime);
	if (mDialogueSystem->isDialogueFinished())
	{
		mCursor->setMode(Cursor::NORMAL);
		mUI->setState(UI::INGAME);
		mDialogueSystem->reset();
	}

	//Only update currently "Targeted" Item to avoid having to loop through and update all Items
	updateTargetItem(deltaTime);

	mCursor->update(window);

	//Change mouse cursor on hover
	if (mCursor->getMode() != Cursor::DIALOGUE && mCursor->getMode() != Cursor::DISABLED && mUI->getState() == UI::INGAME && mUpdateTime > 60)
	{
		mouseHover();
		mUpdateTime = 0;
	}
	else
		mUpdateTime++; //TODO - Remove mUpdateTime

	if (mMovedStar && mPickedUpScrewdevice)
	{
		if (!mReadyToLeave)
		{
			mDialogueSystem->setLevel1End();
			mCursor->setMode(Cursor::DIALOGUE);
			mUI->setState(UI::INGAME);
			mReadyToLeave = true;
		}
		if (!mDialogueSystem->getLevel1End())
		{
			mLevelComplete = true;
		}
	}

	if (!mPlayer->getIsOnPosition() && mPlayer->getActiveAnimation() != "Push")
	{
		mPlayer->setActiveAnimation("Walk");
	}

	//Make Roger Swim
	mRoger->update(deltaTime);
	if (mActiveScene == 0)
	{
		if (!mReadyForScrewdevice)
		{
			if (mRoger->getPosition().x > 550)
			{
				mRoger->moveToPosition(470, 150);
				mRoger->setScale(0.07f, 0.07f);
			}
			if (mRoger->getPosition().x < 500)
			{
				mRoger->moveToPosition(580, 150);
				mRoger->setScale(-0.07f, 0.07f);
			}
		}
		else
		{
			if (mRoger->getPosition().x > 590)
			{
				mRoger->moveToPosition(470, 150);
				mRoger->setScale(0.07f, 0.07f);
			}
			if (mRoger->getPosition().x < 500)
			{
				mRoger->moveToPosition(1000, 150);
				mRoger->setScale(-0.07f, 0.07f);
			}
		}
	}
	else if (mActiveScene == 1)
	{
		if (!mReadyForScrewdevice)
		{
			if (mRoger->getPosition().x > 450)
			{
				mRoger->moveToPosition(170, 310);
				mRoger->setScale(0.2f, 0.2f);
			}
			if (mRoger->getPosition().x < 300)
			{
				mRoger->moveToPosition(800, 310);
				mRoger->setScale(-0.2f, 0.2f);
			}
		}
		else
		{
			if (mRoger->getPosition().x > 570)
			{
				mRoger->moveToPosition(170, 310);
				mRoger->setScale(0.2f, 0.2f);
			}
			if (mRoger->getPosition().x < 300)
			{
				mRoger->moveToPosition(800, 310);
				mRoger->setScale(-0.2f, 0.2f);
			}
		}
	}
}

bool Level1::isLevelComplete()
{
	return mLevelComplete;
}

void Level1::updateTargetItem(float deltaTime)
{
	if (mTargetItem != NULL)
	{
		mTargetItem->update(deltaTime);
		if (mTargetItem->getIsOnPosition())
		{
			//Put everything back to normal after the "Pushing cutscene"
			if (mPushingBlock)
			{
				mPushingObjectSound.stop();
				mPushingBlock = false;
				mCursor->setMode(Cursor::NORMAL);
				mPlayer->setActiveAnimation("Idle");
				mPlayer->setSpeed(100.0f);
				mTargetItem->setSpeed(100.0f);
			}
			//Put everything back to normal after the "Fishing cutscene"
			if (mFishing)
			{
				mCriticalItemSound.play();
				mFishing = false;
				mTargetItem->toggleActive();
				mInventory->addItem(mTargetItem);
				mReadyForScrewdevice = true;
				mPlayer->setActiveAnimation("Idle");
				mPlayer->setScale(sf::Vector2f(0.25f, 0.25f));
				mPlayer->setPosition(490, 500);
				mPlayer->moveToPosition(490, 500);
				mCursor->setMode(Cursor::NORMAL);
			}
		}
	}
}

void Level1::lookAtTargetItem()
{
	mTargetItem->toggleIsLookedAt();
	if (mTargetItem->getId() == "Cube")
	{
		mDialogueSystem->reset();
		mDialogueSystem->hasClicked("rubicCube", mPlayer);
		mUI->setState(UI::INGAME);
		mCursor->setMode(Cursor::DIALOGUE);
	}
	if (mTargetItem->getId() == "Magnet")
	{
		mDialogueSystem->reset();
		mDialogueSystem->hasClicked("magnet", mPlayer);
		mUI->setState(UI::INGAME);
		mCursor->setMode(Cursor::DIALOGUE);
	}
	if (mTargetItem->getId() == "Bowl")
	{
		mDialogueSystem->reset();
		mDialogueSystem->hasClicked("bowl", mPlayer);
		mUI->setState(UI::INGAME);
		mCursor->setMode(Cursor::DIALOGUE);
	}
	if (mTargetItem->getId() == "Block")
	{
		mDialogueSystem->reset();
		mDialogueSystem->hasClicked("block", mPlayer);
		mUI->setState(UI::INGAME);
		mCursor->setMode(Cursor::DIALOGUE);
	}
	if (mTargetItem->getId() == "Astronaut")
	{
		mDialogueSystem->reset();
		mDialogueSystem->hasClicked("astronaut", mPlayer);
		mUI->setState(UI::INGAME);
		mCursor->setMode(Cursor::DIALOGUE);
	}
	if (mTargetItem->getId() == "String")
	{
		mDialogueSystem->reset();
		mDialogueSystem->hasClicked("string", mPlayer);
		mUI->setState(UI::INGAME);
		mCursor->setMode(Cursor::DIALOGUE);
	}
	if (mTargetItem->getId() == "Star")
	{
		mDialogueSystem->reset();
		mDialogueSystem->hasClicked("star", mPlayer);
		mUI->setState(UI::INGAME);
		mCursor->setMode(Cursor::DIALOGUE);
	}
}

void Level1::pickupTargetItem()
{
	//Make Item inactive when it is picked up
	mTargetItem->toggleActive();
	if (mTargetItem->getId() == "Magnet")
	{
		mInventory->addItem(mTargetItem);
		std::cout << "Plockade upp magnet";
		mRegularItemSound.play();
	}
	if (mTargetItem->getId() == "String")
	{
		mInventory->addItem(mTargetItem);
		std::cout << "Plockade upp fiskespo";
		mRegularItemSound.play();
	}
	if (mTargetItem->getId() == "Astronaut")
	{
		if (mInventory->selectedItem() != NULL && mInventory->selectedItem()->getId() == "FishingRodMagnet")
		{
			//TODO - Add Rubics Cube Drop
			mPlayer->setPosition(600, 305);
			mPlayer->moveToPosition(600, 305);
			if (!mPlayer->isFacingLeft())
			{
				mPlayer->flipPlayer();
			}
			mPlayer->setActiveAnimation("Fishing");
			mPlayer->setScale(sf::Vector2f(0.45f, 0.45f));
			mFishing = true;
			mCursor->setMode(Cursor::DISABLED);
			mMagnetDropSound.play();
			//TODO - Check if fishing animation is done before doing this
			mTargetItem->toggleActive();
			mTargetItem->setSpeed(20.0f);
			mTargetItem->moveToPosition(500, 250);
		}
		else
		{
			mTargetItem->toggleActive();
		}
	}
}

void Level1::interactTargetItem()
{
	//Check if Item has already been interacted with
	if (!mTargetItem->isInteracted())
	{
		mTargetItem->toggleInteractable();
		if (mTargetItem->getId() == "Block")
		{
			mCursor->setMode(Cursor::DISABLED);
			mPushingBlock = true;

			mPlayer->setSpeed(50.0f);
			mTargetItem->setSpeed(50.0f);

			mPlayer->setActiveAnimation("Push");
			mPlayer->moveToPosition(615, 500);

			mTargetItem->moveToPosition(860, 315);
			mTargetItem->toggleInteracted();

			mPushingObjectSound.setLoop(true);
			mPushingObjectSound.play();

			//Find Astronaut in ItemVector and make it active
			for (Level::ItemVector::size_type i = 0; i < getItems().size(); i++)
			{
				if (getItems()[i]->getId() == "Astronaut")
				{
					getItems()[i]->toggleActive();
					getItems()[i]->togglePickupable();
				}
			}

			std::cout << "Knuffade Klossen";
		}
		if (mTargetItem->getId() == "Star")
		{
			mTargetItem->toggleActive();
			mWallStar->toggleActive();
			mCriticalItemSound.play(); //TODO - Add proper Star sound
			addItem(mWallStar);
			mMovedStar = true;
			std::cout << "Satte stjärnan på väggen";
		}
	}
}

void Level1::mouseClickCheckItemCollision(sf::Vector2f point)
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
				if (getItems()[i]->getId() == "Cube")
				{
					//Move Player to the closest point that is still inside the playrect
					mPlayer->moveToPosition(340, 370);
					//Set the Item as "Target Item"
					mTargetItem = getItems()[i];
					//Enable Item interaction
					mItemInteraction = true;
				}
				if (getItems()[i]->getId() == "Magnet")
				{
					mPlayer->moveToPosition(340, 370);
					mTargetItem = getItems()[i];
					mItemInteraction = true;
				}
				if (getItems()[i]->getId() == "Bowl")
				{
					mPlayer->moveToPosition(340, 370);
					mTargetItem = getItems()[i];
					mItemInteraction = true;
				}
				if (getItems()[i]->getId() == "Block")
				{
					if (getActiveScene() == 0)
					{
						mPlayer->moveToPosition(560, 365);
					}
					else
					{
						mPlayer->moveToPosition(490, 500);
					}
					mTargetItem = getItems()[i];
					mItemInteraction = true;
				}
				if (getItems()[i]->getId() == "Astronaut")
				{
					if (getActiveScene() == 0)
					{
						mPlayer->moveToPosition(560, 365);
					}
					else
					{
						mPlayer->moveToPosition(490, 500);
					}
					mTargetItem = getItems()[i];
					mItemInteraction = true;
				}
				if (getItems()[i]->getId() == "String")
				{
					mPlayer->moveToPosition(340, 370);
					mTargetItem = getItems()[i];
					mItemInteraction = true;
				}
				if (getItems()[i]->getId() == "Star")
				{
					mPlayer->moveToPosition(480, 450);
					mTargetItem = getItems()[i];
					mItemInteraction = true;
				}
			}
		}
	}
}

void Level1::mouseClickCheckRectCollision(sf::Vector2f point)
{
	for (Level::rectVector::size_type i = 0; i < getRects().size(); i++)
	{
		if (checkCollision(getRects()[i], point))
		{
			// i == 0 is the fishtankplace, or Thomas Room if in fishtankplace
			if (i == 0)
			{
				if (getActiveScene() == 0)
				{
					if (!mLookedAtAquarium)
					{
						mDialogueSystem->reset();
						mDialogueSystem->hasClicked("aquarium", mPlayer);
						mUI->setState(UI::INGAME);
						mCursor->setMode(Cursor::DIALOGUE);
						mLookedAtAquarium = true;
					}
					else
					{
						//Make Player get into position for Scene change
						mPlayer->moveToPosition(400, 370);
						//Set Collision Rect to Scene change position
						mSceneChangeRect = sf::FloatRect(sf::Vector2f(400, 370), sf::Vector2f(10, 10));
						//Set if Player should toggle on Scene Change
						mPlayerToggle = true;
						//Set starting position of Player in new Scene
						mSceneChangePlayerPos = sf::Vector2f(160, 480);
						//Set which Scene will be the new Scene
						mNewScene = 1;
					}
				}
				else
				{
					//Make Player get into position for Scene change
					mPlayer->moveToPosition(150, 480);
					//Set Collision Rect to Scene change position
					mSceneChangeRect = sf::FloatRect(sf::Vector2f(150, 480), sf::Vector2f(10, 10));
					//Set if Player should toggle on Scene Change
					mPlayerToggle = true;
					//Set starting position of Player in new Scene
					mSceneChangePlayerPos = sf::Vector2f(400, 370);
					//Set which Scene will be the new Scene
					mNewScene = 0;
				}
			}
			// i == 1 is books in the bookcase
			else if (i == 1)
			{
				mDialogueSystem->reset();
				mDialogueSystem->hasClicked("books", mPlayer);
				mUI->setState(UI::INGAME);
				mCursor->setMode(Cursor::DIALOGUE);
			}
			// i == 2 is lamp on table
			else if (i == 2)
			{
				mDialogueSystem->reset();
				mDialogueSystem->hasClicked("lamp", mPlayer);
				mUI->setState(UI::INGAME);
				mCursor->setMode(Cursor::DIALOGUE);
			}
			// i == 3 is radio on table
			else if (i == 3)
			{
				mDialogueSystem->reset();
				mDialogueSystem->hasClicked("radio", mPlayer);
				mUI->setState(UI::INGAME);
				mCursor->setMode(Cursor::DIALOGUE);
			}
			// i == 4 is posters on wall
			else if (i == 4)
			{
				mDialogueSystem->reset();
				mDialogueSystem->hasClicked("poster", mPlayer);
				mUI->setState(UI::INGAME);
				mCursor->setMode(Cursor::DIALOGUE);
			}
			// i == 5 is backpack near bed
			else if (i == 5)
			{
				mDialogueSystem->reset();
				mDialogueSystem->hasClicked("backpack", mPlayer);
				mUI->setState(UI::INGAME);
				mCursor->setMode(Cursor::DIALOGUE);
			}
			// i == 6 is bump in the rug
			else if (i == 6)
			{
				if (mReadyForScrewdevice)
				{
					for (Level::ItemVector::size_type i = 0; i < getItems().size(); i++)
					{
						if (getItems()[i]->getId() == "Screwdevice")
						{
							if (getItems()[i]->getActive())
							{
								mCriticalItemSound.play();
								mInventory->addItem(getItems()[i]);
								getItems()[i]->toggleActive();
								mPickedUpScrewdevice = true;
								//mDialogueSystem->hasClicked("ScrewDevice", mPlayer);
								//mCursor->setMode(Cursor::DIALOGUE);
							}
						}
					}
				}
			}
			// i == 7 is the door
			else if (i == 7)
			{
				/*mDialogueSystem->reset();
				mDialogueSystem->hasClicked("thomasdoor", mPlayer);
				mDialogueMode = true;*/
				if (mMovedStar && mPickedUpScrewdevice)
				{
					// Change Level
					std::cout << "LEVEL COMPLETE GOOD JOB BUT IT'S NOT OVER YET, NEXT TIME ON HITTAREN HILMA STUFF HAPPENS" << std::endl;
					//mReadyToLeave = true;
				}
				else
				{
					std::cout << "IT'S NOT OVER YET" << std::endl;
				}
			}
		}
	}
}

UI* Level1::getUI()
{
	return mUI;
}