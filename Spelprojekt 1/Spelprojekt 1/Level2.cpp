#include "Level2.h"

using namespace std;

Level2::Level2(ResourceHandler &handler) :
	mRects(),
	mPlayRects(),
	mIsActive(false),
	mItemInteraction(false),
	mLevelComplete(false),
	mMouseReleased(false),
	mAutoDialogueTriggered(false),
	mTalkedToArnold(false),
	mSteamMachineWorking(false)
{
}


Level2::~Level2()
{
	mRects.clear();
	mPlayRects.clear();
	mItems.clear();
}


Level2::ItemVector Level2::getItems()
{
	return mItems;
}


void Level2::addItem(Item* item)
{
	mItems.push_back(item);
}


void Level2::removeItem(Item* item)
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


Player* Level2::getPlayer()
{
	return mPlayer;
}


void Level2::playBackgroundMusic()
{
	music.play();
}


void Level2::playAmbience()
{
	mAmbientSound.play();
}


void Level2::drawBackground(sf::RenderWindow &window)
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
	//Help Rectangles
	window.draw(rectangleSteamMachine);
	window.draw(rectangleVise);
	window.draw(rectangleDrawer);
	window.draw(rectangleBicycle);
	window.draw(rectangleComputer);
	window.draw(rectanglePosters);
	window.draw(rectangleToolwall);

	drawItems(mItems, window);
}


void Level2::drawForeground(sf::RenderWindow &window)
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


void Level2::drawItems(ItemVector items, sf::RenderWindow &window)
{
	for (ItemVector::size_type i = 0; i < mItems.size(); i++)
	{
		if (mItems[i]->getActive())
		{
			mItems[i]->draw(window);
		}
	}
}

void Level2::drawUI(sf::RenderWindow &window)
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
		/*if (mActiveScene == 1 && mBlockPushed && mInventory->selectedItem()->getId() == "FishingRodMagnet")
		{
		window.draw(mAstronautGlow);
		}*/
	}
}


void Level2::addRect(sf::FloatRect* rect)
{
	mRects.push_back(rect);
}


void Level2::removeRect(int index)
{
	//TODO - Should set Rect size to 0 and/or move it outside screen bounds
}


const Level::rectVector Level2::getPlayRects()
{
	return mPlayRects;
}


void Level2::toggleActive(ResourceHandler &handler, sf::RenderWindow &window, UI *ui)
{
	if (!mIsActive)
	{
		handler.loadLevel2(window);

		//Default bool values
		mItemInteraction = false;
		mLevelComplete = false;
		mMouseReleased = false;
		mAutoDialogueTriggered = false;
		mTalkedToArnold = false;
		mSteamMachineWorking = false;

		mActiveScene = 0;

		//Room Textures
		//Background texture
		background.setSize(sf::Vector2f(1520, 576));
		background.setTexture(handler.getTexture("Workshop.png"));

		//Playground texture
		/*playground.setSize(sf::Vector2f(1024, 576));
		playground.setTexture(handler.getTexture("thomaspg.png"));*/

		//Foreground texture
		/*foreground.setSize(sf::Vector2f(1024, 576));
		foreground.setTexture(handler.getTexture("thomasfg.png"));*/

		// Zoom Textures
		//Background Zoom texture
		/*backgroundZoom.setSize(sf::Vector2f(1024, 576));
		backgroundZoom.setTexture(handler.getTexture("thomaszoombg.png"));*/

		//Playground Zoom texture
		/*playgroundZoom.setSize(sf::Vector2f(1024, 576));
		playgroundZoom.setTexture(handler.getTexture("thomaszoompg.png"));*/

		//Foreground Zoom texture
		/*foregroundZoom.setSize(sf::Vector2f(1024, 576));
		foregroundZoom.setTexture(handler.getTexture("thomaszoomfg.png"));*/

		//Help rectangles
		rectangleSteamMachine.setPosition(sf::Vector2f(683, 189));
		rectangleSteamMachine.setSize(sf::Vector2f(90, 50));
		rectangleVise.setPosition(sf::Vector2f(963, 203));
		rectangleVise.setSize(sf::Vector2f(60, 40));
		rectangleDrawer.setPosition(sf::Vector2f(1270, 330));
		rectangleDrawer.setSize(sf::Vector2f(100, 100));
		rectangleBicycle.setPosition(sf::Vector2f(150, 219));
		rectangleBicycle.setSize(sf::Vector2f(200, 100));
		rectangleComputer.setPosition(sf::Vector2f(1440, 275));
		rectangleComputer.setSize(sf::Vector2f(100, 100));
		rectanglePosters.setPosition(sf::Vector2f(1400, 95));
		rectanglePosters.setSize(sf::Vector2f(110, 140));
		rectangleToolwall.setPosition(sf::Vector2f(813, 47));
		rectangleToolwall.setSize(sf::Vector2f(200, 130));

		//Sound/music
		/*music.openFromFile(handler.getMusic("Level1Music.ogg"));
		music.setLoop(true);
		music.setVolume(10);
		music.play();*/

		/*mAmbientSound.setBuffer(*handler.getSound("Level1_Ambience.ogg"));
		mAmbientSound.setLoop(true);
		mAmbientSound.setVolume(10);
		mAmbientSound.play();*/

		mCriticalItemSound.setBuffer(*handler.getSound("Critical_Item.ogg"));
		mCriticalItemSound.setVolume(70);

		mRegularItemSound.setBuffer(*handler.getSound("Regular_Item_Pickup.ogg"));
		mMenuMainUISound.setBuffer(*handler.getSound("Menu_MainUI.ogg"));
		mMenuHatSound.setBuffer(*handler.getSound("Menu_Hat.ogg"));
		mMenuInventorySound.setBuffer(*handler.getSound("Menu_Inventory.ogg"));

		//View
		mView.setCenter(512, 288);
		mView.setSize(1024, 576);

		//Player
		mPlayer = new Player(handler, sf::Vector2f(414, 342));

		//Inventory
		mInventory = new Inventory(handler);
		mInventory->setCraftableItems(handler, 1);

		//DialogueSystem
		mDialogueSystem = new DialogueSystem(handler, 1);

		//Mouse Cursor
		mCursor = new Cursor(handler);

		//Menu
		mUI = ui; //TODO - Test mUI** and &ui if not working

		//Clues
		mClues = new Clue(handler, "ClueBackground1.png");
		/*mClues->add(handler, "Clue1First.png", sf::Vector2f(58, 31));
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
		mClues->getClue(6)->setState1();*/

		//Create Items
		mCable = new Item(handler, sf::Vector2f(595, 165), "Cable");
		mAirbag = new Item(handler, sf::Vector2f(74, 321), "Airbag");
		mFilledBalloon = new Item(handler, sf::Vector2f(74, 321), "FilledBalloon"); //Invisible/Not Active, get from Steam Machine
		mJuice = new Item(handler, sf::Vector2f(74, 321), "Juice"); //Invisible/Not Active, get from Arnold
		mGlove = new Item(handler, sf::Vector2f(895, 226), "Glove");
		mKey = new Item(handler, sf::Vector2f(1170, 45), "Key"); //Invisible, get from Birdnest
		mWorkshopStick = new Item(handler, sf::Vector2f(1058, 120), "WorkshopStick");
		mCloth = new Item(handler, sf::Vector2f(805, 225), "Cloth");
		mCan = new Item(handler, sf::Vector2f(1330, 112), "Can"); //Invisible/Not Active, get from Putte
		mPutte = new Item(handler, sf::Vector2f(1330, 112), "Putte");
		mArnold = new Item(handler, sf::Vector2f(480, 165), "Arnold");
		mSteamMachine = new Item(handler, sf::Vector2f(683, 189), "SteamMachine");
		mVise = new Item(handler, sf::Vector2f(963, 203), "Vise");
		mDrawer = new Item(handler, sf::Vector2f(1270, 330), "Drawer");

		//Item Glow
		/*mAstronautGlow.setTexture(*handler.getTexture("AstronautGlow.png"));
		mAstronautGlow.setPosition(477, 287);
		mAstronautGlow.setScale(0.7f, 0.7f);*/

		//Playground rectangles
		mPlayRects.push_back(createRect(295, 334, 940, 224));
		mPlayRects.push_back(createRect(1255, 430, 135, 127));

		//Add Rects here
		////Steam machine
		//mRects.push_back(createRect(683, 189, 90, 50));
		////Vise
		//mRects.push_back(createRect(963, 203, 60, 40));
		////Drawer
		//mRects.push_back(createRect(1270, 330, 100, 100));
		//Bicycle
		mRects.push_back(createRect(150, 219, 200, 100));
		//Computer
		mRects.push_back(createRect(1440, 275, 100, 100));
		//Posters
		mRects.push_back(createRect(1400, 95, 110, 140));
		//Toolwall
		mRects.push_back(createRect(813, 47, 200, 130));
		//Scenechange
		//mRects.push_back(createRect(963, 203, 60, 40));

		//Items - Set as Active, Pickupable, Interactable
		mCable->toggleActive();
		mCable->togglePickupable();

		mAirbag->toggleActive();
		mAirbag->togglePickupable();

		mGlove->toggleActive();
		mGlove->togglePickupable();

		mKey->toggleActive();
		mKey->togglePickupable();

		mWorkshopStick->toggleActive();
		mWorkshopStick->togglePickupable();

		mCloth->toggleActive();
		mCloth->togglePickupable();

		mPutte->toggleActive();

		mArnold->toggleActive(); //TODO - Toggle later instead?

		mSteamMachine->toggleActive();

		mVise->toggleActive();

		mDrawer->toggleActive();
		mDrawer->toggleInteractable();

		//Add to ItemVector
		addItem(mCable);
		addItem(mAirbag);
		addItem(mGlove);
		addItem(mKey);
		addItem(mWorkshopStick);
		addItem(mCloth);
		addItem(mPutte);
		addItem(mArnold);
		addItem(mSteamMachine);
		addItem(mVise);
		addItem(mDrawer);
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
	}
	mIsActive = !mIsActive;
}


bool Level2::isActive()
{
	return mIsActive;
}


sf::View Level2::getView()
{
	return mView;
}


void Level2::moveViewWithPlayer(float playerPos)
{
	mView.setCenter(playerPos, 288);
}


void Level2::clearScene()
{
	mRects.clear();
	mPlayRects.clear();
	mItems.clear();
}


void Level2::internalSwap(int num)
{
	// Workshop
	if (num == 0)
	{
		mActiveScene = 0;
		//Walkable area
		mPlayRects.push_back(createRect(295, 334, 940, 224));
		mPlayRects.push_back(createRect(1255, 430, 135, 127));

		//Rects
		//Bicycle
		mRects.push_back(createRect(150, 219, 200, 100));
		//Computer
		mRects.push_back(createRect(1440, 275, 100, 100));
		//Posters
		mRects.push_back(createRect(1400, 95, 110, 140));
		//Toolwall
		mRects.push_back(createRect(813, 47, 200, 130));
		//Scenechange
		mRects.push_back(createRect(963, 203, 60, 40));

		//Repopulate ItemVector with active items
		if (mCable->getActive())
		{
			addItem(mCable);
		}
		if (mAirbag->getActive())
		{
			addItem(mAirbag);
		}
		if (mGlove->getActive())
		{
			addItem(mGlove);
		}
		if (mKey->getActive())
		{
			addItem(mKey);
		}
		if (mWorkshopStick->getActive())
		{
			addItem(mWorkshopStick);
		}
		if (mCloth->getActive())
		{
			addItem(mCloth);
		}
		if (mPutte->getActive())
		{
			addItem(mPutte);
		}
		if (mArnold->getActive())
		{
			addItem(mArnold);
		}
		if (mSteamMachine->getActive())
		{
			addItem(mSteamMachine);
		}
		if (mVise->getActive())
		{
			addItem(mVise);
		}
		if (mDrawer->getActive())
		{
			addItem(mDrawer);
		}
	}
	// Zoom
	else
	{
		mActiveScene = 1;
		//Walkable area
		mPlayRects.push_back(createRect(295, 334, 940, 224));
		mPlayRects.push_back(createRect(1255, 430, 135, 127));

		//Rects
		//Scenechange
		mRects.push_back(createRect(963, 203, 60, 40));


		//Repopulate ItemVector with active items
		if (mKey->getActive())
		{
			addItem(mKey);
		}
		if (mWorkshopStick->getActive())
		{
			addItem(mWorkshopStick);
		}
		if (mPutte->getActive())
		{
			addItem(mPutte);
		}
	}
}


void Level2::changeScene(int num)
{
	clearScene();
	internalSwap(num);
}


int Level2::getActiveScene()
{
	return mActiveScene;
}


Level2::rectVector Level2::getRects()
{
	return mRects;
}


sf::FloatRect* Level2::createRect(float positionX, float positionY, float sizeX, float sizeY)
{
	sf::FloatRect* floatRect = new sf::FloatRect(positionX, positionY, sizeX, sizeY);
	return floatRect;
}


//Check collision between a single rectangle and a point
int Level2::checkCollision(const sf::FloatRect &boundingBox, sf::Vector2f &point)
{
	if (boundingBox.contains(point))
	{
		return 1;
	}
	return 0;
}
//Check collision between a single rectangle and a point
int Level2::checkCollision(sf::FloatRect* boundingBox, sf::Vector2f &point)
{
	if (boundingBox->contains(point))
	{
		return 1;
	}
	return 0;
}
//Check collision between a vector of rectangles and a point
int Level2::checkCollision(const std::vector<sf::FloatRect*> RectVector, sf::Vector2f &point)
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
int Level2::checkCollision(sf::FloatRect* boundingBox, sf::FloatRect &rect)
{
	if (boundingBox->intersects(rect))
	{
		return 1;
	}
	return 0;
}
//Check collision between a vector of rectangles and a rectangle
int Level2::checkCollision(const std::vector<sf::FloatRect*> RectVector, sf::FloatRect &rect)
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


void Level2::eventListen(sf::RenderWindow &window)
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


void Level2::mouseClick(sf::Event &event)
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
void Level2::mouseHover()
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
			// i == 0 is bicycle
			if (i == 0)
			{
				if (mActiveScene == 1)
				{
					mCursor->setMode(Cursor::SCENECHANGE);
				}
				else
				{
					mCursor->setMode(Cursor::EYE);
				}
			}
			// i == 1 is computer
			else if (i == 1)
			{
				mCursor->setMode(Cursor::EYE);
			}
			// i == 2 is posters
			else if (i == 2)
			{
				mCursor->setMode(Cursor::EYE);
			}
			// i == 3 is toolwall
			else if (i == 3)
			{
				mCursor->setMode(Cursor::EYE);
			}
			// i == 4 is zoom
			else if (i == 4)
			{
				if (mActiveScene == 0)
				{
					mCursor->setMode(Cursor::SCENECHANGE);
				}
				else
				{
					mCursor->setMode(Cursor::EYE);
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

void Level2::mouseReleased(sf::Event & event)
{
	std::cout << "Mouse Released" << std::endl;
	std::cout << "mouse x: " << event.mouseButton.x << std::endl;
	std::cout << "mouse y: " << event.mouseButton.y << std::endl;

	std::cout << "mapped mouse x: " << mWorldPos.x << std::endl;
	std::cout << "mapped mouse y: " << mWorldPos.y << std::endl;

	//Check selected item, collision etc. here
	if (mInventory->selectedItem() != NULL
		&& mInventory->selectedItem()->getId() == "Can"
		&& mArnold->getRectangle().contains(mWorldPos)
		&& mActiveScene == 0)
	{
		mMouseReleased = true;
		mItemInteraction = true;
		mPlayer->moveToPosition(580, 350);
		mTargetItem = mArnold;
	}
	else if (mInventory->selectedItem() != NULL
			&& mInventory->selectedItem()->getId() == "Juice"
			&& mSteamMachine->getRectangle().contains(mWorldPos)
			&& mActiveScene == 0)
	{
		mMouseReleased = true;
		mItemInteraction = true;
		mPlayer->moveToPosition(727, 338);
		mTargetItem = mSteamMachine;
	}
	else if (mInventory->selectedItem() != NULL
			&& mInventory->selectedItem()->getId() == "Balloon"
			&& mSteamMachineWorking
			&& mSteamMachine->getRectangle().contains(mWorldPos)
			&& mActiveScene == 0)
	{
		mMouseReleased = true;
		mItemInteraction = true;
		mPlayer->moveToPosition(727, 338);
		mTargetItem = mSteamMachine;
	}
	else if (mInventory->selectedItem() != NULL
		&& mInventory->selectedItem()->getId() == "FilledBalloon"
		&& mVise->getRectangle().contains(mWorldPos)
		&& mActiveScene == 0)
	{
		mMouseReleased = true;
		mItemInteraction = true;
		mPlayer->moveToPosition(1004, 338);
		mTargetItem = mVise;
	}
	else if (mInventory->selectedItem() != NULL
		&& mInventory->selectedItem()->getId() == "ExtensionArm"
		&& mKey->getRectangle().contains(mWorldPos)
		&& mActiveScene == 1)
	{
		mMouseReleased = true;
		mItemInteraction = true;
		mPlayer->moveToPosition(1004, 338); //TODO - Fix this
		mTargetItem = mKey;
	}
	else if (mInventory->selectedItem() != NULL
		&& mInventory->selectedItem()->getId() == "Key"
		&& mDrawer->getRectangle().contains(mWorldPos)
		&& mActiveScene == 0)
	{
		mMouseReleased = true;
		mItemInteraction = true;
		mPlayer->moveToPosition(1325, 449);
		mTargetItem = mDrawer;
	}
	else
	{
		mInventory->deSelectCheck();
	}
}


void Level2::update(sf::RenderWindow &window, float deltaTime)
{
	//Move View with Player
	if (getActiveScene() == 0)
	{
		//520 is the distance the Player has to be from the left side of the level before the camera starts scrolling, change as necessary
		//1000 is the distance the Player has to be from the right side of the level before the camera starts scrolling, change as necessary
		//In this case the camera scrolls while the Player is between 520 and 1008.
		if (mPlayer->getPosition().x > 520 && mPlayer->getPosition().x < 1008)
		{
			//Make camera follow Player position
			moveViewWithPlayer(mPlayer->getPosition().x);
		}
	}

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

	//Engage walk animation when player is moving
	if (!mPlayer->getIsOnPosition())
	{
		//mPlayer->navigate(mItems, deltaTime);
		mPlayer->setActiveAnimation("Walk");
	}

	//Make sure UI is in correct position at all times
	mUI->setUIPosition(mView.getCenter());
	mInventory->setGridPosition(mView.getCenter());
	mClues->setCluesPosition(mView.getCenter());

	if (!mAutoDialogueTriggered && mPlayer->getPosition().x > 1000)
	{
		cout << "OUT OF NOWHERE, EN PUTTE!" << endl;
		mAutoDialogueTriggered = true;
		/*	mDialogueSystem->reset();
		mDialogueSystem->hasClicked("rubicCube", mPlayer);
		mUI->setState(UI::INGAME);
		mCursor->setMode(Cursor::DIALOGUE);*/
	}
}

bool Level2::isLevelComplete()
{
	return mLevelComplete;
}

void Level2::updateTargetItem(float deltaTime)
{
	if (mTargetItem != NULL)
	{
		mTargetItem->update(deltaTime);
	}
}

void Level2::lookAtTargetItem()
{
	mTargetItem->toggleIsLookedAt();
	if (mTargetItem->getId() == "Arnold")
	{
	/*	mDialogueSystem->reset();
		mDialogueSystem->hasClicked("rubicCube", mPlayer);
		mUI->setState(UI::INGAME);
		mCursor->setMode(Cursor::DIALOGUE);*/
		mTalkedToArnold = true;
	}
	else if (mTargetItem->getId() == "Putte")
	{
		if (mTalkedToArnold)
		{
			/*	mDialogueSystem->reset();
			mDialogueSystem->hasClicked("rubicCube", mPlayer);
			mUI->setState(UI::INGAME);
			mCursor->setMode(Cursor::DIALOGUE);*/
			mInventory->addItem(mCan);
			mArnold->toggleInteractable();
		}
	}
}

void Level2::pickupTargetItem()
{
	if (mTargetItem->getId() == "Cable")
	{
		mInventory->addItem(mTargetItem);
		mUI->setActiveAnimation("InventoryIconGlowOnce");
		std::cout << "Plockade upp kabel";
		mRegularItemSound.play();
		//Make Item inactive when it is picked up
		mTargetItem->toggleActive();
	}
	else if (mTargetItem->getId() == "Airbag")
	{
		mInventory->addItem(mTargetItem);
		mUI->setActiveAnimation("InventoryIconGlowOnce");
		std::cout << "Plockade upp airbag";
		mRegularItemSound.play();
		//Make Item inactive when it is picked up
		mTargetItem->toggleActive();
	}
	else if (mTargetItem->getId() == "Cloth")
	{
		mInventory->addItem(mTargetItem);
		mUI->setActiveAnimation("InventoryIconGlowOnce");
		std::cout << "Plockade upp trasa";
		mRegularItemSound.play();
		//Make Item inactive when it is picked up
		mTargetItem->toggleActive();
	}
	else if (mTargetItem->getId() == "WorkshopStick" && mActiveScene == 1)
	{
		mInventory->addItem(mTargetItem);
		mUI->setActiveAnimation("InventoryIconGlowOnce");
		std::cout << "Plockade upp pinne";
		mRegularItemSound.play();
		//Make Item inactive when it is picked up
		mTargetItem->toggleActive();
	}
	else if (mTargetItem->getId() == "Glove")
	{
		mInventory->addItem(mTargetItem);
		mUI->setActiveAnimation("InventoryIconGlowOnce");
		std::cout << "Plockade upp handske";
		mRegularItemSound.play();
		//Make Item inactive when it is picked up
		mTargetItem->toggleActive();
	}
	else if (mTargetItem->getId() == "Key" && mPlayer->getIsOnPosition() && mMouseReleased)
	{
		mInventory->addItem(mTargetItem);
		mUI->setActiveAnimation("InventoryIconGlowOnce");
		std::cout << "Plockade upp nyckel";
		mRegularItemSound.play();
		//Make Item inactive when it is picked up
		mTargetItem->toggleActive();
		mInventory->deSelectCheck();
	}
}

void Level2::interactTargetItem()
{
	//Check if Item has already been interacted with
	if (!mTargetItem->isInteracted())
	{
		mTargetItem->toggleInteractable();
		if (mTargetItem->getId() == "Arnold")
		{
			if (mMouseReleased)
			{
				/*	mDialogueSystem->reset();
				mDialogueSystem->hasClicked("rubicCube", mPlayer);
				mUI->setState(UI::INGAME);
				mCursor->setMode(Cursor::DIALOGUE);*/
				mInventory->removeItem(mInventory->getSelectedItem());
				mInventory->addItem(mJuice);
				mSteamMachine->toggleInteractable();
			}
		}
		if (mTargetItem->getId() == "SteamMachine")
		{
			if (mMouseReleased && !mSteamMachineWorking)
			{
				/*	mDialogueSystem->reset();
				mDialogueSystem->hasClicked("rubicCube", mPlayer);
				mUI->setState(UI::INGAME);
				mCursor->setMode(Cursor::DIALOGUE);*/
				mInventory->removeItem(mInventory->getSelectedItem());
				mSteamMachineWorking = true;
				mSteamMachine->toggleInteractable();
			}
			else if (mMouseReleased && mSteamMachineWorking)
			{
				mInventory->removeItem(mInventory->getSelectedItem());
				mInventory->addItem(mFilledBalloon);
				mVise->toggleInteractable();
			}
		}
		if (mTargetItem->getId() == "Vise")
		{
			if (mMouseReleased)
			{
				/*	mDialogueSystem->reset();
				mDialogueSystem->hasClicked("rubicCube", mPlayer);
				mUI->setState(UI::INGAME);
				mCursor->setMode(Cursor::DIALOGUE);*/
				mInventory->removeItem(mInventory->getSelectedItem());
				mRects.push_back(createRect(963, 203, 60, 40));
			}
		}
		if (mTargetItem->getId() == "Drawer")
		{
			if (mMouseReleased)
			{
				/*	mDialogueSystem->reset();
				mDialogueSystem->hasClicked("rubicCube", mPlayer);
				mUI->setState(UI::INGAME);
				mCursor->setMode(Cursor::DIALOGUE);*/
				mInventory->removeItem(mInventory->getSelectedItem());
			}
		}
	}
}

void Level2::mouseClickCheckItemCollision(sf::Vector2f point)
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
				if (getItems()[i]->getId() == "Cable")
				{
					mPlayer->moveToPosition(619, 333);
					mTargetItem = getItems()[i];
					mItemInteraction = true;
				}
				else if (getItems()[i]->getId() == "Airbag")
				{
					mPlayer->moveToPosition(260, 523);
					mTargetItem = getItems()[i];
					mItemInteraction = true;
				}
				else if (getItems()[i]->getId() == "Cloth")
				{
					mPlayer->moveToPosition(829, 341);
					mTargetItem = getItems()[i];
					mItemInteraction = true;
				}
				else if (getItems()[i]->getId() == "WorkshopStick")
				{
					if (mActiveScene == 0)
					{
						mPlayer->moveToPosition(1072, 347);
						mTargetItem = getItems()[i];
						mItemInteraction = true;
					}
					else if (mActiveScene == 1)
					{
						// TODO - Fix moveTo etc.
						mPlayer->moveToPosition(1072, 347);
						mTargetItem = getItems()[i];
						mItemInteraction = true;
					}
				}
				else if (getItems()[i]->getId() == "Glove")
				{
					mPlayer->moveToPosition(926, 342);
					mTargetItem = getItems()[i];
					mItemInteraction = true;
				}
				else if (getItems()[i]->getId() == "Key")
				{
					if (mActiveScene == 0)
					{
						mPlayer->moveToPosition(1194, 343);
						mTargetItem = getItems()[i];
						mItemInteraction = true;
					}
					else if (mActiveScene == 1)
					{
						// TODO - Fix moveTo etc.
						mPlayer->moveToPosition(1194, 343);
						mTargetItem = getItems()[i];
						mItemInteraction = true;
					}
				}
				else if (getItems()[i]->getId() == "Putte")
				{
					if (mActiveScene == 0)
					{
						mPlayer->moveToPosition(1225, 343);
						mTargetItem = getItems()[i];
						mItemInteraction = true;
					}
					else if (mActiveScene == 1)
					{
						// TODO - Fix moveTo etc.
						mPlayer->moveToPosition(1225, 343);
						mTargetItem = getItems()[i];
						mItemInteraction = true;
					}
				}
				else if (getItems()[i]->getId() == "Arnold")
				{
					mPlayer->moveToPosition(580, 350);
					mTargetItem = getItems()[i];
					mItemInteraction = true;
				}
				else if (getItems()[i]->getId() == "SteamMachine")
				{
					mPlayer->moveToPosition(727, 338);
					mTargetItem = getItems()[i];
					mItemInteraction = true;
				}
				else if (getItems()[i]->getId() == "Vise")
				{
					mPlayer->moveToPosition(1004, 338);
					mTargetItem = getItems()[i];
					mItemInteraction = true;
				}
				else if (getItems()[i]->getId() == "Drawer")
				{
					mPlayer->moveToPosition(1325, 449);
					mTargetItem = getItems()[i];
					mItemInteraction = true;
				}
			}
		}
	}
}

void Level2::mouseClickCheckRectCollision(sf::Vector2f point)
{
	for (Level::rectVector::size_type i = 0; i < getRects().size(); i++)
	{
		if (checkCollision(getRects()[i], point))
		{
			// i == 0 is Bicycle
			if (i == 0)
			{
				if (mActiveScene == 0)
				{
					cout << "BICYCLE" << endl;
				}
				else
				{
					mPlayer->moveToPosition(1004, 338); // TODO - Fix this
					mSceneChangeRect = sf::FloatRect(sf::Vector2f(1004, 338), sf::Vector2f(10, 10)); // TODO - Fix this
					mPlayerToggle = true;
					mSceneChangePlayerPos = sf::Vector2f(1004, 338); // TODO - Fix this
					mNewScene = 0;
					mSceneChange = true;
				}
			}
			// i == 1 is Computer
			else if (i == 1)
			{
				cout << "COMPUTER" << endl;
			}
			// i == 2 is Posters
			else if (i == 2)
			{
				cout << "POSTERS" << endl;
			}
			// i == 3 is Toolwall
			else if (i == 3)
			{
				cout << "TOOLWALL" << endl;
			}
			// i == 4 is Zoom
			if (i == 4)
			{
				if (getActiveScene() == 0)
				{
					mPlayer->moveToPosition(1004, 338);
					mSceneChangeRect = sf::FloatRect(sf::Vector2f(1004, 338), sf::Vector2f(10, 10));
					mPlayerToggle = true;
					mSceneChangePlayerPos = sf::Vector2f(1004, 338); //TODO - Fix this
					mNewScene = 1;
					mSceneChange = true;
				}
			}
		}
	}
}

UI* Level2::getUI()
{
	return mUI;
}