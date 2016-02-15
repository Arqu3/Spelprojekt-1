#include "Level1.h"

Level1::Level1(ResourceHandler &handler):
mRects(),
mPlayRects(),
mIsActive(false),
mItemInteraction(false),
mInventoryMode(false),
mLookedAtAquarium(false),
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
	ambientSound.play();
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
		if (mItems[i]->getActive())
		{
			mItems[i]->draw(window);
		}
	}
}

void Level1::drawUI(sf::RenderWindow &window)
{
	window.draw(mHatIcon);
	window.draw(mMenuIcon);


	if (mHatMode)
	{
		window.draw(mHatMenu);
	}
	if (mInventoryMode)
	{
		mInventory->draw(window);
	}
	else
	{
		window.draw(mMouseCursor);
	}
	if (mDialogueMode)
	{
		mDialogueSystem->drawDialogue(window);
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

		//UI Icons
		handler.getTexture("haticon.png")->setSmooth(true);
		handler.getTexture("menuicon.png")->setSmooth(true);
		mHatIcon.setTexture(*handler.getTexture("haticon.png"));
		mMenuIcon.setTexture(*handler.getTexture("menuicon.png"));
		mHatIcon.setPosition(sf::Vector2f(10, 470));
		mMenuIcon.setPosition(sf::Vector2f(90, 510));
		mHatIcon.setScale(sf::Vector2f(0.3f, 0.3f));
		mMenuIcon.setScale(sf::Vector2f(0.3f, 0.3f));
		//UI Menus
		mHatMenu.setTexture(*handler.getTexture("hatmenu.png"));
		mHatMenu.setPosition(sf::Vector2f(0, 285));
		mHatMenu.setScale(sf::Vector2f(0.3f, 0.3f));

		//Mouse Textures
		mNormalMouse = *handler.getTexture("mousecursor.png");
		mOpenHandMouse = *handler.getTexture("openhand.png");
		mClosedHandMouse = *handler.getTexture("closedhand.png");
		mSpeechMouse = *handler.getTexture("speechbubble.png");
		mEyeMouse = *handler.getTexture("eyecursor.png");

		//Mouse Cursor
		mMouseCursor.setTexture(mEyeMouse);
		mMouseCursor.setScale(sf::Vector2f(0.2f, 0.2f));

		//Sound/music
		music.openFromFile("Level1Music.ogg");

		//View
		mView.setCenter(512, 288);
		mView.setSize(1024, 576);

		//Player
		mPlayer = new Player(handler, sf::Vector2f(400, 400));

		//Inventory
		mInventory = new Inventory();

		//DialogueSystem
		mDialogueSystem = new DialogueSystem(handler);

		//Create Items
		mScrewdevice = new Item(handler, sf::Vector2f(380, 400), "Screwdevice");
		mMagnet = new Item(handler, sf::Vector2f(325, 270), "Magnet");
		mStar = new Item(handler, sf::Vector2f(475, 435), "Star");
		mAstronaut = new Item(handler, sf::Vector2f(560, 160), "Astronaut");
		mBlock = new Item(handler, sf::Vector2f(570, 160), "Block");
		mString = new Item(handler, sf::Vector2f(250, 370), "String");
		mBowl = new Item(handler, sf::Vector2f(320, 158), "Bowl");
		mCube = new Item(handler, sf::Vector2f(352, 222), "Cube");



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
		addItem(mBlock);
		addItem(mAstronaut);
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
	}
	// Fishtank Zoom
	else
	{
		mActiveScene = 1;
		//Walkable area
		mPlayRects.push_back(createRect(140, 490, 350, 25));
		//Back to room, left side of screen
		mRects.push_back(createRect(0, 30, 120, 470));

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
			if (mInventoryMode)
			{
				mInventory->checkCollision(mInventory->getItems(), mWorldPos);
			}
			else if (mDialogueMode)
			{
				mDialogueSystem->setState();
			}
			else if (!mDisableClick)
			{
				mouseClick(event);
			}
			break;

		case sf::Event::KeyPressed:
			if (event.key.code == sf::Keyboard::Escape)
			{
				window.close();
			}
			if (event.key.code == sf::Keyboard::I)
			{
				for (Level::ItemVector::size_type i = 0; i < mInventory->getItems().size(); i++)
				{
					std::cout << mInventory->getItemId(i) << " ";
				}
			}
			if (event.key.code == sf::Keyboard::M)
			{
				mInventoryMode = !mInventoryMode;
			}
			if (event.key.code == sf::Keyboard::P)
			{
				mPlayer->togglePlayer();
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
	if (checkCollision(mHatIcon.getGlobalBounds(), point))
	{
		if (!mHatMode)
		{
			mHatMode = true;
		}
		else
		{
			mHatMode = false;
		}
	}

	//Check if Menu Icon is clicked
	if (checkCollision(mMenuIcon.getGlobalBounds(), point))
	{
		if (!mMenuMode)
		{
			mMenuMode = true;
			mDisableClick = true;
		}
		else
		{
			mMenuMode = false;
			mDisableClick = false;
		}
	}

	//Check if playrect collision
	if (checkCollision(getPlayRects(), point))
	{
		mPlayer->setActiveAnimation("Walk");
		mPlayer->moveToPosition(point.x, point.y);
		mItemInteraction = false;
	}

	//Check Item collision
	//Loop through all Items in active level
	for (Level::ItemVector::size_type i = 0; i < getItems().size(); i++)
	{
		//Check if mouse collided with Item
		if (checkCollision(getItems()[i]->getRectangle(), point))
		{
			//Check if Item is Active
			if (getItems()[i]->getActive())
			{
				mPlayer->setActiveAnimation("Walk");
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

	//Check Rect Collisions
	for (Level::rectVector::size_type i = 0; i < getRects().size(); i++)
	{
		if (checkCollision(getRects()[i], point))
		{
			mPlayer->setActiveAnimation("Walk");
			// i == 0 is the fishtankplace, or Thomas Room if in fishtankplace
			if (i == 0)
			{
				if (getActiveScene() == 0)
				{
					if (!mLookedAtAquarium)
					{
						mDialogueSystem->reset();
						mDialogueSystem->hasClicked("aquarium", mPlayer);
						mDialogueMode = true;
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
				mDialogueMode = true;
			}
			// i == 2 is lamp on table
			else if (i == 2)
			{
				mDialogueSystem->reset();
				mDialogueSystem->hasClicked("lamp", mPlayer);
				mDialogueMode = true;
			}
			// i == 3 is radio on table
			else if (i == 3)
			{
				mDialogueSystem->reset();
				mDialogueSystem->hasClicked("radio", mPlayer);
				mDialogueMode = true;
			}
			// i == 4 is posters on wall
			else if (i == 4)
			{
				mDialogueSystem->reset();
				mDialogueSystem->hasClicked("poster", mPlayer);
				mDialogueMode = true;
			}
			// i == 5 is backpack near bed
			else if (i == 5)
			{
				mDialogueSystem->reset();
				mDialogueSystem->hasClicked("backpack", mPlayer);
				mDialogueMode = true;
			}
			// i == 6 is bump in the rug
			else if (i == 6)
			{
				//TODO - Add check for if Astronaut is in Inventory
				mDialogueSystem->reset();
				mDialogueSystem->hasClicked("mat", mPlayer);
				mDialogueMode = true;
			}
			// i == 7 is the door
			else if (i == 7)
			{
				//TODO - Add check for if Screwdevice is in Inventory
				/*mDialogueSystem->reset();
				mDialogueSystem->hasClicked("thomasdoor", mPlayer);
				mDialogueMode = true;*/
				mPlayer->moveToPosition(765, 340);
			}
		}
	}
}

//Change mouse cursor depending on what it is hovering over
void Level1::mouseHover()
{
	/*if (mInventory->getSelectedItem != NULL)
	{
		mMouseCursor.setTexture(mClosedHandMouse);
	}*/
	mMouseCursor.setTexture(mNormalMouse);
	mMouseCursor.setOrigin(sf::Vector2f(0.0f, 0.0f));

	//Check if playrect collision
	if (checkCollision(getPlayRects(), mMouseCursor.getGlobalBounds()))
	{
		mMouseCursor.setTexture(mNormalMouse); // TODO - Add walk cursor maybe?
		mMouseCursor.setOrigin(sf::Vector2f(0.0f, 0.0f));
	}

	//Check Item collision
	//Loop through all Items in active level
	for (Level::ItemVector::size_type i = 0; i < getItems().size(); i++)
	{
		//Check if mouse collided with Item
		if (getItems()[i]->getRectangle().intersects(mMouseCursor.getGlobalBounds()))
		{
			//Check if Item is Active
			if (getItems()[i]->getActive())
			{
				if (!getItems()[i]->isLookedAt())
				{
					mMouseCursor.setTexture(mEyeMouse);
					mMouseCursor.setOrigin(sf::Vector2f(80.0f, 70.0f));
				}
				//Check if Item can be picked up
				else if (getItems()[i]->getPickupable())
				{
					mMouseCursor.setTexture(mOpenHandMouse);
					mMouseCursor.setOrigin(sf::Vector2f(80.0f, 70.0f));
				}
				//Check if Item can be interacted with
				else if (getItems()[i]->getInteractable())
				{
					//Check if Item has already been interacted with
					if (!getItems()[i]->isInteracted())
					{
						mMouseCursor.setTexture(mOpenHandMouse);
						mMouseCursor.setOrigin(sf::Vector2f(80.0f, 70.0f));
					}
				}
			}
		}
	}

	//Check Rect Collisions
	for (Level::rectVector::size_type i = 0; i < getRects().size(); i++)
	{
		if (checkCollision(getRects()[i], mMouseCursor.getGlobalBounds()))
		{
			// i == 0 is the fishtankplace, or Thomas Room if in fishtankplace
			if (i == 0)
			{
				if (getActiveScene() == 0)
				{
					if (!mLookedAtAquarium)
					{
						mMouseCursor.setTexture(mEyeMouse);
						mMouseCursor.setOrigin(sf::Vector2f(80.0f, 70.0f));
					}
					else
					{
						mMouseCursor.setTexture(mNormalMouse); // TODO - Add scenechange cursor maybe?
						mMouseCursor.setOrigin(sf::Vector2f(0.0f, 0.0f));
					}
				}
				else
				{
					mMouseCursor.setTexture(mNormalMouse); // TODO - Add scenechange cursor maybe?
					mMouseCursor.setOrigin(sf::Vector2f(0.0f, 0.0f));
				}
			}
			// i == 6 is bump in the rug
			else if (i == 6)
			{
				//TODO - Add check for if Astronaut is in Inventory, and change mMouseCursor texture
				mMouseCursor.setTexture(mEyeMouse);
				mMouseCursor.setOrigin(sf::Vector2f(80.0f, 70.0f));
			}
			// i == 7 is door
			else if (i == 7)
			{
				//TODO - Add check for if Screwdevice is in Inventory, and change mMouseCursor texture
				mMouseCursor.setTexture(mEyeMouse);
				mMouseCursor.setOrigin(sf::Vector2f(80.0f, 70.0f));
			}
			else
			{
				mMouseCursor.setTexture(mEyeMouse);
				mMouseCursor.setOrigin(sf::Vector2f(80.0f, 70.0f));
			}
		}
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
				mTargetItem->toggleIsLookedAt();
				if (mTargetItem->getId() == "Cube")
				{
					mDialogueSystem->reset();
					mDialogueSystem->hasClicked("rubicCube", mPlayer);
					mDialogueMode = true;
				}
				if (mTargetItem->getId() == "Magnet")
				{
					mDialogueSystem->reset();
					mDialogueSystem->hasClicked("magnet", mPlayer);
					mDialogueMode = true;
				}
				if (mTargetItem->getId() == "Bowl")
				{
					mDialogueSystem->reset();
					mDialogueSystem->hasClicked("bowl", mPlayer);
					mDialogueMode = true;
				}
				if (mTargetItem->getId() == "Block")
				{
					mDialogueSystem->reset();
					mDialogueSystem->hasClicked("block", mPlayer);
					mDialogueMode = true;
				}
				if (mTargetItem->getId() == "Astronaut")
				{
					mDialogueSystem->reset();
					mDialogueSystem->hasClicked("astronaut", mPlayer);
					mDialogueMode = true;
				}
				if (mTargetItem->getId() == "String")
				{
					mDialogueSystem->reset();
					mDialogueSystem->hasClicked("string", mPlayer);
					mDialogueMode = true;
				}
				if (mTargetItem->getId() == "Star")
				{
					mDialogueSystem->reset();
					mDialogueSystem->hasClicked("star", mPlayer);
					mDialogueMode = true;
				}
			}
			//Check if Item can be picked up
			else if (mTargetItem->getPickupable())
			{
				//Make Item inactive when it is picked up
				mTargetItem->toggleActive();
				if (mTargetItem->getId() == "Magnet")
				{
					mInventory->addItem(mTargetItem);
					std::cout << "Plockade upp magnet";
				}
				if (mTargetItem->getId() == "String")
				{
					mTargetItem->setScale(0.2f, 0.4f);
					mInventory->addItem(mTargetItem);
					std::cout << "Plockade upp tr�d";
				}
			}
			//Check if Item can be interacted with
			else if (mTargetItem->getInteractable())
			{
				//Check if Item has already been interacted with
				if (!mTargetItem->isInteracted())
				{
					mTargetItem->toggleInteractable();
					if (mTargetItem->getId() == "Block")
					{
						mDisableClick = true;

						mPlayer->setSpeed(50.0f);
						mTargetItem->setSpeed(50.0f);

						mPlayer->setActiveAnimation("Push");
						mPlayer->moveToPosition(615, 500);

						mTargetItem->moveToPosition(860, 315);
						mTargetItem->toggleInteracted();

						//Find Astronaut in ItemVector and make it active
						for (Level::ItemVector::size_type i = 0; i < getItems().size(); i++)
						{
							if (getItems()[i]->getId() == "Astronaut")
							{
								getItems()[i]->toggleActive();
							}
						}

						std::cout << "Knuffade Klossen";
					}
					if (mTargetItem->getId() == "Star")
					{
						mTargetItem->setPosition(900, 190);
						std::cout << "Satte stj�rnan p� v�ggen";
					}
				}
			}
			//Disable Item interaction when done
			mItemInteraction = false;
		}
	}

	//Inventory
	mInventory->update(window);

	//DialogueSystem
	mDialogueSystem->update(deltaTime);
	if (mDialogueSystem->isDialogueFinished())
	{
		mDialogueMode = false;
	}

	//Only update currently "Targeted" Item to avoid having to loop through and update all Items
	if (mTargetItem != NULL)
	{
		mTargetItem->update(deltaTime);
		//Put everything back to normal after the "Pushing cutscene"
		if (mTargetItem->getIsOnPosition())
		{
			if (mDisableClick)
			{
				mDisableClick = false;
				mPlayer->setActiveAnimation("Idle");
				mPlayer->setSpeed(100.0f);
				mTargetItem->setSpeed(100.0f);
			}
		}
	}

	//Change mouse cursor on hover
	mMouseCursor.setPosition(sf::Vector2f(mWorldPos));
	if (!mDialogueMode && !mInventoryMode && mUpdateTime > 0)
	{
		mouseHover();
		mUpdateTime = 0;
	}
	else
	{
		mUpdateTime++;
	}
}