#include "Level3.h"


Level3::Level3(ResourceHandler &handler) :
mRects(),
mPlayRects(),
mIsActive(false),
handler(handler),
mLevelComplete(false)
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
		mView.setCenter(512, 288);
		window.draw(background3);
		window.draw(playground3);
	}
	window.draw(rectangle);
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

		//Playground Texture scene 1
		playground.setSize(sf::Vector2f(1024, 576));
		playground.setTexture(handler.getTexture("ARBETSRUMmellangrund.png")); //Add correct texture!

		//Foreground Texture scene 1
		foreground.setSize(sf::Vector2f(2048, 576));
		foreground.setTexture(handler.getTexture("GardenForeground.png")); 

		//Background Texture scene 2
		background2.setSize(sf::Vector2f(1536, 576));
		background2.setTexture(handler.getTexture("VARDAGSRUMbakgrund.png")); //Add correct texture!

		//Playground Texture scene 2
		playground2.setSize(sf::Vector2f(1536, 576));
		playground2.setTexture(handler.getTexture("VARDAGSRUMmellangrund.png")); //Add correct texture!

		//Foreground Texture scene 2
		foreground2.setSize(sf::Vector2f(1536, 576));
		foreground2.setTexture(handler.getTexture("VARDAGSRUMförgrund.png")); //Add correct texture!


		//Background Texture scene 3
		background3.setSize(sf::Vector2f(1024, 576));
		background3.setTexture(handler.getTexture("KÖKbakgrund.png")); //Add correct texture!

		//Playground Texture scene 3
		playground3.setSize(sf::Vector2f(1024, 576));
		playground3.setTexture(handler.getTexture("KÖKmellangrund.png")); //Add correct texture!

		//Foreground Texture scene 3
		foreground3.setSize(sf::Vector2f(1024, 576));
		foreground3.setTexture(handler.getTexture("KÖKförgrund.png")); //Add correct texture!

		//Add sound
		music.openFromFile("Level1Music.ogg");

		//Add HelpRect
		rectangle.setPosition(sf::Vector2f(1973, 123));
		rectangle.setSize(sf::Vector2f(73, 278));
		rectangle.setTexture(handler.getTexture("LastLevel_ItemTest1.png"));

		//Add items
		mTrimmer = new Item(handler, sf::Vector2f(341, 367), "Trimmer");
		mStick = new Item(handler, sf::Vector2f(381, 220), "Stick");
		mFlowers = new Item(handler, sf::Vector2f(156, 525), "Flowers");
		mLeash = new Item(handler, sf::Vector2f(615, 303), "Leash");
		mDog = new Item(handler, sf::Vector2f(730, 350), "Dog");
		mFlagpole = new Item(handler, sf::Vector2f(1386, 195), "Flagpole");
		mSingleFlower = new Item(handler, sf::Vector2f(1390, 265), "Singleflower");

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

		//Rectangles
		mRects.push_back(createRect(630, 126, 66, 134));
		mRects.push_back(createRect(1806, 96, 62, 74));
		mRects.push_back(createRect(1973, 123, 73, 278));

		
		//Playground
		mPlayRects.push_back(createRect(0, 0, 2048, 576));

		//Item Active
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

		//Add to Itemvector
		addItem(mTrimmer);
		addItem(mStick);
		addItem(mFlowers);
		addItem(mLeash);
		addItem(mDog);
		addItem(mFlagpole);
		addItem(mSingleFlower);
		

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

		//Rectangles

	}

	else if (num == 1)
	{
		
		//Scene 2
		mActiveScene = 1;

		//Walkable Area
		
		//Rectangles

	}
	else if (num == 2)
	{
		//Scene 3
		mActiveScene = 2;

		//Walkable Area
		
		//Rectangles
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

				mInventory->setCraftPos(mInventory->getSelectedItem());

				if (mInventory->craftCheck())
				{
					mInventory->craftItem(mInventory->getCraftSelect1(), mInventory->getCraftSelect2());
				}

				mInventory->checkCollision(mInventory->getItems(), mWorldPos, *mUI);

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

		case sf::Event::KeyPressed:
			if (event.key.code == sf::Keyboard::Escape)
			{
				window.close();
			}
			if (event.key.code == sf::Keyboard::I)
			{
				if (mUI->getState() == UI::INVENTORY)
				{
					mUI->setState(UI::INGAME);
					mCursor->setMode(Cursor::NORMAL);
				}
				else
				{
					mUI->setState(UI::INVENTORY);
					mCursor->setMode(Cursor::INVENTORY);
				}
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


void Level3::mouseClick(sf::Event &event)
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
	}

	//Check if Menu Icon is clicked
	if (checkCollision(mUI->getMenuIconRect(), point))
	{
		mCursor->setMode(Cursor::MENU);
		mUI->setState(UI::MAINUI);
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

			}
		}
	}

	//Check Rect Collisions

	for (Level::rectVector::size_type i = 0; i < getRects().size(); i++)
	{
		if (checkCollision(getRects()[i], point))
		{
			mPlayer->setActiveAnimation("Walk");

			// i == 0 is Planet 1 if ActiveScene is 0, or Door if ActiveScene is 1, or Refrigerator if ActiveScene is 2.
			if (i == 0)
			{
				if (getActiveScene() == 0)
				{
					std::cout << "Tantbak!";
					
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
				else
				{
					std::cout << "Refrigerator!";
					mPlayer->moveToPosition(870, 349);
				}
			}

			if (i == 1)
			{
				if (getActiveScene() == 0)
				{
					std::cout << "Bikupa! Bzzz";
				}
			}

			if (i == 2)
			{
				if (getActiveScene() == 0)
				{
					std::cout << "Dörr!";
				}
			}
		}
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
		if (mPlayer->getGlobalRect().intersects(mTargetItem->getRectangle()))
		{
			//Check if Item has already been looked at
			if (!mTargetItem->isLookedAt())
			{
				mTargetItem->toggleIsLookedAt(); //Fixa dialoger i funktion
				mItemInteraction = false;
			}
			//Check if Item can be picked up
			else if (mTargetItem->getPickupable())
			{
				//Make Item inactive when it is picked up
				mTargetItem->toggleActive();

				if (mTargetItem->getId() == "Earth")
				{
					if (mInventory->selectedItem() != NULL && mInventory->selectedItem()->getId() == "Screwdevice")
					{
						mInventory->addItem(mTargetItem);
						std::cout << "Plockade upp Jordglob";

					}
					else
					{
						mTargetItem->toggleActive();
					}

				}

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
					if (mInventory->selectedItem() != NULL && mInventory->selectedItem()->getId() == "Trimmer")
					{
						mInventory->addItem(mTargetItem);
						mTargetItem->changeTexture(handler, "StickIcon.png");
						std::cout << "Plockade upp Pinne!";

					}
					else
					{
						mTargetItem->toggleActive();
						mTargetItem->toggleInteractable();
					}

				}

			}


			//Check if Item can be interacted with
			else if (mTargetItem->getInteractable())
			{
				//Check if Item has already been interacted with
				if (!mTargetItem->isInteracted())
				{
					mTargetItem->toggleInteractable();

					//Grammophone
					if (mTargetItem->getId() == "Gramophone")
					{


						if (mInventory->selectedItem() != NULL && mInventory->selectedItem()->getId() == "Needle")
						{
							mInventory->removeItem(mInventory->getSelectedItem());

							for (Level::ItemVector::size_type i = 0; i < getItems().size(); i++)
							{
								if (getItems()[i]->getId() == "Fish")
								{
									getItems()[i]->togglePickupable();
									getItems()[i]->setSpeed(300.0f);
									getItems()[i]->moveToPosition(861, 349);
									mTargetItem = getItems()[i];
									mCursor->setMode(Cursor::DISABLED);
									//mFishFalling = true;
								}
							}
						}
						else
						{
							mTargetItem->toggleInteractable();
						}

						std::cout << "Spelar ljud, fisk ramlar ner";
					}

					if (mTargetItem->getId() == "Leash")
					{


						if (mInventory->selectedItem() != NULL && mInventory->selectedItem()->getId() == "Trimmer")
						{
							mTargetItem->changeTexture(handler, "LastLevel_ItemTest2.png"); //Add correct texture!
							mUnleashed = true;
							std::cout << "Klipper kopplet!";
						}
						else
						{
							mTargetItem->toggleInteractable();
						}

						
					}

					if (mTargetItem->getId() == "Dog")
					{
						if (mInventory->selectedItem() != NULL && mInventory->selectedItem()->getId() == "Stick" && mUnleashed == true)
						{
							
							mTargetItem->moveToPosition(2000, 416);
							std::cout << "Kastade pinnen!";
							mTargetItem->setActiveAnimation("Dog");
						}
						else
						{
							mTargetItem->toggleInteractable();
						}


					}


					if (mTargetItem->getId() == "Flagpole")
					{
						if (mInventory->selectedItem() != NULL && mInventory->selectedItem()->getId() == "Flowers")
						{
							mInventory->removeItem(mInventory->getSelectedItem());


							for (Level::ItemVector::size_type i = 0; i < getItems().size(); i++)
							{
								if (getItems()[i]->getId() == "Singleflower")
								{
									getItems()[i]->toggleActive();
								}
							}

						}

						else
						{
					
							mTargetItem->toggleInteractable();
						}

					}

					if (mTargetItem->getId() == "Singleflower")
					{
						mTargetItem->moveToPosition(1390, 121);
					}
				}
			}
			//Disable Item interaction when done
			mItemInteraction = false;
		}
	}

	//Animation updates
	mDog->update(deltaTime);

	//Inventory
	mInventory->update(window);

	//Only update currently "Targeted" Item to avoid having to loop through and update all Items
	if (mTargetItem != NULL)
	{
		mTargetItem->update(deltaTime);
		//Put everything back to normal after the "Pushing cutscene"
		if (mTargetItem->getIsOnPosition())
		{
			/*if (mFishFalling)
			{
				mFishFalling = false;
				mCursor->setMode(Cursor::NORMAL);
				mTargetItem->setSpeed(100.0f);
			}

			if (mCatWalking)
			{
				mCatWalking = false;
				mCursor->setMode(Cursor::NORMAL);
				mTargetItem->setSpeed(100.0f);
			}*/
		}
	}

	mCursor->setPosition(sf::Vector2f(mWorldPos));
	mCursor->update(window);

	if (mCursor->getMode() != Cursor::DIALOGUE && mCursor->getMode() != Cursor::INVENTORY && mCursor->getMode() != Cursor::DISABLED && mCursor->getMode() != Cursor::MENU)
	{
		mouseHover();
	}
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
			// i == 10 is stairs in scene 1
			if (i == 10)
			{
				if (mActiveScene == 0)
				{
					mCursor->setMode(Cursor::NORMAL);
				}
				else
				{
					mCursor->setMode(Cursor::EYE);
				}
			}

			// i == 5 is stairs in scene 2
			else if (i == 5)
			{
				if (mActiveScene == 1)
				{
					mCursor->setMode(Cursor::NORMAL);
				}
				else
				{
					mCursor->setMode(Cursor::EYE);
				}
			}

			// i == 0 is door in scene 2
			else if (i == 0)
			{
				if (mActiveScene == 1)
				{
					mCursor->setMode(Cursor::NORMAL);
				}
			}

			//i == 2 is door in scene 3
			else if (i == 2)
			{
				if (mActiveScene == 2)
				{
					mCursor->setMode(Cursor::NORMAL);
				}
				else
				{
					mCursor->setMode(Cursor::NORMAL);
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

bool Level3::isLevelComplete()
{
	return mLevelComplete;
}

UI* Level3::getUI()
{
	return mUI;
	//TODO - add ui stuff here
}