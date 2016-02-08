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

	//View
	mView.setCenter(512, 288);
	mView.setSize(1024, 576);

	//Create Items
	mScrewdevice = new Item(handler, sf::Vector2f(380, 400), "Screwdevice");
	mMagnet = new Item(handler, sf::Vector2f(325, 270), "Magnet");
	mStar = new Item(handler, sf::Vector2f(475, 435), "Star");
	mAstronaut = new Item(handler, sf::Vector2f(560, 160), "Astronaut");
	mBlock = new Item(handler, sf::Vector2f(570, 160), "Block");
	mString = new Item(handler, sf::Vector2f(250, 370), "String");
	mBowl = new Item(handler, sf::Vector2f(320, 158), "Bowl");
	mCube = new Item(handler, sf::Vector2f(352, 222), "Cube");


	//Player
	mPlayer = new Player(handler, sf::Vector2f(400, 400));

	//Inventory
	mInventory = new Inventory();
	mItemInteraction = false;
	mInventoryMode = false;

	//DialogueSystem


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
		mPlayRects.push_back(createRect(110, 360, 660, 200));
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
		if (mAstronaut->getActive())
		{
		}
		mAstronaut->setPosition(500, 315);
		mAstronaut->setScale(1.0f, 1.0f);
		addItem(mAstronaut);
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

void Level1::update(sf::RenderWindow &window)
{
	////Only do this if the level needs moving camera
	////mLHandler->getLevel(1) is currently LastLevel, change as necessary
	//if (mLHandler->getActiveLevel() == mLHandler->getLevel(1))
	//{
	//	//Scene 1 is the big, second room in LastLevel, change as necessary
	//	if (mLHandler->getActiveLevel()->getActiveScene() == 1)
	//	{
	//		//520 is the distance the Player has to be from the left side of the level before the camera starts scrolling, change as necessary
	//		//1000 is the distance the Player has to be from the right side of the level before the camera starts scrolling, change as necessary
	//		//In this case the camera scrolls while the Player is between 520 and 1000.
	//		if (mLHandler->getPlayer()->getPosition().x > 520 && mLHandler->getPlayer()->getPosition().x < 1000)
	//		{
	//			//Make camera follow Player position
	//			mLHandler->getActiveLevel()->moveViewWithPlayer(mLHandler->getPlayer()->getPosition().x);
	//		}
	//	}
	//}


	//Check if Player is in position to change Scene
	if (mPlayer->getRect().intersects(mSceneChangeRect))
	{
		//Toggle Player if the new Scene needs it
		if (mPlayerToggle)
		{
			//TODO - toggle Player
		}
		//Set Player position to the starting position of the new Scene
		mPlayer->setPosition(mSceneChangePlayerPos.x, mSceneChangePlayerPos.y);
		//Change to the new Scene
		changeScene(mNewScene);
	}


	//Check if Item interaction is enabled, which it only is when an Item is clicked
	if (mItemInteraction)
	{
		//Check if any part of the Player intersects with the Item
		if (mPlayer->getGlobalRect().intersects(mTargetItem->getRectangle()))
		{
			//Check if Item has already been looked at
			if (!mTargetItem->isLookedAt())
			{
				mTargetItem->toggleIsLookedAt();
				if (mTargetItem->getId() == "Cube")
				{
					mDialogueSystem->displayRubicCubeDialogue();
				}
				if (mTargetItem->getId() == "Magnet")
				{
					//mDialogueSystem->displayMagnetDialogue();
					std::cout << "Effin' magnets, how do they work!?";
				}
				if (mTargetItem->getId() == "Bowl")
				{
					//mDialogueSystem->displayBowlDialogue();
					std::cout << "Skål!";
				}
				if (mTargetItem->getId() == "Block")
				{
					//mDialogueSystem->displayBlockDialogue();
					std::cout << "En kloss framför akvariet, undrar om det finns en astronaut bakom?";
				}
				if (mTargetItem->getId() == "Astronaut")
				{
					//mDialogueSystem->displayAstronautDialogue();
					std::cout << "Nämen titta, en astronaut.";
				}
				if (mTargetItem->getId() == "String")
				{
					//mDialogueSystem->displayStringDialogue();
					std::cout << "En tråd på golvet.";
				}
				if (mTargetItem->getId() == "Star")
				{
					//mDialogueSystem->displayStarDialogue();
					std::cout << "Stjärnklart!";
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
					mInventory->addItem(mTargetItem);
					std::cout << "Plockade upp tråd";
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
						//Move Block, TODO - change to smooth movement, set Animation to "Push" and move Player
						mTargetItem->setPosition(630, 315);
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
						std::cout << "Satte stjärnan på väggen";
					}
				}
			}
			//Disable Item interaction when done
			mItemInteraction = false;
		}
	}


	//If Player is moving to the left (getDirection.x < 0) and isn't already facing left, flip Player
	if (mPlayer->getDirection().x < 0 && !mPlayer->isFacingLeft())
	{
		mPlayer->flipPlayer();
	}
	//If Player is moving to the right (getDirection.x > 0) and is facing left, flip Player
	if (mPlayer->getDirection().x > 0 && mPlayer->isFacingLeft())
	{
		mPlayer->flipPlayer();
	}


	//Inventory
	mInventory->update(window);
	if (mInventoryMode)
	{
		mInventory->draw(window);
	}

}

void Level1::mouseClick(sf::Event &event)
{
	std::cout << "MouseClick!" << std::endl;
}

void Level1::eventListen(sf::RenderWindow &window)
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		switch (event.type)
		{
			//window closed
		case sf::Event::Closed:
			window.close();
			break;

			//mouse button pressed
		case sf::Event::MouseButtonPressed:
			// get the current mouse position in the window
			mPixelPos = sf::Mouse::getPosition(window);
			// convert it to world coordinates
			mWorldPos = window.mapPixelToCoords(mPixelPos);
			//if Inventory Mode is enabled, only check for collisions with Items in Inventory
			if (mInventoryMode)
			{
				mInventory->checkCollision(mInventory->getItems(), mWorldPos);
			}
			else
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
				//mLHandler->togglePlayer();
			}
			break;

		default:
			break;
		}
	}
}

Player* Level1::getPlayer()
{
	return mPlayer;
}