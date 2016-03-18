#include "Level1.h"

using namespace std;

Level1::Level1(ResourceHandler &handler) :
mRects(),
mPlayRects(),
mIsActive(false),
mItemInteraction(false),
mPickedUpFishingRod(false),
mPickedUpMagnet(false),
mLookedAtAquarium(false),
mPushingBlock(false),
mBlockPushed(false),
mCubePlaced(false),
mReadyForScrewdevice(false),
mPickedUpScrewdevice(false),
mMovedStar(false),
mReadyToLeave(false),
mLevelComplete(false),
mHasCraftedFishingRod(false),
mMouseReleased(false),
mhasJumped(false),
mWillJump1(false),
mWillJump2(false),
mHasUsedFishingRod(false),
mLookedAtBooks(false),
mLookedAtLamp(false),
mLookedAtRadio(false),
mLookedAtPosters(false),
mLookedAtBackpack(false)
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
	//window.draw(rectangle); // Help rectangle
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
	//Spooky scary spider draw
	mSpider->draw(window);

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
	if (mUI->getState() == UI::CLUES)
	{
		mClues->draw(window);
		for (unsigned int i = 0; i < mClues->getClues().size(); i++)
		{
			if (mClues->getClue(i)->isHover(mWorldPos))
			{
				mClues->getClue(i)->drawText(window);
			}
		}
	}
	if (mCursor->getMode() == Cursor::DIALOGUE)
	{
		mDialogueSystem->drawDialogue(window);
	}

	mCursor->draw(window);
	if (mInventory->getSelectedItem() != -1)
	{
		mInventory->drawCursorSprite(window);
		if (mActiveScene == 1 && mBlockPushed && mInventory->selectedItem()->getId() == "FishingRodMagnet")
		{
			window.draw(mAstronautGlow);
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


void Level1::toggleActive(ResourceHandler &handler, sf::RenderWindow &window, UI *ui)
{
	if (!mIsActive)
	{
		handler.loadLevel1(window);

		//Default bool values
		mItemInteraction = false;
		mPickedUpFishingRod = false;
		mPickedUpMagnet = false;
		mLookedAtAquarium = false;
		mPushingBlock = false;
		mBlockPushed = false;
		mCubePlaced = false;
		mReadyForScrewdevice = false;
		mPickedUpScrewdevice = false;
		mMovedStar = false;
		mReadyToLeave = false;
		mLevelComplete = false;
		mHasCraftedFishingRod = false;
		mMouseReleased = false;
		mLookedAtBooks = false;
		mLookedAtLamp = false;
		mLookedAtRadio = false;
		mLookedAtPosters = false;
		mLookedAtBackpack = false;

		mActiveScene = 0;

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
		rectangle.setPosition(sf::Vector2f(440, 150));
		rectangle.setSize(sf::Vector2f(215, 200));

		//Sound/music
		music.openFromFile(handler.getMusic("Level1Music.ogg"));
		music.setLoop(true);
		music.setVolume(10);
		music.play();

		mAmbientSound.setBuffer(*handler.getSound("Level1_Ambience.ogg"));
		mAmbientSound.setLoop(true);
		mAmbientSound.setVolume(10);
		mAmbientSound.play();

		mAquariumSound.setBuffer(*handler.getSound("Aquarium.ogg"));
		mAquariumSound.setLoop(true);
		mAquariumSound.setVolume(0);
		mAquariumSound.play();

		mCriticalItemSound.setBuffer(*handler.getSound("Critical_Item.ogg"));
		mCriticalItemSound.setVolume(70);

		mRadioSound.setBuffer(*handler.getSound("Radio_Noise.ogg"));
		mMagnetCatchSound.setBuffer(*handler.getSound("Magnet_Catch.ogg"));
		mMagnetDropSound.setBuffer(*handler.getSound("Magnet_Drop.ogg"));
		mPushingObjectSound.setBuffer(*handler.getSound("Pushing_Object.ogg"));
		mRegularItemSound.setBuffer(*handler.getSound("Regular_Item_Pickup.ogg"));
		mMenuMainUISound.setBuffer(*handler.getSound("Menu_MainUI.ogg"));
		mMenuHatSound.setBuffer(*handler.getSound("Menu_Hat.ogg"));
		mMenuInventorySound.setBuffer(*handler.getSound("Menu_Inventory.ogg"));

		//View
		mView.setCenter(512, 288);
		mView.setSize(1024, 576);

		//Player
		mPlayer = new Player(handler, sf::Vector2f(705, 500));

		//Inventory
		mInventory = new Inventory(handler);
		mInventory->setCraftableItems(handler, 0);

		//DialogueSystem
		mDialogueSystem = new DialogueSystem(handler, 0);
		mDialogueSystem->setLevel1Start();

		//Mouse Cursor
		mCursor = new Cursor(handler);
		mCursor->setMode(Cursor::DIALOGUE);

		//Menu
		mUI = ui; //TODO - Test mUI** and &ui if not working

		//Clues
		mClues = new Clue(handler, "ClueBackground1.png");
		mClues->add(handler, "Clue1First.png", sf::Vector2f(58, 31));
		mClues->getClue(0)->setStrings("Jag måste hitta en stjärna, en \nastronaut, och en skruvmakapär.", "");
		mClues->getClue(0)->setState1();

		mClues->add(handler, "thomasstar.png", sf::Vector2f(210, 185));
		mClues->getClue(1)->setStrings("Först måste jag hitta stjärnan.", "Jag hittade stjärnan på golvet!");
		mClues->getClue(1)->setState1();

		mClues->add(handler, "thomasastronaut.png", sf::Vector2f(405, 80));
		mClues->getClue(2)->setStrings("Nu måste jag hitta astronauten.", "Astronauten är i akvariumet \nmen jag måste fiska upp den!");

		mClues->add(handler, "Clue1Aqua.png", sf::Vector2f(610, 70));
		mClues->getClue(3)->setStrings("Jag måste hitta något att fiska \nupp astronauten med.", "Med magnetfiskaren kan jag få \ntag i astronauten!");

		mClues->add(handler, "FishingRodMagnet.png", sf::Vector2f(710, 260));
		mClues->getClue(4)->setStrings("Nu måste jag bara fiska upp \nastronauten också.", "Astronauten har blivit hittad!");

		mClues->add(handler, "ScrewDeviceINV.png", sf::Vector2f(800, 400));
		mClues->getClue(5)->setStrings("Var kan nu skruvmakapären \nvara?", "Äntligen! Skruvmakapären är \nhittad!");

		mClues->add(handler, "InfoIcon.png", sf::Vector2f(280, 450));
		mClues->getClue(6)->setStrings("Detta är ledtrådskartan. \nHär kan du läsa vad du har gjort \nhittills och vad du bör göra \nhärnäst. Bara håll musen över \nen ledtråd för att läsa den. \nPilarna låter dig se ledtrådar \nför banor du tidigare klarat.", "");
		mClues->getClue(6)->setState1();

		//Spooky scary spider
		mSpider = new RiddleSpider(handler, sf::Vector2f(750, -500));

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

		//Item Glow
		mAstronautGlow.setTexture(*handler.getTexture("AstronautGlow.png"));
		mAstronautGlow.setPosition(477, 287);
		mAstronautGlow.setScale(0.7f, 0.7f);

		//Playground rectangles
		mPlayRects.push_back(createRect(110, 360, 610, 200));
		mPlayRects.push_back(createRect(670, 330, 160, 80));

		//Fishtank, Zoom
		mRects.push_back(createRect(440, 150, 215, 200));

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
		addItem(mMagnet);
		addItem(mStar);
		addItem(mBlock);
		addItem(mAstronaut);
		addItem(mString);
		addItem(mBowl);
		addItem(mCube);
		addItem(mRoger);

		mUI->setActiveAnimation("CluesIconGlow");
	}
	else
	{
		delete mPlayer;
		delete mInventory;
		delete mDialogueSystem;
		delete mClues;
		mItems.clear();
		mRects.clear();
		mPlayRects.clear();
		mUI->setActiveAnimation("None");
		//TODO - Add Volume Fadeout?
		music.stop();
		mAmbientSound.stop();
		mAquariumSound.stop();
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
		mRects.push_back(createRect(440, 150, 215, 200));

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
			if (mCubePlaced)
			{
				mCube->setScale(-0.3f, 0.3f);
				mCube->setPosition(618, 200);
			}
			else
			{
				mCube->setScale(0.3f, 0.3f);
				mCube->setPosition(352, 222);
			}
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
		if (!mLookedAtAquarium)
		{
			mDialogueSystem->reset();
			mDialogueSystem->hasClicked("aquarium", mPlayer);
			mUI->setState(UI::INGAME);
			mCursor->setMode(Cursor::DIALOGUE);
			mLookedAtAquarium = true;
		}

		mActiveScene = 1;
		//Walkable area
		mPlayRects.push_back(createRect(140, 490, 350, 25));
		//Back to room, left side of screen

		mRects.push_back(createRect(0, 30, 120, 440));

		mAquariumSound.setVolume(20);

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
				mBlock->setPosition(633, 315);
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
		if (mCube->getActive() && mCubePlaced)
		{
			mCube->setScale(-1.0f, 1.0f);
			mCube->setPosition(645.0f, 450.0f);
			addItem(mCube);
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
					mInventory->craftItem(mInventory->getCraftSelect1(), mInventory->getCraftSelect2());
					//Clues
					mHasCraftedFishingRod = true;
					if (mClues->getClue(2)->getState2())
					{
						mClues->getClue(3)->setState2();
						mClues->getClue(4)->setState1();

						mUI->setActiveAnimation("CluesIconGlowOnce");
					}
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
			else if (mCursor->getMode() != Cursor::DISABLED && !mPushingBlock && !mFishing)
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
			else if (mCursor->getMode() != Cursor::DISABLED && !mPushingBlock && !mFishing)
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


void Level1::mouseClick(sf::Event &event)
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
		mSceneChange = false;
	}

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
			// i == 0 is the fishtankplace, or Thomas Room if in fishtankplace
			if (i == 0)
			{
				if (getActiveScene() == 0)
				{
					mCursor->setMode(Cursor::SCENECHANGE);
				}
				else
				{
					mCursor->setMode(Cursor::SCENECHANGE);
				}
			}
			// i == 1 is books in the bookcase
			else if (i == 1 && !mLookedAtBooks)
			{
				mCursor->setMode(Cursor::EYE);
			}
			// i == 2 is lamp on table
			else if (i == 2 && !mLookedAtLamp)
			{
				mCursor->setMode(Cursor::EYE);
			}
			// i == 3 is radio on table
			else if (i == 3 && !mLookedAtRadio)
			{
				mCursor->setMode(Cursor::EYE);
			}
			// i == 4 is posters on wall
			else if (i == 4 && !mLookedAtPosters)
			{
				mCursor->setMode(Cursor::EYE);
			}
			// i == 5 is backpack near bed
			else if (i == 5 && !mLookedAtBackpack)
			{
				mCursor->setMode(Cursor::EYE);
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
				mCursor->setMode(Cursor::NORMAL);
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

void Level1::mouseReleased(sf::Event & event)
{
	std::cout << "Mouse Released" << std::endl;
	std::cout << "mouse x: " << event.mouseButton.x << std::endl;
	std::cout << "mouse y: " << event.mouseButton.y << std::endl;

	std::cout << "mapped mouse x: " << mWorldPos.x << std::endl;
	std::cout << "mapped mouse y: " << mWorldPos.y << std::endl;

	//Fishing interaction
	if (mInventory->selectedItem() != NULL
		&& mBlockPushed
		&& mInventory->selectedItem()->getId() == "FishingRodMagnet"
		&& mAstronaut->getRectangle().contains(mWorldPos)
		&& mActiveScene == 1)
	{
		mHasUsedFishingRod = true;

		mMouseReleased = true;
		mItemInteraction = true;
		mPlayer->moveToPosition(490, 500);
		mTargetItem = mAstronaut;
		mCursor->setMode(Cursor::DISABLED);
		mInventory->deSelectCheck();
		addItem(mCube);
		mCube->setScale(-1.0f, 1.0f);
		mCube->setPosition(645.0f, 450.0f);
		mCubePlaced = true;
	}
	else
	{
		mInventory->deSelectCheck();
	}
}


void Level1::update(sf::RenderWindow &window, float deltaTime)
{
	//Check if Player is in position to change Scene
	if (mPlayer->getRect().intersects(mSceneChangeRect) && mSceneChange && !mItemInteraction)
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
		mSceneChange = false;
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

	//Inventory update
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

	//UI update
	mUI->update(deltaTime);

	if (!mWillJump1 && mHasUsedFishingRod && mPlayer->getIsOnPosition() && mMouseReleased)
	{
		mWillJump1 = true;
		mPlayer->setActiveAnimation("Jump");
		mPlayer->setFrameTime(0.03f);
	}

	//Jump sequence update
	if (mActiveScene == 1 && mWillJump1)
	{
		if (mPlayer->getPosition() == sf::Vector2f(688, 321))
		{
			mhasJumped = true;
			mWillJump1 = false;
			mHasUsedFishingRod = false;
			mItemInteraction = true;
			mPlayer->setPosition(570, 268);
		}

		mPlayer->sequenceMove1();
	}

	if (mActiveScene == 1 && mWillJump2)
	{
		mPlayer->sequenceMove2();

		if (mPlayer->getPosition() == sf::Vector2f(490, 500))
		{
			mWillJump2 = false;
			mPlayer->setActiveAnimation("Idle");
		}
	}

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

	//Mouse Cursor update
	mCursor->update(window);

	//Change mouse cursor on hover
	if (mCursor->getMode() != Cursor::DIALOGUE && mCursor->getMode() != Cursor::DISABLED && mUI->getState() == UI::INGAME)
	{
		mouseHover();
	}

	if (mMovedStar && mPickedUpScrewdevice)
	{
		if (!mReadyToLeave)
		{
			music.setVolume(10);
			mAmbientSound.setVolume(10);
			mAquariumSound.setVolume(0);
			mDialogueSystem->setLevel1End();
			mCursor->setMode(Cursor::DIALOGUE);
			mUI->setState(UI::INGAME);
			mReadyToLeave = true;
		}
		if (mReadyToLeave && !mDialogueSystem->getLevel1End())
		{
			mLevelComplete = true;
		}
	}

	//Spooky scary spider update
	mSpider->update(deltaTime);

	//Engage walk animation when player is moving, if not pushing
	if (!mPlayer->getIsOnPosition() && mPlayer->getActiveAnimation() != "Push" && mPlayer->getActiveAnimation() !=  "Jump")
	{
		//mPlayer->navigate(mItems, deltaTime);
		mPlayer->setActiveAnimation("Walk");
	}

	//Make sure UI is in correct position at all times
	mUI->setUIPosition(mView.getCenter());
	mInventory->setGridPosition(mView.getCenter());
	mClues->setCluesPosition(mView.getCenter());

	//Reset volume Of music and ambient sounds after start dialogue
	if (!mDialogueSystem->getLevel1Start() && !mDialogueSystem->getLevel1End() && music.getVolume() < 70)
	{
		music.setVolume(80);
		mAmbientSound.setVolume(50);
		mAquariumSound.setVolume(5);
	}

	//Make Roger Swim, forever, and further once the Astronaut is gone
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
		//Make splash sound when throwing fishing line in the water
		if (mFishing && mPlayer->getCurrentFrame() == 25)
		{
			mMagnetDropSound.play();
		}
		//Make Hilma pull up Astronaut after casting fishing line
		if (mFishing && mPlayer->getCurrentFrame() == 27)
		{
			mMagnetCatchSound.play();
			mPlayer->setFrameTime(0.05f);
			mPlayer->setActiveAnimation("FishingPull");
		}
		if (mPlayer->getActiveAnimation() == "FishingPull" && mPlayer->getCurrentFrame() == 4)
		{
			mTargetItem->setSpeed(200.0f);
			mTargetItem->moveToPosition(500, 230);
		}
		if (mTargetItem->getIsOnPosition())
		{
			//Put everything back to normal after the "Pushing cutscene"
			if (mPushingBlock)
			{
				mPushingObjectSound.stop();
				mPushingBlock = false;
				mBlockPushed = true;
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
				mUI->setActiveAnimation("InventoryIconGlowOnce");
				mPlayer->setFrameTime(0.03f);
				//mPlayer->setActiveAnimation("Idle");
				mPlayer->setScale(sf::Vector2f(0.25f, 0.25f));
				mPlayer->setActiveAnimation("Jump");

				mWillJump2 = true;
				mPlayer->setPosition(688, 321);

				mCursor->setMode(Cursor::NORMAL);
				mReadyForScrewdevice = true;
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
		/*mDialogueSystem->reset();
		mDialogueSystem->hasClicked("block", mPlayer);
		mUI->setState(UI::INGAME);
		mCursor->setMode(Cursor::DIALOGUE);*/
	}
	if (mTargetItem->getId() == "Astronaut" && !mMouseReleased)
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
	if (mTargetItem->getId() == "Magnet")
	{
		mInventory->addItem(mTargetItem);
		mUI->setActiveAnimation("InventoryIconGlowOnce");
		std::cout << "Plockade upp magnet";
		mRegularItemSound.play();
		mPickedUpMagnet = true;
		if (mPickedUpFishingRod)
		{
			mUI->setActiveAnimation("InventoryIconGlow");
		}
		//Make Item inactive when it is picked up
		mTargetItem->toggleActive();
	}
	if (mTargetItem->getId() == "String")
	{
		mInventory->addItem(mTargetItem);
		mUI->setActiveAnimation("InventoryIconGlowOnce");
		std::cout << "Plockade upp fiskespo";
		mRegularItemSound.play();
		mPickedUpFishingRod = true;
		if (mPickedUpMagnet)
		{
			mUI->setActiveAnimation("InventoryIconGlow");
		}
		//Make Item inactive when it is picked up
		mTargetItem->toggleActive();
	}
	if (mTargetItem->getId() == "Astronaut" && mhasJumped)
	{
		mPlayer->resetSequence();

		//mPlayer->setPosition(570, 268);
		//mPlayer->moveToPosition(570, 268);
		if (!mPlayer->isFacingLeft())
		{
			mPlayer->flipPlayer();
		}
		mPlayer->setActiveAnimation("Fishing");
		mPlayer->setScale(sf::Vector2f(0.54f, 0.54f));
		mFishing = true;

		//Clues
		mClues->getClue(4)->setState2();
		mClues->getClue(5)->setState1();
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
			mPlayer->moveToPosition(625, 500);

			mTargetItem->moveToPosition(870, 315);
			mTargetItem->toggleInteracted();

			mPushingObjectSound.setLoop(true);
			mPushingObjectSound.play();

			mAstronaut->toggleActive();
			mAstronaut->togglePickupable();

			std::cout << "Knuffade Klossen";
		}
		if (mTargetItem->getId() == "Star")
		{
			mTargetItem->toggleActive();
			mWallStar->toggleActive();
			mCriticalItemSound.play();
			addItem(mWallStar);
			mMovedStar = true;
			mClues->getClue(1)->setState2();
			mClues->getClue(2)->setState1();
			mUI->setActiveAnimation("CluesIconGlowOnce");
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
					if (mCubePlaced && mActiveScene == 0)
					{
						mPlayer->moveToPosition(560, 365);
					}
					else if (mCubePlaced && mActiveScene == 1)
					{
						mPlayer->moveToPosition(570, 500);
					}
					else
					{
						mPlayer->moveToPosition(340, 370);
					}
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
				if (getItems()[i]->getId() == "Block" && mActiveScene == 1)
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
					//Clues
					mClues->getClue(2)->setState2();
					mClues->getClue(3)->setState1();
					mUI->setActiveAnimation("CluesIconGlowOnce");

					//Set correct clue depending on crafted item
					if (mHasCraftedFishingRod)
					{
						mClues->getClue(3)->setState2();
						mClues->getClue(4)->setState1();
						mUI->setActiveAnimation("CluesIconGlowOnce");
					}
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
					//Make Player get into position for Scene change
					mPlayer->moveToPosition(400, 370);
					//Set Collision Rect to Scene change position
					mSceneChangeRect = sf::FloatRect(sf::Vector2f(400, 370), sf::Vector2f(10, 10));
					//Set if Player should toggle on Scene Change
					mPlayerToggle = true;
					//Set starting position of Player in new Scene
					mSceneChangePlayerPos = sf::Vector2f(260, 490); //160, 480
					//Set which Scene will be the new Scene
					mNewScene = 1;
					mSceneChange = true;
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

					mSceneChange = true;
				}
			}
			// i == 1 is books in the bookcase
			else if (i == 1 && !mLookedAtBooks)
			{
				mDialogueSystem->reset();
				mDialogueSystem->hasClicked("books", mPlayer);
				mUI->setState(UI::INGAME);
				mCursor->setMode(Cursor::DIALOGUE);
				mLookedAtBooks = true;
			}
			// i == 2 is lamp on table
			else if (i == 2 && !mLookedAtLamp)
			{
				mDialogueSystem->reset();
				mDialogueSystem->hasClicked("lamp", mPlayer);
				mUI->setState(UI::INGAME);
				mCursor->setMode(Cursor::DIALOGUE);
				mLookedAtLamp = true;
			}
			// i == 3 is radio on table
			else if (i == 3 && !mLookedAtRadio)
			{
				mDialogueSystem->reset();
				mDialogueSystem->hasClicked("radio", mPlayer);
				mUI->setState(UI::INGAME);
				mCursor->setMode(Cursor::DIALOGUE);
				mLookedAtRadio = true;
			}
			// i == 4 is posters on wall
			else if (i == 4 && !mLookedAtPosters)
			{
				mDialogueSystem->reset();
				mDialogueSystem->hasClicked("poster", mPlayer);
				mUI->setState(UI::INGAME);
				mCursor->setMode(Cursor::DIALOGUE);
				mLookedAtPosters = true;
			}
			// i == 5 is backpack near bed
			else if (i == 5 && !mLookedAtBackpack)
			{
				mDialogueSystem->reset();
				mDialogueSystem->hasClicked("backpack", mPlayer);
				mUI->setState(UI::INGAME);
				mCursor->setMode(Cursor::DIALOGUE);
				mLookedAtBackpack = true;
			}
			// i == 6 is bump in the rug
			else if (i == 6)
			{
				if (mReadyForScrewdevice)
				{
					if (mScrewdevice->getActive())
					{
						mCriticalItemSound.play();
						mInventory->addItem(mScrewdevice);
						mUI->setActiveAnimation("InventoryIconGlowOnce");
						mScrewdevice->toggleActive();
						mPickedUpScrewdevice = true;
						mClues->getClue(5)->setState2();
					}
				}
			}
			// i == 7 is the door
			else if (i == 7)
			{
				std::cout << "IT'S NOT OVER YET" << std::endl;
			}
		}
	}
}

UI* Level1::getUI()
{
	return mUI;
}